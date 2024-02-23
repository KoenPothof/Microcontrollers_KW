/*
 * Opdracht2.c
 *
 * Created: 2/2/2024 11:50:30
 * Author : koenp
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>


int main(void)
{
	DDRD = 0xFF;
	PORTC = 0x01;
    
    while (1) 
    {
		if(PINC == 1){
			PORTD = 0b10000000;
		}else{
			PORTD = 0b00000000;
		}
    }
	return 0;
}

