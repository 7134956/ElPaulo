#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stdint.h"

/* SPI display */
/* Тактируем выбраные блоки */
#define SPI_RCC				RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1
/* Настройка модуля SPI */
#define SPI_UNIT			SPI1
/* Настройка выводов SPI */
#define SPI_PORT			GPIOA
#define SPI_PINS			GPIO_Pin_5 | GPIO_Pin_7
/* Настройка вывода CS */
#define SPI_PORT_CS			GPIOA
#define SPI_PIN_CS			GPIO_Pin_6
/* Настройка вывода A0 */
#define SPI_PORT_A0			GPIOA
#define SPI_PIN_A0			GPIO_Pin_4

/* Display driver */
	//u8g_InitComFn(&u8g, &u8g_dev_st7586s_hw_spi, u8g_com_hw_spi_fn); //Minimal RAM mode
	//u8g_InitComFn(&u8g, &u8g_dev_st7586s_4x_hw_spi, u8g_com_hw_spi_fn); //Speed mode
#define U8G_INIT			u8g_InitComFn(&u8g, &u8g_dev_st7586s_20x_hw_spi, u8g_com_hw_spi_fn); //Max speed mode
	//u8g_InitComFn(&u8g, &u8g_dev_st7586s_20x_hw_spi, u8g_com_hw_spi_9bit_fn); //Max speed mode. 3-wire SPI
	//u8g_InitComFn(&u8g, &u8g_dev_st7669a_4x_hw_spi, u8g_com_hw_spi_fn); //Speed mode
	//u8g_InitComFn(&u8g, &u8g_dev_sh1106_128x64_i2c, u8g_com_hw_i2c_fn); //

/* I2C, EEPROM */
#define I2C_RCC				RCC_APB1Periph_I2C1 | RCC_APB2Periph_GPIOB
#define I2C_UNIT			I2C1
#define	I2C_PORT			GPIOB
#define	I2C_PINS			GPIO_Pin_6 | GPIO_Pin_7
#define I2C_SPEED			100000

#define EEPROM_WRITE_ADDRESS	0x50
#define EEPROM_READ_ADDRESS		0x50
#define I2C_FLASH_PAGESIZE		32
#define EEPROM_HW_ADDRESS		0xA0   /* E0 = E1 = E2 = 0 */

/* EEPROM allocated */
#define HIST_TIMES_CACHE 1791 //Место хранения времен сохраненных заездов (64 ячейки) Х (4 байта)
#define HIST_INDEX_START 2047 //Место однобайтного указателя номера последней ячейки с заездом
#define HIST_CONTENT_START 2048 //Начало блока с заездами
#define HIST_UNINT_SIZE 32	//Размер блока сохраненного заезда
#define CONFIG_UNINT_SIZE 64 //Размер блока настроек
#define HIST_ITEM_COUNT 64 //Число сохраняемых заездов в памяти (Вторая половина eeprom)
#define BUF_MASK (HIST_ITEM_COUNT-1)

#ifdef SYSTEM_WIN
#include <SDL_rwops.h>
#define FILE "SAVE.BIN"
#endif

/* Beeper */
#define BEEP_BUF_SIZE	8 //размер буфера звуков.
#define BEEP_BUF_MASK	(BEEP_BUF_SIZE-1)
#define BEEP_TIM			TIM3
#define BEEP_RCC_TIM			RCC_APB1Periph_TIM3
#define BEEP_RCC_PORT			RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO
#define BEEP_PIN			GPIO_Pin_0
#define BEEP_CCR			CCR3
#define BEEP_ARR			ARR

#endif /* _CONFIG_H_ */
