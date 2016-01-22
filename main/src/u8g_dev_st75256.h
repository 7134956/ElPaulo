#ifndef _DEV_ST75256_H_
#define _DEV_ST75256_H_

#include "u8g.h"
#include "stm32f10x_conf.h"

uint8_t u8g_dev_st75256_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);
extern u8g_dev_t u8g_dev_st75256_hw_spi;
extern u8g_dev_t u8g_dev_st75256_4x_hw_spi;
extern u8g_dev_t u8g_dev_st75256_20x_hw_spi;

#endif /* _DEV_ST75256_H_ */
