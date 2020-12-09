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
int printfY;
int printfX;

ISR(ADC_vect)
{
	cli();
	//ADCSRA &= ~(1<<ADATE) & ~(1<<ADSC);
	unsigned int ADC_data;
	unsigned int ADCTILY;
	unsigned int ADCTILX;
		switch (MUXSwitch)
		{
			case 1:
			ADC_data = ADC;
			ReadTemp(ADC_data);
			MUXSwitch = 2;
			break;
			case 2:
			ADCTILY = ADC;
			printfY = ADC;
			ReadY(ADCTILY);
			MUXSwitch = 3;
			break;
			case 3:
			ADCTILX = ADC;
			printfX = ADC;
			ReadX(ADCTILX);
			MUXSwitch ++;
			break;
			default:
			break;
		}
	
	switchMux(MUXSwitch);
}

ISR(TIMER1_COMPA_vect)
{
	//printf("%d -y\n", printfY);
	//printf("%d -x\n", printfX);
	//printf("---------------------------\n");
		
}

int main(void)
{
	UartInit();
	
	init();
	MUXSwitch = 0;
	switchMux(MUXSwitch);
	while (1)
	{			
	}
}


