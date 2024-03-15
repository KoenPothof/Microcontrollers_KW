/*
 * 2.B.2.c
 *
 * Created: 3/15/2024 10:56:41
 * Author : koenp
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// Interrupt service routine voor externe interrupt 0 (INT0)
ISR(INT0_vect) {
	PORTA <<= 1; // Verschuif de waarde van PORTA één bit naar links
	if (!PORTA) // Controleer of PORTA nul is geworden na het verschuiven
	PORTA = 1; // Als PORTA nul is, stel het in op 1
}

// Interrupt service routine voor externe interrupt 1 (INT1)
ISR(INT1_vect) {
	PORTA >>= 1; // Verschuif de waarde van PORTA één bit naar rechts
	if (!PORTA) // Controleer of PORTA nul is geworden na het verschuiven
	PORTA = 1 << 7; // Als PORTA nul is, stel het in op 0b10000000 (MSB)
}

void initSetup() {
	DDRA = 0xFF; // Stel alle pinnen van Port A in als uitgangen

	EICRA |= 0x0F; // Configureer de External Interrupt Control Register A voor oplopende flank voor INT0 en INT1
	EIMSK |= 0x03; // Stel bits 0 en 1 van External Interrupt Mask Register in om INT0 en INT1 in te schakelen
	sei(); // Schakel de globale interrupt vlag in

	PORTA = 1; // Zet de eerste pin van Port A hoog, de rest laag
}

int main(void) {
	initSetup(); // Voer initiële setup uit

	while (1) {
		// Blijf in een oneindige lus en wacht op interrupts
	}
}

