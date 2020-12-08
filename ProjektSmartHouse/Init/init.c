/*
 * init.c
 *
 * Created: 07/12/2020 09.30.05
 *  Author: Wind
 */ 
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

void init(void)
{
	PWM_Init();
	ADC_init();
	Timer_init();
}