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

#define PASS_THRESHOLD 20

#define TRIGGER_PIN 1     // The GPIO pin connected to the trigger pin of the ultrasonic sensor
#define ECHO_PIN 0        // The GPIO pin connected to the echo pin of the ultrasonic sensor
#define LED_PIN PA0

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

void initUltrasonic() {
	DDRD |= (1 << TRIGGER_PIN); // Set trigger pin as output
	DDRD &= ~(1 << ECHO_PIN);   // Set echo pin as input
}

void triggerPulse() {
	PORTD |= (1 << TRIGGER_PIN); // Set trigger pin high
	_delay_us(10);               // Wait for 10 microseconds
	PORTD &= ~(1 << TRIGGER_PIN);// Set trigger pin low
}

uint16_t measureDistance() {
	uint16_t pulse_width = 0;
	uint32_t timeout = 10000; // Set a timeout value (adjust as needed)

	// Wait for echo pin to go high
	while (!(PIND & (1 << ECHO_PIN)) && timeout > 0) {
		timeout--;
		_delay_us(2);
	}

	// Measure pulse width
	while ((PIND & (1 << ECHO_PIN)) && timeout > 0) {
		pulse_width++;
		_delay_us(2);
	}

	return pulse_width; // Return the pulse width
}

// LED aan
void ledOn(){
	PORTA |= (1 << LED_PIN); // zet de LED aan
}

// LED uit
void ledOff(){
	PORTA &= ~(1 << LED_PIN); // zet de LED uit
}

void timerStart(){
	 PORTC = 0x01;
	 DDRE = 0x0F;

	 TCCR1B |= ((1 << CS10 ) | (1 << CS11 )); // Set timer Fcpu/64

	 for (;;) {
		 if (TCNT1 >= 62496) {
			 TCNT1 = 0; // Reset timer
			 seconden += 0.5; // You should initialize 'seconden' somewhere
			 writeLedDisplay(seconden);
		 }

		 triggerPulse(); // Send trigger pulse

		 uint16_t pulse_width = measureDistance(); // Measure echo pulse width

		 uint16_t distance = pulse_width/58; // Convert pulse width to distance in cm

		if (seconden==2){
			ledOff();
		}
		 if (distance < 10) { // Threshold distance
			 PORTE = 0b00000000; // Turn off LEDs
			 seconden = 0; // Reset the counter
			 ledOn();
			 
			 } else {
			 PORTE = 0b11111111; // Turn on LEDs
		 }
	 }
}

int main()
{
	DDRA |= (1 << LED_PIN);
	// inilialize
	spi_masterInit();              	// Initialize spi module
	displayDriverInit();            // Initialize display chip
	initUltrasonic();
	timerStart();
		
	
	return (1);
}

