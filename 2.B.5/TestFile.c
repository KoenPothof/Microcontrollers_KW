/*
 * TestFile.c
 *
 * Created: 1-3-2024 12:37:07
 *  Author: Wessel
 */ 
#include <util/delay.h>
#include "main.h"

int main(void) {
	// Initialisatie en weergave van de tekst "Dirk" op positie 2 van het LCD-scherm
	init(); // Initialiseer het LCD-scherm
	set_cursor(2); // Stel de cursorpositie in op 2
	//display_text("Dirk");
	_delay_ms(20000); // Wacht 20 seconden

	// Initialisatie en weergave van de tekst "Frans" op positie 5 van het LCD-scherm
	init(); // Initialiseer het LCD-scherm opnieuw (elke keer opnieuw om zeker te zijn van de staat)
	set_cursor(5); // Stel de cursorpositie in op 5
	//display_text("Frans");
	_delay_ms(20000); // Wacht 20 seconden

	// Initialisatie en weergave van de tekst "Geert" op positie 1 van het LCD-scherm
	init(); // Initialiseer het LCD-scherm opnieuw
	set_cursor(1); // Stel de cursorpositie in op 1
	//display_text("Geert");
	_delay_ms(20000); // Wacht 20 seconden

	return 1;
}
