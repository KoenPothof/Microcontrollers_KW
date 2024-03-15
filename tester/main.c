/*
 * tester.c
 *
 * Created: 3/15/2024 10:14:51
 * Author : koenp
 */ 

LCD.h:
#ifndef MYMATH_H
#define MYMATH_H

void init();
void display_text(char *str);
void display_integer(int num);
void set_cursor(int position);

#endif

LCD.c:
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_clear(void);

void init() {
	DDRC = 0xFF;
	DDRD = 0xFF;
	init_4bits_mode();
	init_4bits_mode();
	lcd_clear();
}

void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);
	_delay_ms(1);
	PORTC &= ~(1<<LCD_E);
	_delay_ms(1);
}

void init_4bits_mode(void) {
	DDRC = 0xFF;
	PORTC = 0x00;

	PORTC = 0x20;
	lcd_strobe_lcd_e();

	PORTC = 0x20;
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
}

void display_text(char *str) {
	for (; *str; str++) {
		unsigned char byte = *str;
		// First nibble.
		PORTC = byte;
		PORTC |= (1<<LCD_RS);
		lcd_strobe_lcd_e();

		// Second nibble
		PORTC = (byte<<4);
		PORTC |= (1<<LCD_RS);
		lcd_strobe_lcd_e();
	}
}

void display_integer(int num) {
	char buffer[16]; // Buffer voor de omgezette tekenreeks
	sprintf(buffer, "%d", num); // Omzetten van integer naar tekenreeks
	display_text(buffer); // Weergeven van de tekenreeks op het LCD-scherm
}

void lcd_write_command(unsigned char byte)

{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_clear(void) {
	lcd_write_command(0x01);
	_delay_ms(2);
}

void set_cursor(int position) {
	lcd_write_command(0x80 | (position & 0x7F));
}


Main.c:
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main (void){
	
	DDRD = 0b11111111;
	PORTE = 0x01;
	PORTG = 0x01;
	
	init(); //initialiseer lcd
	set_cursor(5);
	
	int i = 0;
	display_integer(i); //zet alvast de 0 op het LCD scherm
	
	while (1) {
		_delay_ms(100);
		if(PINE == 1 && PING == 1){
			while(PINE == 1 && PING == 1){ //wacht totdat te knoppen los worden gelaten
				_delay_ms(10);
			}
			i = 0;
			init(); //reset lcd
			display_integer(i); //display i
			}else if(PINE == 1){
			while(PINE == 1){ //wacht totdat de knop wordt losgelaten
				_delay_ms(10);
			}
			i++;
			init(); //reset lcd
			display_integer(i); //display i
			}else if(PING == 1 && i > 0){ //zorg ervoor dat de i niet in de min kan
			while(PING == 1){ //wacht totdat de knop wordt losgelaten
				_delay_ms(10);
			}
			i--;
			init(); //reset lcd
			display_integer(i); //display i
		}
	}
	return 1;
}
