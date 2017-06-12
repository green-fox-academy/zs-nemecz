/*
 * PWM_project.c
 *
 * Created: 2017.06.12. 10:48:28
 * Author : Vivo
 */ 

#include <avr/io.h>
#define F_CPU	16000000
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "PWM_project.h"
#include "ADC_driver.h"
#include "UART_driver.h"

void system_init()
{	
	//PIND6 as output
	DDRD |= 1 << DDRD6;
	
	// Call the DAC driver init function
	ADC_Init();
	
	UART_Init();
	
}


int main(void)
{
	system_init();
	timer_init();
	uint16_t adc_data;
	
	
	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	
	
    /* Replace with your application code */
    while (1) 
    {
		adc_data = ADC_Read();
		printf("ADC data: %d\r\n", adc_data);
		OCR0A = adc_data >> 2;
		printf("OCRA: %d\r\n", OCR0A);
	
    }
}



