#define F_CPU 8000000UL
#include "headerfiles.h"
void ringAlarm();
void stopAlarm();
void onHazardLight();
void playRadio();
void PWM_init();
void offHazardLight();
void getAllValuesGps();
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
	float Xa,Ya,Za;
	while (1){
		//flame detection
		if(pinRead(PINC,flame)==0x10){
			ringAlarm();onHazardLight();
			_delay_ms(1000);
			stopAlarm();offHazardLight();
			LCD_String("Flame Detected !");
			getAllValuesGps();
			//LCD_String(Altitude_Buffer);
			//LCD_String(degrees_buffer);
			sendMessage("Flame Detected",longtitude,latitude);
		}//if end
		else{
			//set wheel speed vehicle
			int val=ADC_Read(0);
			float speed=(val/1024.0)*255.0;
			OCR0=(int)speed;
			//get pressure
			int value = ADC_Read(1);
			if (value > 107){// if value gt 107 vehicle is moving
				//get gyroscope values;
				Read_RawValue();
				Xa = (Acc_x/16384.0)*9.8066;
				Ya = (Acc_y/16384.0)*9.8066;
				Za = (Acc_z/16384.0)*9.8066;
				if(pinRead(PINC,alcohol)==0x20){//alcohol detection
					LCD_Clear();
					LCD_String("Alcohol Detected"); 
					getAllValuesGps();
					//LCD_String(Altitude_Buffer);
					//LCD_String(degrees_buffer);
					sendMessage("Alcohol Detected",longtitude,latitude);
				}//if end
				else if(1 && isDriverSleepingGyro(Xa,Ya,Za)){//alcohol not detected  //1 ==> IR Detection                     
						ringAlarm();onHazardLight();
						for(int i=1;i<=5;i++){
							if(pinRead(PINC,3)==0x08){//if button not pressed
								stopAlarm();offHazardLight();
								goto start;
							}//button if end
							_delay_ms(1000);
						}//for loop end
						LCD_String("Sleeping");
						getAllValuesGps();
						//LCD_String(Altitude_Buffer);
						//LCD_String(degrees_buffer);
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
						}//for loop end
						while(1){}
				}//else if end
			}//main else end
			else{
				
			}
		}
	}//while end
}//main end

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
	

