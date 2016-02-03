#include "config.h"
#include "led.h"
#include "stm32f10x.h"

//-----------------------------------------------------------------------------
//Настроука портов светодиодов
//-----------------------------------------------------------------------------
void LED_init() {
	/* Initialize LEDs mounted on STM32 board */
	GPIO_InitTypeDef GPIO_InitStructure; //Создаем структуру
	/* Initialize LED which connected to PC13, Enable the Clock*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //Включаем порты
	/* Pin 13 - blue LED,*/
	GPIO_InitStructure.GPIO_Pin = PIN_LED_BLUE; //Выбирам нужные порты
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //Режим работы портов
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //Частота портов
	GPIO_Init(GPIOC, &GPIO_InitStructure); // Применяем настройки
	GPIOC->ODR |= PIN_LED_BLUE;
}

//-----------------------------------------------------------------------------
//Инверсия светодиода
//-----------------------------------------------------------------------------
void invert_leds(uint8_t led) {
//	if(led & LED_RED)
//	{
//		GPIOB->ODR ^= PIN_LED_RED;
//	}
	if (led & LED_BLUE) {
		GPIOC->ODR ^= PIN_LED_BLUE;
	}
}

//-----------------------------------------------------------------------------
//Включает указанные светодиоды
//-----------------------------------------------------------------------------
void set_leds(uint8_t led) {
//	if(led & LED_RED)
//	{
//		GPIOB->ODR |= PIN_LED_RED;
//	}
	if (led & LED_BLUE) {
		GPIOC->ODR &= ~PIN_LED_BLUE;
	}
}

//-----------------------------------------------------------------------------
//Выключает указанные светодиоды
//-----------------------------------------------------------------------------
void reset_leds(uint8_t led) {
//	if(led & LED_RED)
//	{
//		GPIOB->ODR &=~ PIN_LED_RED;
//	}
	if (led & LED_BLUE) {
		GPIOC->ODR |= PIN_LED_BLUE;
	}
}
