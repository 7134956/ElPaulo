#ifndef FLASH_H
#define FLASH_H

#include "config.h"

#define ADDRESS 0x801fc00

uint32_t readFlash(uint32_t);
void writeFlash(uint32_t, uint32_t);

#endif
