#include "PWM_pot.h"
#include <avr/io.h>
#include <stdint.h>

void FAST_PWM_init()
{
	// Set FAST PWM mode, with comparison of OCRA
	TCCR2A |= 1 << WGM21;
	TCCR2A |= 1 << WGM20;
	TCCR2B &= ~(1 << WGM22);
	
	// Clear OC2A on Compare Match, set OC2A at BOTTOM (non-inverting mode)
	TCCR2A |= 1 << COM2A1;
	TCCR2A &= ~(1 << COM2A0);

	// 1024 prescaler
	TCCR2B |= 1 << CS22;
	TCCR2B |= 1 << CS21;
	TCCR2B |= 1 << CS20;

	// Set OCR2A register 
	OCR2A = 255;	// 255 is max duty cycle
	
	// Enable OC2A as output
	DDRB |= 1 << DDRB3;
}

void set_PWM_duty(float duty)
{
	OCR2A = 255 * (float)duty / 100;
}
