
/*
 * ADC.h
 *
 * Created: 5/10/2022 11:41:37 AM
 *  Author: THADSHAJINY
 */ 
 void ADC_Init()
		 {
			 DDRB=0xFF;    //Make port B as output port
			// DDRD=0xFF;		//MAke port D as an output port
			 DDRA=0x00;      //MAke port A as an input port
			 ADCSRA=0x87;		//Make ADC enable & select clk/128
			 ADMUX=0xC0;       //Vref=2.56V,ADC0single ended input & data right aligned
		 }
			 
int ADC_Read(char channel)
	{
		int Ain,AinLow;
		ADCSRA|=(1<<ADSC);   //start conversion
		while((ADCSRA & (1<<ADIF))==0);  //wait for conversion to finish
	// PORTD=ADCL;    //send lower byte to portD
	// PORTB=ADCH;  //send hugh byte to port B
		_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
		Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
	}