#ifndef _DEV_ST7669A_H_
#define _DEV_ST7669A_H_

#include "u8g.h"
#include "stm32f10x_conf.h"

uint8_t u8g_dev_st7669a_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);
extern u8g_dev_t u8g_dev_st7669a_hw_spi;
extern u8g_dev_t u8g_dev_st7669a_4x_hw_spi;

#endif /* _DEV_ST7669A_H_ */
