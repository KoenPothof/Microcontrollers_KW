/*
 * 4.B.1.c
 *
 * Created: 3/15/2024 11:21:02
 * Author : koenp
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void initADC() {
	// Stel de deelfactor in op 64 (prescaler = 64)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
	// Stel de referentiespanning in op VCC
	ADMUX |= (1 << REFS0);
	// Kies 'hoge byte gevuld' voor de AD-waarden
	ADMUX |= (1 << ADLAR);
	// Enable de ADC
	ADCSRA |= (1 << ADEN);
}

// Functie om een ADC conversie te starten en te wachten op voltooiing
uint16_t readADC(uint8_t channel) {
	// Kies het juiste kanaal in ADMUX
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	// Start de ADC conversie
	ADCSRA |= (1 << ADSC);
	// Wacht tot de conversie voltooid is
	while (ADCSRA & (1 << ADSC));
	// Geef de resultaten terug
	return ADC;
}

int main() {
	// Initialiseer de ADC
	initADC();

	// Definieer variabelen om de resultaten op te slaan
	uint16_t adcResult;

	// Hoofdprogramma
	while (1) {
		// Lees de ADC-waarde van het gekozen kanaal (bijvoorbeeld kanaal 0)
		adcResult = readADC(0);
		
		// Voer hier verdere bewerkingen uit met de ADC-waarde
		
		// Wacht een korte periode voordat de volgende meting wordt uitgevoerd
		_delay_ms(1000);
	}

	return 0;
}

