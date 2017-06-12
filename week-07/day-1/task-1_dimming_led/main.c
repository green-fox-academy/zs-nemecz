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
#include "PWM_project.h"

void system_init()
{
	DDRD |= 1 << DDRD6;
	
}


int main(void)
{
	system_init();
	timer_init();
	
	set_duty_cycle(90);
	
    /* Replace with your application code */
    while (1) 
    {
		//PORTD |= 1 << PORTD6;
    }
}

