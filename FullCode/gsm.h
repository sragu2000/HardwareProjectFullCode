void USART_initialize(long USART_BAUDRATE);
unsigned char USART_rxc();
void USART_transmit(char ch);
void USART_send(char *str);

void USART_initialize(long USART_BAUDRATE)
{
	UCSRB|=(1<<RXEN)|(1<<TXEN);  /* enables RX and TX */
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); /* 8 bit data length */
	UBRRL=BAUD_PRESCALE; /* make sure the UBRR is set correctly */
	UBRRH=(BAUD_PRESCALE>>8);
}
unsigned char  USART_rxc()
{
	while ((UCSRA&(1<<RXC))==0); /* while data received is null */
	return UDR; /* read data from buffer */
}
void USART_transmit(char ch)
{
	while (!(UCSRA&(1<<UDRE))); /* wait till UDRE = 1, buffer becomes empty and TX buffer is ready to receive new data */
	UDR=ch; /* return the given command */
}
void USART_send(char *str)
{
	while (*str!='\0')
	{
		USART_transmit(*str);
		str++;
	}
}

void sendMessage(char* msg,char* longtitude,char* latitude)
{
	
	unsigned char cmd_1[4]="AT";
	unsigned char cmd_2[10]="AT+CMGF=1";
	unsigned char cmd_3[10]="AT+CMGS=";
	char* cmd_4 = msg;
	strcat(cmd_4,"\rLocation\r   Longitude : ");
	strcat(cmd_4,longtitude);
	strcat(cmd_4,"\r   Latitude : ");
	strcat(cmd_4,latitude);
	unsigned char num[11] = "0771234567";
	LCD_Clear();
	LCD_String_xy(1,0,"Message");
	LCD_String_xy(2,3,"Forwarding");
	//USART_send(msg);
	_delay_ms(500);
	
	
	for (int i=0;cmd_1[i]!='\0';i++) /*checking communication*/
	{
		USART_transmit(cmd_1[i]);
		_delay_ms(100);
	}
	USART_transmit('\r'); /*carriage return ---> begining from the first line without going to next line*/
	_delay_ms(200);
	
	for (int i=0;cmd_2[i]!='\0';i++) /* set the operating mode to SMS text mode*/
	{
		USART_transmit(cmd_2[i]);
		_delay_ms(100);
	}
	USART_transmit('\r');
	_delay_ms(200);
	
	for (int i=0;cmd_3[i]!='\0';i++) /* send SMS in text mode*/
	{
		USART_transmit(cmd_3[i]);
		_delay_ms(100);
	}
	UDR='"';
	_delay_ms(100);
	for (int i=0;num[i]!='\0';i++) /* SMS to be sent */
	{
		USART_transmit(num[i]);
		_delay_ms(100);
	}
	UDR='"';
	_delay_ms(100);
	UDR='\r';
	_delay_ms(200);

	for (int i=0;cmd_4[i]!='\0';i++) /* message */
	{
		USART_transmit(cmd_4[i]);
		_delay_ms(100);
	}
	_delay_ms(200);
	LCD_Clear();
	LCD_String_xy(1,0,"Message sent");
	_delay_ms(3000);
	LCD_Clear();
}