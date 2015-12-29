
#ifndef ATA6870_FUNC_H
#define ATA6870_FUNC_H

/******************************************************************************
 Includes
******************************************************************************/

#include "config.h"

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
