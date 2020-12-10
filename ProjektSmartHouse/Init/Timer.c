/*
 * Timer.c
 *
 * Created: 01/12/2020 13.34.59
 *  Author: Wind
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


void Timer_init(void)
{
	TCCR1B |= (1<<WGM12);				// Mode 4, CTC = WGM10 - WGM13 = 0100, Table 20-6 (page 176)
	TIMSK1 |= (1<<OCIE1A);				// Timer/Counter1, Output Compare A Match Interrupt Enable, 20.15.8 (page 184)
	OCR1A = 62499;	// OCR1A = (Tdelay * F_CPU / N) - 1 => 61.5 gives 1ms => 62499 gives 1s
	TCCR1B |= (1<<CS12); //| (1<<CS10));				// Prescaler: 256, CS=100, Table 20-7 (page 177). Timer starts!
	sei();
	
}