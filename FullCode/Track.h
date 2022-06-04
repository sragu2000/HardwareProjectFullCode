
/*
 * Track.h
 *
 * Created: 5/10/2022 1:19:01 PM
 *  Author: ishu
 */ 


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
