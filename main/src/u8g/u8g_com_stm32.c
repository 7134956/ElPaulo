/*
7134956@gmail.com 2016
*/

#include "stm32f10x.h"
#include "u8g.h"

/*---------------------Configure SPI for display ----------------------------*/
/* Тактируем выбраные блоки */
#define SPI_RCC				RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1
/* Выбор модуля SPI */
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
/* For speed SPI transfer. If SPI_CLK >= CPU_CLK/2 */
//#define SPI_SKIP_BUSY
/*---------------------End configure SPI for display ------------------------*/

#define DELAY_TIM_FREQUENCY 1000000 /* = 1MHZ -> timer runs in microseconds */

#define SPI_8BIT 1
#define SPI_16BIT 2

#define CS_ON() GPIO_ResetBits (SPI_PORT_CS, SPI_PIN_CS)
#define CS_OFF() GPIO_SetBits (SPI_PORT_CS, SPI_PIN_CS)

#define A0_HIGH() GPIO_SetBits (SPI_PORT_A0, SPI_PIN_A0)
#define A0_LOW()  GPIO_ResetBits (SPI_PORT_A0, SPI_PIN_A0)

void SPIInit(uint8_t);

/******************************************************************************
 *Настройка SPI-шины для дисплея
 *****************************************************************************/
void SPIInit(uint8_t param) {
	/* configure pins used by SPI1
	 * PA4 = A0 (RS)
	 * PA5 = SCK
	 * PA6 = MISO use as CS
	 * PA7 = MOSI (SDA)
	 * CPOL = 1
	 * CPHA = 1
	 */

	GPIO_InitTypeDef SPI_Pin_Init; //Настройка пинов SPI1.
	GPIO_InitTypeDef SPI_Pin_CS_Init; //CS.
	GPIO_InitTypeDef SPI_Pin_A0_Init; //A0
	SPI_InitTypeDef SPI_Unit_Init; //Настройка SPI1.

	RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE); //Вкл. тактирование SPI и PIN-ов.
	SPI_Pin_Init.GPIO_Pin = SPI_PINS;
	SPI_Pin_Init.GPIO_Mode = GPIO_Mode_AF_PP; //Настраиваем SPI1_SCK и SPI1_MOSI
	SPI_Pin_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT, &SPI_Pin_Init);

	SPI_Pin_CS_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI_Pin_CS_Init.GPIO_Pin = SPI_PIN_CS;
	SPI_Pin_CS_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT_CS, &SPI_Pin_CS_Init);

	SPI_Pin_A0_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI_Pin_A0_Init.GPIO_Pin = SPI_PIN_A0;
	SPI_Pin_A0_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_PORT_A0, &SPI_Pin_A0_Init);

	CS_OFF(); //CS=1.

	SPI_Unit_Init.SPI_Direction = SPI_Direction_1Line_Tx; //Только TX = MOSI = выход.
	SPI_Unit_Init.SPI_Mode = SPI_Mode_Master; //Мастер.
	if(param == SPI_8BIT)
	SPI_Unit_Init.SPI_DataSize = SPI_DataSize_8b; //Можно и 16!
	if(param == SPI_16BIT)
	SPI_Unit_Init.SPI_DataSize = SPI_DataSize_16b; //Можно и 8!
	SPI_Unit_Init.SPI_CPHA = SPI_CPHA_2Edge; //Со 2-го фронта.
	SPI_Unit_Init.SPI_CPOL = SPI_CPOL_High; //В режиме ожидания SCK - 1.
	SPI_Unit_Init.SPI_NSS = SPI_NSS_Soft; //Програмный NSS (в железе отключено).
	//Need clock 10Mhz by datasheet. Work tested on full speed 36Mhz.
	SPI_Unit_Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //Скорость.
	SPI_Unit_Init.SPI_FirstBit = SPI_FirstBit_MSB; //Со старшего бита.
	SPI_Unit_Init.SPI_CRCPolynomial = 7; //Фигня какая-то.

	SPI_Init(SPI_UNIT, &SPI_Unit_Init);

	SPI_Cmd(SPI_UNIT, ENABLE); //Запуск SPI1.
}

/******************************************************************************
 *set TIM1 to run at DELAY_TIM_FREQUENCY
 *****************************************************************************/
void delay_init(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Включаем тактирование таймера */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/* Настраиваем таймер */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	SystemCoreClockUpdate ();
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / DELAY_TIM_FREQUENCY) - 1;
	TIM_TimeBaseStructure.TIM_Period = UINT16_MAX;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Включаем счетчик */
	TIM_Cmd(TIM1, ENABLE);
	
	/* Выключаем тактирование */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, DISABLE);
}

/******************************************************************************
 *Delay by the provided number of micro seconds.
 *Limitation: "us" * System-Freq in MHz must now overflow in 32 bit.
 *Values between 0 and 1.000.000 (1 second) are ok.
 *****************************************************************************/
void delay_micro_seconds(uint32_t us) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1->CNT = (uint16_t)0;
	/* use 16 bit count wrap around */
	while ((uint16_t)(TIM1->CNT) <= us);
	RCC->APB2ENR &=~ RCC_APB2ENR_TIM1EN;
}

 /****************************************************************************/
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

/******************************************************************************
 *st7586s on SPI 8 bit

Com_fn unpack page buffer to display

2 pixels on byte

B-black
W-white
LG-Light gray
DG-Dark grey

BW mode

0b00011000, B W
0b00000000, W W
0b00011000, B W
0b11000000, W B
0b11011000, B B
0b10010000, B B
0b01001000, W W

Gray mode
0b00011000, B W
0b00000000, W W
0b00011000, B W
0b11000000, W B
0b11011000, B B
0b10010000, DG DG
0b01001000, LG LG

 *****************************************************************************/
uint8_t u8g_com_stm32_st7586s_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr) {
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
			RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
			CS_OFF();
		} else {
			/* enable */
			RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
			CS_ON();
		}
	}
		break;
	case U8G_COM_MSG_RESET: {
		u8g_10MicroDelay();
	}
		break;
	case U8G_COM_MSG_WRITE_BYTE: {
#ifdef SPI_SKIP_BUSY
		SPI_UNIT->DR = arg_val;
#else				
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) {};
		SPI_I2S_SendData(SPI1, arg_val);
#endif
	}
		break;
	case U8G_COM_MSG_WRITE_SEQ: {

		register uint8_t *ptr = arg_ptr;
		uint8_t byte, i;
		while (arg_val > 0) {
			for (i = 0; i < 4; i++) {
				byte = ((*ptr & 128) / 8) | ((*ptr & 64) * 2); //Старший бит
				*ptr <<= 2;
#ifdef SPI_SKIP_BUSY
				SPI_UNIT->DR = byte;
#else				
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) {}; 
				SPI_I2S_SendData(SPI1, byte);
#endif
			}
			ptr++;
			arg_val--;
		}
	}
		break;
	}
	return 1;
}
