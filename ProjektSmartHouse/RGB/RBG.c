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
	printf("%d -y\n", YADC);
	OCR1C = YADC / 4;
	OCR1B = YADC / 4;
		
}

void ReadX(int XADC)
{
	printf("%d -x\n", XADC);
	OCR1A = XADC / 4 ;
	
}