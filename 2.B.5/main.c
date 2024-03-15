#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_clear(void);  

// Functie om de initialisatie uit te voeren
void init() {
	DDRC = 0xFF; // Stel alle pinnen van Port C in als uitgangen voor het LCD-scherm
	DDRD = 0xFF; // Stel alle pinnen van Port D in als uitgangen voor het LCD-scherm
	init_4bits_mode(); // Initialiseer het LCD-scherm in 4-bits modus
	lcd_clear(); // Wis het LCD-scherm
}

// Functie om het stuursignaal E van het LCD-scherm te activeren
void lcd_strobe_lcd_e(void) {
	PORTC |= (1 << LCD_E); // Zet de E-pin van het LCD-scherm hoog
	_delay_ms(1); // Wacht 1 milliseconde
	PORTC &= ~(1 << LCD_E); // Zet de E-pin van het LCD-scherm laag
	_delay_ms(1); // Wacht 1 milliseconde
}

// Functie om het LCD-scherm in 4-bits modus te initialiseren
void init_4bits_mode(void) {
	PORTC = 0x00; // Zet alle pinnen van Port C laag

	// Initialisatie volgens 4-bits mode
	PORTC = 0x20; // Verzend instructie voor 4-bits mode
	lcd_strobe_lcd_e(); // Stuur E-signaal om de instructie te bevestigen
	PORTC = 0x20; // Herhaal de instructie
	lcd_strobe_lcd_e(); // Stuur E-signaal om de instructie te bevestigen
	PORTC = 0x80; // Stel LCD-scherm in op 2 regels, 5x7 matrix
	lcd_strobe_lcd_e(); // Stuur E-signaal om de instructie te bevestigen
	PORTC = 0x00; // Schakel display uit
	lcd_strobe_lcd_e(); // Stuur E-signaal om de instructie te bevestigen
	PORTC = 0xF0; // Schakel 4-bits modus in
	lcd_strobe_lcd_e(); // Stuur E-signaal om de instructie te bevestigen
	PORTC = 0x00; // Zet alle pinnen van Port C laag
	lcd_strobe_lcd_e(); // Stuur E-signaal om de instructie te bevestigen
	PORTC = 0x60; // Verzend functie instructie
	lcd_strobe_lcd_e(); // Stuur E-signaal om de instructie te bevestigen
}

// Functie om een commando naar het LCD-scherm te schrijven
void lcd_write_command(unsigned char byte) {
	// Eerste nibble
	PORTC = byte; // Schrijf de eerste nibble naar Port C
	PORTC &= ~(1 << LCD_RS); // Stel RS-pin laag voor commandotransmissie
	lcd_strobe_lcd_e(); // Activeer het E-signaal om het commando te schrijven

	// Tweede nibble
	PORTC = (byte << 4); // Verschuif de tweede nibble naar links
	PORTC &= ~(1 << LCD_RS); // Stel RS-pin laag voor commandotransmissie
	lcd_strobe_lcd_e(); // Activeer het E-signaal om het commando te schrijven
}

// Functie om het LCD-scherm te wissen
void lcd_clear(void) {
	lcd_write_command(0x01); // Stuur het commando om het LCD-scherm te wissen
	_delay_ms(2); // Wacht 2 milliseconden
}

// Functie om de cursorpositie in te stellen op het LCD-scherm
void set_cursor(int position) {
	lcd_write_command(0x80 | (position & 0x7F)); // Stel de cursorpositie in op het LCD-scherm
}