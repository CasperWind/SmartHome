/*
 * ADC.c
 *
 * Created: 01/12/2020 13.33.11
 *  Author: Wind
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init(void)
{
	ADMUX = (1 << REFS0);	// 5V supply used for ADC reference, select ADC channel 0, datasheet 28.9.1
	DIDR0 = (1 << ADC0D);	// disable digital input on ADC0 pin, datasheet 28.9.6
	// enable ADC, start ADC, Enable Interrupt, ADC clock = 16MHz / 128 = 125kHz, datasheet 28.9.2
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	sei();
}