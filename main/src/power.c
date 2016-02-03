#include "config.h"
#include "power.h"
#include "main.h"

//Выбор режима сна процессора (powerstate)
#define POWERSTATE_STOP 1 //Остановка ядра.
#define POWERSTATE_SLEEP 2 //Остановка тактирования
#define POWERSTATE_OFF 3 //Полное выключение

void sleep(uint8_t);
void SetSysClock(uint8_t);

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
extern config_t config;
extern count_t count;
#endif
extern state_t state;

uint8_t powerModeSet = POWERMODE_NULL;
#ifdef SYSTEM_STM32
/*******************************************************************************
 *Обслуживание энергопотребления
 ******************************************************************************/
void powerService() {
	uint8_t onCounter = 0;
	if (state.powerMode == POWERMODE_NORMAL)
		if (state.taskList & ~(TASK_TIMER | TASK_STOPWATCH))
			setPowerMode(POWERSTATE_SLEEP);
	if (state.powerMode == POWERMODE_NULL) {
		setPowerMode(POWERMODE_NULL);
		while (1) {
			ADC_SoftwareStartConvCmd(ADC2, ENABLE);
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Включаем тактирование таймера
			TIM4->CNT = 0; //Обнуляем счетчик
			while (TIM_GetCounter(TIM4) < 3277)
				;
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN; //Выключаем тактирование таймера
			if (ADC_GetConversionValue(ADC2) > 500) {
				if (onCounter < 5)
					onCounter++;
				else {
					setPowerMode(POWERMODE_NORMAL);
					break;
				}
			} else
				sleep(POWERSTATE_OFF); //Если нет условий для включения, вырубаем
		}
	} else if (state.powerMode == POWERMODE_SLEEP)
		sleep(POWERSTATE_SLEEP);

	if (state.powerMode != powerModeSet)
		setPowerMode(state.powerMode);
}
#endif

/*******************************************************************************
 *Переход в указанный режим работы
 ******************************************************************************/
void setPowerMode(uint8_t mode) {
#ifdef SYSTEM_STM32
	if (powerModeSet == mode) {
		switch (mode) {
		case POWERMODE_NORMAL: {
			count.toSleep = 0; //Не спать, не спать!
		}
			break;
		case POWERMODE_NULL: {
			/* Разрешим прерывания отказов */
			SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA;
			SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA;
			SCB->SHCSR |= SCB_SHCSR_USGFAULTENA;
			SetSysClock(CLK_24M);
#ifdef DEBUG
			init_printf(NULL, DBG_print); //Для использования функций printf, sprintf
#else		
			init_printf(NULL, putcUSART); //Для использования функций printf, sprintf
#endif			
			ButtonsInit(MODE_ADC); //Настройка портов кнопок
			CircleTimerInit(); //Настройка таймера оборотов колеса и прочего счета
		}
			break;
		}
	} else {
		switch (mode) {
//		case POWERMODE_ACTIVE : {}break;
		case POWERMODE_NORMAL: {
			SysTickInit(100); //Запуск системного таймера. Вызов 100 раз в секунд
			drawInit(); //Запуск дисплея
			ButtonsInit(MODE_ADC); //Настройка портов кнопок
			RTC_init(); //Запуск часов реального времени
			CircleSensorInit(); //Настройка входа датчика оборотов колеса
			SysTickInit(100); //Запуск таймера. Вызов 100 раз в секунд
			i2c_init(); //Запустили i2c шину
			loadParams(); //Загрузили параметры из EEPROM
			PWM_init(); //Настройка ШИМ
			PWMSet(0, config.PWM[0]);
			PWMSet(1, config.PWM[1]);
			PWMSet(2, config.PWM[2]);
			USARTInit(); //Настройка портов USART
			LED_init(); //Настройка портов светодиодов
			beep_init(); //Настройка бипера
			drawInit(); //Запуск дисплея
			term_init(); //Запуск внутреннего термометра
			BMS_init(); //Подготовка к работе с BMS
			//IWDG_Init(7, 156);//Запустили сторожевой таймер на отсчет 500 мсек
		}
			break;
		case POWERMODE_SLEEP: {
			state.taskList |= TASK_REDRAW;
		}
			break;
		case POWERMODE_OFF: {
			sleep(POWERSTATE_OFF);
		}
			break;
		}
	}
#endif
	state.powerMode = mode;
	powerModeSet = mode;
}

#ifdef SYSTEM_STM32
/*******************************************************************************
 *Уйти в заданный режим сна выполнив необходимые действия
 ******************************************************************************/
void sleep(uint8_t powerstate) {
	reset_leds(LED_BLUE); //Потушили диод пошли спать
	switch (powerstate) {
	case POWERSTATE_STOP: { //Остановим ядро до любого события
		__WFI();
	}
		break;
	case POWERSTATE_SLEEP: {
		PWMSet(2, 0); //Гасим подсветку
		ButtonsInit(MODE_INT); //Переключили кнопку в режим прерывания
		if (config.SleepDisplayOff)
			displayOff();
		PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
		PWMSet(2, config.PWM[2]);
		SetSysClock(CLK_24M);
		SystemCoreClockUpdate();
		state.taskList |= TASK_UPDATETIME; //Задача обновить время
		ButtonsInit(MODE_ADC);
		setPowerMode(POWERMODE_NORMAL);
		if (config.SleepDisplayOff)
			drawInit(); //Запуск дисплея
	}
		break;
	case POWERSTATE_OFF: {
		/* Enable PWR clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
		/* Enable WKUP pin */
		PWR_WakeUpPinCmd(ENABLE);
		/* Request to enter STANDBY mode (Wake Up flag is cleared in PWR_EnterSTANDBYMode function) */
		PWR_EnterSTANDBYMode();
	}
		break;
	}
	set_leds(LED_BLUE); //Зажгли диод пошли работать
}

/*******************************************************************************
 *Настройка тактовой частоты
 ******************************************************************************/
void SetSysClock(uint8_t clockMode) {
	__IO uint32_t HSEStatus = RESET;
	uint16_t StartUpCounter = 0;
	//	Сбрасываем все перед настройкой
	/* Set HSION bit */
	RCC->CR |= (uint32_t)0x00000001;

	/* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
	RCC->CFGR &= (uint32_t)0xF8FF0000;

	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t)0xFEF6FFFF;

	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t)0xFFFBFFFF;

	/* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	RCC->CFGR &= (uint32_t)0xFF80FFFF;

	/* Disable all interrupts and clear pending bits  */
	RCC->CIR = 0x009F0000;

//---------------------------------------------------------------------------	
	/* Конфигурацяи  SYSCLK, HCLK, PCLK2 и PCLK1 */
	/* Включаем HSE */
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
	/* Ждем пока HSE не выставит бит готовности либо не выйдет таймаут*/
	do
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	}while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	/* Если HSE запустился нормально */
	if ((RCC->CR & RCC_CR_HSERDY))
	{
		/* Включаем буфер предвыборки FLASH */
		FLASH->ACR |= FLASH_ACR_PRFTBE;
		/* Конфигурируем цикл ожидания Flash */
		/* Это нужно потому, что Flash не может работать на высокой частоте */
		FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
		if(clockMode == CLK_8M)
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0;
		else if(clockMode == CLK_24M)
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;
		else if(clockMode == CLK_72M)
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

		/* HCLK = SYSCLK */
//		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
		/* PCLK2 = HCLK */
//		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
		if(clockMode == CLK_72M) {
			/* PCLK1 = HCLK / 2 */
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
		} else {
			/* PCLK1 = HCLK */
		   RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
		}
		if(clockMode == CLK_8M) {
			/* Select HSE as system clock source */
			RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
			RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;

			/* Wait till HSE is used as system clock source */
			while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04)
			{
			}
//				/*  PLL configuration:  = (HSE / 2) * 2 = 8 MHz */
//				RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
//				RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL2);
		} else {
			/* Конфигурируем множитель PLL. При условии, что кварц на 8МГц!*/
			switch(clockMode) {
				case CLK_72M : {
					/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
					RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
					RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
				}break;
				case CLK_24M : {
					/*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
					RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
					RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);

				}break;
			}
			/* Включаем PLL */
			RCC->CR |= RCC_CR_PLLON;
			/* Ожидаем, пока PLL выставит бит готовности */
			while((RCC->CR & RCC_CR_PLLRDY) == 0)
			{
			}
			/* Выбираем PLL как источник системной частоты */
			RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
			RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
			/* Ожидаем, пока PLL выберется как источник системной частоты */
			while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
			{
			}
		}
		//Отключим лишнее
		RCC->CR &= (uint32_t)((uint32_t)~(RCC_CR_HSION | RCC_CR_HSEBYP));
	}
	else
	{
		ERR("HSE not started");
	}
	SystemCoreClockUpdate();
}
#endif
