
/*
 * LCD_16x2_H_file.h
 *
 * Created: 5/10/2022 11:14:56 AM
 *  Author: ishu
 */ 
#define LCD_Data_Dir DDRB
#define LCD_Command_Dir DDRC
#define LCD_Data_Port PORTB
#define LCD_Command_Port PORTC
#define EN PC2
#define RW PC1
#define RS PC0

void LCD_Command (char cmd)	/* LCD command write function */
{
	LCD_Data_Port = cmd;
	LCD_Command_Port &= ~((1<<RS)|(1<<RW));	/* RS = Low(command), RW = Low (write) */
	LCD_Command_Port |= (1<<EN); /* Enable signal */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(2);
}
void LCD_Char (char char_data) /* LCD data write function */
{
	LCD_Data_Port = char_data;
	LCD_Command_Port &= ~(1<<RW);/* RW = Low (Write) */
	LCD_Command_Port |= (1<<EN)|(1<<RS); /* RS = High (data), and Enable = High*/
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}
void LCD_Init () /* LCD Initialize function */
{
	LCD_Command_Dir |= (1<<RS)|(1<<RW)|(1<<EN);
	LCD_Data_Dir = 0xFF;
	
	_delay_ms(18); /* To get things ready, the LCD power up time should always be greater than 15ms */
	LCD_Command (0x38);	/* Initialize 8bit mode */
	LCD_Command (0x0C);	/* Display ON, Cursor OFF */
	LCD_Command (0x06);	/* Auto Increment cursor */
	LCD_Command (0x01);	/* Clear LCD command */
	LCD_Command (0x80); /* 8 is for first line and 0 is for 0th position */
}
void LCD_String (char *str) /* Send string to LCD function */
{
	for(int i=0;str[i]!=0;i++)
	{
		LCD_Char (str[i]);
	}
}
void LCD_String_xy (char row, char pos, char *str) /* Send row, position and string to LCD function */
{
	if (row == 1)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row */
	else if (row == 2)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of Second row */
	LCD_String(str);
}
void LCD_Clear() /* Clear LCD*/
{
	LCD_Command(0x01);
}