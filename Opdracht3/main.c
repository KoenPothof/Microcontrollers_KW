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
	DDRA = 0xFF; // Stel alle pinnen van Port A in als uitgangen
	PORTA = 0b00000001; // Stel de eerste pin van Port A hoog, de rest laag
	
	while (1)
	{
		if(PORTA != 0b00000000){ // Controleer of PORTA niet gelijk is aan 0
			PORTA = (PORTA << 1); // Verschuif de waarde van PORTA naar links (rol linksom) en schrijf het terug naar PORTA
			_delay_ms(500); // Vertraging van 500 milliseconden
		}
		else{
			PORTA = 0b00000001; // Als PORTA gelijk is aan 0, zet de eerste pin van Port A hoog en de rest laag
			_delay_ms(500); // Vertraging van 500 milliseconden
		}
	}
	return 0;
}

