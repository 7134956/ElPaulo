#ifndef _EEPROM_H_
#define _EEPROM_H_
#include "config.h"

//*****************************************************************************
// Declare function prototypes
//*****************************************************************************
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr,	uint16_t NumByteToWrite);
void I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr,	uint16_t NumByteToRead);
#ifdef SYSTEM_STM32
void I2C_EE_ByteWrite(uint8_t* pBuffer, uint16_t WriteAddr);
void I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr,	uint8_t NumByteToWrite);
void I2C_EE_WaitEepromStandbyState(void);
#endif

void saveTrack(void);
void loadRacelist(void);
void saveParams(void);
void loadParams(void);
void loadHistItem(void);

#endif /* _EEPROM_H_ */
