/**
\file avr_macros.h
\brief Library for all common Macro Definition

\verbatim

Created: 01-05-2020 08:20:10 PM
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
RXD (D0) PD0  2|    |27  PC4 (A4/ADC4)
TXD (D1) PD1  3|    |26  PC3 (A3/ADC3)
    (D2) PD2  4|    |25  PC2 (A2/ADC2)
PWM (D3) PD3  5|    |24  PC1 (A1/ADC1)
XCK (D4) PD4  6|    |23  PC0 (A0/ADC0)
         VCC  7|    |22  GND
         GND  8|    |21  AREF
         PB6  9|    |20  AVCC
         PB7 10|    |19  PB5 (D13)
PWM (D5) PD5 11|    |18  PB4 (D12)
PWM (D6) PD6 12|    |17  PB3 (D11) PWM
    (D7) PD7 13|    |16  PB2 (D10) PWM
    (D8) PB0 14|    |15  PB1 (D9)  PWM
               +----+

\endverbatim

*/

#ifndef AVR_MACROS_H_
#define AVR_MACROS_H_

#pragma message ( "avr_macros.h included" )

#ifndef F_CPU
#define F_CPU     16000000UL /**< AVR CPU Frequency in Hz */
#endif

#define F_50Hz    50UL		 /**< Time Period 20ms */
#define F_100Hz   100UL		 /**< Time Period 10ms */
#define F_200Hz   200UL		 /**< Time Period 5ms */
#define F_500Hz   500UL		 /**< Time Period 2ms */
#define F_1kHz    1000UL	 /**< Time Period 1ms */
#define F_5kHz    5000UL	 /**< Time Period 200us */
#define F_10kHz   10000UL	 /**< Time Period 100us */
#define F_20kHz   20000UL	 /**< Time Period 50us */
#define F_40kHz   40000UL	 /**< Time Period 25us */
#define F_50kHz   50000UL	 /**< Time Period 20us */
#define F_100kHz  100000UL	 /**< Time Period 10us */
#define F_200kHz  200000UL	 /**< Time Period 5us */
#define F_500kHz  500000UL	 /**< Time Period 2us */
#define F_1000kHz 1000000UL	 /**< Time Period 1us */
#define F_1Mhz    1000000UL  /**< Time Period 1us */

#define F_62500Hz 62500UL	 /**< Time Period 16us */
#define F_7812Hz  7812UL	 /**< Time Period 128us */
#define F_976Hz   976UL		 /**< Time Period 1024us */
#define F_244Hz   244UL		 /**< Time Period 4098us */
#define F_61Hz    61UL       /**< Time Period 16393us */

#define ENABLE  0x01
#define DISABLE 0x00

#define BUSY    2
#define ERROR   1
#define OK      0

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~(1<<bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |=  (1<<bit))

#define SETBIT(ADDRESS,BIT)   (ADDRESS |=  (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT)  (ADDRESS ^=  (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS  &  (1<<BIT))

#endif /* AVR_MACROS_H_ */