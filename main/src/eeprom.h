#include "config.h"
#include "u8g.h"
#include "main.h"

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

void *memcpy(void *, const void *, size_t);

void saveTrack(void);
void loadRacelist(void);
void saveParams(void);
void loadParams(void);
void loadHistItem(void);
