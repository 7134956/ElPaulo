#include "config.h"
#include "eeprom.h"
#include "rtc.h"
#include "memory.h"
#include "timer.h"
#include "crc.h"

#ifdef SYSTEM_WIN
#include <SDL.h>
#include <time.h>
#endif

extern track_t track;
extern config_t config;
extern track_t histItem;
extern racelistDay_t racelistDay;
extern uint8_t navigate[];
extern calendar_t calendar;

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

/*******************************************************************************
 Global variables, private define, macro and typedef
 ******************************************************************************/

uint8_t Buffer[256];
uint8_t errorFlag = 0;
void EEPROM_timeout(void);
void loadDefault(void);

/*******************************************************************************
 * @brief      Writes one byte to the I2C EEPROM.
 * @param[in]  pBuffer   : pointer to the buffer  containing the data to be
 *                         written to the EEPROM.
 * @param[in]  WriteAddr : EEPROM's internal address to write to.
 * @return     None
 ******************************************************************************/
#ifdef SYSTEM_STM32
void I2C_EE_ByteWrite(uint8_t* pBuffer, uint16_t WriteAddr) {
	SysTick_task_add(EEPROM_timeout, 1000);
	/* Send STRAT condition */
	I2C_GenerateSTART(I2C_UNIT, ENABLE);

	/* Test on EV5 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_MODE_SELECT))
		;

	/* Send EEPROM address for write */
	I2C_Send7bitAddress(I2C_UNIT, EEPROM_HW_ADDRESS, I2C_Direction_Transmitter);

	/* Test on EV6 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;

	/* Send the EEPROM's internal address to write to : MSB of the address first */
	I2C_SendData(I2C_UNIT, (uint8_t) ((WriteAddr & 0xFF00) >> 8));

	/* Test on EV8 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	/* Send the EEPROM's internal address to write to : LSB of the address */
	I2C_SendData(I2C_UNIT, (uint8_t) (WriteAddr & 0x00FF));

	/* Test on EV8 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	/* Send the byte to be written */
	I2C_SendData(I2C_UNIT, *pBuffer);

	/* Test on EV8 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	/* Send STOP condition */
	I2C_GenerateSTOP(I2C_UNIT, ENABLE);
	SysTick_task_del(EEPROM_timeout);
}

/*******************************************************************************
 * @brief      Reads a block of data from the EEPROM.
 * @param[in]  pBuffer : pointer to the buffer that receives the data read
 *                       from the EEPROM.
 * @param[in]  ReadAddr : EEPROM's internal address to read from.
 * @param[in]  NumByteToRead : number of bytes to read from the EEPROM.
 * @return     None
 ******************************************************************************/
void I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead) {
	SysTick_task_add(EEPROM_timeout, 1000);
	/* While the bus is busy */
	while (!errorFlag && I2C_GetFlagStatus(I2C_UNIT, I2C_FLAG_BUSY))
		;

	/* Send START condition */
	I2C_GenerateSTART(I2C_UNIT, ENABLE);

	/* Test on EV5 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_MODE_SELECT))
		;

	/* Send EEPROM address for write */
	I2C_Send7bitAddress(I2C_UNIT, EEPROM_HW_ADDRESS, I2C_Direction_Transmitter);

	/* Test on EV6 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;

	/* Send the EEPROM's internal address to read from: MSB of the address first */
	I2C_SendData(I2C_UNIT, (uint8_t) ((ReadAddr & 0xFF00) >> 8));

	/* Test on EV8 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	/* Send the EEPROM's internal address to read from: LSB of the address */
	I2C_SendData(I2C_UNIT, (uint8_t) (ReadAddr & 0x00FF));

	/* Test on EV8 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	/* Send STRAT condition a second time */
	I2C_GenerateSTART(I2C_UNIT, ENABLE);

	/* Test on EV5 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_MODE_SELECT))
		;

	/* Send EEPROM address for read */
	I2C_Send7bitAddress(I2C_UNIT, EEPROM_HW_ADDRESS, I2C_Direction_Receiver);

	/* Test on EV6 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		;

	/* While there is data to be read */
	while (!errorFlag && NumByteToRead) {
		if (NumByteToRead == 1) {
			/* Disable Acknowledgement */
			I2C_AcknowledgeConfig(I2C_UNIT, DISABLE);

			/* Send STOP Condition */
			I2C_GenerateSTOP(I2C_UNIT, ENABLE);
		}

		/* Test on EV7 and clear it */
		if (!errorFlag && I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
			/* Read a byte from the EEPROM */
			*pBuffer = I2C_ReceiveData(I2C_UNIT);

			/* Point to the next location where the byte read will be saved */
			pBuffer++;

			/* Decrement the read bytes counter */
			NumByteToRead--;
		}
	}

	/* Enable Acknowledgement to be ready for another reception */
	I2C_AcknowledgeConfig(I2C_UNIT, ENABLE);
	SysTick_task_del(EEPROM_timeout);
}

/*******************************************************************************
 * @brief      Writes buffer of data to the I2C EEPROM.
 * @param[in]  pBuffer : pointer to the buffer  containing the data to be
 *                       written to the EEPROM.
 * @param[in]  WriteAddr : EEPROM's internal address to write to.
 * @param[in]  NumByteToWrite : number of bytes to write to the EEPROM.
 * @return     None
 ******************************************************************************/
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite) {
	uint8_t NumOfPage = 0, NumOfSingle = 0, count = 0;
	uint16_t Addr = 0;

	Addr = WriteAddr % EEPROM_PAGESIZE;
	count = EEPROM_PAGESIZE - Addr;
	NumOfPage = NumByteToWrite / EEPROM_PAGESIZE;
	NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;

	SysTick_task_add(EEPROM_timeout, 1000);
	
	/* If WriteAddr is EEPROM_PAGESIZE aligned  */
	if (Addr == 0) {
		/* If NumByteToWrite < EEPROM_PAGESIZE */
		if (NumOfPage == 0) {
			I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
			I2C_EE_WaitEepromStandbyState();
		}
		/* If NumByteToWrite > EEPROM_PAGESIZE */
		else {
			while (!errorFlag && NumOfPage--) {
				I2C_EE_PageWrite(pBuffer, WriteAddr, EEPROM_PAGESIZE);
				I2C_EE_WaitEepromStandbyState();
				WriteAddr += EEPROM_PAGESIZE;
				pBuffer += EEPROM_PAGESIZE;
			}

			if (NumOfSingle != 0) {
				I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
				I2C_EE_WaitEepromStandbyState();
			}
		}
	}
	/* If WriteAddr is not EEPROM_PAGESIZE aligned  */
	else {
		/* If NumByteToWrite < EEPROM_PAGESIZE */
		if (NumOfPage == 0) {
			/* If the number of data to be written is more than the remaining space
			 in the current page: */
			if (NumByteToWrite > count) {
				/* Write the data conained in same page */
				I2C_EE_PageWrite(pBuffer, WriteAddr, count);
				I2C_EE_WaitEepromStandbyState();

				/* Write the remaining data in the following page */
				I2C_EE_PageWrite((uint8_t*) (pBuffer + count), (WriteAddr + count), (NumByteToWrite - count));
				I2C_EE_WaitEepromStandbyState();
			} else {
				I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
				I2C_EE_WaitEepromStandbyState();
			}
		}
		/* If NumByteToWrite > EEPROM_PAGESIZE */
		else {
			NumByteToWrite -= count;
			NumOfPage = NumByteToWrite / EEPROM_PAGESIZE;
			NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;

			if (count != 0) {
				I2C_EE_PageWrite(pBuffer, WriteAddr, count);
				I2C_EE_WaitEepromStandbyState();
				WriteAddr += count;
				pBuffer += count;
			}

			while (!errorFlag && NumOfPage--) {
				I2C_EE_PageWrite(pBuffer, WriteAddr, EEPROM_PAGESIZE);
				I2C_EE_WaitEepromStandbyState();
				WriteAddr += EEPROM_PAGESIZE;
				pBuffer += EEPROM_PAGESIZE;
			}
			if (NumOfSingle != 0) {
				I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
				I2C_EE_WaitEepromStandbyState();
			}
		}
	}
	SysTick_task_del(EEPROM_timeout);
}
/*******************************************************************************
 * @brief      Writes more than one byte to the EEPROM with a single WRITE cycle.
 *             Note: The number of byte can't exceed the EEPROM page size.
 * @param[in]  pBuffer : pointer to the buffer containing the data to be
 *                       written to the EEPROM.
 * @param[in]  WriteAddr : EEPROM's internal address to write to.
 * @param[in]  NumByteToWrite : number of bytes to write to the EEPROM.
 * @return     None
 ******************************************************************************/
void I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite) {
	SysTick_task_add(EEPROM_timeout, 1000);
	/* While the bus is busy */
	while (!errorFlag && I2C_GetFlagStatus(I2C_UNIT, I2C_FLAG_BUSY))
		;

	/* Send START condition */
	I2C_GenerateSTART(I2C_UNIT, ENABLE);

	/* Test on EV5 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_MODE_SELECT))
		;

	/* Send EEPROM address for write */
	I2C_Send7bitAddress(I2C_UNIT, EEPROM_HW_ADDRESS, I2C_Direction_Transmitter);

	/* Test on EV6 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;

	/* Send the EEPROM's internal address to write to : MSB of the address first */
	I2C_SendData(I2C_UNIT, (uint8_t) ((WriteAddr & 0xFF00) >> 8));

	/* Test on EV8 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	/* Send the EEPROM's internal address to write to : LSB of the address */
	I2C_SendData(I2C_UNIT, (uint8_t) (WriteAddr & 0x00FF));

	/* Test on EV8 and clear it */
	while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;

	/* While there is data to be written */
	while (!errorFlag && NumByteToWrite--) {
		/* Send the current byte */
		I2C_SendData(I2C_UNIT, *pBuffer);

		/* Point to the next byte to be written */
		pBuffer++;

		/* Test on EV8 and clear it */
		while (!errorFlag && !I2C_CheckEvent(I2C_UNIT, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
			;
	}

	/* Send STOP condition */
	I2C_GenerateSTOP(I2C_UNIT, ENABLE);
	SysTick_task_del(EEPROM_timeout);
}

/*******************************************************************************
 * @brief  Wait for EEPROM Standby state
 ******************************************************************************/
void I2C_EE_WaitEepromStandbyState(void) {
	SysTick_task_add(EEPROM_timeout, 1000);
	//   __IO uint16_t SR1_Tmp = 0;

	do {
		/* Send START condition */
		I2C_GenerateSTART(I2C_UNIT, ENABLE);

		/* Read I2C_EE SR1 register to clear pending flags */
//        SR1_Tmp = I2C_ReadRegister(I2C_EE, I2C_Register_SR1);
		/* Send EEPROM address for write */
		I2C_Send7bitAddress(I2C_UNIT, EEPROM_HW_ADDRESS, I2C_Direction_Transmitter);
	} while (!errorFlag && !(I2C_ReadRegister(I2C_UNIT, I2C_Register_SR1) & 0x0002));

	/* Clear AF flag */
	I2C_ClearFlag(I2C_UNIT, I2C_FLAG_AF);

	/* STOP condition */
	I2C_GenerateSTOP(I2C_UNIT, ENABLE);
	SysTick_task_del(EEPROM_timeout);
}
#endif

#ifdef SYSTEM_WIN
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite) {
	SDL_RWops *io = SDL_RWFromFile(SAVEFILE, "r+b");
	if (io == NULL)
		io = SDL_RWFromFile(SAVEFILE, "w+b");
	io->seek(io, WriteAddr, SEEK_SET);
	io->write(io, pBuffer, NumByteToWrite, 1);
	io->close(io);
}

void I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr,	uint16_t NumByteToRead){
	SDL_RWops *io = SDL_RWFromFile(SAVEFILE, "r+b");
	if (io != NULL) {
		io->seek(io, ReadAddr, SEEK_SET);
	    io->read(io, pBuffer, NumByteToRead, 1);
	    io->close(io);
	}
}
#endif

/*******************************************************************************
 * Сохранить заезд в следующую ячейку кольцевого буффера
 ******************************************************************************/
void saveTrack(void) {
	uint8_t idxIN; //Указатель на последний записанный заезд
		if(errorFlag)
		return;
	if (track.distance) {
		memcpy(&Buffer[0], &track.peakSpeed, 2);
		memcpy(&Buffer[2], &track.startCapacity, 2);
		memcpy(&Buffer[4], &track.endCapacity, 2);
		memcpy(&Buffer[6], &track.circle, 2);
		memcpy(&Buffer[8], &track.distance, 4);
		memcpy(&Buffer[12], &track.tics, 4);
		memcpy(&Buffer[16], &track.startTime, 4);
		I2C_EE_BufferRead(&idxIN, HIST_INDEX_START, 1);
		idxIN++;
		idxIN &= HIST_BUF_MASK;
		I2C_EE_BufferWrite(Buffer, HIST_CONTENT_START + HIST_UNINT_SIZE * idxIN, HIST_UNINT_SIZE); //Сохранили данные заезда
		I2C_EE_BufferWrite((uint8_t*) &track.startTime, HIST_TIMES_CACHE + 4 * idxIN, 4);//Сохранили время заезда в буффер времен для быстрого доступа
		I2C_EE_BufferWrite(&idxIN, HIST_INDEX_START, 1); //Сохранили новый индекс
	}
}

/*******************************************************************************
 * Выход флаги активных дней, сохранненных в памяти
 * Вход год, месяц
 ******************************************************************************/
uint32_t readDayActiv(uint16_t y, uint8_t m) {
	uint8_t i;
	tm_t histTime; //Временная структура с временем заезда
	uint32_t flags = 0; //Тут сохряняем флаги активных дней
	I2C_EE_BufferRead(Buffer, HIST_TIMES_CACHE, 4 * HIST_ITEM_COUNT); //Загружаем массив времен заездов
	for (i = 0; i < HIST_ITEM_COUNT; i++) {
		CounterToFtime(*(uint32_t*) &Buffer[i * 4], &histTime);
		if ((histTime.tm_year + 1900 == y) && (histTime.tm_mon + 1 == m)) {
			SB(flags, histTime.tm_mday);
		}
	}
	SB(flags, 0); //Признак наличия данных
	return flags;
}

/*******************************************************************************
 * Сохранение в память настроек
 ******************************************************************************/
void saveParams(void) {
	if(errorFlag)
		return;
	memcpy(&Buffer[0], &config.PWM[0], 3);
	memcpy(&Buffer[3], &track.odometr, 8);
	//memcpy(&Buffer[11], &track.peakSpeed, 2);
	//memcpy(&Buffer[13], &track.distance, 4);
	//memcpy(&Buffer[17], &track.startCapacity, 2);
	memcpy(&Buffer[19], &track.circle, 2);
	//memcpy(&Buffer[21], &track.tics, 4);
	//memcpy(&Buffer[25], &track.endCapacity, 2);
	//memcpy(&Buffer[27], &track.startTime, 4);
	memcpy(&Buffer[31], &config.lang, 1);
	memcpy(&Buffer[32], &config.maxFPS, 1);
	memcpy(&Buffer[33], &config.SecInTime, 1);
	memcpy(&Buffer[34], &config.SleepSec, 2);
	memcpy(&Buffer[36], &config.SleepDisplayOff, 1);
	memcpy(&Buffer[37], &config.password, 2);
	memcpy(&Buffer[39], &config.contrast, 1);
	memcpy(&Buffer[40], &config.bat_KS, 2);
	memcpy(&Buffer[44], &config.racelistType, 1);
	memcpy(&Buffer[45], &config.service, 4);
	memcpy(&Buffer[49], &config.saveRace, 2);
	memcpy(&Buffer[51], &config.autoPowerOff, 2);

	config.crc = crc32_calc(Buffer, CONFIG_UNINT_SIZE - 4);
	memcpy(&Buffer[60], &config.crc, 4);
	I2C_EE_BufferWrite(Buffer, EEPROM_WRITE_ADDRESS, CONFIG_UNINT_SIZE);
}

/*******************************************************************************
 * Загрузка из памяти настроек
 ******************************************************************************/
void loadParams(void) {
	I2C_EE_BufferRead(Buffer, EEPROM_READ_ADDRESS, CONFIG_UNINT_SIZE);
	if (*((uint32_t *) (&Buffer[CONFIG_UNINT_SIZE - 4])) == crc32_calc(Buffer, CONFIG_UNINT_SIZE - 4)) {
		memcpy(&config.PWM[0], &Buffer[0], 3);
		memcpy(&track.odometr, &Buffer[3], 8);
		//memcpy(&track.peakSpeed, &Buffer[11], 2);
		//memcpy(&track.distance, &Buffer[13], 4);
		//memcpy(&track.startCapacity, &Buffer[17], 2);
		memcpy(&track.circle, &Buffer[19], 2);
		//memcpy(&track.tics, &Buffer[21], 4);
		//memcpy(&track.endCapacity, &Buffer[25], 2);
		//memcpy(&track.startTime, &Buffer[27], 4);
		memcpy(&config.lang, &Buffer[31], 1);
		memcpy(&config.maxFPS, &Buffer[32], 1);
		memcpy(&config.SecInTime, &Buffer[33], 1);
		memcpy(&config.SleepSec, &Buffer[34], 2);
		memcpy(&config.SleepDisplayOff, &Buffer[36], 1);
		memcpy(&config.password, &Buffer[37], 2);
		memcpy(&config.contrast, &Buffer[39], 1);
		memcpy(&config.bat_KS, &Buffer[40], 2);
		memcpy(&config.racelistType, &Buffer[44], 1);
		memcpy(&config.service, &Buffer[45], 4);
		memcpy(&config.saveRace, &Buffer[49], 2);
		memcpy(&config.autoPowerOff, &Buffer[51], 2);

		memcpy(&config.crc, &Buffer[60], 4);
	} else
		loadDefault();
}

/*******************************************************************************
 * Загрузка настроек по умолчанию
 ******************************************************************************/
void loadDefault(void) {
		config.PWM[0] = 0;
		config.PWM[1] = 0;
		track.odometr = 0;
		track.peakSpeed = 0;
		track.distance = 0;
		track.startCapacity = 0;
		track.circle = 2310;
		track.tics = 0;
		track.endCapacity = 0;
		track.startTime = 0;
		config.service = 1000;
		config.lang = 0;
		config.maxFPS = 2;
		config.SecInTime = 1;
		config.SleepSec = 60;
		config.SleepDisplayOff = 0;
		config.password = 0000;
		config.contrast = 60;
		config.bat_KS = 1054;
		config.racelistType = 0;
		config.saveRace = 60;
		config.autoPowerOff = 120;
}

/*******************************************************************************
 * Заполняет массивы для вывода на экране списка заездов
 ******************************************************************************/
//	uint8_t Buffer[HIST_ITEM_COUNT*4];
	uint8_t Rx2_Buffer[HIST_UNINT_SIZE];
void loadRacelist(void) {
	tm_t histTime;
	uint8_t i;
	uint8_t j = 0;
	uint16_t pos;
	
	racelistDay.itemsDisplay = 0;
	I2C_EE_BufferRead(Buffer, HIST_TIMES_CACHE, 4 * HIST_ITEM_COUNT);//Загружаем массив времен заездов
	for (i = 0; i < HIST_ITEM_COUNT; i++) {
		CounterToFtime(*(uint32_t*)&Buffer[i*4], &histTime);
		if ((histTime.tm_year + 1900 == calendar.year)
				&& (histTime.tm_mon + 1 == calendar.month)
				&& (histTime.tm_mday == navigate[1])) //Если дата совпадает
		{
			pos = HIST_CONTENT_START + HIST_UNINT_SIZE * i;
			racelistDay.adres[j] = pos;		
			I2C_EE_BufferRead(Rx2_Buffer, pos, HIST_UNINT_SIZE); //Считываем инфу по заезду
			racelistDay.startTime[j] = histTime.tm_hour * 100 + histTime.tm_min;//Время старта
			racelistDay.distance[j] = *((uint32_t*) &Rx2_Buffer[8]);//Пройденное расстояние
			racelistDay.averSpeed[j] = ((racelistDay.distance[j] * 11796ULL) / *(uint32_t*) &Rx2_Buffer[12]);//Средняя скорость
			j++;
			racelistDay.itemsDisplay = j;
		}
		if (j == 6)
		break;
	}
}

/*******************************************************************************
 *
 ******************************************************************************/
void EEPROM_reset() {
#ifdef SYSTEM_STM32
	uint8_t i;
	for(i = 0; i < 9; i++){
		I2C_SendData(I2C_UNIT, 0xFF);
	}
//#endif
}

/*******************************************************************************
 * Обработчик неисправности EEPROM
 ******************************************************************************/
#define ERROR_EEPROM 1
void EEPROM_timeout() {
//#ifdef SYSTEM_STM32
	uint16_t errors;
	errors = BKP_ReadBackupRegister(BKP_DR2);
	if(errors & ERROR_EEPROM){ //Знаем об ошибке
		errorFlag = 1;
		loadDefault();
		messageCall("SYSTEM ERROR!", "I2C TIMEOUT!", POPUP_ERROR);
	}else{
		errors |= ERROR_EEPROM;
		BKP_WriteBackupRegister(BKP_DR2, errors);
		NVIC_SystemReset();
	}
#endif
}
