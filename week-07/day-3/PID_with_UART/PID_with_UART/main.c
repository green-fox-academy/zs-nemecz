#include "freq_meas.h"
#include "UART_driver.h"
#include "AC_driver.h"
#include "ADC_driver.h"
#include "PWM_pot.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
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
	float ctrler_out_min = 0.0;
	float ctrler_out_max = 255.0;
	float rpm_error;
	float previous_rpm_error = 0;
	float ctrler_out;
	float P = 0.01;
	float I = 0.07;
	float D = 0.02;
	float D_error;
	float integral;
	int cntr = 0;
	float duty_cyle;
	float rpm;
	float ref_rpm = 2500.0;
	
	
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
	
	char command_char[100];
	/*//get ref
	printf("Please set desired RPM: \t");
	gets(command_char);
	ref_rpm = atof(command_char);
	printf("\nreference RPM set to %.2f\n", ref_rpm);*/
	
	//get P
	printf("Please set desired P: \t");
	gets(command_char);
	P = atof(command_char);
	printf("\nP set to %.2f\n", P);
	
	//get I
	printf("Please set desired I: \t");
	gets(command_char);
	I = atof(command_char);
	printf("\nI set to %.2f\n", I);
	
	//get D
	printf("Please set desired D: \t");
	gets(command_char);
	D = atof(command_char);
	printf("\nD set to %.2f\n", D);
	
	_delay_ms(500);
	
	/*while(cntr != 1000) {
		
		OCR2A = 200;
		cntr++;
	}*/
	
	// Infinite loop
	while (1) {
		
		_delay_ms(50);
		rpm = get_rpm();
		printf("measured RPM: %.2f\n", rpm);
		
		rpm_error = ref_rpm - rpm;
		integral = integral + rpm_error;
		D_error = (previous_rpm_error - rpm_error) * D;
		ctrler_out = P * rpm_error + I * integral + D_error;
		//printf("reference RPM is: %.2f\n", ref_rpm);		
		
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
		
		adc_data = ADC_Read();
		ref_rpm = (float)adc_data * 5;
		printf("***Current reference: %.2f***\n", ref_rpm);
	}
}


