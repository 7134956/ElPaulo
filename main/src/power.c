#include "main.h"
#include "power.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
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
#endif

#ifdef SYSTEM_WIN
#endif
extern config_t config;
extern count_t count;
extern state_t state;

/*******************************************************************************
 *Переход в указанный режим работы
 ******************************************************************************/
void setPowerMode(uint8_t mode) {
#ifdef SYSTEM_STM32
	switch(mode) {
		case POWERMODE_TURBO : {}break;
		case POWERMODE_ACTIVE : {}break;
		case POWERMODE_NORMAL : {
			count.toSleep = 0; //Не спать, не спать!
		}break;
		case POWERMODE_SLEEP : {
			state.taskList |= TASK_REDRAW;
		}break;
		case POWERMODE_OFF : {}break;
	}
	state.powerMode = mode;
#endif
}

/*******************************************************************************
 *Переход в режимы энергосбережения
 ******************************************************************************/
void setPowerState(uint8_t mode) {
#ifdef SYSTEM_STM32
	state.taskList |= 128; //FIXME delite for work
	if(!state.taskList) {
		set_leds(LED_BLUE); //Потушили диод пошли спать
		switch(mode) {
			case POWERMODE_NORMAL : {
				__WFI();
			}break;
			case POWERMODE_SLEEP : {
				PWMSet(2, 0);
				ButtonsInit(MODE_INT); //Переключили кнопку в режим прерывания
				if(config.SleepDisplayOff)
				displayOff();
				PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
				PWMSet(2, config.PWM[2]);
				SetSysClock(CLK_24M);
				SystemCoreClockUpdate();
				state.taskList |= TASK_UPDATETIME;//Задача обновить время
				ButtonsInit(MODE_ADC);
				setPowerMode(POWERMODE_NORMAL);
				if(config.SleepDisplayOff)
				drawInit();//Запуск дисплея
			}break;
			case POWERMODE_OFF : {
				/* Enable PWR clock */
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
				/* Enable WKUP pin */
				PWR_WakeUpPinCmd(ENABLE);
				/* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
				PWR_EnterSTANDBYMode();
			}break;
		}
		reset_leds(LED_BLUE); //Зажгли диод пошли работать
	}
#endif
}

/*******************************************************************************
 *Настройка блоков соответственно состоянию
 ******************************************************************************/
void initMCU(uint8_t state) {
#ifdef SYSTEM_STM32
	switch(state) {
		case STATE_NULL : {
			init_printf(NULL, putcUSART); //Для использования функций printf, sprintf
			ButtonsInit(MODE_ADC);//Настройка портов кнопок
			/* Разрешим прерывания отказов */
			SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA;
			SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA;
			SCB->SHCSR |= SCB_SHCSR_USGFAULTENA;
		}break;
		case STATE_SLEEP : {
			displayOff();
		}break;
		case STATE_START : {
			ButtonsInit(MODE_ADC); //Настройка портов кнопок
			RTC_init();//Запуск часов реального времени
			CircleSensorInit();//Настройка входа датчика оборотов колеса
			CircleTimerInit();//Настройка таймера оборотов колеса
			SysTickInit(100);//Запуск таймера. Вызов 100 раз в секунд
			i2c_init();//Запустили i2c шину
			loadParams();//Загрузили параметры из EEPROM
			PWM_init();//Настройка ШИМ яркости
			PWMSet(0, config.PWM[0]);
			PWMSet(1, config.PWM[1]);
			PWMSet(2, config.PWM[2]);
//			USARTInit();//Настройка портов USART
			LED_init();//Настройка портов светодиодов
			beep_init();//Настройка бипера
			drawInit();//Запуск дисплея
			term_init();//Запуск внутреннего термометра
		}break;
		case STATE_MAIN : {
			SysTickInit(100); //Запуск таймера. Вызов 100 раз в секунд
			drawInit();//Запуск дисплея
			ButtonsInit(MODE_ADC);//Настройка портов кнопок
		}break;
		case STATE_OFF : {
			displayOff();
		}break;
	}
#endif
}

void SetSysClock(uint8_t clockMode) {
#ifdef SYSTEM_STM32
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;

//	  /* Set HSION bit */
//  RCC->CR |= (uint32_t)0x00000001;
//	
//	  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
//	RCC->CFGR &= (uint32_t)0xF8FF0000;
//	
//	  /* Reset HSEON, CSSON and PLLON bits */
//  RCC->CR &= (uint32_t)0xFEF6FFFF;
//	
//	  /* Reset HSEBYP bit */
//  RCC->CR &= (uint32_t)0xFFFBFFFF;
//	
//	  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
//  RCC->CFGR &= (uint32_t)0xFF80FFFF;
//	
//	  /* Disable all interrupts and clear pending bits  */
//  RCC->CIR = 0x009F0000;

//---------------------------------------------------------------------------	
//	/* Конфигурацяи  SYSCLK, HCLK, PCLK2 и PCLK1 */
//	/* Включаем HSE */
//	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
//	/* Ждем пока HSE не выставит бит готовности либо не выйдет таймаут*/
//	do
//	{
//		HSEStatus = RCC->CR & RCC_CR_HSERDY;
//		StartUpCounter++;
//	}while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
//	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
//	{
//		HSEStatus = (uint32_t)0x01;
//	}
//	else
//	{
//		HSEStatus = (uint32_t)0x00;
//	}
//	/* Если HSE запустился нормально */
//	if (HSEStatus == (uint32_t)0x01)
//	{
//		/* Включаем буфер предвыборки FLASH */
//		FLASH->ACR |= FLASH_ACR_PRFTBE;
//		/* Конфигурируем Flash на 2 цикла ожидания */
//		/* Это нужно потому, что Flash не может работать на высокой частоте */
//		FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
//		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

//		/* HCLK = SYSCLK */
//		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

//		/* PCLK2 = HCLK */
//		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

////if(clockMode == CLK_72M){
//		/* PCLK1 = HCLK / 2 */
//		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
////} else {
//		/* PCLK1 = HCLK */
//		//   RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
////}
//		/* Конфигурируем множитель PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
//		/* При условии, что кварц на 8МГц! */
//		switch(clockMode) {
//			case CLK_72M : {
//				/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
//				RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
//				RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
//			}break;
//			case CLK_24M : {
//				/*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
//				RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
//				RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
//			}break;
//			case CLK_8M : {
////	
////	    /* Select HSE as system clock source */
////    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
////    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;    

////    /* Wait till HSE is used as system clock source */
////    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04)
////    {
////    }
//				/*  PLL configuration:  = (HSE / 2) * 2 = 8 MHz */
//				RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
//				RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL2);
//			}break;
//		}
//		/* Включаем PLL */
//		RCC->CR |= RCC_CR_PLLON;

//		/* Ожидаем, пока PLL выставит бит готовности */
//		while((RCC->CR & RCC_CR_PLLRDY) == 0)
//		{
//		}
//		/* Выбираем PLL как источник системной частоты */
//		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
//		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

//		/* Ожидаем, пока PLL выберется как источник системной частоты */
//		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
//		{
//		}
//	}
//	else
//	{
//		/* Все плохо... HSE не завелся... Чего-то с кварцем или еще что...
//		 Надо бы както обработать эту ошибку... Если мы здесь, то мы работаем
//		 от HSI! */
//	}
#endif
}
