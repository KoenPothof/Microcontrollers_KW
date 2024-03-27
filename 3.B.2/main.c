#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BIT(x)    (1 << (x))

void wait( int ms );
void adcInit( void );


int main( void ) {
	DDRF = 0x00;                    // set PORTF for input (ADC)
	DDRA = 0xFF;                    // set PORTA for output
	adcInit();                        // initialize ADC

	while (1)
	{
		ADCSRA |= BIT(6);                // Start ADC
		while ( ADCSRA & BIT(6) ) ;        // Wait for completion
		PORTA = ADCH;                    // Show MSB (bit 9:2) of ADC
		wait(500);                        // every 50 ms (busy waiting)
	}
}

int opdrachtb2( void )
{
	DDRF = 0x00;                    // set PORTF for input (ADC)
	DDRA = 0xFF;                    // set PORTA for output
	adcInit();                        // initialize ADC

	while (1)
	{
		ADCSRA |= BIT(6);                // Start ADC
		while ( ADCSRA & BIT(6) ) ;        // Wait for completion
		PORTA = ADCH;                    // Show MSB (bit 9:2) of ADC
		wait(500);                        // every 50 ms (busy waiting)
	}
}

// Initialize ADC: 10-bits (left justified), free running
// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b11100011;            // AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;        // ADC-enable, no interrupt, start, free running, division by 64
}

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );            // library function (max 30 ms at 8MHz)
	}
}