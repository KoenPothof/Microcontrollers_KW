#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main (void){
	
	init();
	set_cursor(2);
	display_text("Begin");
	
	DDRD = 0b11111111;
	PORTE = 0x01;
	PORTG = 0x01;
	
	int i = 0;
	while (1) {
		_delay_ms(100);
		if(PINE == 1 && PING == 1){
			i = 0;
			_delay_ms(400);
			init();
			display_text("e en f ingedrukt");
			_delay_ms(500);
		}else if(PINE == 1){
			i++;
			_delay_ms(400);
			init();
			display_text("e ingedrukt");
			_delay_ms(500);
	}else if(PING == 1 && i > 0){
		i--;
		_delay_ms(400);
		init();
		display_text("f ingedrukt");
		_delay_ms(500);
	}
		if(i>15){
			i = 16;
		}
	}
	return 1;
}