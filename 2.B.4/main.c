/*
 * 2.B.4.c
 *
 * Created: 23-2-2024 13:44:11
 * Author : Wessel
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

PATTERN_STRUCT pattern[] = { 
	{0b00100000, 250},
	{0b00010000, 250},
	{0b00001000, 250},
	{0b00000100, 250},
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
	{0b00000000, 250},
};

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

int main( void ) {
	DDRD = 0b11111111;	
	while (1==1) {
		int index = 0;
		while( index < 19) {
			PORTD = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	}
	return 1;
}

