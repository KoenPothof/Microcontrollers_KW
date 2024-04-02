#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

#define BIT(x)		( 1<<x )
#define DDR_SPI		DDRB					// SPI-data richtingsregister
#define PORT_SPI	PORTB					// SPI-uitvoerregister
#define SPI_SCK		1						// PB1: SPI-pin Systeemklok
#define SPI_MOSI	2						// PB2: SPI-pin MOSI
#define SPI_MISO	3						// PB3: SPI-pin MISO
#define SPI_SS		0						// PB0: SPI-pin Slave Select

#define PASS_THRESHOLD 20

#define TRIGGER_PIN 1     // De GPIO-pin verbonden met de trigger-pin van de ultrasone sensor
#define ECHO_PIN 0        // De GPIO-pin verbonden met de echo-pin van de ultrasone sensor
#define LED_PIN PA0

double seconden = 0;

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

void spi_masterInit(void)
{
	DDR_SPI = 0xff;							// Alle pinnen output: MOSI, SCK, SS, SS_display als output
	DDR_SPI &= ~BIT(SPI_MISO);				// Behalve: MISO input
	PORT_SPI |= BIT(SPI_SS);				// SS_ADC == 1: deselecteer slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	// of: SPCR = 0b11010010;
}

void spi_write( unsigned char data )
{
	SPDR = data;							// Laad byte naar Data-register --> start transmissie
	while( !(SPSR & BIT(SPIF)) ); 			// Wacht op voltooide transmissie
}

void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

void spi_writeWord (unsigned char adress, unsigned char data){
	spi_slaveSelect(0); // Selecteer display chip
	spi_write(adress); // Verstuur adres
	spi_write(data); // Verstuur data
	spi_slaveDeSelect(0); // Deselecteer display chip
}

void displayDriverInit()
{
	spi_writeWord(0x09, 0xFF);		// 09: Decode Mode -> 1's = BCD mode voor alle cijfers
	spi_writeWord(0x0A, 0x0F);		// 0A: Helderheid -> level F (1 t/m F)
	spi_writeWord(0x0B, 0x0F);		// 0B: Scan-limiet -> Digits 0 t/m 3
	spi_writeWord(0x0C, 0x01);		// 0C: Afsluiten -> 1 = normaal
}

void displayOn()
{
	spi_writeWord(0x0C, 0x01); // Afsluiten -> 1 = normaal
}

void displayOff()
{
	spi_writeWord(0x0C, 0x00); // Afsluiten -> 1 = normaal
}

void writeLedDisplay(int value){
	int digit1 = -1;
	int digit2 = -1;
	int digit3 = -1;
	char digit4 = -1;
	
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
		digit4 = 0x0F; // Hier moet eigenlijk een - teken staan
		value = (value * -1);
		digit3 = value;
		} else if (value <= -10 && value > -100){
		digit4 = 0x0F; // Hier moet eigenlijk een - teken staan
		value = (value * -1);
		digit3 = value / 10;
		digit2 = value % 10;
		} else if (value <= -100 && value > -1000){
		digit4 = 0x0F; // Hier moet eigenlijk een - teken staan
		value = (value * -1);
		digit3 = value / 100;
		digit2 = (value / 10) % 10;
		digit1 = value % 10;
	}
	
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
	DDRD |= (1 << TRIGGER_PIN); // Zet trigger-pin als output
	DDRD &= ~(1 << ECHO_PIN);   // Zet echo-pin als input
}

void triggerPulse() {
	PORTD |= (1 << TRIGGER_PIN); // Zet trigger-pin hoog
	_delay_us(10);               // Wacht 10 microseconden
	PORTD &= ~(1 << TRIGGER_PIN);// Zet trigger-pin laag
}

uint16_t measureDistance() {
	uint16_t pulse_width = 0;
	uint32_t timeout = 10000; // Zet een time-out waarde (aanpassen indien nodig)

	// Wacht tot echo-pin hoog wordt
	while (!(PIND & (1 << ECHO_PIN)) && timeout > 0) {
		timeout--;
		_delay_us(2);
	}

	// Meet pulsbreedte
	while ((PIND & (1 << ECHO_PIN)) && timeout > 0) {
		pulse_width++;
		_delay_us(2);
	}

	return pulse_width; // Geef de pulsbreedte terug
}

void ledOn(){
	PORTA |= (1 << LED_PIN); // Zet de LED aan
}

void ledOff(){
	PORTA &= ~(1 << LED_PIN); // Zet de LED uit
}

void timerStart(){
	PORTC = 0x01;
	DDRE = 0x0F;

	TCCR1B |= ((1 << CS10 ) | (1 << CS11 )); // Zet timer op Fcpu/64

	for (;;) {
		if (TCNT1 >= 62496) {
			TCNT1 = 0; // Reset timer
			seconden += 0.5; // Initialiseer 'seconden' ergens
			writeLedDisplay(seconden);
		}

		triggerPulse(); // Stuur trigger-puls

		uint16_t pulse_width = measureDistance(); // Meet echo-pulsbreedte

		uint16_t distance = pulse_width/58; // Converteer pulsbreedte naar afstand in cm

		if (seconden==2){
			ledOff();
		}
		if (distance < 10) { // Drempelafstand
			PORTE = 0b00000000; // Zet LEDs uit
			seconden = 0; // Reset de teller
			ledOn();
			
			} else {
			PORTE = 0b11111111; // Zet LEDs aan
		}
	}
}

int main()
{
	DDRA |= (1 << LED_PIN);
	// Initialiseer
	spi_masterInit();              	// Initialiseer spi-module
	displayDriverInit();            // Initialiseer display-chip
	initUltrasonic();
	timerStart();
	
	
	return (1);
}
