
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