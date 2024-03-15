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
	DDRD = 0xFF; // Stel alle pinnen van Port D in als uitgangen
	PORTC = 0x01; // Stel de eerste pin van Port C hoog, de rest laag
	
	while (1)
	{
		if(PINC == 1){ // Controleer of de waarde op pin 0 van Port C gelijk is aan 1
			PORTD = 0b10000000; // Zet de meest significante bit van Port D hoog, andere pinnen laag
		}
		else{
			PORTD = 0b00000000; // Zet alle pinnen van Port D laag
		}
	}
	return 0;
}


