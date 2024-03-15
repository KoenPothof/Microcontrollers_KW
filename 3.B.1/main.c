#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main (void){
	
	DDRD = 0b11111111;
	PORTE = 0x01;
	PORTG = 0x01;
	
	init();
	set_cursor(5);
	
	int i = 0;
	display_integer(i);
	
	while (1) {
		_delay_ms(100);
		if(PINE == 1 && PING == 1){
			while(PINE == 1 && PING == 1){
				_delay_ms(10);
			}
			i = 0;
			init();
			display_integer(i);
		}else if(PINE == 1){
			while(PINE == 1){
				_delay_ms(10);
			}
			i++;
			init();
			display_integer(i);
	}else if(PING == 1 && i > 0){
		while(PING == 1){
			_delay_ms(10);
		}
		i--;
		init();
		display_integer(i);
	}
	}
	return 1;
}