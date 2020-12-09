/*
 * SwitchADMUX.c
 *
 * Created: 08/12/2020 12.08.45
 *  Author: Wind
 */ 
#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>

extern int MUXSwitch;

void switchMux()
{
	switch (MUXSwitch)
	{
		case 1:	
		//printf("Case1 i Switch: %d\n", MUXSwitch);	
		ADMUX &= ~(1<<MUX0);
		ADCSRA |= (1<<ADATE) | (1<<ADSC);
		MUXSwitch ++;
		break;
		case 2:
		//printf("Case2 i Switch: %d\n", MUXSwitch);
		ADMUX |= (1<<MUX0);
		ADCSRA |= (1<<ADATE) | (1<<ADSC);
		MUXSwitch ++;
		break;		
		default:
		MUXSwitch = 1;
		break;
	}
}