#include "config.h"
#include "power.h"
#include "main.h"
#include "string.h"
#include "rtc.h"
#include "job.h"
#include "bat.h"
#include "keyboard.h"

void MCU_preinit(void);
void MCU_init(void);
void sleep(void);
void SetSysClock(uint8_t);

power_t powerControl; //Структура с данными по питанию

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
extern count_t count;
#endif
extern state_t state;
extern config_t config;

/*******************************************************************************
 *Обслуживание энергопотребления
 ******************************************************************************/
void powerService() {
	if (powerControl.freqMCU != CLK_NULL) {
		/* Снижаем тактовую частоту до допустимого уровня */
		if (state.taskList & (TASK_CLOCK_MAX)) {
			powerControl.freqMCU = CLK_72M;
		} else if (state.taskList & (TASK_DRIVE))
			powerControl.freqMCU = CLK_24M;
		else
			powerControl.freqMCU = CLK_8M;
		SetClock(); //Задали частоты

		/* Выбираем доступный режим сна */
		if (state.taskList
	//			& (TASK_REDRAW | TASK_UPDATETIME | TASK_SAVEPARAMS)) {
				& (TASK_UPDATETIME)) {
			powerControl.sleepMode = POWERMODE_ACTIVE; //Все работает постоянно
			powerControl.countToSleep = 0; //А сон отсрочим
		} else if (state.taskList
				& (TASK_LIM_REDRAW | TASK_TIMER | TASK_STOPWATCH | TASK_DRIVE
						| TASK_TIMESETUP | TASK_USER)) {
			powerControl.sleepMode = POWERMODE_SLEEP; //Переферия нужна. Можно останавливать только ядро
			powerControl.countToSleep = 0;
			state.taskList &= ~ TASK_USER;
		} else if (state.taskList & TASK_POWEROFF)
			powerControl.sleepMode = POWERMODE_OFF; //Можно полностью выключить
		else if (config.SleepSec
				&& (powerControl.countToSleep == config.SleepSec)) {
			powerControl.sleepMode = POWERMODE_STOP; //Можно останавливать ядро и периферию
		} else
			powerControl.sleepMode = POWERMODE_SLEEP; //Переферия нужна. Можно останавливать только ядро

		/* Если спящий режим изменился выполним действия... */
		if (powerControl.sleepMode_prev != powerControl.sleepMode)
			state.taskList |= TASK_REDRAW;
		else
			sleep(); //Иначе уходим в подходящий режим сна
		powerControl.sleepMode_prev = powerControl.sleepMode;

	} else {
		MCU_preinit();
		MCU_init();
	}
	if (state.taskList & TASK_ALARM) { //Если проснулись по будильнику
		job_exe(RTC_GetCounter());
		state.taskList &= ~ TASK_ALARM; //Сбрасываем флаг
	}
}

/*******************************************************************************
 * Уйти в заданный режим сна выполнив необходимые действия
 ******************************************************************************/
void sleep(void) {
#ifdef SYSTEM_STM32
	reset_leds(LED_BLUE); //Потушили диод пошли спать

	if (!(state.taskList & TASK_REDRAW)
			|| (powerControl.sleepMode == POWERMODE_OFF))
		switch (powerControl.sleepMode) {
		case POWERMODE_ACTIVE: { //Никак не спать
		}
			break;
		case POWERMODE_SLEEP: { //Остановим ядро до любого события
			__WFE();
		}
			break;
		case POWERMODE_STOP: { //Разрешено выключить тактировку переферии
			PWMSet(1, 0); //Гасим подсветку
//#ifdef KEYBOARD_ADC
			keyInit(MODE_INT); //Переключили кнопку в режим прерывания
//#endif
			USARTEXTIInit(); //Настройка порта отладочных сообщений на пробуждение
			if (config.SleepDisplayOff) {
				displayOff();
				setAlarm(job_next()); //Установит будильник на следующее задание
			} else
				setAlarm(0); //Установит будильник на следующую минуту
			while(DMA1_Channel3->CCR & DMA_CCR3_EN){};
			PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);
			if (state.taskList & TASK_ALARM) { //Если проснулись по будильнику
				job_exe(RTC_GetCounter());
				state.taskList &= ~ TASK_ALARM; //Сбрасываем флаг
			}
			else {													//иначе
				setAlarm(job_next()); //Установит будильник на следующее задание
				PWMSet(1, config.PWM[1]);
				powerControl.freqMCU_prev = CLK_NULL;
				SetClock();
//#ifdef KEYBOARD_ADC
				keyInit(MODE_ADC);
//#endif
				powerControl.sleepMode = POWERMODE_SLEEP;	// Убрали СТОП режим
				if (config.SleepDisplayOff) {
					displayOn();
				}
			}
		}
			break;
		case POWERMODE_OFF: {
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
#endif
#ifdef SYSTEM_WIN
	job_exe(RTC_GetCounter());
#endif
}

/*******************************************************************************
 * Начальная инициализация и проверка условий запуска.
 ******************************************************************************/
void MCU_preinit(void) {
#ifdef SYSTEM_WIN
	powerControl.freqMCU = CLK_8M;
#endif
#ifdef SYSTEM_STM32
	uint8_t onCounter;
	/* Копировали флаги сброса */
	state.reset = ((RCC->CSR) >> 24);
	/* Обнуляем флаги сброса */
	RCC_ClearFlag();
	/* Разрешим прерывания отказов */
	SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA;
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA;
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA;
	powerControl.freqMCU = CLK_24M; //Целевая частота ядра
	SetClock();
//#ifdef DEBUG
//	init_printf(NULL, DBG_print); //Для использования функций printf, sprintf
//#else		
	init_printf(NULL, putcUSART); //Для использования функций printf, sprintf
//#endif			
	keyInit(MODE_ADC); //Настройка портов кнопок
	if (state.reset & (RESET_FLAG_PINRST |
										RESET_FLAG_PORRST |
										RESET_FLAG_LPWRRST |
										RESET_FLAG_WWDGRST |
										RESET_FLAG_IWDGRST |
										RESET_FLAG_SFTRST))
		return;
	/* Цикл проверки условия включения */
	while (1) {
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);
//		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Включаем тактирование таймера
//		TIM4->CNT = 0; //Обнуляем счетчик
//		while (TIM_GetCounter(TIM4) < 3277)
//			;
//		RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN; //Выключаем тактирование таймера
		if (ADC_GetConversionValue(ADC2) > 500) {
			if (onCounter < 5)
				onCounter++;
			else
				break;
		} else {
			powerControl.sleepMode = POWERMODE_OFF;
			sleep(); //Если нет условий для включения, вырубаем
		}
	}
#endif
}

/*******************************************************************************
 * Настройка перефирии микроконтроллера
 ******************************************************************************/
void MCU_init(void) {
#ifdef SYSTEM_STM32
	uint8_t langEng = LANGUAGE_ENG;
	i2c_init(); //Запустили i2c шину
	RTC_init(); //Запуск часов реального времени
//	keyInit(MODE_ADC); //Настройка портов кнопок
//	USART2Init(); //Настройка входа цифровой клавиатуры
	batInit();
	loadParams(); //Загрузили параметры из EEPROM
	setStrings(&langEng); //Сначала язык по умолчанию
	setStrings(&config.lang); //Установили заданный язык
	drawInit(); //Запуск дисплея
	PWM_init(); //Настройка ШИМ
	PWMSet(0, config.PWM[0]);
	PWMSet(1, config.PWM[1]);
	CircleSensorInit();
	LED_init(); //Настройка портов светодиодов
	beep_init(); //Настройка бипера
//	term_init(); //Запуск внутреннего термометра
	BMS_init(); //Подготовка к работе с BMS
//	IWDG_Init(7, 156); //Запустили сторожевой таймер на отсчет 500 мсек
#endif
}

/*******************************************************************************
 *Настройка тактовой частоты и переферии под частоту
 ******************************************************************************/
void SetClock(void) {
	if((!powerControl.CloclLockTime && powerControl.freqMCU < powerControl.freqMCU_prev) || (powerControl.freqMCU > powerControl.freqMCU_prev)){
#ifdef SYSTEM_STM32
			SetSysClock(powerControl.freqMCU); // Установим частоты шин
			SysTickInit(100); //Запуск системного таймера. Вызов 100 раз в секунд
			beep_init(); //Настройка бипера
			CircleTimerInit(); //Настройка таймера оборотов колеса и прочего счета
			USARTInit(); //Настройка порта отладочных сообщений
			USART2Init(); //Настройка входа цифровой клавиатуры
#endif
		powerControl.freqMCU_prev = powerControl.freqMCU;
	}
	powerControl.CloclLockTime = 3;
}

/*******************************************************************************
 *Настройка тактировок
 ******************************************************************************/
void SetSysClock(uint8_t clockMode) {
#ifdef SYSTEM_STM32
	__IO uint32_t
	HSEStatus = RESET;
	uint16_t StartUpCounter = 0;
	/* Конфигурацяи  SYSCLK, HCLK, PCLK2 и PCLK1 */
	/* Включаем HSE */
	RCC->CR |= ((uint32_t) RCC_CR_HSEON);
	/* Ждем пока HSE не выставит бит готовности либо не выйдет таймаут*/
	do {
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	/* Если HSE запустился нормально */
	if ((RCC->CR & RCC_CR_HSERDY)) {
		/* Включаем буфер предвыборки FLASH */
		FLASH->ACR |= FLASH_ACR_PRFTBE;
		/* Конфигурируем цикл ожидания Flash */
		/* Это нужно потому, что Flash не может работать на высокой частоте */
		FLASH->ACR &= (uint32_t)((uint32_t) ~FLASH_ACR_LATENCY);
		if (clockMode == CLK_8M)
			FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_0;
		else if (clockMode == CLK_24M)
			FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_1;
		else if (clockMode == CLK_72M)
			FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_2;

		/* HCLK = SYSCLK */
//		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
		/* PCLK2 = HCLK */
//		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
		if (clockMode == CLK_72M) {
			/* PCLK1 = HCLK / 2 */
			RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV2;
		} else {
			/* PCLK1 = HCLK */
			RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV1;
		}
		if (clockMode == CLK_8M || RCC->CR & RCC_CR_PLLON) {
			/* Select HSE as system clock source */
			RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_SW));
			RCC->CFGR |= (uint32_t) RCC_CFGR_SW_HSE;

			/* Wait till HSE is used as system clock source */
			while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) == (uint32_t) RCC_CFGR_SW_HSE) {};
			RCC->CR &= ~RCC_CR_PLLON;

//				/*  PLL configuration:  = (HSE / 2) * 2 = 8 MHz */
//				RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
//				RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL2);
		}
		/* Конфигурируем множитель PLL. При условии, что кварц на 8МГц!*/
		switch (clockMode) {
		case CLK_72M: {
			/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
			RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
			RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
		}
			break;
		case CLK_24M: {
			/*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
			RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
			RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
		}
			break;
		}
		if (clockMode != CLK_8M) {
			/* Включаем PLL */
			RCC->CR |= RCC_CR_PLLON;
			/* Ожидаем, пока PLL выставит бит готовности */
			while ((RCC->CR & RCC_CR_PLLRDY) == 0) {};
			/* Выбираем PLL как источник системной частоты */
			RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_SW));
			RCC->CFGR |= (uint32_t) RCC_CFGR_SW_PLL;
			/* Ожидаем, пока PLL выберется как источник системной частоты */
			while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS)== (uint32_t) RCC_CFGR_SW_PLL) {};
		}
		//Отключим лишнее
		RCC->CR &= (uint32_t)((uint32_t) ~(RCC_CR_HSION | RCC_CR_HSEBYP));
	} else {
		ERR("HSE not started");
	}
	SystemCoreClockUpdate();
#endif
}

