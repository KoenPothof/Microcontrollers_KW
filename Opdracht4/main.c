/*
 * Opdracht4.c
 *
 * Created: 2/2/2024 13:07:59
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
	// Instellen van alle poorten als uitgangen
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;

	// Definitie van een 2D-array om pinconfiguraties op te slaan
	int pinArray[8][8] = {
		{1, 1, 0, 0, 1, 1, 0}, // Voorbeeldrij 1
		{0, 1, 1, 0, 0, 1, 1}, // Voorbeeldrij 2
		{1, 0, 1, 1, 0, 0, 1}, // Voorbeeldrij 3
		{1, 1, 0, 1, 1, 0, 0}, // Voorbeeldrij 4
		{0, 1, 1, 0, 1, 1, 0}, // Voorbeeldrij 5
		{0, 0, 1, 1, 0, 1, 1}, // Voorbeeldrij 6
		{1, 0, 0, 1, 1, 0, 1}, // Voorbeeldrij 7
	};

	while (1)
	{
		// Itereer door elke rij in pinArray
		for(int row = 0; row <= 6; row ++)
		{
			// Stel de uitgangen van elke poort in op basis van de huidige rij in pinArray
			PORTA = pinArray[row][0];
			PORTB = pinArray[row][1];
			PORTC = pinArray[row][2];
			PORTD = pinArray[row][3];
			PORTE = pinArray[row][4];
			PORTF = pinArray[row][5];
			PORTG = pinArray[row][6];

			// Wacht voor een korte periode
			_delay_ms(150);
		}
	}
	return 0;
}

