/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      ATA6870 fuctions header file.
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


#ifndef ATA6870_FUNC_H
#define ATA6870_FUNC_H

/******************************************************************************
 Includes
******************************************************************************/

#include "config.h"

//#include <avr/interrupt.h>
//#include <avr/io.h>
//#include <avr/pgmspace.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <util/delay.h>


/******************************************************************************
 Macro functions
******************************************************************************/

#define SETBIT(x, y)    (x |= (y))              // Set bit y in byte x
#define CLEARBIT(x, y)  (x &= (~y))             // Clear bit y in byte x
#define CHECKBIT(x, y)  (x & (y))               // Check bit y in byte x
#define TOGGLEBIT(x, y) (x ^= (y))              // Toggle bit y in byte x

#define CS_ON() GPIO_ResetBits (GPIOA, GPIO_Pin_6)
#define CS_OFF() GPIO_SetBits (GPIOA, GPIO_Pin_6)

#define PD_N_ON() GPIO_SetBits (GPIOA, GPIO_Pin_4)
#define PD_N_OFF()  GPIO_ResetBits (GPIOA, GPIO_Pin_4)

/******************************************************************************
 Function prototypes.
******************************************************************************/
void _delay_ms(uint16_t);

// SPI Functions
unsigned char SPI_COM(unsigned char ucData);
void ATA6870_SPI_COM(uint8_t ucAdr2, uint8_t ucCommandCode1, uint8_t ucCommandCode2);
void SPI_MasterInit(void);

// Voltage Functions
void CalculateV(uint8_t ChipID);
unsigned char Undervoltage(uint16_t limit, uint8_t chipID);
unsigned char Overvoltage(uint16_t limit,uint8_t chipID);
void Discharge(uint8_t Cells);
unsigned char OpenCellcheck(void);

//Additional Functions
void Configure_Fet(uint8_t Fet);
void ReadNTC(void);
void CCInit(void);
void TimerInit(uint32_t);
void CLK_init(uint32_t);


#endif
