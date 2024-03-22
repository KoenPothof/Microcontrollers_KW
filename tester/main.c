/*
 * tester.c
 *
 * Created: 3/15/2024 10:14:51
 * Author : koenp
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void setupADC()
{
	DDRF &= ~(1<<PF0); // PORTF.0 input ADC
	DDRA = 0xFF; // PORTA outputs for displaying ADC value
	DDRB = 0xFF; // PORTB outputs for displaying ADC value
	// MUX4..0 = 00000 = ADC0
	// ADLAR = 1 Left adjust, AVCC with external capacitor at AREF
	
	ADMUX = 0b01100000;
	// ADEN: ADC Enable, ADSC: ADC Start Conversion
	// ADFR: ADC Free Running Select
	// ADC Prescaler Select Bits : Division Factor = 64
	ADCSRA = 0b11100110;
}
int main(void)
{
	setupADC();
	/* Replace with your application code */
	while (1)
	{
		PORTA = ADCL;
		PORTB = ADCH;
		_delay_ms(100);
	}
}