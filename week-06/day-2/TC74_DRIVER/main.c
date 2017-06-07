/*
 * TC74_DRIVER.c
 *
 * Created: 2017.06.07. 11:13:52
 * Author : zsuzska
 */ 

#include <avr/io.h>


#include "TC74_driver.h"
#include "UART_driver.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

#define LED_DDR			DDRB
#define LED_DDR_POS		DDRB5
#define LED_PIN			PINB
#define LED_PIN_POS		PINB5
#define LED_PORT		PORTB
#define LED_PORT_POS	PORTB5

void system_init()
{
	//TODO
	// Call the TWI driver init function
	TWI_init();
	//TODO
	//Init the uart
	UART_init();
	//turn on LED PIN as output
	LED_DDR |= 1 << LED_DDR_POS;
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
	TCCR0B |= 1 << CS02;
	TCCR0B |= 1 << CS00;
	//enable interrupts globally 
	sei();
}

int main(void)
{

	// Don't forget to call the init function :)
	system_init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	
	// Create a variable which will be a counter variable, initialize it with 0.
	uint8_t cntr = 0;
	const uint8_t cntr_max = 30;
	
	//give address
	uint8_t address = TC74A0_address;
	uint8_t temperature = 0;
	// Try printf
	printf("Startup...\r\n");

	// Infinite loop
	while (1) {
		//TODO
		//Write the temperature frequently.

		//TODO
		//Advanced: Don't use delay, use timer.
		if (TIFR0 & (1 << TOV0)) {
			TIFR0 |= 1 << TOV0;
			if (cntr < cntr_max) {
				cntr++;
				} else {
				cntr = 0;
				//Blink the led to make sure the code is running
				temperature = read_temp(address);
				printf("%d\n\r", temperature);
				LED_PIN |= 1 << LED_PIN_POS;
			}
		}
	}
}