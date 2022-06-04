#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	/* Define prescale value */
void USART_Init(unsigned long BAUDRATE);
char USART_RxChar();
void USART_TxChar(char data);
void USART_SendString(char *str);

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