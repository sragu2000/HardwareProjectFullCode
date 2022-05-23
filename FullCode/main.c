#define F_CPU 8000000UL
#include "headerfiles.h"
char longtitude[15];
char latitude[15];
int main(void){
	start:
	GGA_Index=0;
	setOutput(DDRD,led);
	setOutput(DDRD,buzzer);
	setOutput(DDRD,musicSystem);
	LCD_Init();
	_delay_ms(3000);/* wait for GPS receiver to initialize */
	USART_initialize(9600); /* GSM */
	USART_Init(9600);/* GPS */
	ADC_Init();
	sei();
	I2C_Init();
	PWM_init();
	MPU6050_Init();
	LCD_Clear();
	float Xa,Ya,Za; // for gyroscope
	while (1){
		//flame detection
		if(pinRead(PINC,flame)==0x10){
			ringAlarm();
			onHazardLight();
			_delay_ms(1000);
			stopAlarm();
			offHazardLight();
			LCD_String("Flame Detected !");
			getAllValuesGps();
			sendMessage("Flame Detected",longtitude,latitude);
		}
		else{
			//set wheel speed vehicle
			int val=ADC_Read(0);
			float speed=(val/1024.0)*255.0;
			OCR0=(int)speed;
			//get pressure
			int value = ADC_Read(1);
			if (value > 107){// if value gt 107 vehicle is moving
				if(pinRead(PINC,alcohol)==0x20){
					LCD_Clear();
					LCD_String("Alcohol Detected"); 
					ringAlarm();
					_delay_ms(1000);
					stopAlarm();
					getAllValuesGps();
					sendMessage("Alcohol Detected",longtitude,latitude);
				}
				else{
					Read_RawValue();
					Xa = (Acc_x/16384.0)*9.8066;
					Ya = (Acc_y/16384.0)*9.8066;
					Za = (Acc_z/16384.0)*9.8066;
					if(isDriverSleepingIR() && isDriverSleepingGyro(Xa,Ya,Za)){
						ringAlarm();
						onHazardLight();
						for(int i=1;i<=20;i++){
							if(pinRead(PINC,3)==0x08){
								stopAlarm();
								offHazardLight();
								goto start;
							}
							_delay_ms(250);
						}
						LCD_String("Sleeping");
						getAllValuesGps();
						sendMessage("Driver is Sleeping",longtitude,latitude);
						playRadio();
						//reduce speed of the vehicle
						for(int i=(int)speed;i>=20;i--){
							char c[5];
							itoa(i,c,10);
							LCD_String(c);
							OCR0=i;
							_delay_ms(100);
							LCD_Clear();
						}
						while(1){} //infinite loop with purpose
					}
				}
			}
		}
	}
}

void ringAlarm(){
	portHigh(PORTD,buzzer);//buzzer
}
void stopAlarm(){
	portLow(PORTD,buzzer);
}
void onHazardLight(){
	portHigh(PORTD,led);
}
void offHazardLight(){
	portLow(PORTD,led);
}
void playRadio(){
	portHigh(PORTD,musicSystem);
}
void getAllValuesGps(){
		get_gpstime();                         // Extract Time in UTC- In this function the get the GPS time string type and convert as an integer and print that time
		get_latitude(GGA_Pointers[0]);         // Extract Latitude- convert raw latitude value into degree format and pass that value as string
		//degrees_buffer latitude
		strcpy(latitude,degrees_buffer);
		get_longitude(GGA_Pointers[2]);        /* Extract Longitude */
		//degrees_buffer longtitude
		strcpy(longtitude,degrees_buffer);
		//get_altitude(GGA_Pointers[7]);         /* Extract Altitude in meters*/ 
}

int isDriverSleepingIR(){
	int timeInterval=40;
	int flag=0;
	for(int i=1;i<=timeInterval;i++){
		if(pinRead(PINC,irsensor)==0x40){
			flag++;
		}else{
			flag--;
		}
		_delay_ms(50);
	}
	if(flag==timeInterval){
		return 1;
	}else{
		return 0; 
	}
}

