#include "spi.h"

/*******************************************************************************
 *Настройка SPI-шины для дисплея
 ******************************************************************************/
void SPIInit(uint8_t param) {
	/* configure pins used by SPI1
	 * PA4 = A0 (RS)
	 * PA5 = SCK
	 * PA6 = MISO используем как CS
	 * PA7 = MOSI (SDA)
	 * CPOL = 1
	 * CPHA = 1
	 */

	GPIO_InitTypeDef SPI_Pin_Init; //Настройка пинов SPI1.
	GPIO_InitTypeDef SPI_Pin_CS_Init; //CS.
	GPIO_InitTypeDef SPI_Pin_A0_Init; //A0
	SPI_InitTypeDef SPI1_Init; //Настройка SPI1.

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //Вкл. тактирование порта
														  //с пинами SPI1.
	SPI_Pin_Init.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	SPI_Pin_Init.GPIO_Mode = GPIO_Mode_AF_PP; //Настраиваем SPI1_SCK и SPI1_MOSI
	SPI_Pin_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &SPI_Pin_Init);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //Настройка пина CS.
	SPI_Pin_CS_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI_Pin_CS_Init.GPIO_Pin = GPIO_Pin_6;
	SPI_Pin_CS_Init.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &SPI_Pin_CS_Init);

	SPI_Pin_A0_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI_Pin_A0_Init.GPIO_Pin = GPIO_Pin_4;
	SPI_Pin_A0_Init.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &SPI_Pin_A0_Init);

	CS_OFF(); //CS=1.

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); //Вкл. тактирования SPI1.

	SPI1_Init.SPI_Direction = SPI_Direction_1Line_Tx; //Только TX = MOSI = выход.
	SPI1_Init.SPI_Mode = SPI_Mode_Master; //Мастер.
	if(param == SPI_8BIT)
	SPI1_Init.SPI_DataSize = SPI_DataSize_8b; //Можно и 16!
	if(param == SPI_16BIT)
	SPI1_Init.SPI_DataSize = SPI_DataSize_16b; //Можно и 8!
	SPI1_Init.SPI_CPHA = SPI_CPHA_2Edge; //Со 2-го фронта.
	SPI1_Init.SPI_CPOL = SPI_CPOL_High; //В режиме ожидания SCK - 1.
	SPI1_Init.SPI_NSS = SPI_NSS_Soft; //Програмный NSS (в железе отключено).
	SPI1_Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //Скорость.
	SPI1_Init.SPI_FirstBit = SPI_FirstBit_MSB; //Со старшего бита.
	SPI1_Init.SPI_CRCPolynomial = 7; //Фигня какая-то.

	SPI_Init(SPI1, &SPI1_Init);

	SPI_Cmd(SPI1, ENABLE); //Запуск SPI1.
}
