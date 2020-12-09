/*
 * SwitchADMUX.c
 *
 * Created: 08/12/2020 12.08.45
 *  Author: Wind
 */ 
#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

extern int MUXSwitch;

void switchMux()
{
	switch (MUXSwitch)
	{
		case 1:		
		ADMUX &= ~(1<<MUX0);		
		_delay_ms(500);	
		sei();
		break;
		case 2:
		ADMUX |= (1<<MUX0);
		_delay_ms(500);
		sei();
		break;	
		case 3:
		ADMUX &= ~(1<<MUX0);
		ADMUX |= (1<<MUX1);		
		_delay_ms(500);
		sei();
		break;	
		default:				
		MUXSwitch = 1;
		ADMUX &= ~(1<<MUX0);
		_delay_ms(500);
		sei();
		break;
	}
}