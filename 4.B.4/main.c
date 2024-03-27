/*
 * 4.B.4.c
 *
 * Created: 3/27/2024 15:27:14
 * Author : koenp
 */ 

#include <xc.h>
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <stdio.h>

#define BIT(x)	(1 << (x))

// Initialize ADC: 10-bits (left justified), free running
// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b11100011;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


int main( void ) {
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	//DDRB = 0xFF;				// set PORTB for output
	adcInit();					// initialize ADC
	lcd_init();					// Init lcd

	while (1)
	{
		PORTA = ADCH;
		
		char temp[10];
		sprintf(temp, "%d    ", ADCH);	//Give temp the value of ADCH in string form
		lcd_set_cursor(0);				//Reset cursor
		lcd_display_text(temp);			//Display temp on lcd
		
		wait(100);
	}
}

