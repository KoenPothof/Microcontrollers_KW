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

