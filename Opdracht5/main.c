/*
 * Opdracht5.c
 *
 * Created: 2-2-2024 10:55:36
 * Author : Wessel
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x01;
	int t = 0;
	int i = 0;

	while (1)
	{
		if(PINC == 1){
			t = 1;
		}
		
		if(t == 1){
			t = 0;
			if (i == 0)
			{
				i = 1;
				while(t == 0){
					PORTD = 0b10000000;
					_delay_ms(1000);
					PORTD = 0b00000000;
					_delay_ms(1000);
					if(PINC == 1){
						t = 1;
					}
				}
			} else if (i == 1)
			{
				i = 0;
				while(t == 0){
					PORTD = 0b10000000;
					_delay_ms(250);
					PORTD = 0b00000000;
					_delay_ms(250);
					if(PINC == 1){
						t = 1;
					}
				}
			}
			
		}
		}
	}