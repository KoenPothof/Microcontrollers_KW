#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main (void){
	
	init();
	set_cursor(2);
	display_text("NIGGER");
	
	DDRD = 0b11111111;
	PORTE = 0x01;
	PORTF = 0x01;
	
	int i = 0;
	while (1) {
		_delay_ms(10);
		if(PINE == 1){
			i++;
			_delay_ms(400);
			init();
			display_text("Nikkel 1");
		}
		if(PINE == 1 && PIND == 1){
			i = 0;
			_delay_ms(400);
			init();
			display_text("Nikkel 3");
		}
		if(PIND == 1 && i>5){
			i--;
			_delay_ms(400);
			init();
			display_text("Nikkel 2");
		}
		if(i>15){
			i = 16;
		}
	}
	return 1;
}