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

/* Выберите один драйвер дисплея */
//#define DISPLAY_ST7586S_SPI //Minimal RAM mode
//#define DISPLAY_ST7586S_4X_SPI //Speed mode
///#define DISPLAY_ST7586S_20X_SPI //Max speed mode
//#define DISPLAY_ST75256_SPI //Minimal RAM mode
//#define DISPLAY_ST75256_4X_SPI //Speed mode
//#define DISPLAY_ST75256_20X_SPI //Max speed mode
//#define DISPLAY_ST75256_SPI_DMA //Minimal RAM mode
//#define DISPLAY_ST75256_4X_SPI_DMA //Speed mode
#define DISPLAY_ST75256_20X_SPI_DMA //Max speed mode
//#define DISPLAY_ST7586S_20X_SPI_9B //Max speed mode. 3-wire SPI
//#define DISPLAY_ST7669_4X_SPI //Speed mode
//#define DISPLAY_SH1106_SPI_IIC //

/* Длина PIN кода */
#define PASSWORD_LENGHT 4

/* Выбор типа клавиатуры */
#define KEYBOARD_ADC
//#define KEYBOARD_APPLE
/******************************************************************************/

// Определители вывода текста
#ifdef DEBUG
	#define DBG(arg)  DBG_print((char *)arg)
#else
	#define DBG(arg)	printf("%s", (char *)arg)
#endif
#define ERR(arg) printf("%s", (char *)arg)
#define MSG(arg) printf("%s", (char *)arg)

/* Select display driver */
#ifdef SYSTEM_WIN
#define DISPLAY_SDL //Max speed mode
#endif

///* SPI display */
///* Тактируем выбраные блоки */
//#define SPI_RCC				RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1
///* Настройка модуля SPI */
//#define SPI_UNIT			SPI1
///* Настройка выводов SPI */
//#define SPI_PORT			GPIOA
//#define SPI_PINS			GPIO_Pin_5 | GPIO_Pin_7
///* Настройка вывода CS */
//#define SPI_PORT_CS			GPIOA
//#define SPI_PIN_CS			GPIO_Pin_6
///* Настройка вывода A0 */
//#define SPI_PORT_A0			GPIOA
//#define SPI_PIN_A0			GPIO_Pin_4

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

/* Beeper */
#define BEEP_BUF_SIZE	8 //размер буфера звуков.
#define BEEP_BUF_MASK	(BEEP_BUF_SIZE-1)
#define BEEP_TIM			TIM3
#define BEEP_RCC_TIM		RCC_APB1Periph_TIM3
#define BEEP_RCC_PORT		RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO
#define BEEP_PIN			GPIO_Pin_0
#define BEEP_CCR			CCR3
#define BEEP_ARR			ARR

#endif /* _CONFIG_H_ */
