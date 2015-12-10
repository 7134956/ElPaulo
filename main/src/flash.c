#include "flash.h"
#include "stm32f10x_flash.h"

uint32_t readFlash(uint32_t dataAdr) {
	return *(uint32_t*) dataAdr;
}

void writeFlash(uint32_t dataAdr, uint32_t data) {
	void FLASH_Unlock(void);

	FLASH_ErasePage(ADDRESS);

	FLASH_ProgramWord(dataAdr, data);

	FLASH_Lock();
}
