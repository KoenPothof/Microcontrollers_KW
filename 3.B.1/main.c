#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main (void){
	
	DDRD = 0b11111111;
	PORTE = 0x01;
	PORTG = 0x01;
	
	init(); //initialiseer lcd
	set_cursor(5);
	
	int i = 0;
	display_integer(i); //zet alvast de 0 op het LCD scherm
	
	while (1) {
		_delay_ms(100);
		if(PINE == 1 && PING == 1){
			while(PINE == 1 && PING == 1){ //wacht totdat te knoppen los worden gelaten
				_delay_ms(10);
			}
			i = 0;
			init(); //reset lcd
			display_integer(i); //display i
		}else if(PINE == 1){ 
			while(PINE == 1){ //wacht totdat de knop wordt losgelaten
				_delay_ms(10);
			}
			i++;
			init(); //reset lcd
			display_integer(i); //display i
	}else if(PING == 1 && i > 0){ //zorg ervoor dat de i niet in de min kan
		while(PING == 1){ //wacht totdat de knop wordt losgelaten
			_delay_ms(10);
		}
		i--;
		init(); //reset lcd
		display_integer(i); //display i
	}
	}
	return 1;
}