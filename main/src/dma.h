#ifndef _DMA_H_
#define _DMA_H_

#include "config.h"

void DMA1_SPI1_init(void * source);
void SPI_DMA_Send(uint16_t count);

#endif /* DMA_H_ */
