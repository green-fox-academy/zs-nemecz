#include "ADC_driver.h"
#include <avr/io.h>
#include <stdint.h>

void ADC_Init() {
	// TODO:
	// Set the reference voltage to AVcc.
	ADMUX &= ~(1 << REFS1);
	ADMUX |= 1 << REFS0;
	// TODO:
	// Set the data format to right adjusted, so the bottom 8bits will be in ADCL register
	ADMUX &= ~(1 << ADLAR);
	// TODO:
	// Set the used channel. Use the definitions from ADC_driver.h!
	ADMUX &= ~(1 << MUX3);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX0);
	// TODO:
	// Set the prescaler. Use the definitions from ADC_driver.h!
	ADCSRA |= 1 << ADPS0;
	ADCSRA |= 1 << ADPS1;
	ADCSRA |= 1 << ADPS2;
	// TODO:
	// Enable the ADC peripheral
	ADCSRA |= 1 << ADEN;
}

uint16_t ADC_Read() {
	// TODO:
	// Start a conversion with ADSC bit setup
	ADCSRA |= 1 << ADSC;
	// TODO:
	// Wait for the conversion to finish by checking ADSC bit
	while(!(ADCSRA & (1 << ADIF)));
	// TODO:
	// return with the read data, use the "ADC" register!
	uint16_t data = ADC;
	return data;
}
