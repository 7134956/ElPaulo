/*
 The following delay procedures must be implemented for u8glib. This is done in this file:

 void u8g_Delay(uint16_t val)		Delay by "val" milliseconds
 void u8g_MicroDelay(void)		Delay be one microsecond
 void u8g_10MicroDelay(void)	Delay by 10 microseconds

 Additional requirements:
 
 SysTick must be enabled, but SysTick IRQ is not required. Any LOAD values are fine,
 it is prefered to have at least 1ms
 Example:
 SysTick->LOAD = (SystemCoreClock/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS) - 1;
 SysTick->VAL = 0;
 SysTick->CTRL = 7;   // enable, generate interrupt (SysTick_Handler), do not divide by 2
 */

#include "u8g_arm.h"
#include "usart.h"
#include "printf.h"
#include "spi.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "led.h"
#include "stm32f10x_usart.h"
#include "printf.h"
#include "u8g_arm.h"
#include "u8g.h" // Графическая библиотека
#include "i2c.h"

#include "thread.h"
#include "main.h"
extern state_t state;

uint8_t control = 0;
uint32_t i2cTimeLimit = 0;

/*******************************************************************************
 *
 ******************************************************************************/
void i2c_command(uint8_t data) {
	control = 0;
	i2c_out(data);
}

/*******************************************************************************
 *
 ******************************************************************************/
void I2C_stop() {
	// Send I2C1 STOP Condition
	I2C_GenerateSTOP(I2C1, ENABLE);
	i2cTimeLimit = 0;
}

/*******************************************************************************
 *
 ******************************************************************************/
void I2C_start(uint8_t address, uint8_t direction) {

	// wait until I2C1 is not busy anymore
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {
		i2cTimeLimit++;
	}
	// Send I2C1 START condition
	I2C_GenerateSTART(I2C1, ENABLE);

	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
		i2cTimeLimit++;
	}

	// Send slave Address for write
	I2C_Send7bitAddress(I2C1, address << 1, direction);

	/* wait for I2C1 EV6, check if
	 * either Slave has acknowledged Master transmitter or
	 * Master receiver mode, depending on the transmission
	 * direction
	 */

	if (direction == I2C_Direction_Transmitter) {
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
			i2cTimeLimit++;
		}
	} else if (direction == I2C_Direction_Receiver) {
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
			i2cTimeLimit++;
		}

	}
}

/*******************************************************************************
 *set TIM1 to run at DELAY_TIM_FREQUENCY
 ******************************************************************************/
void delay_init(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable timer clock  - use TIMER5 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / DELAY_TIM_FREQUENCY) - 1;
	TIM_TimeBaseStructure.TIM_Period = UINT16_MAX;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Enable counter */
	TIM_Cmd(TIM1, ENABLE);
}

/*******************************************************************************
 *Delay by the provided number of micro seconds.
 *Limitation: "us" * System-Freq in MHz must now overflow in 32 bit.
 *Values between 0 and 1.000.000 (1 second) are ok.
 ******************************************************************************/
void delay_micro_seconds(uint32_t us) {
	TIM_SetCounter(TIM1, 0);
	/* use 16 bit count wrap around */
	while ((uint16_t) (TIM1->CNT) <= us)
		;
}

/*******************************************************************************
 *
 ******************************************************************************/
void i2c_out(uint8_t data) {
	I2C_start(SSD1306_I2C_ADDRESS, I2C_Direction_Transmitter);
	//Wire.write(control);
	I2C_SendData(I2C1, control);
	// wait for I2C1 EV8_2 --> byte has been transmitted
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		i2cTimeLimit++;
	}
	I2C_SendData(I2C1, data);
	// wait for I2C1 EV8_2 --> byte has been transmitted
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
		i2cTimeLimit++;
	}

	I2C_stop();
}

/*========================================================================*/
/*
 The following delay procedures must be implemented for u8glib

 void u8g_Delay(uint16_t val)		Delay by "val" milliseconds
 void u8g_MicroDelay(void)		Delay be one microsecond
 void u8g_10MicroDelay(void)	Delay by 10 microseconds

 */

void u8g_Delay(uint16_t val) {
	delay_micro_seconds(1000UL * (uint32_t) val);
}

void u8g_MicroDelay(void) {
	delay_micro_seconds(1);
}

void u8g_10MicroDelay(void) {
	delay_micro_seconds(10);
}

/*******************************************************************************
 *Работа с дисплеем по I2C
 ******************************************************************************/
uint8_t u8g_com_hw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr) {

	switch (msg) {
	case U8G_COM_MSG_STOP:
		break;

	case U8G_COM_MSG_INIT:
		i2c_init();
		delay_init();
		u8g_MicroDelay();
		break;

	case U8G_COM_MSG_ADDRESS: /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
		if (arg_val == 0) {
			control = 0;
		} else {
			control = 0x40;
		}
		u8g_10MicroDelay();
		break;

	case U8G_COM_MSG_RESET:

		u8g_10MicroDelay();
		break;

	case U8G_COM_MSG_WRITE_BYTE:

		i2c_out(arg_val);
		u8g_MicroDelay();
		break;

	case U8G_COM_MSG_WRITE_SEQ:
	case U8G_COM_MSG_WRITE_SEQ_P: {

		register uint8_t *ptr = arg_ptr;
		I2C_start(SSD1306_I2C_ADDRESS, I2C_Direction_Transmitter);
		I2C_SendData(I2C1, control);
		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
			i2cTimeLimit++;
		}
		while (arg_val > 0) {
			I2C_SendData(I2C1, *ptr++);
			arg_val--;
			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
				i2cTimeLimit++;
			}
		}
		I2C_stop();
		u8g_MicroDelay();
	}
		break;
	}
	return 1;
}

/*******************************************************************************
 *Работа с дисплеем по SPI 8 bit
 ******************************************************************************/
uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr) {
	switch (msg) {
	case U8G_COM_MSG_STOP:
		//Остановить устройство
		break;
	case U8G_COM_MSG_INIT: {
		delay_init();
		SPIInit(SPI_8BIT); //Инициализация SPI1 (stm32f1)
	}
		break;
	case U8G_COM_MSG_ADDRESS: /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
	{
		if (arg_val == 0)
			A0_LOW();
		if (arg_val == 1)
			A0_HIGH();
	}
		break;
	case U8G_COM_MSG_CHIP_SELECT: {
		if (arg_val == 0) {
			/* disable */
			CS_OFF();
		} else {
			/* enable */
			CS_ON();
		}
	}
		break;
	case U8G_COM_MSG_RESET: {
		u8g_10MicroDelay();
	}
		break;
	case U8G_COM_MSG_WRITE_BYTE: {
//		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) {};//FIXME if need
		SPI_I2S_SendData(SPI1, arg_val);
	}
		break;
	case U8G_COM_MSG_WRITE_SEQ: {
		register uint8_t *ptr = arg_ptr;
		uint8_t byte, i;
		while (arg_val > 0) {
			for (i = 0; i < 4; i++) {
				byte = ((*ptr & 128) / 8) | ((*ptr & 64) * 2); //Старший бит
				*ptr <<= 2;
//				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) {}; //FIXME if need
				__nop(); //Даем время байту отправиться
				SPI1->DR = byte;
//				SPI_I2S_SendData(SPI1, byte);
			}
			ptr++;
			arg_val--;
		}
	}
		break;
	}
	return 1;
}

/*******************************************************************************
 *Работа с дисплеем по SPI 9 bit
 ******************************************************************************/
uint8_t flagCmd = FLAG_CMD;
uint16_t bits9; // 9 бит для отправки
uint8_t buf_in[9]; // буфер, принимающий данные
uint8_t num = 0; // принято байт
uint8_t u8g_com_hw_spi_9bit_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr) {
	uint8_t i;
	switch (msg) {
	case U8G_COM_MSG_STOP:
		//Остановить устройство
		break;
	case U8G_COM_MSG_INIT: {
		delay_init();
		SPIInit(SPI_16BIT); //Инициализация SPI1 (stm32f1)
	}
		break;
	case U8G_COM_MSG_ADDRESS: /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
	{
		flagCmd = arg_val;
	}
		break;
	case U8G_COM_MSG_CHIP_SELECT: {
		if (arg_val == 0) {
			// disable
			CS_OFF();
		} else {
			// enable
			CS_ON();
		}
	}
		break;
	case U8G_COM_MSG_RESET: {
		u8g_10MicroDelay();
	}
		break;
	case U8G_COM_MSG_WRITE_BYTE: {
		bits9 = arg_val << 7;
		if (flagCmd)
			bits9 |= 1 << 15;
		CS_ON();
		SPI1->CR1 |= (uint16_t) SPI_DataSize_16b; //Выставляем бит 16битной передачи
		SPI1->DR = bits9;
		i = 9;
		while (i--) {
		};
		CS_OFF();
		SPI1->CR1 &= (uint16_t) ~SPI_DataSize_16b; //Снимаем бит, получаем восьмибитный режим
		CS_ON();
	}
		break;
		case U8G_COM_MSG_WRITE_SEQ: {
		register uint8_t *ptr = arg_ptr;
		uint8_t byte, i;
		state.taskList |= TASK_TRANSFER; //Установим флаг передачи данных
		while (arg_val > 0) {
			for (i = 0; i < 4; i++) {
				byte = ((*ptr & 128) >> 3) | ((*ptr & 64) << 1); //Старший бит
				*ptr <<= 2;
				buf_in[num] |= byte >> (1 + num) | 1 << (7 - num);
				buf_in[num + 1] = byte << (7 - num);
				SPI1->DR = buf_in[num];
				buf_in[num++] = 0;
				if (num == 8) {
					SPI1->DR = buf_in[8];
					num = 0;
				}
			}
			ptr++;
			arg_val--;
		}
		state.taskList &=~ TASK_TRANSFER; //Снимаем флаг передачи данных
	}
		break;
//		case U8G_COM_MSG_WRITE_SEQ: {
//		uint8_t *ptr = arg_ptr;
////			uint8_t opa;
//		while (arg_val > 0) {
//			arg_val -=2;			
//			SPI1->DR=((*ptr & 128) >> 4) | (*ptr & 64) | 128; 			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//			SPI1->DR=((*ptr & 32) >> 3) | (*ptr & 16)<<1 | 64;			__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//			SPI1->DR=((*ptr & 8) >> 2) | (*ptr & 4)<<2 | 32;				__nop();__nop();__nop();__nop();__nop();__nop();
//			SPI1->DR=((*ptr & 2) >> 1) | (*ptr & 1)<<3 | 16;				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();ptr++;
//			SPI1->DR=((*ptr & 64)>>4) | 8;													__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//			SPI1->DR=(*ptr & 128)	| ((*ptr & 16)>>3) | 4	;					__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//			SPI1->DR=((*ptr & 32) << 1) | ((*ptr & 4) >> 2) | 2;		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//			SPI1->DR=((*ptr & 8)<<2) | 1;														__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//			SPI1->DR=((*ptr & 2) << 3) | (*ptr & 1)<<7;
//			ptr++;
//		}
//	}
//		break;
	}
	return 1;
}

