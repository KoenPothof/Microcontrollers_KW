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
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	int pinArray[8][8] = {
	{1, 1, 0, 0, 1, 1, 0}, 
	{0, 1, 1, 0, 0, 1, 1},
	{1, 0, 1, 1, 0, 0, 1},
	{1, 1, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 1, 1, 0},
	{0, 0, 1, 1, 0, 1, 1},
	{1, 0, 0, 1, 1, 0, 1},
	};
	
	while (1)
	{
		for(int row = 0; row <= 6; row ++) 
		{
			PORTA = pinArray[row][0];
			PORTB = pinArray[row][1];
			PORTC = pinArray[row][2];
			PORTD = pinArray[row][3];
			PORTE = pinArray[row][4];
			PORTF = pinArray[row][5];
			PORTG = pinArray[row][6];
			_delay_ms(150);
		}
	}
	return 0;
}

