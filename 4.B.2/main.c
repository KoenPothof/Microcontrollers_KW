/*
 * 4.B.2.c
 *
 * Created: 3/22/2024 10:50:09
 * Author : koenp
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// bibliotheekfunctie (max 30 ms bij 8 MHz)
	}
}


// Initialiseer ADC:
void adcInit( void )
{
	ADMUX = 0b01100001;			// AREF=VCC, resultaat links uitgelijnd, kanaal 1 op pin PF1
	ADCSRA = 0b11100110;		// ADC-inschakelen, geen onderbreking, geen start, geen vrije loop, deling door 64
}


// Hoofdprogramma: tellen op T1
int main( void )
{
	DDRF = 0x00;					// stel PORTF in als invoer (ADC)
	DDRA = 0xFF;					// stel PORTA in als uitvoer
    DDRB = 0xFF;					// stel PORTB in als uitvoer
	adcInit();						// initialize ADC
    
	while (1)
	{
		PORTB = ADCL;			// Toon MSB/LSB (bit 10:0) van ADC
		PORTA = ADCH;			// Toon bit 8:0 van ADC
		wait(100);				// elke 100 ms (bezig met wachten)
	}
}