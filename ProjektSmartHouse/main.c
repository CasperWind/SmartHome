/*
* ProjektSmartHouse.c
*
* Created: 07/12/2020 08:10
* Author : Wind
*/
#define F_CPU 16E6
#include <stdio.h>
#include "stdio_setup.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "Init/init.h"
#include "Temp/temp.h"



ISR(ADC_vect)
{
	unsigned int ADC_data = ADC;
	ReadTemp(ADC);
}

ISR(TIMER1_COMPA_vect)
{
	printf(" %f \n");
	
}

int main(void)
{
	UartInit();
	
	
	init();
	while (1)
	{
	}
}


