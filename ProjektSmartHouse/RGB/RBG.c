/*
 * RBG.c
 *
 * Created: 08/12/2020 12.04.25
 *  Author: Wind
 */ 
#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>

extern int MUXSwitch;

void ReadY(int YADC)
{
	//ADCSRA &= ~(1<<ADATE);
	printf("%d \n", YADC);	
}