#include "config.h"
#include "main.h"
#include "mtk.h"
#include "menu.h"
#include "keyboard.h"
#include "string.h"
#include "utils.h"
#include "timer.h"
#include "beeper.h"


#ifdef SYSTEM_STM32
#include "led.h"
#include "timer.h"

#include "stm32f10x.h"
#include "usart.h"
#endif

#ifdef SYSTEM_WIN
#include <math.h>
#include <stdlib.h>
#include "bat.h"
bat_t bat;
#endif

#define CONTRAST_MAX 96
#define CONTRAST_MIN 32
#define BaseColor 0
#define NumLevels 4
#define IntensityBits 2
#define FractionBits 16
//Для обработки кнопок
#define ACTION_INC 0
#define ACTION_DEC 1
#define ACTION_IS 2

uint32_t readDayActiv(uint16_t, uint8_t);
uint8_t getButton(void);
void buttonsParse(void);
void changePos(uint8_t, uint8_t, uint8_t, uint8_t);
void changeVal(uint8_t, void *, uint16_t, uint16_t, uint8_t);
void calculateStat(track_t *);
void loadRacelist(void);
void mainLoop(void);
void newState(void);

config_t config;
state_t state;
calendar_t calendar; //Структура с данными открытого календаря
tm_t * dateTime_p; //Указатель на структуру с датой и временем
extern termo_t termo;
extern BMSinfo_t BMSinfo;
extern BMS_t BMS;
extern popup_t popup;
count_t count;
track_t track; //Структура с данными текущей езды
track_t histItem; //Структура с данными сохраненного заезда
racelist_t racelist;
uint8_t navigate[5] = { 0, 0, 0, 0, 0 }; //Массив текущего положения в менюшках
uint8_t stateMain = STATE_NULL; //Выбраное состояние. До запуска устройства нулевое
uint8_t stateMainPrev = STATE_NULL; //Предыдущее выбраное состояние
uint16_t keyPass = 0;
uint8_t contrast;
uint8_t testFlag = 0;

uint8_t drawDelay = 0;
uint8_t drawTaskLimTime = 0;

extern mtk_element_t mtkUtil,
	mtk_BMS_info; //Информация по батарее
mtk_element_t
		mtkPassword, //Пароль
		mtkDisplay, //Меню настройки дисплея
		mtkContrast, //Настройка контрастности
		mtkAutoBright, //Включение автояркости дисплея
		mtkMenuOdometr, //Меню настройки одометра
		mtkCircle, //Настройка длины окружности колеса
		mtkOdometr, //Пройденное расстояние в мм
		mtkPin, //Пароль стартового экрана
		mtkLang, //Выбор языка интерфейса
		mtkDateTime, mtkDate, mtkTime, mtkPower, mtkSecInTime,
		mtkMaxFPS, mtkSleepDisplayOff, mtkSleepSec,
	//	mtkSupply, mtkSupply40, mtkSupply37,
		mtkMenuBMS,
		mtkRacelist, //Вид списка заездов (Календарь или список)
		mtkAbout;

mtk_select_t mtkLangList, mtkRacelistList;

/*******************************************************************************
 *Стартовая функция с главным цыклом
 *В вечном цыкле проверяем были ли нажаты кнопки, вызываем обраболку нажатий,
 *проверяем не изменился ли режим работы, обрабатываем состояние и спим.
 ******************************************************************************/
int main() {
#ifdef SYSTEM_WIN
	uint8_t i;
	uint8_t langEng = LANGUAGE_ENG;
	for (i = 0; i < 6; i++) {
		racelist.startTime[i] = 8888; //Время старта
		racelist.distance[i] = 88888; //Пройденное расстояние
		racelist.averSpeed[i] = 8888; //Средняя скорость
	}
	track.distance = 123450000UL; //Последний путь в мм (0 ... 4294967295)
	track.startCapacity = 10000; //Емкость на старте мАч (от 0 до 65535)

	track.peakSpeed = 11111; //Пиковая скорость в 10м/ч (от 0 до 65535)
	track.tics = 212009600; //Время в пути в тиках (0...4 294 967 295). До полутора суток. 131071 секунд или 2184 минут или 36 часов
	track.odometr = 1000000000; //Общий путь в мм (0 ... 18446744073709551615)
	config.lang = 0;
	stateMain = STATE_START;
	SysTick_task_add(RTC_IRQHandler, 1000); //Эмуляция тиков часов
	RTC_init();
	drawInit();
	BMS_init();//Подготовка к работе с BMS
	loadParams();//Загрузили параметры из EEPROM
	SysTickInit(100);//Запуск таймера. Вызов 100 раз в секунд
	contrastGetSet((uint32_t*)&config.contrast);
	setStrings(&langEng); //Сначала язык по умолчанию
	setStrings(&config.lang); //Установили заданный язык

	bat.voltage = 4000;
	bat.state = BAT_DISCHARGE;
	bat.level = 100;
#endif

	mtkPin.type = ELEMENT_NUM16;
	mtkPin.length = PASSWORD_LENGHT;
	mtkPin.pointer = &keyPass;
	mtkPin.flags = EDITING_PROCESS | TYPE_LOCK;

	/*
	 Disblay------Contrast
	 |             |
	 |         Autobright
	 |
	 Odometr--------Circle
	 |                  |
	 |           Odometr(km)
	 Password
	 |
	 |
	 Date, time------Date
	 |                 |
	 |                 |
	 |               Time
	 Language
	 |
	 |
	 Power-------------Sec in time
	 |	 	 	 	 	 |
	 |	 	 	 	 	 |
	 |	 	 	 	 Display auto off (sec)
	 |	 	 	 	 	 |
	 |	 	 	 	 	 |
	 |	 	 	 	 Auto sleep (sec)
	 About

	 */
//---------Menu display
	//&Элемент, type, &массив строк, длина, флаги свойств, &куда ссылается, &следующий элемент
	//mtk_SetupElement(&, ELEMENT_,  NULL,  0, TYPE_NEEDOK, &pointer , &next);
	mtk_SetupElement(&mtkDisplay, ELEMENT_MENU, NULL, 0, 0, &mtkContrast,	&mtkMenuOdometr);
	mtk_SetupElement(&mtkContrast, ELEMENT_NUM8, NULL, 2, TYPE_FUNC, &contrastGetSet,	&mtkAutoBright);
	mtk_SetupElement(&mtkAutoBright, ELEMENT_FLAG, NULL, 0, 0, &testFlag, NULL);
//---------Menu odometr
	mtk_SetupElement(&mtkMenuOdometr, ELEMENT_MENU, NULL, 0, 0, &mtkCircle,	&mtkPassword);
	mtk_SetupElement(&mtkCircle, ELEMENT_NUM16, NULL, 4, TYPE_NEEDOK,	&track.circle, &mtkOdometr);
	mtk_SetupElement(&mtkOdometr, ELEMENT_NUM64X1M, NULL, 6, TYPE_NEEDOK,	&track.odometr, NULL);
//----------Password enter
	mtk_SetupElement(&mtkPassword, ELEMENT_NUM16, NULL, PASSWORD_LENGHT, TYPE_NEEDOK, &config.password, &mtkDateTime);
//----------DateTime
	mtk_SetupElement(&mtkDateTime, ELEMENT_MENU, NULL, 0, 0, &mtkTime, &mtkLang);
	mtk_SetupElement(&mtkTime, ELEMENT_TIME, NULL, 3, TYPE_NEEDOK | TYPE_FUNC, &timeGetSet, &mtkDate);
	mtk_SetupElement(&mtkDate, ELEMENT_DATE, NULL, 3, TYPE_NEEDOK | TYPE_FUNC, &timeGetSet, NULL);

	mtk_SetupElement(&mtkLang, ELEMENT_SEL, NULL, 2, TYPE_FUNC, &mtkLangList, &mtkPower);
	mtkLangList.pointer = &setStrings;
//------------------------------------------
	mtk_SetupElement(&mtkPower, ELEMENT_MENU, NULL, 0, 0, &mtkMaxFPS, &mtkRacelist);
	mtk_SetupElement(&mtkMaxFPS, ELEMENT_NUM8, NULL, 1, 0, &config.maxFPS, &mtkSecInTime);
	mtk_SetupElement(&mtkSecInTime, ELEMENT_FLAG, NULL, 0, 0, &config.SecInTime, &mtkSleepSec);
	mtk_SetupElement(&mtkSleepSec, ELEMENT_NUM16, NULL, 4, 0, &config.SleepSec, &mtkSleepDisplayOff);
	mtk_SetupElement(&mtkSleepDisplayOff, ELEMENT_FLAG, NULL, 0, 0, &config.SleepDisplayOff, NULL);
//	mtk_SetupElement(&mtkSupply, ELEMENT_MENU, NULL, 0, TYPE_PRIVATE, &mtkSupply40, NULL);
//	mtk_SetupElement(&mtkSupply40, ELEMENT_NUM16, NULL, 4, TYPE_NEEDOK, &config.bat40, &mtkSupply37);
//	mtk_SetupElement(&mtkSupply37, ELEMENT_NUM16, NULL, 4, TYPE_NEEDOK, &config.bat37, NULL);

//--------------------------------------
	mtk_SetupElement(&mtkRacelist, ELEMENT_SEL, NULL, 2, 0, &mtkRacelistList, &mtkMenuBMS);
	mtkRacelistList.pointer = &config.racelistType;
//--------------------------------------
	mtk_SetupElement(&mtkMenuBMS, ELEMENT_MENU, NULL, 0, 0, &mtk_BMS_info,	&mtkAbout);
//--------------------------------------
	mtk_SetupElement(&mtkAbout, ELEMENT_GFUNC, NULL, 0, 0, &about, NULL);
//---------

	//setStrings(&config.lang);

	state.taskList |= TASK_UPDATETIME; //Ставим задачу взять время со счетчика
	state.taskList |= TASK_REDRAW; //Запросим первую перерисовку экрана
	//Перед входом в главный цыкл...
	mainLoop();
	return 0;
}

/*******************************************************************************
 *Главный цыкл после включения устройства
 ******************************************************************************/
void mainLoop() {
	while (1) {
		powerService(); //Управление энергопотреблением
#ifdef SYSTEM_STM32
		parseUSART();
#endif
#ifdef SYSTEM_WIN
		state.button = getButton(); //Проверяем нажатия
#endif
		if (state.button > 1) {
			beep(2000, 50);
			buttonsParse(); //Разбор кнопочных нажатий
			state.taskList |= TASK_REDRAW;
		}
		if (stateMainPrev != stateMain)
			newState();
		switch (stateMain) {
		case STATE_START: {
			if (keyPass == config.password)
				stateMain = STATE_MAIN;
		}
			break;
		case STATE_STAT: {
			calculateStat(&track);
		}
			break;
		case STATE_MAIN: {
		}
			break;
		case STATE_TERMO: {
		}
			break;
		case STATE_OFF: {

		}
			break;
		case STATE_CALENDAR: {
			if (!VB(racelist.dayActiv_f, 0)) {
				racelist.dayActiv_f = readDayActiv(calendar.year,
						calendar.month);
			}
		}
			break;
		case STATE_SILENT: {
		}
			break;
		case STATE_NULL: {
			stateMain = STATE_START;
		}
			break;
		}
		/* Обработка запроса ограниченной отрисовки */
		if (state.taskList & TASK_LIM_REDRAW) { //Если стоит задача отложенной перерисовки
			if (!config.maxFPS){ //Ограничения нету
				state.taskList |= TASK_REDRAW;
				state.taskList &= ~ TASK_LIM_REDRAW;
			}
			else if (!SysTick_task_check(drawTask))	//Не запущен планировщик перерисовки
				SysTick_task_add(drawTask, 10); //Запускаем планировщик перерисовки
		}
		/* Запуск обновления экрана, если нужно */
#ifdef SYSTEM_STM32
		if ((state.taskList & TASK_REDRAW) && !(DMA1_Channel3->CCR & DMA_CCR3_EN) && (stateMain != STATE_SILENT)) {
#elif defined SYSTEM_WIN
		if ((state.taskList & TASK_REDRAW) && (stateMain != STATE_SILENT)) {
#endif

#ifdef DEBUG_DISPLAY
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Включаем тактирование таймера
			TIM4->CNT = 0;//Обнуляем счетчик
#endif
			if (config.maxFPS)
				drawDelay = (100 / config.maxFPS);
			redrawDisplay(); //Рисуем кадр
#ifdef DEBUG_DISPLAY
			track.circleTics = TIM4->CNT; //Считали значение счетчика. 32768 импульсов в секунду
			RCC->APB1ENR &= ~ RCC_APB1ENR_TIM4EN;//Включаем тактирование таймера
#endif
			state.taskList &= ~ TASK_REDRAW; //Снимаем запросы перерисовки
		}
	}
}

/*******************************************************************************
 *Смена состояния устройства
 ******************************************************************************/
void newState() {
	switch (stateMainPrev) {
	case STATE_SETUP: {
		if (state.taskList & TASK_SAVEPARAMS) {
			saveParams();
			state.taskList &= ~ TASK_SAVEPARAMS;
		}
	}
		break;
	}
	switch (stateMain) {
	case STATE_MAIN: {
		if ((stateMainPrev == STATE_SILENT) || (stateMainPrev == STATE_START) || (stateMainPrev == STATE_NULL))
			dateTime_p = timeGetSet(NULL); //Настроим указатель на дату, время.
		if (state.taskList & TASK_TIMESETUP) {
			stateMain = STATE_SETUP;
			changePos(0, 1, 1, ACTION_IS);
			mtk_SetRootElement(&mtkTime);
			mtk_SelectElement(1);
			state.taskList &= ~ TASK_TIMESETUP;
		}
	}
		break;
	case STATE_SETUP: {
		mtk_SetRootElement(&mtkDisplay);
	}
		break;
	case STATE_UTIL: {
		utilInit();
	}
		break;
	case STATE_START: {
		if (stateMainPrev == STATE_NULL) {
			beep(500, 100);
			beep(600, 100);
			beep(700, 100);
			if (state.reset) {
				if (state.reset & RESET_FLAG_LPWRRST)
					popup.body = "Low-power";
				if (state.reset & RESET_FLAG_WWDGRST)
					popup.body = "Win watchDog";
				if (state.reset & RESET_FLAG_IWDGRST)
					popup.body = "Ind watchDog";
				if (state.reset & RESET_FLAG_SFTRST)
					popup.body = "Software reset";
				if (state.reset & RESET_FLAG_PORRST)
					popup.body = "Power on";
				if (state.reset & RESET_FLAG_PINRST)
					popup.body = "Hard reset";
				popup.head = "Reset reason";
				popup.type = POPUP_NULL;
			} else {
				popup.head = "Hi Barada!";
				popup.body = "Enter PIN";
			}
		}
	}
		break;
	case STATE_BAT: {
		mtk_SetRootElement(&mtk_BMS_info);
	}
		break;
	case STATE_SILENT:
	case STATE_OFF: {
		saveParams();
		redrawDisplay();
#ifdef SYSTEM_STM32
		beep(700, 100);
		beep(600, 100);
		beep(500, 100);
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Включаем тактирование таймера
		TIM4->CNT = 0;//Обнуляем счетчик
		while (TIM_GetCounter(TIM4) < 65535);
		displayOff();
		state.taskList |= TASK_POWEROFF;
#endif
#ifdef SYSTEM_WIN
		exit(1);
#endif
	}
		break;
	case STATE_CALENDAR: {
		calendar.day = dateTime_p->tm_mday;
		calendar.month = dateTime_p->tm_mon + 1;
		calendar.year = dateTime_p->tm_year + 1900;
		CB(racelist.dayActiv_f, 0);
	}
		break;
	case STATE_STAT: {
		calculateStat(&track);
	}
		break;
	case STATE_TERMO: {
		termo.max = 0;
		termo.min = 0xFFFF;
		termo.in = 0;
		termo.count = 0;
	}
		break;
	}
	stateMainPrev = stateMain;
}

/*******************************************************************************
 *Обработка нажатий кнопок в зависимости от стостояния
 ******************************************************************************/
void buttonsParse() {
	state.taskList |= TASK_USER; // Отметим активность пользователя
	if (popup.type) { //Если есть всплывающее сообщение
		switch (state.button) {
		case BUTTON_UP:
			break;
		case BUTTON_DOWN:
			break;
		case BUTTON_LEFT: {
			popup.type = POPUP_NULL;
		}
			break;
		case BUTTON_RIGHT: {
			popup.type++;
			popup.head = NULL;
			if (popup.type == 4)
				popup.type = 1;
		}
			break;
		}
		state.button = BUTTON_NULL;
	} else
		//if(){}else
		switch (stateMain) {
		case STATE_START: {
		mtk_Command(state.button);
	}
		break;
	case STATE_MAIN: {
		switch (state.button) {
		case BUTTON_UP: {
			if (navigate[0]) {
				navigate[0] = 0;
			}
		}
			break;
		case BUTTON_DOWN: {
			if (!navigate[0])
				navigate[0] = 1;
			else
				stateMain = STATE_SILENT;
		}
			break;
		case BUTTON_LEFT: {
			if (navigate[0]) {
				navigate[0] = 0;
				keyPass = 0;
				stateMain = STATE_START;
			}
		}
			break;
		case BUTTON_RIGHT: {
			if (navigate[0]) {
				stateMain = STATE_OFF;
			}
		}
			break;
		}
	}
		break;
/*-------------------------------CALENDAR-------------------------------------*/
	case STATE_CALENDAR: {
		if (navigate[3]) { //Если открыли статистику заезда
			switch (state.button) {
			case BUTTON_UP: {
				navigate[3] = 0;
			}
				break;
			case BUTTON_DOWN: {
				navigate[3] = 0;
			}
				break;
			case BUTTON_LEFT: {
				navigate[3] = 0;
			}
				break;
			case BUTTON_RIGHT: {
				navigate[3] = 0;
			}
				break;
			}
		} else if (navigate[2]) { //Если вошли в список заездов
			switch (state.button) {
			case BUTTON_UP: {
				changePos(2, 1, racelist.itemsDisplay, ACTION_DEC);
			}
				break;
			case BUTTON_DOWN: {
				changePos(2, 1, racelist.itemsDisplay, ACTION_INC);
			}
				break;
			case BUTTON_LEFT: {
				changePos(2, 0, 0, ACTION_IS);
			}
				break;
			case BUTTON_RIGHT: {
				loadHistItem();
				calculateStat(&histItem);
				navigate[3] = 1;
			}
				break;
			}
		} else { //Навигируем в окошке с календариком
			switch (state.button) {

			case BUTTON_UP: {
				if (!navigate[1]) {
					changePos(0, 0, 3, ACTION_DEC);
				} else {
					changePos(1, 0, 0, ACTION_IS);
				}
			}
				break;
			case BUTTON_DOWN: {
				if (!navigate[1]) {
					changePos(0, 0, 3, ACTION_INC);
				} else {
					changePos(2, 0, 1, ACTION_IS); //Входим в список заездов
					loadRacelist(); //Считываем информацию для списка заездов из памяти в массивы структурки
				}
			}
				break;
			case BUTTON_LEFT: {
				if (navigate[0] == 2) {
					if (calendar.month > 1)
						calendar.month--;
					else
						calendar.month = 12;
					CB(racelist.dayActiv_f, 0);
				} else if (navigate[0] == 3) {
					calendar.year--;
					CB(racelist.dayActiv_f, 0);
				} else if (navigate[0] == 1) {
					if (!navigate[1])
						changePos(1, 0, dateTime_p->tm_mday, ACTION_IS);
					else
						changePos(1, 1, 30, ACTION_DEC);
				}
			}
				break;
			case BUTTON_RIGHT: {
				if (navigate[0] == 2) {
					if (calendar.month < 12)
						calendar.month++;
					else
						calendar.month = 1;
					CB(racelist.dayActiv_f, 0);
				} else if (navigate[0] == 3) {
					calendar.year++;
					CB(racelist.dayActiv_f, 0);
				} else if (navigate[0] == 1) {
					if (!navigate[1]) {
						if ((calendar.year == dateTime_p->tm_year + 1900) && (calendar.month == dateTime_p->tm_mon + 1))
							changePos(1, 0, dateTime_p->tm_mday, ACTION_IS);
						else
							changePos(1, 0, 15, ACTION_IS);
					} else
						changePos(1, 1, lastdayofmonth(calendar.year, calendar.month), ACTION_INC);
				}
			}
				break;
			}
		}
	}
		break;
		/*----------------------------------UTIL-------------------------------------*/
	case STATE_UTIL: {
		if (!navigate[0]) {
			switch (state.button) {
			case BUTTON_UP:
			case BUTTON_DOWN: {
				changePos(0, 1, 1, ACTION_IS);
				mtk_Command(state.button);
			}
				break;
			}
		} else if (!mtk_Command(state.button)) {
			changePos(0, 0, 0, ACTION_IS);
			state.button = BUTTON_NULL;
		}
	}
		break;
		/*----------------------------------SETUP-------------------------------------*/
	case STATE_SETUP: {
		if (!navigate[0]) {
			switch (state.button) {
			case BUTTON_UP:
			case BUTTON_DOWN: {
				changePos(0, 1, 1, ACTION_IS);
				mtk_Command(state.button);
				state.taskList |= TASK_SAVEPARAMS;
			}
				break;
			}
		} else if (!mtk_Command(state.button)) {
			changePos(0, 0, 0, ACTION_IS);
			state.button = BUTTON_NULL;
		}
	}
		break;
		/*-----------------------------------BAT--------------------------------------*/
//	case STATE_BAT: {
//		if (!navigate[0]) {
//			switch (state.button) {
//			case BUTTON_UP:
//			case BUTTON_DOWN: {
//				changePos(0, 1, 1, ACTION_IS);
//				mtk_Command(state.button);
//				//	state.taskList |= TASK_SAVEPARAMS;
//			}
//				break;
//			}
//		} else {
//			if (!mtk_Command(state.button)) {
//				changePos(0, 0, 0, ACTION_IS);
//				state.button = BUTTON_NULL;
//			}
//		}
//	}
//		break;
/*--------------------------------TERMO---------------------------------------*/
	case STATE_TERMO: {
		switch (state.button) {
		case BUTTON_UP: {
			if (!navigate[1]) {
				changePos(0, 0, 6, ACTION_DEC);
			} else
				changeVal(8, &termo.speed, 1, 10, ACTION_INC);
			SysTick_task_add(&addTermItem, 1000/termo.speed);
		}
			break;
		case BUTTON_DOWN: {
			if (!navigate[1]) {
				changePos(0, 0, 6, ACTION_INC);
			} else
				changeVal(8, &termo.speed, 1, 10, ACTION_DEC);
			SysTick_task_add(&addTermItem, 1000/termo.speed);
		}
			break;
		case BUTTON_LEFT: {
			if (navigate[1]) {
				SysTick_task_del(&addTermItem);
				termo.count = 0;
				termo.min = 0xff;
				termo.max = 0;
				navigate[1] = 0;
			} else if (navigate[0]) {
				changePos(0, 0, 0, ACTION_IS);
				state.button = BUTTON_NULL;
			}
		}
			break;
		case BUTTON_RIGHT: {
			if (navigate[0]) {
				termo.speed = 1;
				SysTick_task_add(&addTermItem, 1000/termo.speed);
				changePos(1, 1, 1, ACTION_IS);
			}
		}
			break;
		}
	}
		break;
/*------------------------------STATISTICS------------------------------------*/
	case STATE_STAT: {
		switch (state.button) {
		case BUTTON_UP: {
			if (!navigate[0]) {
				navigate[0] = 1;
			} else {
//				navigate[0]=0;
			}
		}
			break;
		case BUTTON_DOWN: {
			if (!navigate[0]) {
				navigate[0] = 1;
			} else {
				saveTrack();
				track.distance = 0;
				track.startCapacity = BMS.capacity;
				track.endCapacity = BMS.capacity;
				track.peakSpeed = 0;
				track.tics = 0;
				track.startTime = 0;
				navigate[0] = 0;
			}
		}
			break;
		case BUTTON_LEFT: {
			if (navigate[0]) {
				navigate[0] = 0;
				state.button = BUTTON_NULL;
			}
		}
			break;
		case BUTTON_RIGHT: {
			if (navigate[0]) {
				track.distance = 0;
				track.startCapacity = BMS.capacity;
				track.endCapacity = BMS.capacity;
				track.peakSpeed = 0;
				track.tics = 0;
				track.startTime = 0;
				calculateStat(&track);
				navigate[0] = 0;
				state.button = BUTTON_NULL;
			}
		}
			break;
		}
	}
		break;
/*---------------------------------LIGHT--------------------------------------*/
	case STATE_LIGHT: {
		switch (state.button) {
		case BUTTON_UP: {
			if (!navigate[1]) {
				changePos(0, 0, PWM_COUNT, ACTION_DEC);
			}
		}
			break;
		case BUTTON_DOWN: {
			if (!navigate[1]) {
				changePos(0, 0, PWM_COUNT, ACTION_INC);
			}
		}
			break;
		case BUTTON_LEFT: {
			if (navigate[0]) {
				config.PWM[navigate[0] - 1] = config.PWM[navigate[0] - 1]/2;
				PWMSet(navigate[0] - 1, config.PWM[navigate[0] - 1]);
			}
		}
			break;
		case BUTTON_RIGHT: {
			if (navigate[0]) {
				if (config.PWM[navigate[0] - 1] == 0) {
					config.PWM[navigate[0] - 1] = 1;
				} else if (config.PWM[navigate[0] - 1] > 64)
					config.PWM[navigate[0] - 1] = 255;
				else
					config.PWM[navigate[0] - 1] = config.PWM[navigate[0] - 1]*2;
				PWMSet(navigate[0] - 1, config.PWM[navigate[0] - 1]);
			}
		}
			break;
		}
	}
		break;
	}
/*--------------Тут переключение вкладок при подходящем состоянии-------------*/
	if ((stateMain != STATE_START) && (!navigate[0])) {
		switch (state.button) {
		case BUTTON_RIGHT: {
			if (stateMain < 9) {
				stateMain++;
			} else {
				stateMain = 1;
			}
		}
			break;
		case BUTTON_LEFT: {
			if (stateMain > 1) {
				stateMain--;
			} else {
				stateMain = 9;
			}
		}
			break;
		case BUTTON_UP: {
		}
			break;
		case BUTTON_DOWN: {
		}
			break;
		}
	}
	state.button = BUTTON_NULL;
}

/*******************************************************************************
 *Вычисление скорости по числу тиков за оборот
 *32768 импульсов в секунду *3600 секунд в часе
 ******************************************************************************/
void circleStep(uint16_t count) {
	if (!count)
		track.speed = 0;
	else {
		track.speed = (track.circle * 1179648UL) / (count * 100UL);
		if (track.speed > track.peakSpeed)
			track.peakSpeed = track.speed;
	}
	if (track.startTime == 0)
	track.startTime = RTC_GetCounter();
}

/*******************************************************************************
 *Изменение позиции в заданном уровне меню
 ******************************************************************************/
void changePos(uint8_t pos, uint8_t min, uint8_t max, uint8_t action) {
	changeVal(8, &navigate[pos], min, max, action);
}

/*******************************************************************************
 *Изменение значения числа в заданных пределах
 ******************************************************************************/
void changeVal(uint8_t size, void *n, uint16_t min, uint16_t max,
		uint8_t action) {
	uint16_t x = 0;
	if (size == 8)
		x = *((uint8_t*) n);
	else if (size == 16)
		x = *((uint16_t*) n);
	switch (action) {
	case ACTION_INC: {
		if (x >= max) {
			x = min;
		} else
			x++;
	}
		break;
	case ACTION_DEC: {
		if (x <= min) {
			x = max;
		} else
			x--;
	}
		break;
	case ACTION_IS: {
		x = max;
	}
		break;
	}
	if (size == 8)
		*((uint8_t*) n) = x;
	else if (size == 16)
		*((uint16_t*) n) = x;
}

/*******************************************************************************
 *Высчитывает параметры заезда
 ******************************************************************************/
void calculateStat(track_t *tr) {
	//Средняя скорость в 10м/ч (от 0 до 65535) (дистанция_в_мм/10000)/(Время в тиках/117964800)
	if (tr->tics > 0)
		tr->averageSpeed = ((tr->distance * 11796ULL) / tr->tics);
	else
		tr->averageSpeed = 0;
	tr->discharge = tr->startCapacity - tr->endCapacity; // Потрачено емкости за заезд в ма*ч;
	if (tr->distance > 100000)
		tr->expense = tr->discharge * 10 / (tr->distance / 100000); //Расход электроэнергии мА*ч/км (от 0 до 65535)
	else
		tr->expense = 0;
	if (tr->expense > 0)
		tr->toCharging = 30000 / tr->expense; //Рассчетный оставшийся пробег до зарядки в 100м (от 0 до 65535)
	else
		tr->toCharging = 0;
}

/*******************************************************************************
 *Добавить значение температуры в буфер граффика
 ******************************************************************************/
void addTermItem(void) {
	uint8_t i;
#ifdef SYSTEM_WIN
	termo.buff[termo.in] = 10
			* (sin((double) (termo.in / 15.0) + (double) 50) * 40 + 100);
#endif
#ifdef SYSTEM_STM32
	termo.buff[termo.in] = (double)100*(double)temp_s();
#endif
	termo.in++;
	if (termo.in == BUF_TERMO_SIZE)
		termo.in = 0;
	if (termo.count < BUF_TERMO_SIZE)
		termo.count++;
	for (i = 0; i < termo.count; i++) {
		if (termo.buff[i] < termo.min)
			termo.min = termo.buff[i];
		if (termo.buff[i] > termo.max)
			termo.max = termo.buff[i];
	}
}

/*******************************************************************************
 * Планировщик отрисовки с ограничением скорости кадров
 * Вызываем 100 раз в секунду
 * Сама себя выключит если в течении двух секунд не востребована
 ******************************************************************************/
void drawTask(void) {
	if (drawDelay) {
		drawDelay -= 1;
	} else if (state.taskList & TASK_LIM_REDRAW) {
		drawTaskLimTime = 200;
		state.taskList &= ~ TASK_LIM_REDRAW;
		state.taskList |= TASK_REDRAW;
	} else if (drawTaskLimTime)
		drawTaskLimTime--;
	else
		SysTick_task_del(drawTask); //Вырубаем планировщик отрисовки
}

