#include "config.h"
#include "power.h"
#include "main.h"
#include "string.h"
#include "rtc.h"

void MCU_preinit(void);
void MCU_init(void);
void sleep(void);
void SetSysClock(uint8_t);

power_t powerControl; //Структура с данными по питанию

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
extern config_t config;
extern count_t count;
#endif
extern state_t state;

#ifdef SYSTEM_STM32
/*******************************************************************************
 *Обслуживание энергопотребления
 ******************************************************************************/
void powerService() {
	if (powerControl.freqMCU != CLK_NULL) {

		if (!powerControl.CloclLockTime) { //Прошел лимит времени удержания частоты
			/* Снижаем тактовую частоту до допустимого уровня */
			if (state.taskList & (TASK_CLOCK_MAX)) {
				powerControl.freqMCU = CLK_72M;
			} else if (state.taskList & (TASK_DRIVE))
				powerControl.freqMCU = CLK_24M;
			else
				powerControl.freqMCU = CLK_8M;
			SetClock(); //Задали частоты
		}

		/* Выбираем доступный режим сна */
		if (state.taskList
				& (TASK_REDRAW | TASK_UPDATETIME | TASK_SAVEPARAMS)) {
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
}
#endif

/*******************************************************************************
 * Уйти в заданный режим сна выполнив необходимые действия
 ******************************************************************************/
#ifdef SYSTEM_STM32
void sleep(void) {
	reset_leds(LED_BLUE); //Потушили диод пошли спать
	
	if(!(state.taskList & TASK_REDRAW) || (powerControl.sleepMode == POWERMODE_OFF))
		switch (powerControl.sleepMode) {
		case POWERMODE_ACTIVE: { //Никак не спать
		}
			break;
		case POWERMODE_SLEEP: { //Остановим ядро до любого события
			__WFI();
		}
			break;
		case POWERMODE_STOP: { //Разрешено выключить тактировку переферии
			PWMSet(2, 0); //Гасим подсветку
			ButtonsInit(MODE_INT); //Переключили кнопку в режим прерывания
			if (config.SleepDisplayOff){
				displayOff();
			}
			else
				setAlarm(0); //Установит будильник на следующую минуту
			PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
			if(state.taskList & TASK_ALARM) //Если проснулись по будильнику
				state.taskList &=~ TASK_ALARM; //Сбрасываем флаг
				else{													//иначе
			PWMSet(2, config.PWM[2]);
			powerControl.freqMCU_prev = CLK_NULL;
			SetClock();
//			state.taskList |= TASK_UPDATETIME | TASK_REDRAW; //Задача обновить время
			ButtonsInit(MODE_ADC);
			powerControl.sleepMode = POWERMODE_SLEEP;// Убрали СТОП режим
			if (config.SleepDisplayOff)
				drawInit(); //Запуск дисплея
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
}

/*******************************************************************************
 * Начальная инициализация и проверка условий запуска.
 ******************************************************************************/
void MCU_preinit(void) {
#ifdef SYSTEM_STM32
	uint8_t onCounter;
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
	ButtonsInit(MODE_ADC); //Настройка портов кнопок
	/* Цикл проверки условия включения */
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
	i2c_init(); //Запустили i2c шину
	RTC_init(); //Запуск часов реального времени
	ButtonsInit(MODE_ADC); //Настройка портов кнопок
	loadParams(); //Загрузили параметры из EEPROM
	setStrings(&config.lang); //Установили язык
	drawInit(); //Запуск дисплея
	PWM_init(); //Настройка ШИМ
	PWMSet(0, config.PWM[0]);
	PWMSet(1, config.PWM[1]);
	PWMSet(2, config.PWM[2]);
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
	if (powerControl.freqMCU_prev != powerControl.freqMCU) {
		SetSysClock(powerControl.freqMCU); // Установим частоты шин
		SystemCoreClockUpdate(); //Обновили значение частоты
		if (powerControl.freqMCU_prev != powerControl.freqMCU) {
			SysTickInit(100); //Запуск системного таймера. Вызов 100 раз в секунд
			beep_init(); //Настройка бипера
			CircleTimerInit(); //Настройка таймера оборотов колеса и прочего счета
			USARTInit(); //Настройка портов USART
		}
		powerControl.freqMCU_prev = powerControl.freqMCU;
	}
	powerControl.CloclLockTime = 2;
}

/*******************************************************************************
 *Настройка тактировок
 ******************************************************************************/
void SetSysClock(uint8_t clockMode) {
	__IO uint32_t
	HSEStatus = RESET;
	uint16_t StartUpCounter = 0;
//	Сбрасываем все перед настройкой
	/* Set HSION bit */
	RCC->CR |= (uint32_t) 0x00000001;

	/* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
	RCC->CFGR &= (uint32_t) 0xF8FF0000;

	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t) 0xFEF6FFFF;

	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t) 0xFFFBFFFF;

	/* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	RCC->CFGR &= (uint32_t) 0xFF80FFFF;

	/* Disable all interrupts and clear pending bits  */
	RCC->CIR = 0x009F0000;

//---------------------------------------------------------------------------	
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
	//	FLASH->ACR &= (uint32_t)((uint32_t) ~FLASH_ACR_LATENCY);
	//	if (clockMode == CLK_8M)
		//	FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_0;
	//	else if (clockMode == CLK_24M)
	//		FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_1;
	//	else if (clockMode == CLK_72M)
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
		if (clockMode == CLK_8M) {
			/* Select HSE as system clock source */
			RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_SW));
			RCC->CFGR |= (uint32_t) RCC_CFGR_SW_HSE;

			/* Wait till HSE is used as system clock source */
			while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x04) {
			}
//				/*  PLL configuration:  = (HSE / 2) * 2 = 8 MHz */
//				RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
//				RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL2);
		} else {
			/* Конфигурируем множитель PLL. При условии, что кварц на 8МГц!*/
			switch (clockMode) {
			case CLK_72M: {
				/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
				RCC->CFGR &= (uint32_t)(
						(uint32_t) ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE
								| RCC_CFGR_PLLMULL));
				RCC->CFGR |= (uint32_t)(
						RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
			}
				break;
			case CLK_24M: {
				/*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
				RCC->CFGR &= (uint32_t)(
						(uint32_t) ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE
								| RCC_CFGR_PLLMULL));
				RCC->CFGR |= (uint32_t)(
						RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2
								| RCC_CFGR_PLLMULL6);
			}
				break;
			}
			/* Включаем PLL */
			RCC->CR |= RCC_CR_PLLON;
			/* Ожидаем, пока PLL выставит бит готовности */
			while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
			}
			/* Выбираем PLL как источник системной частоты */
			RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_SW));
			RCC->CFGR |= (uint32_t) RCC_CFGR_SW_PLL;
			/* Ожидаем, пока PLL выберется как источник системной частоты */
			while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x08) {
			}
		}
		//Отключим лишнее
		RCC->CR &= (uint32_t)((uint32_t) ~(RCC_CR_HSION | RCC_CR_HSEBYP));
	} else {
		ERR("HSE not started");
	}
	SystemCoreClockUpdate();
}
#endif
