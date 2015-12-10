#include "u8g.h"
#include "main.h"

#define HIST_TIMES_CACHE 1791 //Место хранения времен сохраненных заездов (64 ячейки) Х (4 байта)
#define HIST_INDEX_START 2047 //Место однобайтного указателя номера последней ячейки с заездом
#define HIST_CONTENT_START 2048 //Начало блока с заездами
#define HIST_UNINT_SIZE 32	//Размер блока сохраненного заезда
#define CONFIG_UNINT_SIZE 64 //Размер блока настроек
#define HIST_ITEM_COUNT 64 //Число сохраняемых заездов в памяти (Вторая половина eeprom)
#define BUF_MASK (HIST_ITEM_COUNT-1)

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
