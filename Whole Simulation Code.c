#define F_CPU 8000000UL
#define SREG   _SFR_IO8(0x3f)
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <math.h>	

#define portHigh(register,pinNumber) register =  register | (1<<pinNumber)
#define portLow(register,pinNumber) register = register & (~(1<<pinNumber))
#define pinRead(register,pinNumber) (register & (1<<pinNumber))
#define setOutput(register,pinNumber) register = register | (1<<pinNumber)
#define enablePullup(register,pinNumber) register = register | (1<<pinNumber)

#define LCD_Dir DDRB					/* Define LCD data port direction */
#define LCD_Port PORTB					/* Define LCD data port */
#define RS PB0							/* Define Register Select (data reg./command reg.) signal pin */
#define EN PB1 							/* Define Enable signal pin */
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_Init (void)	;
void LCD_String (char *str)	;
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();

void ADC_Init();
int ADC_Read(char channel);

#define XG_OFFS_TC 0x00
#define YG_OFFS_TC 0x01
#define ZG_OFFS_TC 0x02
#define X_FINE_GAIN 0x03
#define Y_FINE_GAIN 0x04
#define Z_FINE_GAIN 0x05
#define XA_OFFS_H 0x06 
#define XA_OFFS_L_TC 0x07
#define YA_OFFS_H 0x08 
#define YA_OFFS_L_TC 0x09
#define ZA_OFFS_H 0x0A 
#define ZA_OFFS_L_TC 0x0B
#define XG_OFFS_USRH 0x13
#define XG_OFFS_USRL 0x14
#define YG_OFFS_USRH 0x15
#define YG_OFFS_USRL 0x16
#define ZG_OFFS_USRH 0x17
#define ZG_OFFS_USRL 0x18
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define FF_THR 0x1D
#define FF_DUR 0x1E
#define MOT_THR 0x1F
#define MOT_DUR 0x20
#define ZRMOT_THR 0x21
#define ZRMOT_DUR 0x22
#define FIFO_EN 0x23
#define I2C_MST_CTRL 0x24
#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV1_ADDR 0x28
#define I2C_SLV1_REG 0x29
#define I2C_SLV1_CTRL 0x2A
#define I2C_SLV2_ADDR 0x2B
#define I2C_SLV2_REG 0x2C
#define I2C_SLV2_CTRL 0x2D
#define I2C_SLV3_ADDR 0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_CTRL 0x30
#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_DO 0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI 0x35
#define I2C_MST_STATUS 0x36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define DMP_INT_STATUS 0x39
#define INT_STATUS 0x3A
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define MOT_DETECT_STATUS 0x61
#define I2C_SLV0_DO 0x63
#define I2C_SLV1_DO 0x64
#define I2C_SLV2_DO 0x65
#define I2C_SLV3_DO 0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET 0x68
#define MOT_DETECT_CTRL 0x69
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define BANK_SEL 0x6D
#define MEM_START_ADDR 0x6E
#define MEM_R_W 0x6F
#define DMP_CFG_1 0x70
#define DMP_CFG_2 0x71
#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74
#define WHO_AM_I 0x75
							
#define SCL_CLK 100000L							
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) 
void I2C_Init();								
uint8_t  I2C_Start(char);						
uint8_t  I2C_Repeated_Start(char);				
void I2C_Stop();					
void I2C_Start_Wait(char);			
uint8_t  I2C_Write(char);		
char I2C_Read_Ack();				
char I2C_Read_Nack();


float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;
void MPU6050_Init()	;
void MPU_Start_Loc();
void Read_RawValue();
int isDriverSleepingGyro(float Xa,float Ya,float Za);

#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	/* Define prescale value */
void USART_Init(unsigned long BAUDRATE);
char USART_RxChar();
void USART_TxChar(char data);
void USART_SendString(char *str);

void convert_to_degrees_lat(char *);
void convert_to_degrees_long(char *);
#define Buffer_Size 150
#define degrees_buffer_size 20
char Latitude_Buffer[15],Longitude_Buffer[15],Altitude_Buffer[8];//define the string size
char lat_degrees_buffer[degrees_buffer_size];                      /* save latitude or longitude in degree - degrees_buffer[20]*/
char long_degrees_buffer[degrees_buffer_size];                      /* save latitude or longitude in degree - degrees_buffer[20]*/
char GGA_Buffer[Buffer_Size];                                  /* save GGA string - GGA_Buffer[150] */
uint8_t GGA_Pointers[20];                                      /* to store instances of ',' */
char GGA_CODE[3];

volatile uint16_t GGA_Index, CommaCounter; // unsigned 16-bit integer - integers between 0 and 65,535

bool	IsItGGAString	= false,
flag1			= false,
flag2			= false;
void get_latitude(uint16_t lat_pointer);
void get_longitude(uint16_t long_pointer);
void get_altitude(uint16_t alt_pointer);
void convert_to_degrees_lat(char *raw);
void convert_to_degrees_long(char *raw);
ISR (USART_RXC_vect);


void sendMessage(char* msg,char* lat,char* lngtd,char* altitude);

//pin definitions
#define flame 4
#define led 6
#define buzzer 7
#define alcohol 5
#define musicSystem 5
#define irsensor 6

//function prototypes
void ringAlarm();
void stopAlarm();
void onHazardLight();
void playRadio();
void PWM_init();
void offHazardLight();
int isDriverSleepingIR();
void sendLocation();

int main(void){
	DDRD=0xE8;
	PORTD=0x04;
	LCD_Init();LCD_String("Initializing..");_delay_ms(50);LCD_Clear();
	I2C_Init();
	PWM_init();
	GGA_Index=0;
	USART_Init(9600);
	sei();
	LCD_String("Welcome");
	_delay_ms(100); //actual delay is 3000ms
	LCD_Clear();
	while (1){

		//flame detection
		if(pinRead(PINC,flame)==0x10){
			LCD_Clear();
			LCD_String("Flame Detected !");
			ringAlarm();
			onHazardLight();
			_delay_ms(500);
			stopAlarm();
			offHazardLight();
			LCD_Clear();
			sendLocation("Flame is Detected");
		}
		else{
			ADC_Init();
			int pressure = ADC_Read(1);
			if (pressure > 109){// if value gt 109 vehicle is moving in proteus 21
				int val=ADC_Read(0);//acce
				float speed=(val/1024.0)*255.0;//adc->pwm
				OCR0=(int)speed;//set speed
				LCD_Clear();
				LCD_String("Driving mode");
				if(pinRead(PINC,alcohol)==0x20){
					LCD_Clear();
					LCD_String("Alcohol Detected");
					ringAlarm();
					_delay_ms(100);
					stopAlarm();
					LCD_Clear();
					sendLocation("Alcohol Detected");
				}else{
					if(isDriverSleepingIR()&& (pinRead(PINC,0)==0x01)){
						LCD_Clear();
						LCD_String("Sleeping");
						ringAlarm();
						onHazardLight();
						LCD_Command(0xc0);
						LCD_String("Waiting..");
						GICR = 1<<INT0;		/* Enable INT0*/
						MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
						sei();			/* Enable Global Interrupt */
						_delay_ms(500); //actual delay is 5000ms
						LCD_Clear();
						LCD_String("Waiting");
						LCD_Command(0xc0);
						LCD_String("Complete");
						offHazardLight();
						stopAlarm();
						OCR0=0;
						LCD_Clear();
						LCD_String("Speed is");
						LCD_Command(0xc0);
						LCD_String("Reducing..");
						sendLocation("Driver is Sleeping");
						playRadio();
						while(1){}//let motor to slowdown fully
					}
				}
			}else{
				LCD_String("Vehicle is");
				LCD_Command(0xc0);
				LCD_String("not moving");
				_delay_ms(50);
				LCD_Clear();
			}
		}//else 1 end
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
int isDriverSleepingIR(){
	LCD_Clear();
	LCD_String("Checking Eyes");
	int timeInterval=5;
	int flag=0;
	for(int i=1;i<=timeInterval;i++){
		if(pinRead(PINC,irsensor)==0x40){
			flag++;
		}else{
			flag--;
		}
		_delay_ms(50);
	}
	LCD_Command(0xc0);
	LCD_String("  -Finished");
	if(flag==timeInterval){
		return 1;
	}else{
		return 0;
	}
}

void sendLocation(char* message){
	get_latitude(GGA_Pointers[0]);char* lat=lat_degrees_buffer;
	get_longitude(GGA_Pointers[2]);char* lngtd=long_degrees_buffer;
	get_altitude(GGA_Pointers[7]);char* altitude=Altitude_Buffer;
	PORTD=0x08;// change signal using mux
	sendMessage(message,lat,lngtd,altitude);
	PORTD=0x00;// turn back to normal
}

ISR(INT0_vect)
{
	LCD_Clear();
	portLow(PORTD,6);
	portLow(PORTD,7);
	_delay_ms(50);
	main();
}
void ADC_Init()
{
	DDRA=0x00;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}

void sendMessage(char* msg,char* lat,char* lngtd,char* altitude){
	unsigned char cmd_1[4]="AT";
	unsigned char cmd_2[10]="AT+CMGF=1";
	unsigned char cmd_3[10]="AT+CMGS=";
	char* cmd_4 = msg;
	strcat(cmd_4,"\r   Location\r   Latitude : ");
	strcat(cmd_4,lat);
	strcat(cmd_4,"\r   Longitude : ");
	strcat(cmd_4,lngtd);
	strcat(cmd_4,"\r   Altitude : ");
	strcat(cmd_4,altitude);
	unsigned char num[11] = "0771234567";
	LCD_Clear();
	LCD_String_xy(1,0,"Message");
	LCD_Command(0xc0);
	LCD_String_xy(2,3,"Forwarding");
	_delay_ms(500);
	for (int i=0;cmd_1[i]!='\0';i++) /*checking communication*/
	{
		USART_TxChar(cmd_1[i]);
		_delay_ms(5);
	}
	USART_TxChar('\r'); /*carriage return ---> begining from the first line without going to next line*/
	_delay_ms(5);
	
	for (int i=0;cmd_2[i]!='\0';i++) /* set the operating mode to SMS text mode*/
	{
		USART_TxChar(cmd_2[i]);
		_delay_ms(5);
	}
	USART_TxChar('\r');
	_delay_ms(5);
	
	for (int i=0;cmd_3[i]!='\0';i++) /* send SMS in text mode*/
	{
		USART_TxChar(cmd_3[i]);
		_delay_ms(5);
	}
	UDR='"';
	_delay_ms(100);
	for (int i=0;num[i]!='\0';i++) /* SMS to be sent */
	{
		USART_TxChar(num[i]);
		_delay_ms(5);
	}
	UDR='"';
	_delay_ms(5);
	UDR='\r';
	_delay_ms(5);

	for (int i=0;cmd_4[i]!='\0';i++) /* message */
	{
		USART_TxChar(cmd_4[i]);
		_delay_ms(5);
	}
	_delay_ms(200);
	LCD_Clear();
	LCD_String_xy(1,0,"Message sent");
	_delay_ms(300);
	LCD_Clear();
}
void I2C_Init()												/* I2C initialize function */
{
	TWBR = BITRATE(TWSR = 0x00);							/* Get bit rate register value by formula */
}	


uint8_t I2C_Start(char slave_write_address)						/* I2C start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != 0x08)										/* Check weather start condition transmitted successfully or not? */
	return 0;												/* If not then return 0 to indicate start condition fail */
	TWDR = slave_write_address;								/* If yes then write SLA+W in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */	
	if (status == 0x18)										/* Check weather SLA+W transmitted & ack received or not? */
	return 1;												/* If yes then return 1 to indicate ack received i.e. ready to accept data byte */
	if (status == 0x20)										/* Check weather SLA+W transmitted & nack received or not? */
	return 2;												/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 3;												/* Else return 3 to indicate SLA+W failed */
}

uint8_t I2C_Repeated_Start(char slave_read_address)			/* I2C repeated start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != 0x10)										/* Check weather repeated start condition transmitted successfully or not? */
	return 0;												/* If no then return 0 to indicate repeated start condition fail */
	TWDR = slave_read_address;								/* If yes then write SLA+R in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == 0x40)										/* Check weather SLA+R transmitted & ack received or not? */
	return 1;												/* If yes then return 1 to indicate ack received */ 
	if (status == 0x20)										/* Check weather SLA+R transmitted & nack received or not? */
	return 2;												/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 3;												/* Else return 3 to indicate SLA+W failed */
}

void I2C_Stop()												/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Enable TWI, generate stop condition and clear interrupt flag */
	while(TWCR & (1<<TWSTO));								/* Wait until stop condition execution */ 
}

void I2C_Start_Wait(char slave_write_address)				/* I2C start wait function */
{
	uint8_t status;											/* Declare variable */
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				/* Enable TWI, generate start condition and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (start condition) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != 0x08)									/* Check weather start condition transmitted successfully or not? */
		continue;											/* If no then continue with start loop again */
		TWDR = slave_write_address;							/* If yes then write SLA+W in TWI data register */
		TWCR = (1<<TWEN)|(1<<TWINT);						/* Enable TWI and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != 0x18 )								/* Check weather SLA+W transmitted & ack received or not? */
		{
			I2C_Stop();										/* If not then generate stop condition */
			continue;										/* continue with start loop again */
		}
		break;												/* If yes then break loop */
	}
}

uint8_t I2C_Write(char data)								/* I2C write function */
{
	uint8_t status;											/* Declare variable */
	TWDR = data;											/* Copy data in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == 0x28)										/* Check weather data transmitted & ack received or not? */
	return 0;												/* If yes then return 0 to indicate ack received */
	if (status == 0x30)										/* Check weather data transmitted & nack received or not? */
	return 1;												/* If yes then return 1 to indicate nack received */
	else
	return 2;												/* Else return 2 to indicate data transmission failed */
}

char I2C_Read_Ack()										/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Enable TWI, generation of ack and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}	

char I2C_Read_Nack()										/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);								/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}	
void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);				/* RS=0, command reg. */
	LCD_Port |= (1<<EN);				/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);				/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)					/* LCD Initialize function */
{
	LCD_Dir = 0xFF;						/* Make LCD command port direction as o/p */
	_delay_ms(20);						/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x33);
	LCD_Command(0x32);		    		/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              	/* Use 2 line and initialize 5*7 matrix in (4-bit mode)*/
	LCD_Command(0x0c);              	/* Display on cursor off*/
	LCD_Command(0x06);              	/* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              	/* Clear display screen*/
	_delay_ms(2);
	LCD_Command (0x80);					/* Cursor 1st row 0th position */
}


void LCD_String (char *str)				/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)				/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);		/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);		/* Command of first row and required position<16 */
	LCD_String(str);					/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);					/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);					/* Cursor 1st row 0th position */
}
void MPU6050_Init()										/* Gyro initialization function */
{
	_delay_ms(150);										/* Power up time >100ms */
	I2C_Start_Wait(0xD0);								/* Start with device write address */
	I2C_Write(SMPLRT_DIV);								/* Write to sample rate register */
	I2C_Write(0x07);									/* 1KHz sample rate */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(PWR_MGMT_1);								/* Write to power management register */
	I2C_Write(0x01);									/* X axis gyroscope reference frequency */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(CONFIG);									/* Write to Configuration register */
	I2C_Write(0x00);									/* Fs = 8KHz */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);								/* Write to Gyro configuration register */
	I2C_Write(0x18);									/* Full scale range +/- 2000 degree/C */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);								/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();
}

void MPU_Start_Loc()
{
	I2C_Start_Wait(0xD0);								/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);							/* Write start location address from where to read */
	I2C_Repeated_Start(0xD1);							/* I2C start with device read address */
}

void Read_RawValue()
{
	MPU_Start_Loc();									/* Read Gyro values */
	Acc_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Temperature = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();
}

int isDriverSleepingGyro(float Xa,float Ya,float Za){
	if((Za>-2.0 && Za<2.0) && (Xa>-3.0 && Xa<3.0) && (Ya>=8.0 && Ya<=9.0)){
		return 0;//driver is not sleeping
	}else{
		return 1;//driver is sleeping
	}
}
void PWM_init(){
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);  /*set OC0 pin as output*/
}
void get_latitude(uint16_t lat_pointer){  //unsigned 16-bit integer - integers between 0 and 65,535
	cli(); //Command Line Interface - CLIs accept as input commands that are entered by keyboard
	uint8_t lat_index; //unsigned 8-bit integer- integer has a range of 0 to 255
	uint8_t index = lat_pointer+1;//unsigned 8-bit integer- integer has a range of 0 to 255
	lat_index=0;
	
	/* parse Latitude in GGA string stored in buffer */
	for(;GGA_Buffer[index]!=',';index++){
		Latitude_Buffer[lat_index]= GGA_Buffer[index];
		lat_index++;
	}
	
	Latitude_Buffer[lat_index++] = GGA_Buffer[index++];
	Latitude_Buffer[lat_index]= GGA_Buffer[index];		/* get direction */
	convert_to_degrees_lat(Latitude_Buffer);   // convert raw latitude into degree format and pass that value as string
	sei(); //It is a macro that executes an assembler instruction to enable interrupts.
}

void get_longitude(uint16_t long_pointer){
	cli(); //Command Line Interface - CLIs accept as input commands that are entered by keyboard
	uint8_t long_index;  //unsigned 8-bit integer- integer has a range of 0 to 255
	uint8_t index = long_pointer+1;
	long_index=0;
	
	/* parse Longitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Longitude_Buffer[long_index]= GGA_Buffer[index];
		long_index++;
	}
	
	Longitude_Buffer[long_index++] = GGA_Buffer[index++];
	Longitude_Buffer[long_index]   = GGA_Buffer[index]; /* get direction */
	convert_to_degrees_long(Longitude_Buffer); // convert raw longitude into degree format and pass that value as string
	sei(); //It is a macro that executes an assembler instruction to enable interrupts.

}

void get_altitude(uint16_t alt_pointer){  //unsigned 16-bit integer - integers between 0 and 65,535
	cli(); //Command Line Interface - CLIs accept as input commands that are entered by keyboard
	uint8_t alt_index;  //unsigned 8-bit integer- integer has a range of 0 to 255
	uint8_t index = alt_pointer+1;
	alt_index=0;
	/* parse Altitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Altitude_Buffer[alt_index]= GGA_Buffer[index];
		alt_index++;
	}
	
	Altitude_Buffer[alt_index]   = GGA_Buffer[index+1];
	sei();//It is a macro that executes an assembler instruction to enable interrupts.
}


void convert_to_degrees_lat(char *raw){
	
	double value;
	float decimal_value,temp;
	
	int32_t degrees;
	
	float position;
	value = atof(raw); /* convert string into float for conversion */
	
	/* convert raw latitude/longitude into degree format */
	decimal_value = (value/100);
	degrees = (int)(decimal_value);
	temp = (decimal_value - (int)decimal_value)/0.6;
	position = (float)degrees + temp;
	
	dtostrf(position, 6, 4, lat_degrees_buffer); /* dtostrf is a function that convert float value into string.Here the position is a float value and it convert as a string degree buffer variable*/
}

void convert_to_degrees_long(char *raw){
	
	double value;
	float decimal_value,temp;
	
	int32_t degrees;
	
	float position;
	value = atof(raw); /* convert string into float for conversion */
	
	/* convert raw latitude/longitude into degree format */
	decimal_value = (value/100);
	degrees = (int)(decimal_value);
	temp = (decimal_value - (int)decimal_value)/0.6;
	position = (float)degrees + temp;
	
	dtostrf(position, 6, 4, long_degrees_buffer); /* dtostrf is a function that convert float value into string.Here the position is a float value and it convert as a string degree buffer variable*/
}

ISR (USART_RXC_vect)
{
	uint8_t oldsrg = SREG;  //unsigned 8-bit integer- integer has a range of 0 to 255
	cli();					//Command Line Interface - CLIs accept as input commands that are entered by keyboard
	char received_char = UDR;
	
	if(received_char =='$'){                                                    /* check for '$' */
		GGA_Index = 0;
		CommaCounter = 0;
		IsItGGAString = false;
	}
	else if(IsItGGAString == true){                                             /* if true save GGA info. into buffer */
		if(received_char == ',' ) GGA_Pointers[CommaCounter++] = GGA_Index;     /* store instances of ',' in buffer */
		GGA_Buffer[GGA_Index++] = received_char;
	}
	else if(GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A'){    /* check for GGA string */
		IsItGGAString = true;
		GGA_CODE[0] = 0; GGA_CODE[1] = 0; GGA_CODE[2] = 0;
	}
	else{
		GGA_CODE[0] = GGA_CODE[1];  GGA_CODE[1] = GGA_CODE[2]; GGA_CODE[2] = received_char;
	}
	SREG = oldsrg;
}
void USART_Init(unsigned long BAUDRATE)		
{
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);  /* enables RX and TX */
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); /* 8 bit data length */
	UBRRL=BAUD_PRESCALE; /* make sure the UBRR is set correctly */
	UBRRH=(BAUD_PRESCALE>>8);
}
char USART_RxChar()	
{
	while (!(UCSRA & (1 << RXC))); /* while data received is null */
	return (UDR); /* read data from buffer */
}
void USART_TxChar(char data)		
{
	while (!(UCSRA&(1<<UDRE))); /* wait till UDRE = 1, buffer becomes empty and TX buffer is ready to receive new data */
	UDR=data; /* return the given command */
}
void USART_SendString(char *str)	
{
	unsigned char i=0;
	while (str[i]!='\0')		/* Send string till null */
	{
		USART_TxChar(str[i]);
		i++;
	}
}