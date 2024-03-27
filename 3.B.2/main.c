#include <avr/io.h>

int main(void) {
	DDRD |= (1 << 7); // Set LED as output
	TCCR1B |= (1 << CS10); // Set up timer

	for (;;) {
		// Check timer value in if statement, true when count matches 15 ms
		if (TCNT1 >= 15000 && TCNT1 < 40000) {
			PORTD &= ~(1 << 7); // Turn the LED off
			} else if (TCNT1 >= 40000) {
			PORTD |= (1 << 7); // Turn the LED on
			TCNT1 = 0; // Reset timer value
		}
	}

	return 0;
}
