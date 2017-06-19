#include "freq_meas.h"
#include "UART_driver.h"
#include "AC_driver.h"
#include "ADC_driver.h"
#include "PWM_pot.h"
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
#define CNTR_MAX		10


void system_init()
{
	LED_DDR |= 1 << LED_DDR_POS;
	freq_meas_init();
	UART_init();
	ADC_Init();
	FAST_PWM_init();
	AC_driver_init();
	
	sei();
}

int main(void)
{
	uint16_t adc_data;
	float rpm;
	float duty_cycle = 100;
	
	// Don't forget to call the init function :)
	system_init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM((void *)UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, (void *)UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	// Try printf
	printf("Startup...\r\n");

	// Infinite loop
	while (1) {
	
		rpm = get_rpm();
		adc_data = ADC_Read();
		//printf("adc: %d\n", adc_data);
		adc_data = adc_data >> 2;
		
		OCR2A = adc_data;
		printf("OCR2A: %d\n", adc_data);
		
		duty_cycle = ((float)adc_data) / 255 * 100;
		printf("duty cycle: %.2f %%\n", duty_cycle);
		
		//printf("OCR2A: %d\n", OCR2A);
		printf("RPM: %f \n\n", rpm);
		
	}
}

