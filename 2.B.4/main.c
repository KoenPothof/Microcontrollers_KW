/*
 * 2.B.4.c
 *
 * Created: 23-2-2024 13:44:11
 * Author : Wessel
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

// Definitie van een structuur genaamd PATTERN_STRUCT om patronen en vertragingen op te slaan
typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

// Array van PATTERN_STRUCT om patronen en vertragingen te definiëren
PATTERN_STRUCT pattern[] = {
	{0b00100000, 250}, // Patroon 1: 0b00100000, vertraging 250 ms
	{0b00010000, 250}, // Patroon 2: 0b00010000, vertraging 250 ms
	{0b00001000, 250}, // Patroon 3: 0b00001000, vertraging 250 ms
	{0b00000100, 250}, // enz..
	{0b00000010, 250},
	{0b00000001, 250},
	{0b00110000, 250},
	{0b00011000, 250},
	{0b00001100, 250},
	{0b00000110, 250},
	{0b00000011, 250},
	{0b00100001, 250},
	{0b00111000, 250},
	{0b00011100, 250},
	{0b00001110, 250},
	{0b00000111, 250},
	{0b00000011, 250},
	{0b00000001, 250},
	{0b00000000, 250}, // Patroon 19: 0b00000000, vertraging 250 ms
};

// Functie om te wachten voor een opgegeven aantal milliseconden
void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms(1); // Wacht 1 milliseconde
	}
}

int main(void) {
	DDRD = 0b11111111; // Stel alle pinnen van Port D in als uitgangen

	while (1 == 1) {
		int index = 0;

		while (index < 19) { // Itereer door alle patronen in de array
			PORTD = pattern[index].data; // Stel de data van het huidige patroon in op Port D
			wait(pattern[index].delay); // Wacht de opgegeven vertraging voor het huidige patroon
			index++;
		}
	}
	return 1;
}
