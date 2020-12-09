/*
 * temp.c
 *
 * Created: 08/12/2020 10.54.19
 *  Author: Wind
 */ 
#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>

extern int MUXSwitch;

void StartOrStopMotor(float TempC)
{
	printf("%f \n", TempC);
	if (TempC > 30)
	{
		OCR3A = 255;
	}
	if (TempC < 25)
	{
		OCR3A = 0;
	}
	
}

void ReadTemp(int GetADC)
{
	//ADCSRA &= ~(1<<ADATE);
	//OCR1C = GetADC / 4;
	float ADC_voltage;
	double temp;
	double tempK;
	float tempC;
	unsigned int ADC_data = GetADC;  // Modtager ADC.
	/*
	her beregner vi ADC'en om til tempraturen i C.
	*/
	ADC_voltage = 5.0 * ADC_data / 1024.0;
	temp = log(10000.0 * (1024.0 / ADC_data -1));
	tempK = 1/(0.001129148+(0.000234125+(0.0000000876741*temp*temp))*temp);
	tempC = tempK - 273.15;
	//her kalder vi metoden til at starte motoren hvis der er over 25 grader.
	StartOrStopMotor(tempC);
	
}