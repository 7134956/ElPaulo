/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      Configuration file.
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * 
 * $Date: 2011-02-22 \n
 *
 * Copyright (c) 2011, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/
/*
Частота процессора и шин пускай 8MHz
CELL 24
Number of ATA6870N 4
SCK Frequency (kHz) 250
CLK Frequency(kHz) 500
*/


#ifndef CONFIG_H
#define CONFIG_H

#include "stdint.h"

#define CLK_PORT 
#define CLK_PIN 
#define CHIP_CLK 500000
#define CHIPS 4

#define DELAY_TIM_FREQUENCY 1000 /* = 1KHZ -> timer runs in milliseconds */

//!< Cells IC 1 Bits 0-5 -> Cells 1-6
#define CELLSIC1 0x3F
//!< Cells IC 2	Bits 0-5 -> Cells 1-6
#define CELLSIC2 0x3F
//!< Cells IC 3 Bits 0-5 -> Cells 1-6
#define CELLSIC3 0x3F
//!< Cells IC 4	Bits 0-5 -> Cells 1-6
#define CELLSIC4 0x3F

//!< Temperature reference resistance in Ohm
#define RES_REF1                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF2                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF3                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF4                (3300)

//!< Temperature Lookup Start
#define T_TLS                   (-20)
//!< Temperature Lookup End
#define T_TLE                   (80)
//!< Temperature Lookup Stepsize
#define T_TLSZ                  (1)

//!< Temperature Lower Threshold
#define T_LOWERTRESHOLD         (-20)
//!< Temperature Upper Threshold
#define T_UPPERTHRESHOLD        (+60)

//!< Shunt resistance in mOhm
#define SHUNT_RESISTANCE        (10)
//!< RCC Conversion Period 0x00 - 256ms, 0x01 - 512ms, 0x02 - 1s, 0x03 - 2s
#define RCC_CONVERSIONPERIOD    (0x00)
//!< RCC Divide Stepsize
#define RCC_DIVIDEDSZ           (0)
//!< RCC Charge Threshold in mA
#define RCC_CHARGETHRESHOLD     (50)
//!< RCC Discharge Threshold in mA
#define RDC_DISCHARGETHRESHOLD  (50)

//!< CC-ADC Regular Current Condition voltage step size in �V
#define RCC_STEP_SIZE_uV        (26.855)
//!< RCC steps size in mA (with a given \ref SHUNT_RESISTANCE)
#define RCC_STEP_SIZE_mA        (RCC_STEP_SIZE_uV/SHUNT_RESISTANCE)
//!< RCC CADRCC Value
#define RCC_CADRCC (~((int)((float)RCC_CHARGETHRESHOLD/RCC_STEP_SIZE_mA)))+1
//!< RDC CADRDC Value
#define RDC_CADRDC (~((int)((float)RDC_DISCHARGETHRESHOLD/RCC_STEP_SIZE_mA)))+1


//!< F_CPU Value in Hz
#define F_CPU 1000000UL //Should not be changed!(See Applicationnote for further info)

//!< ATA6870 Masks
#define CLK         0x02   // PB1
#define PD_N        0x04   // PB2
#define IRQ         0x08   // PB3

//!< Evaluation Masks
#define LED1        0x01   // PA0
#define LED2        0x02   // PA1
#define LED3        0x04   // PA2

//!< SPI Portx
#define NSS_PORTx       PORTB
#define MOSI_PORTx      PORTB
#define MISO_PORTx      PORTB
#define SCK_PORTx       PORTB

//!< ATA6870 Portx
#define CLK_PORTx       PORTB
#define IRQ_PORTx       PORTB
#define PD_N_PORTx      PORTB

//!< Evaluation Portx
#define LED_PORTx       PORTA


//!< SPI DDR
#define NSS_DDRx        DDRB
#define MOSI_DDRx       DDRB
#define MISO_DDRx       DDRB
#define SCK_DDRx        DDRB

//!< ATA6870 DDR
#define CLK_DDRx        DDRB
#define IRQ_DDRx        DDRB
#define PD_N_DDRx       DDRB

//!< Evaluation DDR
#define LED_DDRx        DDRA


//!< SPI Pinx
#define MISO_PINx       PINB

//!< ATA6870 Pinx
#define IRQ_PINx        PINB

//!< Evaluation Pinx
#define LED_PINx        PINB

#endif
