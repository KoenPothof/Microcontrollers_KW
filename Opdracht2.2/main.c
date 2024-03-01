/*
 * Opdracht2.2.c
 *
 * Created: 2/23/2024 13:43:23
 * Author : koenp
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void setup() {
	DDRD = 0xF0;
	DDRA = 0xFF;

	EICRA |= 0x0F; // Zet interupt 0 en 1 op rising edge
	EIMSK |= 0x03; // Enable INT1 & INT0
	sei(); // Enable global interrupt

	PORTA = 1;
}

int main(void)
{
	setup();

	while (1)
	{
	}
}

ISR( INT0_vect ) {
	PORTA <<= 1;
	if (!PORTA)
	PORTA = 1; // Zet de eerste bit op 1
}

ISR( INT1_vect ) {
	PORTA >>= 1;
	if (!PORTA)
	PORTA = 1 << 7; // Zet de laatste bit op 1
}