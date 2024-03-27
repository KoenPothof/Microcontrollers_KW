#include <avr/io.h>

int main(void) {
	DDRD |= (1 << 7); // Zet LED als output
	TCCR1B |= (1 << CS10); // Maak timer

	for (;;) {
		// Check of de timer al op 15ms zit
		if (TCNT1 >= 15000 && TCNT1 < 40000) {
			PORTD &= ~(1 << 7); // LED uit
			} else if (TCNT1 >= 40000) { // check of die 15ms al voorbij zijn
			PORTD |= (1 << 7); // LED aan
			TCNT1 = 0; // Reset timer
		}
	}

	return 0;
}