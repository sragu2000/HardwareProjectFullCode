#define F_CPU 8000000UL
#include "headerfiles.h"
void ringAlarm();
void stopAlarm();
void onHazardLight();
void playRadio();
void PWM_init();
void offHazardLight();
int main(void){
	start:
	GGA_Index=0;
	setOutput(PORTC,led);
	setOutput(PORTD,buzzer);
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
			LCD_String(Altitude_Buffer);
			LCD_String(degrees_buffer);
			sendMessage("Flame Detected");
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
					LCD_String(Altitude_Buffer);
					LCD_String(degrees_buffer);
					sendMessage("Alcohol Detected");
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
						LCD_String(Altitude_Buffer);
						LCD_String(degrees_buffer);
						sendMessage("Driver is Sleeping");
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
	portHigh(PORTC,led);
}
void offHazardLight(){
	portLow(PORTC,led);
}
void playRadio(){
	//function to play radio
}
void PWM_init(){
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);  /*set OC0 pin as output*/
}
