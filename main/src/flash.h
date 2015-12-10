#ifndef FLASH_H
#define FLASH_H

#include "stm32f10x.h"

#define ADDRESS 0x801fc00

uint32_t readFlash(uint32_t);
void writeFlash(uint32_t, uint32_t);

#endif
