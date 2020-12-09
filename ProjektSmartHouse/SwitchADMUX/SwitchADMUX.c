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
		ADMUX &= 0xF8;				//clear analog channel
		ADMUX &= ~(1<<MUX0);		//setter ny analog channel
		_delay_ms(50);	
		sei();
		break;
		case 2:
		ADMUX &= 0xF8;				//clear analog channel
		ADMUX |= (1<<MUX0);			//setter ny analog channel
		_delay_ms(50);
		sei();
		break;	
		case 3:
		ADMUX &= 0xF8;				//clear analog channel
		ADMUX |= (1<<MUX1);			//setter ny analog channel
		_delay_ms(50);
		sei();
		break;	
		default:				
		MUXSwitch = 1;
		ADMUX &= 0xF8;				//clear analog channel
		ADMUX &= ~(1<<MUX0);		//setter ny analog channel
		_delay_ms(50);
		sei();
		break;
	}
}