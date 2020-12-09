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
#include "RGB/RGB.h"
#include "SwitchADMUX/SwitchADMUX.h"
//Denne variabel bruger vi til at switche på nede i ISR(ADC_vetc)
int MUXSwitch;

ISR(ADC_vect)
{
	ADCSRA &= ~(1<<ADATE) & ~(1<<ADSC);
	unsigned int ADC_data;
	unsigned int ADCTILY;
		switch (MUXSwitch)
		{
			case 1:
			ADC_data = ADC;
			//printf("Case1 i ISR %d \n", MUXSwitch);
			ReadTemp(ADC_data);
			break;
			case 2:
			ADCTILY = ADC;
			//printf("Case2 i ISR %d\n", MUXSwitch);
			ReadY(ADCTILY);
			break;
			
			default:
			break;
		}
	
	
}

ISR(TIMER1_COMPA_vect)
{
	
	
}

int main(void)
{
	UartInit();
	
	init();
	while (1)
	{	
		switchMux(MUXSwitch);	
	}
}


