#include <avr/io.h>
#define F_CPU	16000000
#include <avr/delay.h>
#include <avr/interrupt.h>

void timer_init()
{
	//Set clock select bits: /1024
	TCCR0B |= 1 << CS02;
	TCCR0B &= ~(1 << CS01);
	TCCR0B |= 1 << CS00;
	
	//Set FAST PWM - non-inverting mode
	TCCR0A |= 1 << COM0A1;
	TCCR0A &= ~(1 << COM0A0);
	
	//Toggle on compare
	//TCCR0B |= 1 << WGM02;
	
	// Set OC register to fast phase, with TOP in OCR0A
	TCCR0A |= 1 << WGM00;
	TCCR0A |= 1 << WGM01;
	TCCR0A &= ~(1 << WGM02);
	
	OCR0A = 255;

	// Enable OCR0A interrupt
	TIMSK0 |= 1 << OCIE0A;

	// Enable interrupts globally
	sei();
}

int set_duty_cycle(uint8_t duty_cycle)
{
	if ((duty_cycle > 100) || (duty_cycle < 0)) {
		return -1;
	} else {
		OCR0A = ((float)duty_cycle / 100) * 255;
		return 1;
	}
}
