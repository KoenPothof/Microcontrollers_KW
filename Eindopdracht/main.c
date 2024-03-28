#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

#define BIT(x)		( 1<<x )
#define DDR_SPI		DDRB					// spi Data direction register
#define PORT_SPI	PORTB					// spi Output register
#define SPI_SCK		1						// PB1: spi Pin System Clock
#define SPI_MOSI	2						// PB2: spi Pin MOSI
#define SPI_MISO	3						// PB3: spi Pin MISO
#define SPI_SS		0						// PB0: spi Pin Slave Select


double seconden = 0;

// wait(): busy waiting for 'ms' millisecond
// used library: util/delay.h
void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

void spi_masterInit(void)
{
	DDR_SPI = 0xff;							// All pins output: MOSI, SCK, SS, SS_display as output
	DDR_SPI &= ~BIT(SPI_MISO);				// 	except: MISO input
	PORT_SPI |= BIT(SPI_SS);				// SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	// or: SPCR = 0b11010010;
	// Enable spi, MasterMode, Clock rate fck/64, bitrate=125kHz
	// Mode = 0: CPOL=0, CPPH=0;
}


// Write a byte from master to slave
void spi_write( unsigned char data )
{
	SPDR = data;							// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 			// Wait for transmission complete
}

// Write a byte from master to slave and read a byte from slave
// nice to have; not used here
char spi_writeRead( unsigned char data )
{
	SPDR = data;							// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 			// Wait for transmission complete
	data = SPDR;							// New received data (eventually, MISO) in SPDR
	return data;							// Return received byte
}

// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{

	PORTB |= BIT(chipNumber);
}

void spi_writeWord (unsigned char adress, unsigned char data){
	spi_slaveSelect(0); // selecteer display chip
	spi_write(adress); // verstuur adres
	spi_write(data); // verstuur data
	spi_slaveDeSelect(0); // deselecteer display chip
}

// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_writeWord(0x09, 0xFF);		// 09: Decode Mode -> 1's = BCD mode for all digits
	
	spi_writeWord(0x0A, 0x0F);		// 0A: Helderheid -> level F (1 t/m F)
	
	spi_writeWord(0x0B, 0x0F);		// 0B: Scan-limiet -> Digits 0 t/m 3
	
	spi_writeWord(0x0C, 0x01);		// 0C: Afsluiten -> 1 = normaal
}

// Set display on ('normal operation')
void displayOn()
{
	spi_writeWord(0x0C, 0x01); // Afsluiten -> 1 = normaal
}

// Set display off ('shut down')
void displayOff()
{
	spi_writeWord(0x0C, 0x00); // Afsluiten -> 1 = normaal
}

void writeLedDisplay(int value){
	
	// alle digits op -1 zodat je straks kan kijken of deze veranderd worden
	int digit1 = -1;
	int digit2 = -1;
	int digit3 = -1;
	char digit4 = -1;
	
	
	// aan de hand van de value worden de cijfers gesplitst in de digits, bij negatieve value worden de cijfers een digit opgeschoven en komt er een min-teken voor
	if (value < 10 && value >= 0){
		digit4 = value;
		} else if (value >= 10 && value < 100){
		digit4 = value / 10;
		digit3 = value % 10;
		} else if (value >= 100 && value < 1000){
		digit4 = value / 100;
		digit3 = (value / 10) % 10;
		digit2 = value % 10;
		} else if (value >= 1000 && value < 10000){
		digit4 = value / 1000;
		digit3 = (value / 100) % 10;
		digit2 = (value / 10) % 10;
		digit1 = value % 10;
		}  else if (value < 0 && value > -10){
		digit4 = 0x0F; // hier moet eigenlijk een - teken staan
		value = (value * -1);
		digit3 = value;
		} else if (value <= -10 && value > -100){
		digit4 = 0x0F; // hier moet eigenlijk een - teken staan
		value = (value * -1);
		digit3 = value / 10;
		digit2 = value % 10;
		} else if (value <= -100 && value > -1000){
		digit4 = 0x0F; // hier moet eigenlijk een - teken staan
		value = (value * -1);
		digit3 = value / 100;
		digit2 = (value / 10) % 10;
		digit1 = value % 10;
	}
	
	// check of de digits zijn veranderd en print ze dan
	if (digit1 != -1){
		spi_writeWord(1, digit1);
		_delay_ms(10);
		} else {
		spi_writeWord(1, 0x0F);
		_delay_ms(10);
	}
	if (digit2 != -1){
		spi_writeWord(2, digit2);
		_delay_ms(10);
		} else {
		spi_writeWord(2, 0x0F);
		_delay_ms(10);
	}
	if (digit3 != -1){
		spi_writeWord(3, digit3);
		_delay_ms(10);
		} else {
		spi_writeWord(3, 0x0F);
		_delay_ms(10);
	}
	if (digit4 != -1){
		spi_writeWord(4, digit4);
		_delay_ms(10);
		} else {
		spi_writeWord(4, 0x0F);
		_delay_ms(10);
	}
}

void timerStart(){
	PORTC = 0x01;
	TCCR1B |= ((1 << CS10 ) | (1 << CS11 )); // maak timer Fcpu/64

	for (;;) {
		// Wacht tot de timer op 1 seconden zit, dan true
		if (TCNT1 >= 62496) {
			TCNT1 = 0; // Reset timer
			seconden+=0.5;
			writeLedDisplay(seconden);
		}
		if(PINC == 1){
			seconden = 0;
		}
	}
}

int main()
{
	// inilialize
	DDRB=0x01;					  	// Set PB0 pin as output for display select
	spi_masterInit();              	// Initialize spi module
	displayDriverInit();            // Initialize display chip
	timerStart();
		
	
		
	
	return (1);
}


