#ifndef SPI_H
#define SPI_H

#include "stm32f10x_spi.h"
void SPIInit(uint8_t);

#define SPI_8BIT 1
#define SPI_16BIT 2

#define CS_ON() GPIO_ResetBits (GPIOA, GPIO_Pin_6)
#define CS_OFF() GPIO_SetBits (GPIOA, GPIO_Pin_6)

#define A0_HIGH() GPIO_SetBits (GPIOA, GPIO_Pin_4)
#define A0_LOW()  GPIO_ResetBits (GPIOA, GPIO_Pin_4)

#endif
