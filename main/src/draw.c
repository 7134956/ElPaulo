#include "mtk.h"
#include "draw.h"
#include "pwm.h"
#include "rtc.h"
#include "bitmap.h"
#include "main.h"
#include "power.h"
#include "termo.h"
#include "bms.h"

#ifdef SYSTEM_STM32
#include "u8g_arm.h"
#include "termo.h"
#include "config.h"
#endif

uint8_t hStart, vStart, hStep, vStep, j, k;
popup_t popup;
char sTemp[30]; //Общая временная переменная для строки
extern char *month[2][12];
extern char *days[2][7];

u8g_t u8g;

tm_t * time_p; //Указатель на структуру со временем
extern calendar_t calendar;
extern racelist_t racelist; //Информация о заездах
extern track_t track; //Параметры текущего заезда
extern BMSinfo_t BMSinfo;
extern BMS_t BMS;
extern track_t histItem;
extern uint8_t navigate[5];
extern uint8_t stateMain;

extern mtk_element_t mtkPin;	//Пароль стартового экрана
/*		mtkPassword,	//Пароль
		mtkDisplay,		//Меню настройки дисплея
		mtkContrast,	//Настройка контрастности
		mtkAutoBright,	//Включение автояркости дисплея
		mtkOdometr,		//Меню настройки одометра
		mtkCircle,		//Настройка длины окружности колеса
		mtkDateTime,
		mtkDate,
		mtkTime;
*/

extern config_t config;
extern state_t state;
void drawInit(void);
void draw(void); //Функция отрисовки дисплея
void drawMain(void);
void drawTabs(void);
void drawCalendar(void);
void drawLight(void);
void drawRacelist(void);
void drawHistItem(void);
void drawStat(void);
void drawBar(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
void drawStart(void);
void drawTemp(void);
void drawSetup(void);
void drawTempChart(void);
void drawMainQuickMenu(void);
void drawStatQuickMenu(void);
void drawBat(void);
void drawCell(uint8_t, uint8_t, uint8_t);
void drawOff(void);

/*******************************************************************************
 *Запуск дисплея и настройка графики
 ******************************************************************************/
void drawInit(void) {
	#ifdef SYSTEM_WIN
	u8g_Init(&u8g, &u8g_dev_sdl_2bit);
#endif
#ifdef SYSTEM_STM32
U8G_INIT
#endif
	mtk_Init(&u8g);
	time_p = timeGetSet(NULL);//Взяли указатель на время
	u8g_SetContrast(&u8g, config.contrast);
}

/*******************************************************************************
 *Запросить перерисовку
 ******************************************************************************/
uint8_t drawDelay = 0;

void drawTask(void) {
	if (drawDelay) {
		drawDelay -= 1;
	} else if (state.taskList & TASK_LIM_REDRAW) {
		state.taskList &= ~ TASK_LIM_REDRAW;
		state.taskList |= TASK_REDRAW;
	}
}

/*******************************************************************************
 *Включить дисплей
 ******************************************************************************/
void displayOn(void) {
	u8g_SleepOn(&u8g);
}

/*******************************************************************************
 *Выключить дисплей
 ******************************************************************************/
void displayOff(void) {
	u8g_SleepOn(&u8g);
}

/*******************************************************************************
 *Выключить дисплей
 ******************************************************************************/
uint32_t contrastGetSet(uint32_t *contrast) {
	if (contrast) {
		u8g_SetContrast(&u8g, *contrast);
		config.contrast = *contrast;
		return 0;
	} else
		return (uint32_t)config.contrast;
}

/*******************************************************************************
 *Запуск цыкла отрисовки дисплея
 ******************************************************************************/
void redrawDisplay(void) {
	drawDelay = (100 / config.maxFPS);
	u8g_FirstPage(&u8g);
	do {
		draw();
	} while (u8g_NextPage(&u8g));
}

/*******************************************************************************
 *Рисует экран в зависимости от текущего состояния
 ******************************************************************************/
void draw(void) {
	u8g_SetFontPosBottom(&u8g);
	if ((stateMain != STATE_START) && (stateMain != STATE_OFF))
		drawTabs();
	u8g_SetDefaultForegroundColor(&u8g);
	switch (stateMain) {
	case STATE_START: {
		drawStart();
	}
		break;
	case STATE_MAIN: {
		if (navigate[0]) {
			drawMainQuickMenu();
		} else
			drawMain();
	}
		break;
	case STATE_LIGHT: {
		drawLight();
	}
		break;
	case STATE_SETUP: {
		drawSetup();
	}
		break;
	case STATE_TERMO: {
		if (navigate[1])
			drawTempChart();
		else
			drawTemp();
	}
		break;
	case STATE_BAT: {
		drawBat();
	}
		break;
	case STATE_CALENDAR: {
		if (navigate[3]) {
			drawHistItem();
		} else if (navigate[2]) {
			drawRacelist();
		} else {
			drawCalendar();
		}
	}
		break;
	case STATE_SLEEP: 
	case STATE_OFF: {
		drawOff();
	}
		break;
	case STATE_STAT: {
		if (navigate[0]) {
			drawStatQuickMenu();
		} else
			drawStat();
	}
		break;
	}
	if (stateMain != STATE_START)
		if(popup.type)message();
}

/*******************************************************************************
 *Рисует стартовый экран с паролем
 ******************************************************************************/
void drawStart(void) {
	u8g_SetColorIndex(&u8g, 3);
	u8g_SetFont(&u8g, u8g_font_helvR24);
	u8g_DrawRFrame(&u8g, 0, 0, 240, 160, 5);
	u8g_DrawRFrame(&u8g, 5, 5, 230, 150, 5);
	u8g_DrawStr(&u8g, 54, 43, "El   Paulo");
	u8g_DrawXBM(&u8g, 86, 4, 24, 63, u8g_logo_bits);
	u8g_DrawStr(&u8g, 36, 95, "PIN:");
	u8g_DrawFrame(&u8g, 10, 110, 220, 40);
	u8g_SetFont(&u8g, u8g_font_ncenR10);
//	w = 10 + u8g_GetStrWidth(&u8g, popup.body);
//	h = 66;
//	x = (DISPLAY_WIDTH - w) / 2;
	//u8g_DrawStr(&u8g, 15, 125, "Normal start. No errors.");
	//u8g_DrawStr(&u8g, 15, 145, "Please enter PIN code");
	u8g_DrawStr(&u8g, 15, 125, popup.head);
	u8g_DrawStr(&u8g, 15, 145, popup.body);
	u8g_SetFont(&u8g, u8g_font_elpaulo32n);
	mtk_SetRootElement(&mtkPin);
	mtk_Pos(108, 97);
	mtk_Draw();
}

/*******************************************************************************
 *Рисует главную вкладку
 ******************************************************************************/
void drawMain(void) {
	uint8_t i;
	uint8_t barAH; //Емкость батареи в палочках
	uint8_t amps; //Значение тока в палочках

	u8g_SetFont(&u8g, u8g_font_elpaulo32n);
	if (state.taskList & TASK_DRIVE) {
		sprintf(sTemp, "%02u.%01u", track.speed / 100,
				(track.speed % 100) / 10); //Выводим скорость Км/ч
	} else {
		sprintf(sTemp, "__._"); //Выводим скорость Км/ч
	}
	u8g_DrawStr(&u8g, 70, 55, sTemp);
	if (track.speed)
		sprintf(sTemp, "%02d.%02d", BMS.current / (track.speed * 10),
				((BMS.current * 10) / track.speed) % 100); //Текущий расход энергии
	else
		sprintf(sTemp, "__.__"); //Отсутствует
	u8g_DrawStr(&u8g, 46, 96, sTemp);
	sprintf(sTemp, "%03u.%03u", track.distance / 1000000,
			(track.distance % 1000000) / 1000); //Последний пробег
	u8g_DrawStr(&u8g, 22, 137, sTemp);
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	u8g_DrawStr(&u8g, 155, 37, "km");
	u8g_DrawLine(&u8g, 155, 39, 175, 39);
	u8g_DrawStr(&u8g, 161, 54, "h");
	u8g_DrawStr(&u8g, 155, 78, "A\xb7h");
	u8g_DrawLine(&u8g, 155, 80, 186, 80);
	u8g_DrawStr(&u8g, 161, 95, "km");
	u8g_DrawStr(&u8g, 176, 136, "km");
	hStep = 50;
	if (BMSinfo.maxCap)
		barAH = 15 - (155 * BMS.capacity) / (BMSinfo.maxCap * 10);
	else barAH = 15;
	for (i = 0; i < 15; i++) {
		vStart = 22 + i * 8;
		hStep--;
		if (i < 3)
			hStep--;
		if (i < 6)
			hStep--;
		if (i < 13)
			hStep--;

		if (i >= barAH)
			u8g_DrawBox(&u8g, 0, vStart, hStep, 6);
		else
			u8g_DrawFrame(&u8g, 0, vStart, hStep, 6);
	}

#ifdef DEBUG_DISPLAY
	if (track.circleTics != 0) {
		sprintf(sTemp, "%d.%d FPS", 32768 / track.circleTics,
				(327680 / track.circleTics) % 10);
		u8g_DrawStr(&u8g, 20, 160, sTemp);
	}

	sprintf(sTemp,"%d Tics",track.circleTics);
	u8g_DrawStr(&u8g, 120, 160, sTemp);
#else
	sprintf(sTemp, "%02d.%02dAh", BMS.capacity / 1000,
			(BMS.capacity % 1000) / 10);
	u8g_DrawStr(&u8g, 0, 160, sTemp); //Текущий остаток заряда
	sprintf(sTemp, "%02d.%02dV", BMS.voltage / 1000, (BMS.voltage % 1000) / 10);
	u8g_DrawStr(&u8g, 90, 160, sTemp); //Текущее напряжение
	sprintf(sTemp, "%02d.%02dA", BMS.current / 1000, (BMS.current % 1000) / 10);
	u8g_DrawStr(&u8g, 176, 160, sTemp); //Текущий расход тока
#endif
	if (BMSinfo.maxCurrent)
		amps = 15 - ((155 * BMS.current) / (BMSinfo.maxCurrent * 10));
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 6; j++) {
			u8g_DrawLine(&u8g, 220, 20 + j + i * 8, 240, 30 + j + i * 8);
			u8g_DrawLine(&u8g, 200, 30 + j + i * 8, 220, 20 + j + i * 8);
			if (i < amps)
				j = 6;
		}
	}
}

/*******************************************************************************
 *Рисует вкладку с фарами
 ******************************************************************************/
void drawLight(void) {
	uint8_t i;
	hStart = 40;
	vStart = 40;
	hStep = 120;
	vStep = 45;
	for (i = 0; i < PWM_COUNT; i++) {
		sprintf(sTemp, "%d", (100 * PWMGet(i)) / PWM_MAX);

		if (PWMGet(i))
			u8g_DrawStr(&u8g, hStart + 60, vStart - 2 + vStep * i, sTemp);
		else
			u8g_DrawStr(&u8g, hStart + 60, vStart - 2 + vStep * i, "Off");

		drawBar(hStart + 20, vStart + vStep * i, 100, 16, PWM_MAX, PWMGet(i), 0);
	}
	u8g_DrawXBM(&u8g, hStart + hStep + 10, vStart - 8 + vStep * 0, 32, 32,
			u8g_neighbor_bits);

	u8g_DrawXBM(&u8g, hStart + hStep + 10, vStart - 8 + vStep * 1, 32, 32,
			u8g_farthest_bits);

	u8g_DrawXBM(&u8g, hStart + hStep + 10, vStart - 8 + vStep * 2, 32, 32,
			u8g_lightdisplay_bits);

	if (navigate[0]) {
		u8g_SetFont(&u8g, u8g_font_elpauloIco); //мои иконки
		sTemp[0] = ARROW_RIGHT;
		sTemp[1] = 0;
		u8g_DrawStr(&u8g, hStart, vStart + 16 + vStep * (navigate[0] - 1),
				sTemp);
	}
}

/*******************************************************************************
 *Рисует вкладку с календарем
 ******************************************************************************/
void drawCalendar(void) {
	uint8_t i;
	uint8_t lastDay, weekday;
	hStep = 29;
	vStep = 21;
	hStart = 36;
	vStart = 33;
	for (i = 0; i < 7; i++) {
		u8g_DrawStr(&u8g, hStart + 5 + hStep * i, vStart - 1, days[config.lang][i]);
	}
	u8g_SetRot270(&u8g);
	i = u8g_GetStrWidth(&u8g, month[config.lang][calendar.month - 1]);
	u8g_DrawStr(&u8g, 45 - i / 2, 18, month[config.lang][calendar.month - 1]);
	sprintf(sTemp, "%d", calendar.year);
	u8g_DrawStr(&u8g, 96, 18, sTemp);
	u8g_UndoRotation(&u8g);
	u8g_SetFont(&u8g, u8g_font_7x13B);
	u8g_DrawLine(&u8g, hStart, vStart - 1, 239, vStart - 1); // ---
	for (i = 0; i < 8; i++) {
		u8g_DrawLine(&u8g, hStart + i * hStep, 18, hStart + i * hStep, 159); // |||
		u8g_DrawLine(&u8g, hStart, vStart + i * vStep, 239, vStart + i * vStep); // ---
	}
	weekday = weekDay(1, calendar.month, calendar.year);
	j = weekday;
	k = 0;
	lastDay = lastdayofmonth(calendar.year, calendar.month);
	for (i = 0; i < lastDay; i++) {
		if (i + 1 == calendar.day && time_p->tm_mon + 1 == calendar.month
				&& time_p->tm_year + 1900 == calendar.year) { //Если сегодня, выделяем день.
			u8g_DrawFrame(&u8g, hStart + 12 + hStep * j, vStart + 8 + k * vStep,
					17, 13);
		}
		if (navigate[1] == i + 1) { //Если совпадает с курсором выделяем день на календаре
			u8g_DrawFrame(&u8g, hStart + 1 + hStep * j,
					vStart + 1 + (vStep * k), hStep - 1, vStep - 1);
			u8g_DrawFrame(&u8g, hStart + 2 + hStep * j,
					vStart + 2 + (vStep * k), hStep - 3, vStep - 3);
		}
		if (VB(racelist.dayActiv_f, i+1) && VB(racelist.dayActiv_f, 0)) { //Если есть поездка и флаг готовности установлен рисуем пометку на дню
			u8g_DrawTriangle(&u8g, hStart + 2 + hStep * j,
					vStart + 2 + k * vStep, hStart + 10 + hStep * j,
					vStart + 2 + k * vStep, hStart + 2 + hStep * j,
					vStart + 10 + k * vStep);
		}
		sprintf(sTemp, "%02d", i + 1);
		u8g_DrawStr(&u8g, hStart + 14 + hStep * j, vStart + 19 + k * vStep,
				sTemp);
		if (j < 6) {
			j++;
		} else {
			j = 0;
			k++;
		}
	}
	u8g_SetFont(&u8g, u8g_font_elpauloIco); //мои иконки

	if (navigate[0] && !navigate[1]) {
		if (navigate[0] == 3) {
			sTemp[0] = ARROW_LEFT;
			sTemp[1] = 0;
			u8g_DrawStr(&u8g, hStart - 15, vStart + 1 * vStep, sTemp);
		} else if (navigate[0] == 2) {
			sTemp[0] = ARROW_LEFT;
			sTemp[1] = 0;
			u8g_DrawStr(&u8g, hStart - 15, (vStart + 4) + 4 * vStep, sTemp);
		} else {
			sTemp[0] = ARROW_RIGHT;
			sTemp[1] = 0;
			u8g_DrawStr(&u8g, hStart - 15, vStart + 3 * vStep, sTemp);
		}
	}
}

/*******************************************************************************
 *Рисует список заездов
 ******************************************************************************/
void drawRacelist(void) {
	uint8_t i;
	char str[2] = { ARROW_RIGHT, 0 };
	uint8_t vStart = 55, hStart = 40, vStep = 20, hStep = 68;
	char *col[4] = { "N", "Start", " Dst", "Speed" };
	u8g_DrawStr(&u8g, hStart - 20, vStart - 19, col[0]);
	for (i = 1; i < 4; i++) {
		u8g_DrawStr(&u8g, hStart - 64 + hStep * i, vStart - 21, col[i]);
		u8g_DrawLine(&u8g, hStart - 6 + hStep * (i - 1), vStart - 37,
				hStart - 6 + hStep * (i - 1),
				vStart - 18 + racelist.itemsDisplay * vStep);
	}
	u8g_DrawFrame(&u8g, 0, vStart - 17, 240, 2);
	for (i = 0; i < racelist.itemsDisplay; i++) {
		u8g_DrawLine(&u8g, hStart - 20, vStart + 3 + vStep * i, 239,
				vStart + 3 + vStep * i);
		str[1] = i + 49;
		u8g_DrawStr(&u8g, hStart - 20, vStart + i * vStep, str);
		sprintf(sTemp, "%02d:%02d", racelist.startTime[i] / 100, racelist.startTime[i] % 100);
		u8g_DrawStr(&u8g, hStart + hStep * 0, vStart + i * vStep, sTemp);
		sprintf(sTemp, "%03d.%02d", racelist.distance[i] / 1000000,
				(racelist.distance[i] % 1000000) / 10000);
		u8g_DrawStr(&u8g, hStart + hStep * 1, vStart + i * vStep, sTemp);
		sprintf(sTemp, "%02d.%02d", racelist.averSpeed[i] / 100,
				racelist.averSpeed[i] % 100);
		u8g_DrawStr(&u8g, hStart + hStep * 2, vStart + i * vStep, sTemp);
	}
	u8g_SetFont(&u8g, u8g_font_elpauloIco); //Мои иконки
	u8g_DrawStr(&u8g, hStart - 35, vStart - 19 + navigate[2] * vStep, str);
}

/*******************************************************************************
 *Рисует панель вкладок с часами
 ******************************************************************************/
void drawTabs(void) {
	uint8_t widthClock = 95;
	vStep = 18;
	hStep = 18;
	sTemp[0] = STATE_LIGHT;
	sTemp[1] = STATE_CALENDAR;
	sTemp[2] = 3;
	sTemp[3] = STATE_SETUP;
	sTemp[4] = 5;
	sTemp[5] = STATE_TERMO;
	sTemp[6] = STATE_BAT;
	sTemp[7] = STATE_STAT;
	sTemp[8] = 0;
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawBox(&u8g, 0, 0, 240, vStep);	//зачерняем верх
	u8g_SetDefaultBackgroundColor(&u8g);	//инвертный цвет
	u8g_SetFont(&u8g, u8g_font_elpauloIco);	//иконский шрифт
	u8g_DrawStr(&u8g, 1, 17, sTemp); //нарисуем строчку табиконок
	u8g_SetDefaultBackgroundColor(&u8g);
	if (stateMain == STATE_MAIN) {
		u8g_DrawRBox(&u8g, 239 - widthClock, 0, widthClock + 1, vStep + 2, 3);
		u8g_SetDefaultForegroundColor(&u8g);
	} else {
		u8g_DrawRBox(&u8g, (stateMain * hStep) - 18, 0, hStep, vStep + 2, 3);
		u8g_SetDefaultForegroundColor(&u8g);
		sTemp[0] = stateMain;
		sTemp[1] = 0;
		u8g_DrawStr(&u8g, (stateMain * hStep) - 17, 17, sTemp);
		u8g_SetDefaultBackgroundColor(&u8g);
	}
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	if (state.powerMode == POWERMODE_SLEEP)
		sprintf(sTemp, " SLEEP!");
	else if (config.SecInTime)
		sprintf(sTemp, "%02d:%02d:%02d", time_p->tm_hour, time_p->tm_min,
				time_p->tm_sec);
	else
		sprintf(sTemp, " %02d:%02d", time_p->tm_hour, time_p->tm_min);
	u8g_DrawStr(&u8g, 154, 15, sTemp);
}

/*******************************************************************************
 *Рисуем прогрессбар
 ******************************************************************************/
void drawBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t max,
		uint8_t curr, uint8_t type) {
	u8g_DrawFrame(&u8g, x, y, w, h);
	u8g_DrawBox(&u8g, x + 2, y + 2, ((w - 4) * curr) / max, h - 4);
}

/*******************************************************************************
 *Страница с температурами
 ******************************************************************************/
char *termoS[6] = { "Motor", "Control", "BMS", "Bat", "Air", "Addon" };
void drawTemp() {
	uint8_t i;
	vStart = 43;
	hStart = 30;
	vStep = 20;
	hStep = 120;
	for (i = 0; i < 6; i++) {
		u8g_DrawStr(&u8g, hStart, vStart + vStep * i, termoS[i]);
	}
	sprintf(sTemp, "%03d.%d", 999 / 10, 999 % 10);
	u8g_DrawStr(&u8g, hStart + hStep, vStart + vStep * 0, sTemp);
	u8g_DrawStr(&u8g, hStart + hStep, vStart + vStep * 1, sTemp);
	u8g_DrawStr(&u8g, hStart + hStep, vStart + vStep * 2, sTemp);
	u8g_DrawStr(&u8g, hStart + hStep, vStart + vStep * 3, sTemp);
	u8g_DrawStr(&u8g, hStart + hStep, vStart + vStep * 4, sTemp);
	u8g_DrawStr(&u8g, hStart + hStep, vStart + vStep * 5, sTemp);
	if (navigate[0]) {
		sTemp[0] = ARROW_RIGHT;
		sTemp[1] = 0;
		u8g_SetFont(&u8g, u8g_font_elpauloIco); //Мои иконки
		u8g_DrawStr(&u8g, hStart - 18, vStart + 2 + vStep * (navigate[0] - 1),
				sTemp);
	}
}


/*******************************************************************************
 *Рисуем экран граффика температуры
 ******************************************************************************/
termo_t termo;

uint8_t termoVertPos = 0; //Позиция текущей температуры на шкале
void drawTempChart(void) {
	uint8_t i;
	uint8_t termoVertPos,
	graPerDot; //Сотые доли градуса на пиксел
	vStart = 20;
	hStart = 20;
	vStep = 18;
	hStep = 18;
	termo.out = termo.in - 1;
	graPerDot = (termo.max - termo.min)/114; //Сколько градусов на пиксел
	if(!graPerDot)graPerDot = 1;
	termoVertPos = 158 + (termo.min/graPerDot) - (termo.buff[termo.out]/graPerDot);
	u8g_SetRot270(&u8g);
	u8g_SetFont(&u8g, u8g_font_7x13B);
	u8g_DrawStr(&u8g, 5, 12, termoS[navigate[0] - 1]);
	sprintf(sTemp, "%03d", termo.speed);
	u8g_DrawStr(&u8g, 80, 12, sTemp);
	u8g_DrawStr(&u8g, 103, 12, "Sec");
	u8g_UndoRotation(&u8g);
	u8g_SetFont(&u8g, u8g_font_elpauloIco); //мои иконки
	sTemp[0] = ARROW_DOWN;
	u8g_DrawStr(&u8g, hStart - 20, vStart + 16 + navigate[2] * vStep, sTemp);
	sTemp[0] = ARROW_UP;
	u8g_DrawStr(&u8g, hStart - 20, vStart + 78 + navigate[2] * vStep, sTemp);
	u8g_DrawLine(&u8g, hStart - 3, vStart - 2, hStart - 3, 159); //Первая вертикальная

	for (i = 0; i < termo.count; i++) {
		u8g_DrawLine(&u8g, vStart + 32 + i, 158  + (termo.min/graPerDot) - (termo.buff[termo.out]/graPerDot), vStart + 32 + i, 158);
		termo.out--;
		if (termo.out > 200)
			termo.out = BUF_TERMO_SIZE - 1;
	}
	for (i = 0; i < 110; i++) {
		u8g_DrawPixel(&u8g, hStart + i * 2, 31); //Первая горизонтальная
		u8g_DrawPixel(&u8g, hStart + 31, 18 + i * 2); //Первая вертикальная
		u8g_DrawPixel(&u8g, hStart + i * 2, 159); //Третья Горизонтальная
		u8g_DrawPixel(&u8g, 239, i * 2); //Третья вертикальная
		u8g_SetDefaultBackgroundColor(&u8g);
		u8g_DrawPixel(&u8g, vStart - 1 + i * 2, termoVertPos); //Вторая горизонтальная
		u8g_SetDefaultForegroundColor(&u8g);
		u8g_DrawPixel(&u8g, hStart + i * 2, termoVertPos); //Вторая горизонтальная
	}
	u8g_SetFont(&u8g, u8g_font_7x13B);
	sprintf(sTemp, "%02d.%d", termo.buff[termo.in - 1] / 100, (termo.buff[termo.in - 1] % 100) / 10); //Значение температуры
	u8g_DrawStr(&u8g, hStart + 2, termoVertPos-1, sTemp);
	sprintf(sTemp, "%02d.%d", termo.max / 100, (termo.max % 100)/10);
	u8g_DrawStr(&u8g, hStart + 2, 30, sTemp); //Максимальная
	sprintf(sTemp, "%02d.%d", termo.min / 100, (termo.min % 100)/10);
	u8g_DrawStr(&u8g, hStart + 2, 158, sTemp); //Минимальная
}

/*******************************************************************************
 *Меню настроек
 ******************************************************************************/
void drawSetup(void) {
	mtk_Pos(12, 35);
	mtk_Draw();
}

/*******************************************************************************
 *Быстрое меню
 ******************************************************************************/
void drawMainQuickMenu(void) {
	sTemp[1] = 0;
	u8g_DrawStr(&u8g, 100, 50, "Back");
	u8g_DrawStr(&u8g, 50, 90, "Lock");
	u8g_DrawStr(&u8g, 155, 90, "Off");
	u8g_DrawStr(&u8g, 95, 130, "Sleep");
	u8g_SetFont(&u8g, u8g_font_elpauloIco); //мои иконки
	sTemp[0] = ARROW_UP;
	u8g_DrawStr(&u8g, 112, 71, sTemp);
	sTemp[0] = ARROW_LEFT;
	u8g_DrawStr(&u8g, 90, 93, sTemp);
	sTemp[0] = ARROW_RIGHT;
	u8g_DrawStr(&u8g, 134, 93, sTemp);
	sTemp[0] = ARROW_DOWN;
	u8g_DrawStr(&u8g, 113, 114, sTemp);
}

/*******************************************************************************
 *Быстрое меню
 ******************************************************************************/
void drawStatQuickMenu(void) {
	sTemp[1] = 0;
	u8g_DrawStr(&u8g, 70, 50, "Statistics");
	u8g_DrawStr(&u8g, 50, 90, "Back");
	u8g_DrawStr(&u8g, 155, 90, "Reset");
	u8g_DrawStr(&u8g, 54, 130, "Save and reset");
	u8g_SetFont(&u8g, u8g_font_elpauloIco); //мои иконки
	//str[0]=ARROW_UP;
	//u8g_DrawStr(&u8g,112,71, str);
	sTemp[0] = ARROW_LEFT;
	u8g_DrawStr(&u8g, 90, 93, sTemp);
	sTemp[0] = ARROW_RIGHT;
	u8g_DrawStr(&u8g, 134, 93, sTemp);
	sTemp[0] = ARROW_DOWN;
	u8g_DrawStr(&u8g, 113, 114, sTemp);
}

/*******************************************************************************
 *Вкладка с параметрами батареи
 ******************************************************************************/
void drawBat(void) {
	uint8_t x, y, v;
	x = 0;
	y = 38;
	v = 20;
	u8g_DrawStr(&u8g, x, y, "Control");
	drawCell(x, 40, 8);
	x = 115;
	u8g_DrawStr(&u8g, x, y, "83%");
	u8g_DrawStr(&u8g, x, y += v, "3.956V");
	u8g_DrawStr(&u8g, x, y += v, "Discharge");
	x = 0; y = 108;
	u8g_DrawLine(&u8g, x, 88, 239, 88);
	u8g_DrawStr(&u8g, x, y, "Power");
	drawCell(x, 111, 6);
	x = 115;
	u8g_DrawStr(&u8g, x, y, "60%");
	u8g_DrawStr(&u8g, x, y += v, "9000mA·h");
	u8g_DrawStr(&u8g, x, y += v, "Discharge");
}

/*******************************************************************************
 *Рисуем батарейку
 ******************************************************************************/
void drawCell(uint8_t x, uint8_t y, uint8_t val) {
	uint8_t i;
	u8g_DrawFrame(&u8g, x + 72, y + 10, 6, 20);
	u8g_DrawFrame(&u8g, x, y, 73, 40);
	for (i = 0; i < val; i++) {
		u8g_DrawBox(&u8g, x + 2 + i * 7, y + 2, 6, 36);
	}
}
/*******************************************************************************
 *Отрисовка прощания
 ******************************************************************************/
void drawOff(void) {
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	u8g_SetScale2x2(&u8g);
	u8g_DrawStr(&u8g, 20, 45, "Goodbye!");
}

/*******************************************************************************
 *Выводит статистику текущего заезда
 ******************************************************************************/
void drawStat(void) {
	uint8_t i;
	uint32_t timeSec;
	extern char *raceParams[2][7];
	hStart = 0;
	vStart = 36;
	hStep = 0;
	vStep = 20;
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	for (i = 0; i < 7; i++) {
		u8g_DrawLine(&u8g, 0, vStart + 3 + vStep * i, 239,
				vStart + 3 + vStep * i);
		u8g_DrawStr(&u8g, hStart, vStart + i * vStep, raceParams[config.lang][i]);
	}
	u8g_DrawLine(&u8g, 115, 18, 115, 159);
	//Максимальная скорость за заезд.
	sprintf(sTemp, "%02d.%02d km/h", track.peakSpeed / 100, track.peakSpeed % 100);
	u8g_DrawStr(&u8g, 120, vStart + 0 * vStep, sTemp);
	// Расход на километр
	sprintf(sTemp, "%02d.%03d Ah/km", track.expense / 1000, track.expense % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 1 * vStep, sTemp);
	// Время в пути до 36 часов
	timeSec = track.tics / 32768;
	sprintf(sTemp, "%02d:%02d:%02d", timeSec / 3600, (timeSec / 60) % 60, timeSec % 60);
	u8g_DrawStr(&u8g, 120, vStart + 2 * vStep, sTemp);
	// Потрачено емкости за заезд
	sprintf(sTemp, "%02d.%03d Ah", track.discharge / 1000, track.discharge % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 3 * vStep, sTemp);
	// Предпологаемый пробег до разряда
	sprintf(sTemp, "%02d.%01d km", track.toCharging / 10, track.toCharging % 10);
	u8g_DrawStr(&u8g, 120, vStart + 4 * vStep, sTemp);
	//Средняя скорость.  32768 тиков в секунду.
	sprintf(sTemp, "%02d.%02d km/h", track.averageSpeed / 100, track.averageSpeed % 100);
	u8g_DrawStr(&u8g, 120, vStart + 5 * vStep, sTemp);
	// Пройдено километров за все время
	sprintf(sTemp, "%06lu.%02u km", (uint32_t)(track.odometr / 1000000), (uint16_t)((track.odometr % 1000000) / 10000));
	u8g_DrawStr(&u8g, 120, vStart + 6 * vStep, sTemp);
}

/*******************************************************************************
 *Выводит статистику сохраненного заезда
 ******************************************************************************/
void drawHistItem(void) {
	uint8_t i;
	extern char *raceParams[2][7];
	uint32_t timeSec;
	hStart = 0;
	vStart = 36;
	hStep = 0;
	vStep = 20;
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	for (i = 0; i < 4; i++) {
		u8g_DrawLine(&u8g, 0, vStart + 3 + vStep * i, 239,
				vStart + 3 + vStep * i);
		u8g_DrawStr(&u8g, hStart, vStart + i * vStep, raceParams[config.lang][i]);
	}
	//Максимальная скорость за заезд.
	u8g_DrawLine(&u8g, 115, 18, 115, 18 + vStep * i);
	sprintf(sTemp, "%02d.%02d km/h", histItem.peakSpeed / 100, histItem.peakSpeed % 100);
	u8g_DrawStr(&u8g, 120, vStart + 0 * vStep, sTemp);
	// Расход на километр
	sprintf(sTemp, "%02d.%03d Ah/km", histItem.expense / 1000, histItem.expense % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 1 * vStep, sTemp);
	// Время в пути заезда
	timeSec = histItem.tics / 32768;
	sprintf(sTemp, "%02d:%02d:%02d", timeSec / 3600, (timeSec / 60) % 60, timeSec % 60);
	u8g_DrawStr(&u8g, 120, vStart + 2 * vStep, sTemp);
	// Потрачено емкости за заезд
	sprintf(sTemp, "%02d.%03d Ah", histItem.discharge / 1000, histItem.discharge % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 3 * vStep, sTemp);
}

/*******************************************************************************
 *Выводит всплывающее окно
 ******************************************************************************/
void message(void) {
	uint8_t x, y, x2, y2, w, h, i, j;
	char *str1[4] = {"", "Alert", "!!! Error !!!", "??? Query ???"};
	if(!popup.head)
		popup.head = str1[popup.type];
	if(!popup.body)
		popup.body = "Empty message!";
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	w = 10 + u8g_GetStrWidth(&u8g, popup.body);
	h = 66;
	x = (DISPLAY_WIDTH - w) / 2;
	y = (DISPLAY_HEIGHT - h) / 2;
	u8g_SetDefaultBackgroundColor(&u8g);
	u8g_DrawBox(&u8g, x + 1, y + 1, w - 2, h - 2);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawFrame(&u8g, x, y, w, h);
	u8g_DrawFrame(&u8g, x + 2, y + 2, w - 4, h - 4);
	u8g_DrawLine(&u8g, x + 3, y + 20, x + w - 4, y + 20);
	u8g_DrawStr(&u8g, x + ((w - u8g_GetStrWidth(&u8g, popup.head)) / 2), y + 17, popup.head);
	u8g_DrawStr(&u8g, x + 5, y + 37, popup.body);

	sTemp[1] = 0;
	y2 = y + h - 24;
	u8g_DrawLine(&u8g, x + 3, y2, x + w - 4, y2);
	y2 = y+h-7;
	u8g_DrawStr(&u8g, x+15, y2, "Cancel");
	u8g_DrawStr(&u8g, x+w-35, y2, "Ok");
	u8g_SetFont(&u8g, u8g_font_elpauloIco); //мои иконки
	y2 +=2;
	sTemp[0] = ARROW_LEFT;
	u8g_DrawStr(&u8g, x, y2, sTemp);
	sTemp[0] = ARROW_RIGHT;
	u8g_DrawStr(&u8g, x+w-17, y2, sTemp);

	for (i = 0; i < 8; i++) {
		y2 = y + h + i;
		for (j = 8 + x; j < w + x; j++) {
			if ((j + i) % 2)
				u8g_DrawPixel(&u8g, j, y2);
		}
		x2 = x + w + i;
		for (j = 8 + y; j < h + 8 + y; j++) {
			if ((j + i) % 2)
				u8g_DrawPixel(&u8g, x2, j);
		}
	}
}
