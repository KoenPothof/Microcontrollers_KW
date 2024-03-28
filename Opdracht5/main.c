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
	DDRD = 0xFF; // Stel alle pinnen van Port D in als uitgangen
	PORTD = 0x01; // Stel de eerste pin van Port D hoog, de rest laag
	int t = 0;
	int i = 0;

	while (1)
	{
		if(PINC == 1){ // Controleer of de waarde op pin 0 van Port C gelijk is aan 1
			t = 1;
		}
		
		if(t == 1){ // Als t gelijk is aan 1 (knop is ingedrukt)
			t = 0;
			if (i == 0) // Controleer of de modus i gelijk is aan 0
			{
				i = 1;
				while(t == 0){ // Voer een knipperende lus uit zolang t gelijk is aan 0 (knop niet ingedrukt)
					PORTD = 0b10000000; // Zet de meest significante bit van Port D hoog, andere pinnen laag
					_delay_ms(1000); // Wacht 1000 milliseconden
					PORTD = 0b00000000; // Zet alle pinnen van Port D laag
					_delay_ms(1000); // Wacht 1000 milliseconden
					if(PINC == 1){ // Controleer of de knop is ingedrukt
						t = 1;
					}
				}
			}
			else if (i == 1) // Als i gelijk is aan 1
			{
				i = 0;
				while(t == 0){ // Voer een knipperende lus uit zolang t gelijk is aan 0 (knop niet ingedrukt)
					PORTD = 0b10000000; // Zet de meest significante bit van Port D hoog, andere pinnen laag
					_delay_ms(250); // Wacht 250 milliseconden
					PORTD = 0b00000000; // Zet alle pinnen van Port D laag
					_delay_ms(250); // Wacht 250 milliseconden
					if(PINC == 1){ // Controleer of de knop is ingedrukt
						t = 1;
					}
				}
			}
		}
	}
	return 0;
}
