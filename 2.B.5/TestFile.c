/*
 * TestFile.c
 *
 * Created: 1-3-2024 12:37:07
 *  Author: Wessel
 */ 
#include <util/delay.h>
#include "main.h"

int main (void){
	init();
	set_cursor(2);
	display_text("Dirk");
	_delay_ms(20000);
	
	init();
	set_cursor(5);
	display_text("Frans");
	_delay_ms(20000);
	
	init();
	set_cursor(1);
	display_text("Geert");
	_delay_ms(20000);
	
	return 1;
}