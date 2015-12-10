/*

 */

#ifndef _U8G_ARM_H_
#define _U8G_ARM_H_

#include "stm32f10x.h"
#include "u8g.h"
#include "stm32f10x_conf.h"

#include "u8g_dev_st7669a.h"
#include "u8g_dev_st7586s.h"

#define FLAG_CMD 0
#define FLAG_DATA 1

#define DELAY_TIM_FREQUENCY 1000000 /* = 1MHZ -> timer runs in microseconds */
#define SSD1306_I2C_ADDRESS   0x3C	//0x7A		// 011110+SA0+RW - 0x3C or 0x3D
void delay_system_ticks(uint32_t sys_ticks);
void delay_micro_seconds(uint32_t us);
void I2C_stop(void);
void I2C_start(uint8_t address, uint8_t direction);

void i2c_out(uint8_t data);
void i2c_command(uint8_t data);
uint8_t u8g_com_hw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val,	void *arg_ptr);
void delay_init(void);
uint8_t u8g_com_hw_spi_fn(u8g_t*, uint8_t, uint8_t, void *);
uint8_t u8g_com_hw_spi_9bit_fn(u8g_t*, uint8_t, uint8_t, void *);

#endif /* _U8G_ARM_H_ */
