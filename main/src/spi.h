#ifndef _SPI_H_
#define _SPI_H_

#include "config.h"

void SPIInit(uint8_t);

#define SPI_8BIT 1
#define SPI_16BIT 2

#define CS_ON() GPIO_ResetBits (SPI_PORT_CS, SPI_PIN_CS)
#define CS_OFF() GPIO_SetBits (SPI_PORT_CS, SPI_PIN_CS)

#define A0_HIGH() GPIO_SetBits (SPI_PORT_A0, SPI_PIN_A0)
#define A0_LOW()  GPIO_ResetBits (SPI_PORT_A0, SPI_PIN_A0)

#endif /* _SPI_H_ */
