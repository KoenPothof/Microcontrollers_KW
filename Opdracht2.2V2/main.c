/*
 * Opdracht2.2V2.c
 *
 * Created: 3/1/2024 12:41:44
 * Author : koenp
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>




void initSetup() {
	DDRB = 0xFF;
	
	 EICRA |= 0x0F; 
	 EIMSK |= 0x03;
	sei();
	
	PORTB = 1;
}


int main(void) {
	
	initSetup();

	while (1) {
		
	}
}

ISR(INT0_vect) {
	PORTB <<= 1;
	if (!PORTB){
		PORTB = 1;
	}
}

ISR(INT1_vect) {
	PORTB >>= 1;
	if (!PORTB){
		PORTB = 1 << 7;
	}
}

