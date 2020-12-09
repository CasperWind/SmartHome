/*
 * init.c
 *
 * Created: 07/12/2020 09.30.05
 *  Author: Wind
 */ 
#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>
void PWM_Init(void)
{
	uint8_t cnt;
	// Compare Output Mode: Fast PWM Mode: Clear OC0A on Compare Match, set OC0A at BOTTOM, non-inverting mode (Table 16-3)
	TCCR3A |= (1<<COM3A1) | (1<<COM3B1) | (1<<COM3C1) | (1<<WGM30);					// data sheet 16.9.1
	
	//Waveform Generation Mode: Mode 3 Fast PWM: WGM0 = 1, WGM1 = 1 (Table 16-8)
	//TCCR3A |= (0<<WGM00) | (0<<WGM01);
	TCCR3B |= (1<<WGM32);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1 (Table 16-9), frekv. = 980Hz
	TCCR3B |= (1<<CS31) | (1<<CS30);		// data sheet 16.9.2
	
	// Set output to OC0A = PB7, see data sheet 16.9.4 and Arduino MEGA pin configuration: (pin 13), same as LED
	DDRE |= (1<<PE4) | (1<<PE5) | (1<<PE3);
}

void ADC_init(void)
{
	ADMUX = (1 << REFS0);	// 5V supply used for ADC reference, select ADC channel 0, datasheet 28.9.1
	DIDR0 = (1 << ADC0D);	// disable digital input on ADC0 pin, datasheet 28.9.6
	// enable ADC, ADC clock = 16MHz / 128 = 125kHz, datasheet 28.9.2
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	sei();
}

void Timer_init(void)
{
	TCCR1B |= (1<<WGM12);				// Mode 4, CTC = WGM10 - WGM13 = 0100, Table 20-6 (page 176)
	TIMSK1 |= (1<<OCIE1A);				// Timer/Counter1, Output Compare A Match Interrupt Enable, 20.15.8 (page 184)
	OCR1A = 62499;	// OCR1A = (Tdelay * F_CPU / N) - 1 => 61.5 gives 1ms => 62499 gives 1s
	TCCR1B |= (1<<CS12); //| (1<<CS10));				// Prescaler: 256, CS=100, Table 20-7 (page 177). Timer starts!
	sei();
	
}

void init(void)
{
	PWM_Init();
	ADC_init();
	Timer_init();
}