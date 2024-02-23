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
	DDRD = 0xFF;
    
    while (1) 
    {
		PORTD = 0b11000000;
		_delay_ms(500);
		PORTD = 0b00000000;
		_delay_ms(500);
    }
	return 0;
}
