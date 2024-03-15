/*
 * GccApplication1.c
 *
 * Created: 2/2/2024 11:32:59
 * Author : koenp
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0xFF; // Stel alle pinnen van Port D in als uitgangen
	
	while (1)
	{
		PORTD = 0b11000000; // Zet PD7 en PD6 hoog, andere pinnen laag
		_delay_ms(500); // Vertraging van 500 milliseconden
		PORTD = 0b00000000; // Zet alle pinnen laag
		_delay_ms(500); // Vertraging van 500 milliseconden
	}
	return 0;
}

