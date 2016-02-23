#include "config.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

#include "crc.h"

/*******************************************************************************
 *Вычисление контрольной суммы
 ******************************************************************************/
uint32_t crc32_calc(uint8_t *bfr, uint32_t len) {
#ifdef SYSTEM_STM32
	uint32_t l, crc, x, *p;
	RCC->AHBENR |= RCC_AHBENR_CRCEN; //Включаем тактирование CRC
	l = len / 4;
	p = (uint32_t*) bfr;
	x = p[l];
	CRC->CR = CRC_CR_RESET; //Сбрасываем CRC
	while (l--) {
		CRC->DR = *p; //Вкидываем новую порцию
		p++;
	}
	switch (len & 3) {
	case 1:
		CRC->DR = x & 0x000000FF; //Вкидываем новую порцию
		break;
	case 2:
		CRC->DR = x & 0x0000FFFF; //Вкидываем новую порцию
		break;
	case 3:
		CRC->DR = x & 0x00FFFFFF; //Вкидываем новую порцию
		break;
	}
	crc = CRC->DR;	//Берем результат
	RCC->AHBENR &= ~RCC_AHBENR_CRCEN; //Выключаем тактирование CRC
	return 0xFFFFFFFF ^ crc;
#endif
#ifdef SYSTEM_WIN
	return 1;
#endif
}
