#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t pulse_state = 0; // Variabele om de staat van de puls bij te houden

ISR(TIMER2_COMPA_vect) {
	if (pulse_state == 0) {
		// Pulshoogte van 15 ms
		PORTD |= (1 << PD7); // Zet pin PD7 hoog
		OCR2A = 585; // 15 ms bij een prescaler van 64 (250 * 64 * 1/16e6 = 0.015)
		pulse_state = 1;
		} else {
		// Pulslage van 25 ms
		PORTD &= ~(1 << PD7); // Zet pin PD7 laag
		OCR2A = 976; // 25 ms bij een prescaler van 64 (250 * 64 * 1/16e6 = 0.025)
		pulse_state = 0;
	}
}

int main() {
	DDRD |= (1 << PD7); // Zet PD7 als uitgang
	TCCR2A = (1 << WGM21); // CTC-modus
	TCCR2A = (1 << CS22); // Prescaler 64
	TIMSK2 = (1 << OCIE2A); // Timer/Counter2 Output Compare Match A Interrupt Enable
	sei(); // Globale interrupts inschakelen
	OCR2A = 585; // Initialiseer met 15 ms
	while (1) {
		// Blijf in een oneindige lus
	}
	return 0;
}
