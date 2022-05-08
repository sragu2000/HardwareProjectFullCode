#define F_CPU 8000000UL
#include "headerfiles.h"
int main(void){
	setOutput(PORTC,led);
	while (1){
		if(pinRead(PINC,flame)){
			portHigh(PORTC,led);
		}else{
			portLow(PORTC,led);
		}
	}
}