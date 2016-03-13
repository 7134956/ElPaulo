#include "config.h"
#include "power.h"
#include "rtc.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

#define JD0 2451911 // Число дней до 01 января 2001 года

#ifdef SYSTEM_WIN
uint32_t RTC_Counter;
#endif

void Time_Adjust(tm_t*);
void RTC_Configuration(void);
void NVIC_Configuration(void);
void NVIC_GenerateSystemReset(void);
uint8_t isleapyear(uint16_t);

extern state_t state;
extern config_t config;
extern uint32_t i2cTimeLimit;
extern power_t powerControl;

tm_t dateTime; //Структура с актуальной датой и временем
/*******************************************************************************
 * Сколько дней в месяце
 ******************************************************************************/
uint8_t lastdayofmonth(uint16_t year, uint8_t month) {
	uint8_t lastdaysofmonths[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && isleapyear(year))
		return 29;
	return lastdaysofmonths[month];
}

/*******************************************************************************
 * Какой день недели
 ******************************************************************************/
uint8_t weekDay(uint8_t day, uint8_t month, uint16_t year) {
	uint8_t a;
	uint8_t m;
	uint16_t y;
	day += 5; //Первым будет понедельник
	a = (14 - month) / 12;
	y = year - a;
	m = month + 12 * a - 2;
	return ((7000 + (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) + 1)
			% 7;
}

/*******************************************************************************
 * Проверка на високосность
 ******************************************************************************/
uint8_t isleapyear(uint16_t year) {
	if (year % 400 == 0)
		return 1;
	if (year % 100 == 0)
		return 0;
	return year % 4 == 0;
}

/*******************************************************************************
 * Установка или взятие времени
 ******************************************************************************/
tm_t * timeGetSet(tm_t * t) {
	if (!t) {
		return &dateTime;
	} else {
#ifdef SYSTEM_STM32
		Time_Adjust(t);
#endif
#ifdef SYSTEM_WIN
		RTC_Counter = FtimeToCounter(t);
#endif
		state.taskList |= TASK_UPDATETIME;
		return NULL;
	}
}

/*******************************************************************************
 * Запуск часов
 ******************************************************************************/
void RTC_init(void) {
#ifdef SYSTEM_WIN
	dateTime.tm_year = 116;
	dateTime.tm_mon = 1;
	dateTime.tm_mday = 1;
	dateTime.tm_hour = 12;
	dateTime.tm_min = 0;
	dateTime.tm_sec = 0;
	RTC_Counter = FtimeToCounter(&dateTime);
#endif

#ifdef SYSTEM_STM32


	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5) {
		/* Если в бекап регистре не установлена верная метка, настроим часы */
		printf("%s", "\r\n\n RTC not yet configured....");

//		uint8_t	tm_sec;		/* Seconds: 0-59 (K&R says 0-61?) */
//		uint8_t	tm_min;		/* Minutes: 0-59 */
//		uint8_t	tm_hour;	/* Hours since midnight: 0-23 */
//		uint8_t	tm_mday;	/* Day of the month: 1-31 */
//		uint8_t	tm_mon;		/* Months *since* january: 0-11 */
//		uint16_t tm_year;	/* Years since 1900 */
//		uint8_t	tm_wday;	/* Days since Sunday (0-6) */
//		uint16_t tm_yday;	/* Days since Jan. 1: 0-365 */
//		uint8_t	tm_isdst;	/* +1 Daylight Savings Time, 0 No DST,*/

		dateTime.tm_year = 116;
		dateTime.tm_mon = 1;
		dateTime.tm_mday = 1;
		dateTime.tm_hour = 12;
		dateTime.tm_min = 0;
		dateTime.tm_sec = 0;
		/* Настроим счетчик времени */
		Time_Adjust(&dateTime);
		state.taskList |= TASK_TIMESETUP;
	} else {
		printf("%s", "\r\n No need to configure RTC....");
		/* Enable PWR and BKP clocks */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);
		/* Ждем синхронизации */
		RTC_WaitForSynchro();
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
		/* Включаем прерывание счета секунд */
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		/* Включаем прерывание будильника */
		//RTC_ITConfig(RTC_IT_ALR, ENABLE);
		/* Ждем записи регистров */
		RTC_WaitForLastTask();
	}
	/* Настрока прерываний для часов */
	NVIC_Configuration();
	//Обновим структуру со временем
	CounterToFtime(RTC_GetCounter(), &dateTime);
#endif
}

#ifdef SYSTEM_STM32
/*******************************************************************************
 * Настройка прерываний для часов
 ******************************************************************************/
void NVIC_Configuration(void) {
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Настройка группы приоритета прерывания */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* Включим прерывание от часов */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Настроим внешнее прерывание от будильника */
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStruct.EXTI_Line = EXTI_Line17;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	/* Настроим обработчик */
	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 14;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Time_Adjust(tm_t* time) {
	/* RTC Configuration */
	RTC_Configuration();
	printf("%s", "\r\n RTC configured....");

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Change the current time */
	RTC_SetCounter(FtimeToCounter(time));
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);

	/* Clear reset flags */
	RCC_ClearFlag();

}

/*******************************************************************************
 * Настройка часов
 ******************************************************************************/
void RTC_Configuration(void) {
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset Backup Domain */
	BKP_DeInit();

	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {
	}

	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}

//They probably just changed the name. It was in the library source file stm32f10x_nvic.c

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/*******************************************************************************
 * Сброс микроконтроллера.
 ******************************************************************************/
void NVIC_GenerateSystemReset(void) {
	SCB->AIRCR = AIRCR_VECTKEY_MASK | (uint32_t) 0x04;
}
#endif

/*******************************************************************************
 * Внешнее прерывание от будильника.
 ******************************************************************************/
void RTCAlarm_IRQHandler(void) {
#ifdef SYSTEM_STM32
	printf("%s", "RTCAlarm_IRQHandler...");
	EXTI_ClearITPendingBit(EXTI_Line17);
	state.taskList |= TASK_REDRAW | TASK_UPDATETIME | TASK_ALARM;
	printf("%s", "[OK]\r\n");
#endif
}

/*******************************************************************************
 Ежесекундное прерывание от часов.
 ******************************************************************************/
extern uint16_t angle;
void RTC_IRQHandler(void) {
		printf("%s", "RTC_IRQHandler...");
	//Fixme bottom
	angle+=360/60;

#ifdef SYSTEM_STM32
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //Запуск преобразования ADC1
//Fixme up
	
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET) {
		/* Снимаем флаг прерывания секунд */
		RTC_ClearITPendingBit(RTC_IT_SEC);
#endif
#ifdef SYSTEM_WIN
		{
#endif
		if(config.SleepSec && (powerControl.countToSleep < config.SleepSec)) //Приблизим ко сну
		powerControl.countToSleep++;

		if(powerControl.CloclLockTime > 0)
		powerControl.CloclLockTime--;

		/*Обновим время на дисплее*/
		if (state.taskList & TASK_UPDATETIME) {
			CounterToFtime(RTC_GetCounter(), &dateTime);
			state.taskList &=~ TASK_UPDATETIME;
			state.taskList |= TASK_REDRAW;
		}
		else {
			dateTime.tm_sec++;
			if (dateTime.tm_sec == 60) {
				dateTime.tm_sec = 0;
				dateTime.tm_min++;
				if (dateTime.tm_min == 60) {
					dateTime.tm_min = 0;
					dateTime.tm_hour++;
					if (dateTime.tm_hour == 24) {
						CounterToFtime(RTC_GetCounter(), &dateTime);
					}
				}
				state.taskList |= TASK_REDRAW; //Перерисовка каждую минуту
			}
			if(config.SecInTime)state.taskList |= TASK_REDRAW; //Перерисовка если показываем секунды
		}
	}
		printf("%s", "[OK]\r\n");
}
/*******************************************************************************
 * Установить через сколько секунд сработает будильник
 ******************************************************************************/
#ifdef SYSTEM_STM32
void setAlarm(uint32_t count) {
	printf("%s", "setAlarm...");
	/* Ждем когда все операции будут завершены */
	RTC_WaitForLastTask();
	if(count)
	/*  */
	RTC_SetAlarm(RTC_GetCounter() + count);
	else
	RTC_SetAlarm(RTC_GetCounter()-(RTC_GetCounter()%60)+60);
	/* Ждем завершения операции */
	RTC_WaitForLastTask();
	printf("%s", "[OK]\r\n");
}
#endif
/*******************************************************************************
 * Затычка для SDL версии
 ******************************************************************************/
#ifdef SYSTEM_WIN
uint32_t RTC_GetCounter(void){
	return RTC_Counter;
}
#endif

/*******************************************************************************
 * Преобразование значения счетчика в григорианскую дату и время
 ******************************************************************************/
void CounterToFtime(uint32_t counter, tm_t * dateTime) {
	uint32_t ace;
	uint8_t b, d, m;
	ace = (counter / 86400) + 32044 + JD0;
	b = (4 * ace + 3) / 146097; // может ли произойти потеря точности из-за переполнения 4*ace ??
	ace = ace - ((146097 * b) / 4);
	d = (4 * ace + 3) / 1461;
	ace = ace - ((1461 * d) / 4);
	m = (5 * ace + 2) / 153;
	dateTime->tm_mday = ace - ((153 * m + 2) / 5) + 1;
	dateTime->tm_mon = m + 2 - (12 * (m / 10));
	dateTime->tm_year = (100 * b + d - 4800 + (m / 10)) - 1900;
	dateTime->tm_hour = (counter / 3600) % 24;
	dateTime->tm_min = (counter / 60) % 60;
	dateTime->tm_sec = (counter % 60);
	dateTime->tm_wday = weekDay(dateTime->tm_mday, dateTime->tm_mon + 1, dateTime->tm_year + 1900);
}

/*******************************************************************************
 * Преобразование григорианской даты и времени в значение счетчика
 ******************************************************************************/
uint32_t FtimeToCounter(tm_t * dateTime) {
	uint8_t a, m;
	uint16_t y;
	uint32_t JDN;
// Вычисление необходимых коэффициентов
	a = (13 - dateTime->tm_mon) / 12;
	y = dateTime->tm_year + 1900 + 4800 - a;
	m = dateTime->tm_mon + (12 * a) - 2;
// Вычисляем значение текущего Юлианского дня
	JDN = dateTime->tm_mday;
	JDN += (153 * m + 2) / 5;
	JDN += 365 * y;
	JDN += y / 4;
	JDN += -y / 100;
	JDN += y / 400;
	JDN -= 32045;
	JDN -= JD0;// так как счетчик у нас не резиновый, уберем дни которые прошли до 01 янв 2001
	JDN *= 86400;// переводим дни в секунды
	JDN += (dateTime->tm_hour * 3600);// и дополняем его секундами текущего дня
	JDN += (dateTime->tm_min * 60);
	JDN += (dateTime->tm_sec);
// итого имеем количество секунд с 00-00 01 янв 2001
	return JDN;
}
