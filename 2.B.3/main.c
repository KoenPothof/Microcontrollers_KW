#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

// Array met binair gecodeerde cijfers en letters voor een 7-segment display
const unsigned char Numbers[17] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
	0b01111001, // E
};

// Functie om een bepaald cijfer/teken weer te geven op een 7-segment display
void display(int digit) {
	PORTD = Numbers[digit]; // Toon het cijfer/teken op het 7-segment display
}

int main(void) {
	DDRD = 0b11111111; // Stel alle pinnen van Port D in als uitgangen (voor het 7-segment display)
	PORTC = 0x01; // Zet de interne pull-up weerstanden voor pin PC0 aan
	PORTB = 0x01; // Zet de interne pull-up weerstanden voor pin PB0 aan

	int i = 0;

	while (1) {
		// Incrementeer de waarde als de knop op pin PC0 (PINC == 1) wordt ingedrukt
		if (PINC == 1) {
			i++;
			_delay_ms(400); // Wacht 400 milliseconden om debounce te voorkomen
		}
		
		// Decrementeer de waarde als de knop op pin PB0 (PINB == 1) wordt ingedrukt
		if (PINB == 1) {
			if (i > 0) {
				i--;
				_delay_ms(400); // Wacht 400 milliseconden om debounce te voorkomen
			}
		}

		
		if (i > 15) {
			i = 16;
		}

		// Reset de waarde naar 0 als beide knoppen tegelijkertijd worden ingedrukt
		if (PINB == 1 && PINC == 1) {
			i = 0;
			_delay_ms(400); // Wacht 400 milliseconden om debounce te voorkomen
		}

		display(i); // Geef de huidige waarde weer op het 7-segment display
	}
	return 1;
}
