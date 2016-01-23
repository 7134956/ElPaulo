/*
 * Оконный сторожевой таймер.
 * Считает сверху вниз от максимального значения 0x7F
 * 
 * Делает сброс контроллера, если досчитает до 0x3F или
 * если попытаться обновить счетчик раньше чем досчитает до
 * заданного окна.
 */
 
#include "wdg.h"
#include "stm32f10x.h"

#define CONFIG_WDG_COUNTER	0x7F
#define CONFIG_WDG_WINDOW		0x7F

/* CFR register bit mask */
#define CFR_WDGTB_MASK    ((uint32_t)0xFFFFFE7F)
#define CFR_W_MASK        ((uint32_t)0xFFFFFF80)
#define BIT_MASK          ((uint8_t)0x7F)


void WWDG_Init(void){
	uint32_t tmpreg = 0;
	
	/* Установим бит тактирования оконного сторожевого таймера. */
	RCC->APB1ENR |= RCC_APB1ENR_WWDGEN;
	
	//Настроим частоту счета сторожевого таймера
  /* Очистим биты WDGTB[1:0] */
  tmpreg = WWDG->CFR & CFR_WDGTB_MASK;
  /* Настроим биты предделителя WDGTB[1:0] */
	//24000000/4096/8 = 732,421875 Гц
	//При максимальном значении у нас всего 100мСек до сброса
  tmpreg |= WWDG_Prescaler_8;
  /* Записшем значение в регистр */
  WWDG->CFR = tmpreg;
	
  //Установим значение окна 
  /* Очистим W[6:0] биты */
  tmpreg = WWDG->CFR & CFR_W_MASK;
  /* Установим для битов W[6:0] заначение(CONFIG_WDG_WINDOW) начала окна  */
  tmpreg |= CONFIG_WDG_WINDOW & (uint32_t)BIT_MASK;
  /* Записшем значение в регистр */
  WWDG->CFR = tmpreg;
	
	/* Включение таймера с установкой значения для начала счета*/
  WWDG->CR = WWDG_CR_WDGA | CONFIG_WDG_COUNTER;
}

void WWDG_Renew(void){
	/* Обновляем значение таймера*/
  WWDG->CR = CONFIG_WDG_COUNTER & BIT_MASK;
}

///**
//  * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
//  * @note   Once enabled this interrupt cannot be disabled except by a system reset. 
//  * @param  None
//  * @retval None
//  */
//void WWDG_EnableIT(void)
//{
//  WWDG->CFR |= WWDG_CFR_EWI;
//}

///**
//  * @brief  Clears Early Wakeup interrupt flag.
//  */
//void WWDG_ClearFlag(void)
//{
//  WWDG->SR = (uint32_t)RESET;
//}

////Настройка независимого сторожевого таймера
////Tout=((4*2^prer)*rlr)/40 (ms).
//void IWDG_Init(uint8_t prer, uint16_t rlr){
//	IWDG->KR=0X5555;//Ключ для доступа к таймеру
//	IWDG->PR=prer;//Обновление предделителя
//	IWDG->RLR=rlr;//Загружаем регистр перезагрузки, счет идет вниз от этого значения
//	IWDG->KR=0XAAAA;//перезагрузка
//	IWDG->KR=0XCCCC;//Запуск в работы
//}
