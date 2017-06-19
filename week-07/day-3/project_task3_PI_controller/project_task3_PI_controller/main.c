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

float rpm;

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
	float ref_rpm = 1500.0;
	float ctrler_out_min = 0.0;
	float ctrler_out_max = 255.0;
	float rpm_error;
	float ctrler_out;
	float P = 0.99;
	float I = 0.8;
	float integral;
	int cntr = 0;
	float duty_cyle;
	
	
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
	while(cntr != 1000) {
		OCR2A = 255;
		cntr++;
		printf("cntr: %d\n", cntr);
	}
	
	// Infinite loop
	while (1) {
		_delay_ms(12);
		rpm = get_rpm();
		printf("RPM: %.2f\n", rpm);
		
		rpm_error = ref_rpm - rpm;
		integral = integral + rpm_error;
		ctrler_out = P * rpm_error + I * integral;

		if (ctrler_out < ctrler_out_min) {
			ctrler_out = ctrler_out_min;
			integral = integral - rpm_error;
		}
		else if (ctrler_out > ctrler_out_max) {
			ctrler_out = ctrler_out_max;
			integral = integral - rpm_error;
		}
		
		OCR2A = (uint8_t)ctrler_out;
		
		duty_cyle = ((float) ctrler_out) / 255 * 100;
		printf("Duty Cycle : %.2f\n\n", duty_cyle);
	}
}

