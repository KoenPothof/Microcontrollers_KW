/*
 * 4.B.2.c
 *
 * Created: 3/22/2024 10:50:09
 * Author : koenp
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// Functie om de ADC in te stellen
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

// Functie om de ADC-waarde om te zetten in LED-output op poort A en B
void showADCValueOnLEDs(uint16_t adcValue) {
	// Zet de ADC-waarde om naar een waarde tussen 0 en 1023
	uint16_t scaledValue = adcValue;

	// Zet de LED-output op poort A
	PORTA = scaledValue;

	// Zet de LED-output op poort B
	PORTB = scaledValue;
}

int main() {
	// Initialiseer de ADC
	initADC();

	// Zet poort A en B als uitgangen voor de LED's
	DDRA = 0xFF;
	DDRB = 0xFF;

	
	uint16_t adcResult;


	while (1) {
		// Lees de ADC-waarde van kanaal 1
		adcResult = readADC(1);
		
		// Toon de ADC-waarde op de LED's van poort A en B
		showADCValueOnLEDs(adcResult);

		// Wacht een korte periode voordat de volgende meting wordt uitgevoerd
		_delay_ms(100);
	}

	return 0;
}


