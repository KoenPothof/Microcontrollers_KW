/*
 * tester.c
 *
 * Created: 3/15/2024 10:14:51
 * Author : koenp
 */ 

#include <avr/io.h>

// Inclusie van de nodige headers
#include <util/delay.h> // Voor delay functies
#include "main.h" // Voor functiedeclaraties en macrodefinities

// Definitie van de main-functie
int main(void) {
	// Initialisatie en weergave van de tekst "Dirk" op positie 2 van het LCD-scherm
	init(); // Initialiseer het LCD-scherm
	set_cursor(2); // Stel de cursorpositie in op 2
	display_text("Dirk"); // Toon de tekst "Dirk"
	_delay_ms(20000); // Wacht 20 seconden

	// Initialisatie en weergave van de tekst "Frans" op positie 5 van het LCD-scherm
	init(); // Initialiseer het LCD-scherm opnieuw (elke keer opnieuw om zeker te zijn van de staat)
	set_cursor(5); // Stel de cursorpositie in op 5
	display_text("Frans"); // Toon de tekst "Frans"
	_delay_ms(20000); // Wacht 20 seconden

	// Initialisatie en weergave van de tekst "Geert" op positie 1 van het LCD-scherm
	init(); // Initialiseer het LCD-scherm opnieuw
	set_cursor(1); // Stel de cursorpositie in op 1
	display_text("Geert"); // Toon de tekst "Geert"
	_delay_ms(20000); // Wacht 20 seconden

	return 1; // Geef 1 terug om aan te geven dat het programma succesvol is afgerond
}
