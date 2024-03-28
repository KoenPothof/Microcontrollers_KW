/*
 * 4.B.4.c
 *
 * Created: 3/27/2024 15:27:14
 * Author : koenp
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcdView.h"
#include <stdio.h>

#define BIT(x)	(1 << (x))

// Initialize ADC: 10-bits (left justified), free running
// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b01100001;			// Stel ADC-referentie in op AVCC, resultaat links uitgelijnd, kanaal 1 op pin PF1
	ADCSRA = 0b11100110;		// Schakel ADC in, geen onderbreking, start, vrije loop-modus, deling door 64
}

// Functie voor bezig wachten
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// Vertraging van 1 milliseconde met bibliotheekfunctie (maximaal 30 ms bij 8MHz)
	}
}

int main( void ) {
	DDRF = 0x00;				// Zet PORTF als invoer (ADC)
	DDRA = 0xFF;				// Zet PORTA als uitvoer
	adcInit();					// Initialiseer ADC
	lcd_init();					// Initialiseer LCD

	while (1)
	{
		PORTA = ADCH;               // Lees ADC-waarde en stuur deze naar PORTA
		char temp[10];              // Maak een tekenreeks-array om de temperatuurwaarde op te slaan
		
		sprintf(temp, "%d    ", ADCH); // Converteer ADC-waarde naar een tekenreeks en sla deze op in 'temp'
		// De extra spaties worden toegevoegd om eventuele overgebleven karakters van eerdere metingen te wissen
		
		lcd_set_cursor(0);				// Reset LCD-cursorpositie
		lcd_display_text(temp);			// Toon temperatuur op LCD
		wait(100);		                // Wacht 100 milliseconden voordat de volgende meting wordt uitgevoerd
	}
}