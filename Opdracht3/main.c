/*
 * Opdracht3.c
 *
 * Created: 2/2/2024 12:10:22
 * Author : koenp
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL // 16 MHz clock speed
#endif
#define BIT(x) (1 << (x)) 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRA = 0xFF;
	PORTA = 0b00000001;
    
   while (1)
   {
	   if(PORTA != 0b00000000){
	   PORTA = (PORTA<< 1);
	   _delay_ms(500);
	   }else{
		PORTA = 0b00000001;
		_delay_ms(500);
	   }
	}
    return 0;
}

