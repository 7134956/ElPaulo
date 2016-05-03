#include "config.h"
#include "power.h"
#include "main.h"
#include "string.h"
#include "rtc.h"
#include "job.h"
#include "bat.h"
#include "keyboard.h"
#include "eeprom.h"

void MCU_preinit(void);
void MCU_init(void);
void sleep(void);
void SetSysClock(uint8_t);
void turnOff(void);

power_t powerControl; //Структура с данными по питанию

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
extern count_t count;
#endif
extern state_t state;
extern config_t config;

/*******************************************************************************
 * Обслуживание энергопотребления
 ******************************************************************************/
void powerService() {
	if (powerControl.freqMCU != CLK_NULL) {
		/* Снижаем тактовую частоту до допустимого уровня */
		if (state.taskList & (TASK_CLOCK_MAX)) {
			powerControl.freqMCU = CLK_72M;
		} else if (state.taskList & (TASK_DRIVE | TASK_USER)){
			powerControl.freqMCU = CLK_24M;
			powerControl.CloclLockTime = 3;
		}
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
			state.taskList &= ~TASK_USER;
		} else if (state.taskList & TASK_POWEROFF)
			powerControl.sleepMode = POWERMODE_OFF; //Можно полностью выключить
		else if (config.SleepSec
				&& (powerControl.countToSleep == config.SleepSec)) {
			powerControl.sleepMode = POWERMODE_STOP; //Можно останавливать ядро и периферию
		} else
			powerControl.sleepMode = POWERMODE_SLEEP; //Переферия нужна. Можно останавливать только ядро

		/* Если спящий режим изменился выполним действия... */
		if (powerControl.sleepMode_prev != powerControl.sleepMode) {
			state.taskList |= TASK_REDRAW;
			if (powerControl.sleepMode == POWERMODE_STOP) {
				job_set(turnOff, RTC_GetCounter() + config.autoPowerOff * 60);
			} else if (powerControl.sleepMode_prev == POWERMODE_STOP) {
				job_del(turnOff);
			}
		} else
			sleep(); //Иначе уходим в подходящий режим сна
		powerControl.sleepMode_prev = powerControl.sleepMode;

	} else {
		MCU_preinit();
		MCU_init();
	}
	if (state.taskList & TASK_ALARM) { //Если проснулись по будильнику
		job_exe(RTC_GetCounter());
		state.taskList &= ~TASK_ALARM; //Сбрасываем флаг
	}
}

/*******************************************************************************
 * Уйти в заданный режим сна выполнив необходимые действия
 ******************************************************************************/
void sleep(void) {
	if(config.sleepOff)
		return;
#ifdef SYSTEM_STM32
	reset_leds(LED_BLUE); //Потушили диод пошли спать
	if (!(state.taskList & TASK_REDRAW)
			|| (powerControl.sleepMode == POWERMODE_OFF))
		switch (powerControl.sleepMode) {
		case POWERMODE_ACTIVE: { //Никак не спать
		}
			break;
		case POWERMODE_SLEEP: { //Остановим ядро до любого события
			if(state.taskList & TASK_BAT_MEASURE)
				bat_measure();
			__WFE();
		}
			break;
		case POWERMODE_STOP: { //Разрешено выключить тактировку переферии
			TIM_SetCompare2(TIM2, 0); //Гасим подсветку экрана
			TIM_SetCompare3(TIM2, 0); //Гасим фару
			keyInit(MODE_INT); //Переключили кнопку в режим прерывания
			USARTEXTIInit(); //Настройка порта отладочных сообщений на пробуждение
			if (config.SleepDisplayOff) {
				displayOff();
				setAlarm(job_next()); //Установит будильник на следующее задание
			} else
				setAlarm(RTC_GetCounter()-(RTC_GetCounter()%60)+60); //Установим будильник на следующую минуту
			while(DMA1_Channel3->CCR & DMA_CCR3_EN){};
			PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);
			if (state.taskList & TASK_ALARM) { //Если проснулись по будильнику
				job_exe(RTC_GetCounter());
				state.taskList &= ~TASK_ALARM; //Сбрасываем флаг
			}
			else {
				setAlarm(job_next()); //Установит будильник на следующее задание
				PWMSet(1, config.PWM[1]);
				PWMSet(0, config.PWM[0]);
				powerControl.freqMCU_prev = CLK_NULL;
				SetClock();
				keyInit(MODE_ADC);
				powerControl.sleepMode = POWERMODE_SLEEP;	// Убрали СТОП режим
				if (config.SleepDisplayOff) {
					displayOn();
				}
			}
		}
			break;
		case POWERMODE_OFF: {
			saveTrack();
			job_del(&saveTrack);
			displayOff();
			BKP_WriteBackupRegister(BKP_DR2, 0); //Сбросили ошибки
			setAlarm(job_next()); //Установит будильник на следующее задание
			/* Enable PWR clock */
			RCC->APB1ENR |= RCC_APB1Periph_PWR;
			/* Enable WKUP pin */
			PWR->CSR |= PWR_CSR_EWUP;
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
 * Выключить питание.
 ******************************************************************************/
void turnOff(void) {
#ifdef SYSTEM_STM32
	state.taskList |= TASK_POWEROFF;
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
//	uint8_t onCounter;

	/* Настройка группы приоритета прерывания */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* Копировали флаги сброса */
	state.reset = ((RCC->CSR) >> 24);
	/* Обнуляем флаги сброса */
	RCC_ClearFlag();
	/* Разрешим прерывания отказов */
	SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA | SCB_SHCSR_MEMFAULTENA | SCB_SHCSR_USGFAULTENA;
	powerControl.freqMCU = CLK_24M; //Целевая частота ядра
	SetClock();
	/* Отключаем JTAG */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	init_printf(NULL, putcUSART); //Для использования функции printf
	keyInit(MODE_ADC); //Настройка портов кнопок
	if (state.reset & (RESET_FLAG_PINRST | RESET_FLAG_PORRST |	RESET_FLAG_LPWRRST |
	RESET_FLAG_WWDGRST | RESET_FLAG_IWDGRST | RESET_FLAG_SFTRST))
		return;
	/* Enable PWR clock */
	RCC->APB1ENR |= RCC_APB1Periph_PWR;
	/* Disable WKUP pin */
	PWR->CSR &= ~PWR_CSR_EWUP;
	/* Disable PWR clock */
	RCC->APB1ENR &= ~RCC_APB1Periph_PWR;
	/* Цикл проверки условия включения */
//	while (1) {
//		ADC_SoftwareStartConvCmd(ADC2, ENABLE);
//		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Включаем тактирование таймера
//		TIM4->CNT = 0; //Обнуляем счетчик
//		while (TIM_GetCounter(TIM4) < 3277)
//			;
//		RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN; //Выключаем тактирование таймера
//		if (ADC_GetConversionValue(ADC2) > 500) {
//			if (onCounter < 5)
//				onCounter++;
//			else
//				break;
//		} else {
//			powerControl.sleepMode = POWERMODE_OFF;
//			sleep(); //Если нет условий для включения, вырубаем
//		}
//	}
#endif
}

/*******************************************************************************
 * Настройка перефирии микроконтроллера
 ******************************************************************************/
void MCU_init(void) {
#ifdef SYSTEM_STM32
	i2c_init(); //Запустили i2c шину
	EEPROM_reset();
	RTC_init(); //Запуск часов реального времени
	keyInitVal();
	batInit();
	loadParams(); //Загрузили параметры из EEPROM
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
	batInit(); //Батарея велокомпа
//	IWDG_Init(7, 156); //Запустили сторожевой таймер на отсчет 500 мсек
#endif
}

/*******************************************************************************
 * Настройка тактовой частоты и переферии под частоту
 ******************************************************************************/
void SetClock(void) {
	if((!powerControl.CloclLockTime && powerControl.freqMCU < powerControl.freqMCU_prev) || (powerControl.freqMCU > powerControl.freqMCU_prev)){
#ifdef SYSTEM_STM32
		SetSysClock(powerControl.freqMCU); // Установим частоты шин
		CircleTimerInit(); //Настройка таймера оборотов колеса и прочего счета
		SysTickInit(100); //Запуск системного таймера. Вызов 100 раз в секунд
		USARTInit(); //Настройка порта отладочных сообщений
		beep_init(); //Настройка бипера
//		PWM_init(); //Настройка ШИМ
#endif
		powerControl.freqMCU_prev = powerControl.freqMCU;
		powerControl.CloclLockTime = 3;
		state.taskList |= TASK_REDRAW;
	}
}

/*******************************************************************************
 * Настройка тактировок
 * Кварц на 8МГц
 * ADC = 4MHz
 ******************************************************************************/
void SetSysClock(uint8_t clockMode) {
#ifdef SYSTEM_STM32
	__IO uint32_t
	HSEStatus = RESET;
	uint16_t StartUpCounter = 0;
	/* Конфигурацяи  SYSCLK, HCLK, PCLK2 и PCLK1 */
	/* Включаем HSE */
	RCC->CR |= RCC_CR_HSEON;
	/* Ждем пока HSE не выставит бит готовности либо не выйдет таймаут*/
	do {
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
	/* Включаем буфер предвыборки FLASH */
	FLASH->ACR |= FLASH_ACR_PRFTBE;
	/* Если HSE запустился нормально */
	if (RCC->CR & RCC_CR_HSERDY) {
		/* HSE как тактовый источник */
		RCC->CFGR &=  ~RCC_CFGR_SW;
		RCC->CFGR |= RCC_CFGR_SW_HSE;
		/* Ожидание готовности HSE */
		while ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SW_HSE);
		/* Отключаем PLL для настройки*/
		RCC->CR &= ~RCC_CR_PLLON;
		/* Конфигурируем частоты RCC.*/
		switch (clockMode) {
		case CLK_72M: {
			/* PLLCLK = HSE * 9 = 72 MHz, APB1 = PLLCLK / 2 = 36MHz, FLASH_LATENCY = 2, ADC = HCLK / 8 = 4 */
			RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL | RCC_CFGR_PPRE1 | RCC_PCLK2_Div8);
			RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9 | RCC_CFGR_PPRE1_DIV2 | RCC_PCLK2_Div8;
			FLASH->ACR &= ~FLASH_ACR_LATENCY;
			FLASH->ACR |= FLASH_ACR_LATENCY_2;
		}
			break;
		case CLK_24M: {
			/*  PLLCLK = HSE * 3 = 24 MHz, APB1 = PLLCLK = 24MHz, FLASH_LATENCY = 1, ADC = HCLK / 6 = 4 */
			RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL | RCC_CFGR_PPRE1 | RCC_PCLK2_Div8);
			RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6 | RCC_CFGR_PPRE1_DIV1 | RCC_PCLK2_Div6;
			FLASH->ACR &= ~FLASH_ACR_LATENCY;
			FLASH->ACR |= FLASH_ACR_LATENCY_1;
		}
			break;
		case CLK_8M: {
			/*  SYSCLK = HSE = 8 MHz, APB1 = PLLCLK = 8MHz, FLASH_LATENCY = 0, ADC = HCLK / 2 = 4 */
			FLASH->ACR &= ~FLASH_ACR_LATENCY;
			FLASH->ACR |= FLASH_ACR_LATENCY_0;
			RCC->CFGR &= ~(RCC_CFGR_PPRE1 | RCC_PCLK2_Div8);
			RCC->CFGR &= RCC_PCLK2_Div2;
		}
			break;
		}
		if (clockMode != CLK_8M) {
			/* Включаем PLL */
			RCC->CR |= RCC_CR_PLLON;
			/* Ожидаем, пока PLL выставит бит готовности */
			while ((RCC->CR & RCC_CR_PLLRDY) == 0);
			/* Выбираем PLL как источник системной частоты */
			RCC->CFGR &=  ~RCC_CFGR_SW;
			RCC->CFGR |= RCC_CFGR_SW_PLL;
			/* Ожидаем, пока PLL выберется как источник системной частоты */
			while ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SW_PLL);
		}
		//Отключим лишнее
		RCC->CR &= ~(RCC_CR_HSION | RCC_CR_HSEBYP);
	} else {
		ERR("HSE not started");
	}
	SystemCoreClockUpdate();
#endif
}

