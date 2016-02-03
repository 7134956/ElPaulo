#include "config.h"
#include "stm32f10x.h"
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
	SPI_Unit_Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //Скорость.
	SPI_Unit_Init.SPI_FirstBit = SPI_FirstBit_MSB; //Со старшего бита.
	SPI_Unit_Init.SPI_CRCPolynomial = 7; //Фигня какая-то.

	SPI_Init(SPI_UNIT, &SPI_Unit_Init);

	SPI_Cmd(SPI_UNIT, ENABLE); //Запуск SPI1.
}
