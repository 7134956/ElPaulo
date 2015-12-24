#include "dma.h"
#include "stm32f10x.h"

/*******************************************************************************
 *Настройка блока DMA
 ******************************************************************************/
void DMA_init(void) {
	//
	DMA_InitTypeDef DMA_InitStructure;
	//Тактирование включается следующим образом:
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //Тактирование включается
	//Прежде всего сбросим предыдущие настройки DMA
	DMA_DeInit(DMA1_Channel3);
	//Теперь приступим непосредственно к настройке. Она выглядит следующим образом:
	//Указатель на регистр периферийного устройства
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&SPI1->DR);
	//Адрес в памяти
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) text;
	//Переферия это приемник
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	//Размер передаваемого буффера
//	DMA_InitStructure.DMA_BufferSize = sizeof(text);
	//Не инкрементировать адресс переферии
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//Инкрементировать адрес в памяти
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	//
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	//После выполнения работы сработает прерывание
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	//
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	//Отключаем режим передачи из памяти в память
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	//Разрешаем SPI1 работать в DMA.
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	//Устанавливаем прерывания от DMA по окончанию передачи
	DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
	//Включаем общие прерывания в NVIC.
	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
}
