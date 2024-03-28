/*
 * 4.B.3.c
 *
 * Created: 3/27/2024 13:38:09
 * Author : koenp
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

// wait(): bezig wachten voor 'ms' milliseconden
// Gebruikte bibliotheek: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// bibliotheekfunctie (max 30 ms bij 8MHz)
	}
}


// Initialiseer ADC: 10-bits (links uitgelijnd), continu
void adcInit( void )
{
	ADMUX = 0b01100011;			// AREF=VCC, resultaat links uitgelijnd, kanaal 3 op pin PF3
	ADCSRA = 0b10000110;		// ADC-inschakelen, geen onderbreking, geen start, geen vrije loop, deling door 64
}


// Hoofdprogramma: ADC op PF1
int main( void )
{
	DDRF = 0x00;				// stel PORTF in als invoer (ADC)
	DDRA = 0xFF;				// stel PORTA in als uitvoer
	adcInit();					// initialiseer ADC

	while (1)
	{
		ADCSRA |= BIT(6);			// Start een ADC-conversie door het ADSC bit te zetten in het ADCSRA-register
		while (ADCSRA & BIT(6));	// Wacht tot de ADC-conversie is voltooid door te controleren of het ADSC bit is gewist
		PORTA = ADCH;				// Zet de waarde van het meest significante byte (MSB) van de ADC-conversieresultaat op PORTA
		wait(100);				// elke 100 ms (busy wachten)
	}
}