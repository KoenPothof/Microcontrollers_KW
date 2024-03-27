/*
 * tester.c
 *
 * Created: 3/15/2024 10:14:51
 * Author : koenp
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <built_in.h>
unsigned int adc_rd;

void main() {
	DDRB = 0xFF;               // Set PORTB as output
	DDRC = 0xFF;               // Set PORTC as output
	
	while (1) {
		adc_rd = ADC_Read(2);    // get ADC value from 2nd channel
		PORTB = adc_rd;          // display adc_rd[7..0]
		PORTC = Hi(adc_rd);      // display adc_rd[9..8]
	}
}