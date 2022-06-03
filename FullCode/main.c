#define F_CPU 8000000UL
#include "headerfiles.h"
int main(void){
	start:
	DDRD=0xE4;
	LCD_Init();
	ADC_Init();
	I2C_Init();
	PWM_init();
	MPU6050_Init();
	LCD_Clear();
	LCD_String("Welcome");
	_delay_ms(200);
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
						playRadio();
						//reduce speed of the vehicle
						OCR0=0;
						//driver should reset the system in order to drive again
						while(1){}//let motor to slowdown fully
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

