/**
\file avr_utils.h
\brief Library for Utility Functions

\verbatim

Created: 01-08-2020 09:20:10 PM
Author : Arnab Kumar Das
Website: www.ArnabKumarDas.com
Microcontroller Supported: ATmega48A/PA/88A/PA/168A/PA/328/P or Arduino UNO/NANO/MINI

Copyright (c) 2014-2020 Arnab Kumar Das
You may freely modify and share this code, as long as you keep this
notice intact (including the links above).
Licensed under the Creative Commons BY-SA 3.0 license:

  http://creativecommons.org/licenses/by-sa/3.0/

Disclaimer: To the extent permitted by law, Arnab Kumar Das provides this work
without any warranty.  It might be defective, in which case you agree
to be responsible for all resulting costs and damages.

                +-\/-+
          PC6  1|    |28  PC5 (A5/ADC5)
RXD  (D0) PD0  2|    |27  PC4 (A4/ADC4)
TXD  (D1) PD1  3|    |26  PC3 (A3/ADC3)
     (D2) PD2  4|    |25  PC2 (A2/ADC2)
PWM  (D3) PD3  5|    |24  PC1 (A1/ADC1)
XCK  (D4) PD4  6|    |23  PC0 (A0/ADC0)
          VCC  7|    |22  GND
          GND  8|    |21  AREF
          PB6  9|    |20  AVCC
          PB7 10|    |19  PB5 (D13)
OC0B (D5) PD5 11|    |18  PB4 (D12)
OC0A (D6) PD6 12|    |17  PB3 (D11) PWM
     (D7) PD7 13|    |16  PB2 (D10) PWM
     (D8) PB0 14|    |15  PB1 (D9)  PWM
                +----+

\endverbatim

*/

#ifndef AVR_UTILS_H_
#define AVR_UTILS_H_

#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#pragma message ( "avr_utils.h included" )

/**
 *  \brief Public Function to Reverse a Buffer of Size Length
 *  
 *  \param [in,out] Buffer : Pointer to Memory Location to Store Data
 *  \param [in] Size : Variable to Store Length of Buffer
 *  \return void
 */
void UTILS_ReverseBuffer(uint8_t *Buffer, size_t Size)
{
	uint8_t ch;
	uint8_t *begin_ptr = Buffer;
	uint8_t *end_ptr = Buffer + Size - 1;
	for (size_t i = 0; i < Size / 2; i++)
	{
		ch = *end_ptr;
		*end_ptr = *begin_ptr;
		*begin_ptr = ch;
		begin_ptr++;
		end_ptr--;
	}
}

/**
 *  \brief Public Function to Reverse a string Data
 *  
 *  \param [in,out] Buffer : Pointer to Memory Location to Store string Data
 *  \return void
 */
void UTILS_ReverseString(char *Buffer)
{
	size_t size;
	char ch;
	char *begin_ptr = Buffer;
	char *end_ptr = Buffer;
	while (*++end_ptr);
	size = end_ptr - begin_ptr; 
	for (size_t i = 0; i < size / 2; i++)
	{
		ch = *end_ptr;
		*end_ptr = *begin_ptr;
		*begin_ptr = ch;	
		begin_ptr++;
		end_ptr--;
	}
}

/**
 *  \brief Public Function to Convert an int Data into a string Data
 *  
 *  \param [in] Number : Variable to Store int Data
 *  \param [out] Buffer : Pointer to Memory Location to Store string Data
 *  \return Length of string Data
 */
uint8_t UTILS_IntToString(int Number, char *Buffer)
{
	uint8_t i = 0;
	uint8_t sign = 0;
	if (Number < 0)
	{
		Number *= -1;
		sign = 1;
	}
	do
	{
		Buffer[i++] = Number % 10 + '0';
	}
	while ((Number /= 10) > 0);
	if (sign == 1)
	{
		Buffer[i++] = '-';
	}
	UTILS_ReverseBuffer((uint8_t*)Buffer,i);
	Buffer[i] = '\0';
	return i;
}

/**
 *  \brief Public Function to Convert an long Data into a string Data
 *  
 *  \param [in] Number : Variable to Store long Data
 *  \param [out] Buffer : Pointer to Memory Location to Store string Data
 *  \return Length of string Data
 */
uint8_t UTILS_LongToString(long Number, char *Buffer)
{
	uint8_t i = 0;
	uint8_t sign = 0;
	if (Number < 0)
	{
		Number *= -1;
		sign = 1;
	}
	do
	{
		Buffer[i++] = Number % 10 + '0';
	}
	while ((Number /= 10) > 0);
	if (sign == 1)
	{
		Buffer[i++] = '-';
	}
	UTILS_ReverseBuffer((uint8_t*)Buffer,i);
	Buffer[i] = '\0';
	return i;
}

/**
 *  \brief Public Function to Convert an float Data into a string Data
 *  
 *  \param [in] Number : Variable to Store float Data
 *  \param [out] Buffer : Pointer to Memory Location to Store string Data
 *  \param [in] Precision : Variable to Store Precision of Decimal Number
 *  \return Length of string Data
 */
uint8_t UTILS_FloatToString(float Number, char *Buffer, uint8_t Precision)
{
	int ipart = (int)Number;
	float fpart = Number - (float)ipart;
	size_t length1 = UTILS_IntToString(ipart,Buffer);
	if (Precision != 0) 
	{
		Buffer[length1] = '.';
	}
	if ((fpart < 0.1 && fpart > 0.0) || (fpart < -0.0 && fpart > -1.0))
	{
		length1++;
		Buffer[length1] = '0';
	}
	fpart = fpart * pow(10, Precision);
	fpart = abs(fpart);
	size_t length2 = UTILS_IntToString((int)fpart,Buffer+length1+1);
	Buffer[length1 + 1 + length2] = '\0';
	return length1 + 1 + length2;
}

/**
 *  \brief Public Function to Convert an string Data into a int Data
 *  
 *  \param [in] Buffer : Pointer to Memory Location to Store string Data
 *  \return Converted int Data
 */
int UTILS_StringToInt(char* Buffer)
{
	uint8_t sign = 0;
	int number = 0;
	if (*Buffer == '-')
	{
		sign = 1;
		Buffer++;
	}
	while (*Buffer)
	{
		number = number*10 + (*Buffer -'0');
		Buffer++;
	}
	if (sign)
	{
		number = (-1) * number;
	}
	return number;
}

/**
 *  \brief Public Function to Convert an string Data into a long Data
 *  
 *  \param [in] Buffer : Pointer to Memory Location to Store string Data
 *  \return Converted long Data
 */
int UTILS_StringToLong(char* Buffer)
{
	uint8_t sign = 0;
	long number = 0;
	if (*Buffer == '-')
	{
		sign = 1;
		Buffer++;
	}
	while (*Buffer)
	{
		number = number*10 + (*Buffer -'0');
		Buffer++;
	}
	if (sign)
	{
		number = (-1) * number;
	}
	return number;
}

#endif /* AVR_UTILS_H_ */