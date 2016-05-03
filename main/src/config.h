#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifndef SYSTEM_WIN
#define SYSTEM_STM32
#endif

/*********************************Includes*************************************/
#include "stdint.h"
#include "bitmap.h"
#include "eeprom.h"
#include "termo.h"
#include "pwm.h"
#include "draw.h"
#include "power.h"
#include "bms.h"

#ifdef SYSTEM_STM32
#define NULL 0
#include "printf.h"
#include "led.h"
#include "termo.h"
#include "buttons.h"
#include "usart.h"
#include "eeprom.h"
#include "pwm.h"
#include "beeper.h"
#include "draw.h"
#include "timer.h"
#include "rtc.h"
#include "i2c.h"
#include "wdg.h"
#include "dbg.h"
#include "power.h"
#include "i2c.h"
#include "bms.h"
#endif

#ifdef SYSTEM_WIN
/* Select display driver */
#define DISPLAY_SDL
#undef NULL
#define NULL 0
//#include <time.h>
#include <stdio.h>
//#include <math.h>
#define SAVEFILE "SAVE.BIN"
#endif

/***************************Настройки сборки***********************************/
/* Отладка */
//#define DEBUG
//#define DEBUG_KEYBOARD
//#define DEBUG_DISPLAY

/* Драйвер дисплея. Должен быть указан в проекте */
#if \
defined (DISPLAY_ST7586S_SPI) || /* Minimal RAM mode */\
defined (DISPLAY_ST7586S_4X_SPI) || /* Speed mode */\
defined (DISPLAY_ST7586S_20X_SPI) || /* Max speed mode */\
defined (DISPLAY_ST75256_SPI) || /* Minimal RAM mode */\
defined (DISPLAY_ST75256_4X_SPI) || /* Speed mode */\
defined (DISPLAY_ST75256_20X_SPI) || /* Max speed mode */\
defined (DISPLAY_ST75256_SPI_DMA) || /* Minimal RAM mode */\
defined (DISPLAY_ST75256_4X_SPI_DMA) || /* Speed mode */\
defined (DISPLAY_ST75256_20X_SPI_DMA) || /* Max speed mode */\
defined (DISPLAY_ST7586S_20X_SPI_9B) || /* Max speed mode. 3-wire SPI */\
defined (DISPLAY_ST7669_4X_SPI) || /* Speed mode */\
defined (DISPLAY_SH1106_SPI_IIC) || /* SH1106 display */\
defined (DISPLAY_SDL) /* Linux or Windows */
#else
#error "!!!Display not defined!!!"
#endif

/* Длина PIN кода */
#define PASSWORD_LENGHT 4

/******************************************************************************/

// Определители вывода текста
//FIXME
//#ifdef DEBUG
//	#define DBG(arg)  DBG_print((char *)arg)
//#else
//	#define DBG(arg)	printf("%s", (char *)arg)
//#endif
#define ERR(arg) printf("%s", (char *)arg)
//#define MSG(arg) printf("%s", (char *)arg)

/* I2C, EEPROM */
#define I2C_RCC		RCC_APB1Periph_I2C2 | RCC_APB2Periph_GPIOB
#define I2C_UNIT	I2C2
#define	I2C_PORT	GPIOB
#define	I2C_PINS	GPIO_Pin_10 | GPIO_Pin_11
#define I2C_SPEED	100000

#define EEPROM_WRITE_ADDRESS	0x50
#define EEPROM_READ_ADDRESS		0x50
#define EEPROM_PAGESIZE			32
#define EEPROM_HW_ADDRESS		0xA0   /* E0 = E1 = E2 = 0 */

/* EEPROM allocated */
/* */
#define HIST_TIMES_CACHE	1791	//Место хранения времен сохраненных заездов (64 ячейки) Х (4 байта)
#define HIST_INDEX_START	2047	//Место однобайтного указателя номера последней ячейки с заездом
#define HIST_CONTENT_START	2048	//Начало блока с заездами
#define HIST_UNINT_SIZE		32		//Размер блока сохраненного заезда
#define CONFIG_UNINT_SIZE	64		//Размер блока настроек
#define HIST_ITEM_COUNT		64		//Число сохраняемых заездов в памяти (Вторая половина eeprom)
#define HIST_BUF_MASK		(HIST_ITEM_COUNT-1)

/* Beeper */
#define BEEP_BUF_SIZE	6 //размер буфера звуков.
#define BEEP_BUF_MASK	(BEEP_BUF_SIZE-1)
#define BEEP_TIM		TIM3
#define BEEP_RCC_TIM	RCC_APB1Periph_TIM3
#define BEEP_RCC_PORT	RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO
#define BEEP_PIN		GPIO_Pin_0
#define BEEP_CCR		CCR3
#define BEEP_ARR		ARR

#endif /* _CONFIG_H_ */
