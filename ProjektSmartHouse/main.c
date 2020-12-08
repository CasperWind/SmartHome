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

int ADCskifter = 1;
float ADC_voltage;
double temp;
double tempK;
float tempC;
float yaxe;

ISR(ADC_vect)
{
	unsigned int ADC_data = ADC;
	switch (ADCskifter)
	{
		case 1:
		ADC_voltage = 5.0 * ADC_data / 1024.0;
		temp = log(10000.0 * (1024.0 / ADC_data -1));
		tempK = 1/(0.001129148+(0.000234125+(0.0000000876741*temp*temp))*temp);
		tempC = tempK - 273.15;
		if (tempC > 25)
		{
			OCR3A = 255;
		}
		if (tempC < 23)
		{
			OCR3A = 0;
		}
		ADMUX |= (1<<MUX0);
		ADCskifter = 2;
		break;
		case 2:
		
		//yaxe = ADC_data;
		//ADCskifter = 3;
		//break;
		//case 3:
		//ADMUX &= ~(1<<MUX0);
		////ADMUX |= (1<<MUX1);
		//
		//ADCskifter = 1;
		////ADMUX &= ~(1<<MUX1);
		break;
		default:
		ADCskifter = 1;
		break;
	}
	
	
}

ISR(TIMER1_COMPA_vect)
{
	printf(" %f \n", tempC);
	
}

int main(void)
{
	UartInit();
	
	
	init();
	while (1)
	{
	}
}


