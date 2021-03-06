#include "config.h"
#include "draw.h"
#include "bitmap.h"
#include "rtc.h"
#include "bat.h"
#include "utils.h"
#include "power.h"
#include "beeper.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

uint8_t hStart, vStart, hStep, vStep, j, k;
message_t message;
extern char *month[12];
extern char *days[7];

u8g_t u8g;

tm_t * time_p; //Указатель на структуру со временем
extern uint32_t timer;
extern calendar_t calendar;
extern racelistDay_t racelistDay; //Информация о заездах
extern track_t track; //Параметры текущего заезда
extern BMS_info_t BMS_info;
extern BMS_t BMS;	//Силовая батарея
extern bat_t bat;	//Батарейка питания велокомпа
extern track_t histItem;
extern uint8_t navigate[5];
extern uint8_t stateMain;
extern stopwatch_t sWatch;
extern power_t powerControl;
extern mtk_element_t mtkPin;	//Пароль стартового экрана
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
void drawBar(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, uint8_t);
void drawStart(void);
void drawTemp(void);
void drawTempChart(void);
void drawMainQuickMenu(void);
void drawStatQuickMenu(void);
void drawBat(void);
void drawCell(uint8_t, uint8_t, uint8_t);
void drawOff(void);
void drawScrSvr(void);
void drawDigit(uint8_t, uint8_t, uint8_t, uint8_t);
void drawNum(uint8_t *, uint8_t, uint8_t, uint8_t);
void drawSegment(uint8_t, uint8_t, uint8_t, uint8_t);
void drawMessage(void);
void drawCalibration(void);
void drawTest(void);

/*******************************************************************************
 * Запуск дисплея и настройка графики
 ******************************************************************************/
void drawInit(void) {
#ifdef DISPLAY_SDL
	u8g_Init(&u8g, &u8g_dev_sdl_2bit);//For PC
#elif defined DISPLAY_ST7586S_SPI
	u8g_InitComFn(&u8g, &u8g_dev_st7586s_jlx240160g666_hw_spi, u8g_com_stm32_st7586s_hw_spi_fn); //Minimal RAM mode
#elif defined DISPLAY_ST7586S_4X_SPI
	u8g_InitComFn(&u8g, &u8g_dev_st7586s_jlx240160g666_4x_hw_spi, u8g_com_stm32_st7586s_hw_spi_fn); //Speed mode
#elif defined DISPLAY_ST7586S_20X_SPI
	u8g_InitComFn(&u8g, &u8g_dev_st7586s_jlx240160g666_20x_hw_spi, u8g_com_stm32_st7586s_hw_spi_fn); //Max speed mode
#elif defined DISPLAY_ST75256_SPI
	u8g_InitComFn(&u8g, &u8g_dev_st75256_jlx240160g676_hw_spi, u8g_com_stm32_hw_spi_fn); //Minimal RAM mode
#elif defined DISPLAY_ST75256_4X_SPI
	u8g_InitComFn(&u8g, &u8g_dev_st75256_jlx240160g676_4x_hw_spi, u8g_com_stm32_hw_spi_fn); //Speed mode
#elif defined DISPLAY_ST75256_20X_SPI
	u8g_InitComFn(&u8g, &u8g_dev_st75256_jlx240160g676_20x_hw_spi, u8g_com_stm32_hw_spi_fn); //Max speed mode
#elif defined DISPLAY_ST75256_SPI_DMA
	u8g_InitComFn(&u8g, &u8g_dev_st75256_jlx240160g676_hw_spi, u8g_com_stm32_hw_spi_dma_fn); //Minimal RAM mode
#elif defined DISPLAY_ST75256_4X_SPI_DMA
	u8g_InitComFn(&u8g, &u8g_dev_st75256_jlx240160g676_4x_hw_spi, u8g_com_stm32_hw_spi_dma_fn); //Speed mode
#elif defined DISPLAY_ST75256_20X_SPI_DMA
	u8g_InitComFn(&u8g, &u8g_dev_st75256_jlx240160g676_20x_dma_hw_spi, u8g_com_stm32_hw_spi_dma_fn); //Max speed mode
#elif defined DISPLAY_ST7586S_20X_SPI_9B
	u8g_InitComFn(&u8g, &u8g_dev_st7586s_20x_hw_spi, u8g_com_hw_spi_9bit_fn); //Max speed mode. 3-wire SPI
#elif defined DISPLAY_ST7669_4X_SPI
	u8g_InitComFn(&u8g, &u8g_dev_st7669a_4x_hw_spi, u8g_com_hw_spi_fn); //Speed mode
#elif defined DISPLAY_SH1106_SPI_IIC
	u8g_InitComFn(&u8g, &u8g_dev_sh1106_128x64_i2c, u8g_com_hw_i2c_fn); //
#endif	
	mtk_Init(&u8g);
	time_p = timeGetSet(NULL);//Взяли указатель на время
	u8g_SetContrast(&u8g, config.contrast);
}

/*******************************************************************************
 * Включить дисплей
 ******************************************************************************/
void displayOn(void) {
	u8g_SleepOff(&u8g);
}

/*******************************************************************************
 * Выключить дисплей
 ******************************************************************************/
void displayOff(void) {
	u8g_SleepOn(&u8g);
}

/*******************************************************************************
 * Выключить дисплей
 ******************************************************************************/
uint32_t contrastGetSet(uint32_t *contrast) {
	if (contrast) {
		u8g_SetContrast(&u8g, *contrast);
		config.contrast = *contrast;
		return 0;
	} else
		return (uint32_t) config.contrast;
}

/*******************************************************************************
 * Запуск цыкла отрисовки дисплея
 ******************************************************************************/
void redrawDisplay(void) {
	u8g_FirstPage(&u8g);
	do {
		draw();
	} while (u8g_NextPage(&u8g));
}

/*******************************************************************************
 * Рисует экран в зависимости от текущего состояния
 ******************************************************************************/
void draw(void) {
	u8g_SetFontPosBaseline(&u8g);
	if (powerControl.sleepMode == POWERMODE_STOP)
		drawScrSvr();
	else if(stateMain == STATE_CALIB)
		drawCalibration();
	else {
		if ((stateMain != STATE_START) && (stateMain != STATE_OFF)
				&& (stateMain != STATE_SILENT) && (stateMain != STATE_CALIB) && (stateMain != STATE_WARNING))
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
		case STATE_WARNING: {
			drawTest();
		}
			break;

		case STATE_SETUP:
		case STATE_UTIL: {
			mtk_Pos(16, 35);
			mtk_Draw();
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
			if (config.racelistType) {
				mtk_Pos(0, 35);
				mtk_Draw();
			} else {
				if (navigate[3]) {
					drawHistItem();
				} else if (navigate[2]) {
					drawRacelist();
				} else {
					drawCalendar();
				}
			}
		}
			break;
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
			if (message.count)
				drawMessage();
	}
}

/*******************************************************************************
 * Рисует стартовый экран с паролем
 ******************************************************************************/
void drawStart(void) {
	u8g_SetFont(&u8g, u8g_font_helvR24);
	u8g_DrawRFrame(&u8g, 0, 0, 240, 160, 5);
	u8g_DrawRFrame(&u8g, 5, 5, 230, 150, 5);
	u8g_DrawStr(&u8g, 54, 43, "El   Paulo");
	u8g_DrawXBM(&u8g, 86, 4, 24, 63, u8g_logo_bits);
	u8g_DrawStr(&u8g, 36, 95, "PIN:");
	u8g_DrawFrame(&u8g, 10, 110, 220, 40);
	u8g_SetFont(&u8g, u8g_font_ncenR10);
	if (message.count) {
		u8g_DrawStr(&u8g, 15, 125, message.popup[message.count - 1].head);
		u8g_DrawStr(&u8g, 15, 145, message.popup[message.count - 1].body);
	} else {
		u8g_DrawStr(&u8g, 15, 125, "All excellent ;-)");
		u8g_DrawStr(&u8g, 15, 145, "Please enter PIN code");
	}
	u8g_SetFont(&u8g, u8g_font_elpaulo32n);
	mtk_SetRootElement(&mtkPin);
	mtk_Pos(108, 97);
	mtk_Draw();
}

/*******************************************************************************
 * Рисует панель вкладок с часами
 ******************************************************************************/
void drawTabs(void) {
	char sTemp[16];
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
	u8g_SetFont(&u8g, u8g_font_elpaulo20);

	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawBox(&u8g, 0, 0, 240, vStep);	//зачерняем верх
	u8g_SetDefaultBackgroundColor(&u8g);	//инвертный цвет
	u8g_DrawStr(&u8g, 1, 16, sTemp); //нарисуем строчку табиконок
	u8g_SetDefaultBackgroundColor(&u8g);
	if (stateMain == STATE_MAIN) {
		u8g_DrawRBox(&u8g, 239 - widthClock, 0, widthClock + 1, vStep + 2, 3);
		u8g_SetDefaultForegroundColor(&u8g);
	} else {
		u8g_DrawRBox(&u8g, (stateMain * hStep) - 18, 0, hStep, vStep + 2, 3);
		u8g_SetDefaultForegroundColor(&u8g);
		sTemp[0] = stateMain;
		sTemp[1] = 0;
		u8g_DrawStr(&u8g, (stateMain * hStep) - 17, 16, sTemp);
		u8g_SetDefaultBackgroundColor(&u8g);
	}
	if (config.SecInTime) {
		sprintf(sTemp, "%02d:%02d:%02d", time_p->tm_hour, time_p->tm_min,
				time_p->tm_sec);
		u8g_DrawStr(&u8g, 156, 15, sTemp);
	} else {
		sprintf(sTemp, "%02d:%02d", time_p->tm_hour, time_p->tm_min);
		u8g_DrawStr(&u8g, 171, 15, sTemp);
	}
}

/*******************************************************************************
 * Рисует главную вкладку
 ******************************************************************************/
void drawMain(void) {
	uint8_t x1, x2;
	char sTemp[15];
	uint8_t i;
	uint8_t barAH; //Емкость батареи в палочках
	int8_t amps; //Значение тока в палочках

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
	if (state.taskList & TASK_STOPWATCH)
		sprintf(sTemp, "%01d:%02d:%02d:%01d", sWatch.dsH[sWatch.nums] / 36000,
				(sWatch.dsH[sWatch.nums] / 600) % 60,
				(sWatch.dsH[sWatch.nums] / 10) % 60,
				sWatch.dsH[sWatch.nums] % 10);
	else if (state.taskList & TASK_TIMER)
	sprintf(sTemp, "%01d:%02d:%02d", timer / 3600,
			(timer / 60) % 60,
			(timer) % 60);
	else
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
	if (!(state.taskList & (TASK_STOPWATCH | TASK_TIMER)))
		u8g_DrawStr(&u8g, 176, 136, "km");
	hStep = 50;
	/* Левый бар заряда батареи */
	if (BMS_info.maxCap)
		barAH = (155 * BMS.capacity) / (BMS_info.maxCap * 10);
	else barAH = bat.level * 15 / 100; //Заряд батареи велокомпа
	for (i = 0; i < 15; i++) {
		vStart = 22 + i * 8;
		hStep--;
		if (i < 3)
			hStep--;
		if (i < 6)
			hStep--;
		if (i < 13)
			hStep--;

		if (i >= 15 - barAH)
			u8g_DrawBox(&u8g, 0, vStart, hStep, 6);
		else
			u8g_DrawFrame(&u8g, 0, vStart, hStep, 6);
	}
#ifdef SYSTEM_WIN
	if(0) { //FIXME Если нет данных бмс
#else
	if (1) { //Если есть бмс
		sprintf(sTemp, "%d.%d MHz", SystemCoreClock / 1000000, SystemCoreClock % 1000000);
		u8g_DrawStr(&u8g, 20, 160, sTemp);
#endif
	} else {
		sprintf(sTemp, "%02d.%02dAh", BMS.capacity / 1000,
				(BMS.capacity % 1000) / 10);
		u8g_DrawStr(&u8g, 0, 160, sTemp); //Текущий остаток заряда
		sprintf(sTemp, "%02d.%02dV", BMS.voltage / 1000,
				(BMS.voltage % 1000) / 10);
		u8g_DrawStr(&u8g, 90, 160, sTemp); //Текущее напряжение
		sprintf(sTemp, "%02d.%02dA", BMS.current / 1000,
				(BMS.current % 1000) / 10);
		u8g_DrawStr(&u8g, 176, 160, sTemp); //Текущий расход тока
	}
	if (BMS_info.maxCurrent)
		amps = ((155 * BMS.current) / (BMS_info.maxCurrent * 10));
	else if (track.accelerationMax)
		amps = ((155 * track.acceleration) / (track.accelerationMax * 10));
	else
		amps = 0;
	/* Правый бар индикатор ускорения */
	if (amps >= 0) {
		x1 = 29; x2 = 20;
	} else {
		amps = -amps;
		x1 = 20; x2 = 29;
	}
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 6; j++) {
			u8g_DrawLine(&u8g, 220, x2 + j + i * 8, 239, x1 + j + i * 8);
			u8g_DrawLine(&u8g, 201, x1 + j + i * 8, 220, x2 + j + i * 8);
			if (i < 15 - amps)
				j = 6;
		}
	}
}

/*******************************************************************************
 * Рисует вкладку с фарами
 ******************************************************************************/
void drawLight(void) {
	char sTemp[6];
	uint8_t i, x, y;
	hStart = 40;
	vStart = 50;
	hStep = 120;
	vStep = 60;
	x = hStart + 60;
	for (i = 0; i < PWM_COUNT; i++) {
		if (PWMGet(i))
			//sprintf(sTemp, "%d.%d", (100 * PWMGet(i)) / PWM_MAX,  ((1000 * PWMGet(i)) / PWM_MAX) % 10); //Проценты
			sprintf(sTemp, "1/%d", PWM_MAX / PWMGet(i)); //Доли
		else
			sprintf(sTemp, "Off");
		u8g_DrawStr(&u8g, x, vStart - 2 + vStep * i, sTemp);
		drawBar(hStart + 20, vStart + vStep * i, 100, 16, PWM_MAX, PWMGet(i), 0);
	}
	x = hStart + hStep + 10;
	y = vStart - 8;
	u8g_DrawXBM(&u8g, x, y + vStep * 0, 32, 32, u8g_lightdisplay_bits);
	u8g_DrawXBM(&u8g, x, y + vStep * 1, 32, 32, u8g_neighbor_bits);
	if (navigate[0]) {
		sTemp[0] = ARROW_RIGHT;
		sTemp[1] = 0;
		y = vStart + 16 + vStep * (navigate[0] - 1);
		u8g_DrawStr(&u8g, hStart, y, sTemp);
	}
}

/*******************************************************************************
 * Рисуем прогрессбар
 ******************************************************************************/
void drawBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t max,
		uint16_t curr, uint8_t type) {
	u8g_DrawFrame(&u8g, x, y, w, h);
	u8g_DrawBox(&u8g, x + 2, y + 2, ((w - 4) * curr) / max, h - 4);
}

/*******************************************************************************
 * Рисует вкладку с календарем
 ******************************************************************************/
void drawCalendar(void) {
	char sTemp[6];
	uint8_t i;
	uint8_t lastDay, weekday;
	hStep = 29;
	vStep = 21;
	hStart = 36;
	vStart = 33;
	for (i = 0; i < 7; i++) {
		u8g_DrawStr(&u8g, hStart + 5 + hStep * i, vStart - 1, days[i]);
	}
	u8g_SetRot270(&u8g);
	i = u8g_GetStrWidth(&u8g, month[calendar.month - 1]);
	u8g_DrawStr(&u8g, 45 - i / 2, 18, month[calendar.month - 1]);
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
		if (VB(racelistDay.dayActiv_f, i+1) && VB(racelistDay.dayActiv_f, 0)) { //Если есть поездка и флаг готовности установлен рисуем пометку на дню
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
	if (navigate[0] && !navigate[1]) {
		u8g_SetFont(&u8g, u8g_font_elpaulo20);
		sTemp[1] = 0;
		if (navigate[0] == 3) {
			sTemp[0] = ARROW_LEFT;
			u8g_DrawStr(&u8g, hStart - 15, vStart + 1 * vStep, sTemp);
		} else if (navigate[0] == 2) {
			sTemp[0] = ARROW_LEFT;
			u8g_DrawStr(&u8g, hStart - 15, (vStart + 4) + 4 * vStep, sTemp);
		} else {
			sTemp[0] = ARROW_RIGHT;
			u8g_DrawStr(&u8g, hStart - 15, vStart + 3 * vStep, sTemp);
		}
	}
}

/*******************************************************************************
 * Рисует дневной список заездов
 ******************************************************************************/
void drawRacelist(void) {
	char sTemp[10];
	uint8_t i;
	char str[2] = { ARROW_RIGHT, 0 };
	uint8_t vStart = 55, hStart = 40, vStep = 20, hStep = 68;
	char *col[4] = { "N", "Start", " Dst", "Speed" };
	u8g_DrawStr(&u8g, hStart - 20, vStart - 19, col[0]);
	for (i = 1; i < 4; i++) {
		u8g_DrawStr(&u8g, hStart - 64 + hStep * i, vStart - 21, col[i]);
		u8g_DrawLine(&u8g, hStart - 6 + hStep * (i - 1), vStart - 37, hStart - 6 + hStep * (i - 1), vStart - 18 + racelistDay.itemsDisplay * vStep);
	}
	u8g_DrawFrame(&u8g, 0, vStart - 17, 240, 2);
	u8g_DrawStr(&u8g, hStart - 35, vStart - 19 + navigate[2] * vStep, str);
	if(racelistDay.itemsDisplay)
	for (i = 0; i < racelistDay.itemsDisplay; i++) {
		u8g_DrawLine(&u8g, hStart - 20, vStart + 3 + vStep * i, 239, vStart + 3 + vStep * i);
		str[0] = i + 49;
		u8g_DrawStr(&u8g, hStart - 20, vStart + i * vStep, str);
		sprintf(sTemp, "%02d:%02d", racelistDay.startTime[i] / 100, racelistDay.startTime[i] % 100);
		u8g_DrawStr(&u8g, hStart + hStep * 0, vStart + i * vStep, sTemp);
		sprintf(sTemp, "%03d.%02d", racelistDay.distance[i] / 1000000, (racelistDay.distance[i] % 1000000) / 10000);
		u8g_DrawStr(&u8g, hStart + hStep * 1, vStart + i * vStep, sTemp);
		sprintf(sTemp, "%02d.%02d", racelistDay.averSpeed[i] / 100, racelistDay.averSpeed[i] % 100);
		u8g_DrawStr(&u8g, hStart + hStep * 2, vStart + i * vStep, sTemp);
	}else
		u8g_DrawStr(&u8g, hStart, vStart, "Empty");
}

/*******************************************************************************
 * Страница с температурами
 ******************************************************************************/
char *termoS[6] = { "Motor", "Control", "BMS", "Bat", "Air", "Addon" };
void drawTemp() {
	char sTemp[10];
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
		u8g_DrawStr(&u8g, hStart - 18, vStart + 2 + vStep * (navigate[0] - 1),
				sTemp);
	}
}

/*******************************************************************************
 * Рисуем экран граффика температуры
 ******************************************************************************/
termo_t termo;
uint8_t termoVertPos = 0; //Позиция текущей температуры на шкале
void drawTempChart(void) {
	char sTemp[10];
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
 * Быстрое меню 1
 ******************************************************************************/
void drawMainQuickMenu(void) {
	char sTemp[2];
	sTemp[1] = 0;
	u8g_DrawStr(&u8g, 100, 50, "Back");
	u8g_DrawStr(&u8g, 50, 90, "Lock");
	u8g_DrawStr(&u8g, 155, 90, "Off");
	u8g_DrawStr(&u8g, 95, 130, "Sleep");
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
 * Быстрое меню 2
 ******************************************************************************/
void drawStatQuickMenu(void) {
	char sTemp[2];
	sTemp[1] = 0;
	u8g_DrawStr(&u8g, 70, 50, "Statistics");
	u8g_DrawLine(&u8g, 70, 53, 168, 53);
	u8g_DrawStr(&u8g, 50, 90, "Back");
	u8g_DrawStr(&u8g, 155, 90, "Reset");
	u8g_DrawStr(&u8g, 54, 130, "Save and reset");
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
 * Вкладка с параметрами батареи
 ******************************************************************************/
void drawBat(void) {
	char sTemp[13];
	uint8_t x, y, v;
	
	x = 0;
	y = 38;
	v = 20;
	u8g_DrawStr(&u8g, x, y, "Control");
	drawCell(x, 40, bat.level/10);
	x = 115;
	switch (bat.state) {
	case BAT_DISCHARGE:		//Используется
		sprintf(sTemp, "Use");
		break;
	case BAT_CHARGE:		//Заряжается
		sprintf(sTemp, "Charge");
		break;
	case BAT_FULL:			//Заряд окончен
		sprintf(sTemp, "Full");
		break;
	case BAT_RESERVE:		//Не используется
		sprintf(sTemp, "Reserve");
		break;
	case BAT_NULL:
		sprintf(sTemp, "NULL");
		break;
	}
	u8g_DrawStr(&u8g, x, y, sTemp);
	sprintf(sTemp, "%d%%", bat.level);
	u8g_DrawStr(&u8g, x, y += v, sTemp);
	sprintf(sTemp, "%d.%03d (%04d)", bat.voltage / 1000, bat.voltage % 1000, bat.value);
	u8g_DrawStr(&u8g, x, y += v, sTemp);
	x = 0;
	y = 108;
	u8g_DrawLine(&u8g, x, 88, 239, 88);

	u8g_DrawStr(&u8g, x, y, "Power");
	drawCell(x, 111, BMS.percents / 10);
	x = 115;
	switch (BMS.state) {
	case BMS_NOTFOUND:		//Используется
		sprintf(sTemp, "Not found");
		break;
	case BMS_USE:		//Заряжается
		sprintf(sTemp, "Use");
		break;
	case BMS_CHARGE:			//Заряд окончен
		sprintf(sTemp, "Charge");
		break;
	case BMS_FULL:		//Не используется
		sprintf(sTemp, "Full");
		break;
	case BMS_AVAILABLE:
		sprintf(sTemp, "Available");
		break;
	}
	u8g_DrawStr(&u8g, x, y, sTemp);
	if(BMS.state)
		sprintf(sTemp, "%02d%%", BMS.percents);
	else
		sprintf(sTemp, "__%%");
	u8g_DrawStr(&u8g, x, y += v, sTemp);
	if(BMS.state)
		sprintf(sTemp, "%04dmA\xB7h", BMS.capacity);
	else
		sprintf(sTemp, "____mA\xB7h");
	u8g_DrawStr(&u8g, x, y += v, sTemp);
}

/*******************************************************************************
 * Рисуем батарейку
 ******************************************************************************/
void drawCell(uint8_t x, uint8_t y, uint8_t val) {
	uint8_t i;
	
	u8g_DrawFrame(&u8g, x + 72, y + 10, 6, 20);
	u8g_DrawFrame(&u8g, x, y, 73, 40);
	x -= 5;
	y += 2;
	for (i = 0; i < val; i++) {
		u8g_DrawBox(&u8g, x += 7, y, 6, 36);
	}
}

/*******************************************************************************
 * Отрисовка прощания
 ******************************************************************************/
void drawOff(void) {
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	u8g_SetScale2x2(&u8g);
	u8g_DrawStr(&u8g, 20, 45, "Goodbye!");
}

/*******************************************************************************
 * Выводит статистику текущего заезда
 ******************************************************************************/
void drawStat(void) {
	uint8_t i;
	uint32_t timeSec;
	char sTemp[15];
	extern char *raceParams[7];
	
	hStart = 0;
	vStart = 36;
	hStep = 0;
	vStep = 20;
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	for (i = 0; i < 7; i++) {
		u8g_DrawLine(&u8g, 0, vStart + 3 + vStep * i, 239,
				vStart + 3 + vStep * i);
		u8g_DrawStr(&u8g, hStart, vStart + i * vStep, raceParams[i]);
	}
	u8g_DrawLine(&u8g, 115, 18, 115, 159);
	//Максимальная скорость за заезд.
	sprintf(sTemp, "%02d.%02d km/h", track.peakSpeed / 100, track.peakSpeed % 100);
	u8g_DrawStr(&u8g, 120, vStart + 2 * vStep, sTemp);
	// Расход на километр
	sprintf(sTemp, "%02d.%03d Ah/km", track.expense / 1000, track.expense % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 4 * vStep, sTemp);
	// Время в пути до 36 часов
	timeSec = track.tics / 32768;
	sprintf(sTemp, "%02d:%02d:%02d", timeSec / 3600, (timeSec / 60) % 60, timeSec % 60);
	u8g_DrawStr(&u8g, 120, vStart + 0 * vStep, sTemp);
	// Потрачено емкости за заезд
	sprintf(sTemp, "%02d.%03d Ah", track.discharge / 1000, track.discharge % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 3 * vStep, sTemp);
	// Предпологаемый пробег до разряда
	sprintf(sTemp, "%02d.%01d km", track.toCharging / 10, track.toCharging % 10);
	u8g_DrawStr(&u8g, 120, vStart + 5 * vStep, sTemp);
	//Средняя скорость.  32768 тиков в секунду.
	sprintf(sTemp, "%02d.%02d km/h", track.averageSpeed / 100, track.averageSpeed % 100);
	u8g_DrawStr(&u8g, 120, vStart + 1 * vStep, sTemp);
	// Пройдено километров за все время
	sprintf(sTemp, "%06lu.%02u km", (uint32_t)(track.odometr / 1000000), (uint16_t)((track.odometr % 1000000) / 10000));
	u8g_DrawStr(&u8g, 120, vStart + 6 * vStep, sTemp);
}

/*******************************************************************************
 * Выводит статистику сохраненного заезда
 ******************************************************************************/
void drawHistItem(void) {
	char sTemp[15];
	uint8_t i;
	extern char *raceParams[7];
	uint32_t timeSec;
	
	hStart = 0;
	vStart = 36;
	hStep = 0;
	vStep = 20;
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	for (i = 0; i < 5; i++) {
		u8g_DrawLine(&u8g, 0, vStart + 3 + vStep * i, 239, vStart + 3 + vStep * i);
		u8g_DrawStr(&u8g, hStart, vStart + i * vStep, raceParams[i]);
	}
	//Максимальная скорость за заезд.
	u8g_DrawLine(&u8g, 115, 18, 115, 18 + vStep * i);
	sprintf(sTemp, "%02d.%02d km/h", histItem.peakSpeed / 100, histItem.peakSpeed % 100);
	u8g_DrawStr(&u8g, 120, vStart + 2 * vStep, sTemp);
	// Расход на километр
	sprintf(sTemp, "%02d.%03d Ah/km", histItem.expense / 1000, histItem.expense % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 4 * vStep, sTemp);
	// Время в пути
	timeSec = histItem.tics / 32768;
	sprintf(sTemp, "%02d:%02d:%02d", timeSec / 3600, (timeSec / 60) % 60, timeSec % 60);
	u8g_DrawStr(&u8g, 120, vStart + 0 * vStep, sTemp);
	// Потрачено емкости за заезд
	sprintf(sTemp, "%02d.%03d Ah", histItem.discharge / 1000, histItem.discharge % 1000);
	u8g_DrawStr(&u8g, 120, vStart + 3 * vStep, sTemp);
	//Средняя скорость.  32768 тиков в секунду.
	sprintf(sTemp, "%02d.%02d km/h", histItem.averageSpeed / 100, histItem.averageSpeed % 100);
	u8g_DrawStr(&u8g, 120, vStart + 1 * vStep, sTemp);
}

/*******************************************************************************
 * Вызов сообщения
 ******************************************************************************/
void messageCall(char * head, char * body, uint8_t type){
	static const uint16_t beepAlert[] = {5,1,20,15,2,15,20,15,2,55,1,4};
	static const uint16_t beepError[] = {5,1,20,15,2,15,20,15,2,15,20,15,2,15,20,15,2,55,1,8};
	static const uint16_t beepQuery[] = {5,1,20,15,2,55,1,2};
	
	if (message.count < MESSAGE_SLOTS) {
		message.popup[message.count].head = head;
		message.popup[message.count].body = body;
		message.popup[message.count].type = type;
		message.count++;
	}
	switch (type) {
	case POPUP_ALERT: {
		beepPlay(beepAlert);
	}
		break;
	case POPUP_ERROR: {
		beepPlay(beepError);
	}
		break;
	case POPUP_QUERY: {
		beepPlay(beepQuery);
	}
		break;
	}
}

/*******************************************************************************
 * Выводит всплывающее окно
 ******************************************************************************/
void drawMessage(void) {
	char sTemp[2];
	uint8_t x, y, x2, y2, w, h, i, j;
	char *str1[4] = {"", "\x14 Alert \x14", "\x12 Error \x12", "\x13 Query \x13"};
	
	if(!message.popup[message.count - 1].head)
		message.popup[message.count - 1].head = str1[message.popup[message.count - 1].type];
	if(!message.popup[message.count - 1].body)
		message.popup[message.count - 1].body = "Empty message!";
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	w = 10 + u8g_GetStrWidth(&u8g, message.popup[message.count - 1].body);
	if(w < 130)
		w = 130;
	h = 66;
	x = (DISPLAY_WIDTH - w) / 2;
	y = (DISPLAY_HEIGHT - h) / 2;
	u8g_SetDefaultBackgroundColor(&u8g);
	u8g_DrawBox(&u8g, x + 1, y + 1, w - 2, h - 2);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_DrawFrame(&u8g, x, y, w, h);
	u8g_DrawFrame(&u8g, x + 2, y + 2, w - 4, h - 4);
	u8g_DrawLine(&u8g, x + 3, y + 20, x + w - 4, y + 20);
	u8g_DrawStr(&u8g, x + ((w - u8g_GetStrWidth(&u8g, message.popup[message.count - 1].head)) / 2), y + 17, message.popup[message.count - 1].head);
	u8g_DrawStr(&u8g, x + 5, y + 37, message.popup[message.count - 1].body);

	sTemp[1] = 0;
	y2 = y + h - 24;
	u8g_DrawLine(&u8g, x + 3, y2, x + w - 4, y2);
	y2 = y+h-7;
	if(message.popup[message.count - 1].type == POPUP_QUERY)
	u8g_DrawStr(&u8g, x+15, y2, "Cancel");
	else
		u8g_DrawStr(&u8g, x+15, y2, "Ok");
	u8g_DrawStr(&u8g, x+w-35, y2, "Ok");
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

/*******************************************************************************
 * Тестирование
 ******************************************************************************/
void drawTest(void) {

}

/*******************************************************************************
 * Заставка для спящего режима в виде стильизованных часов
 ******************************************************************************/
void drawScrSvr(void) {
	extern char *days[7];
	uint8_t i, x, y, s, step;
	
	x=5;
	y=15;
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	for(i=0; i<7; i++){
		u8g_DrawStr(&u8g, x+35 * i, y, days[i]);
	}
	u8g_DrawBox(&u8g, x - 5 + 35 * time_p->tm_wday, y + 3, 30, 5);
	
	x = 4;
	y = 35;
	s = 36;
	step = s/2;
	drawNum(&x, y, s, time_p->tm_hour);
	x += 57;
	u8g_DrawBox(&u8g, x, y + 10, 10, 10);
	u8g_DrawBox(&u8g, x, y + 50, 10, 10);
	x = 145;
	drawNum(&x, y, s, time_p->tm_min);

	s = 17;
	y = 124;
	x = 2;
	step = s*1.5;
	drawNum(&x, y, s, time_p->tm_mday);
	x += step-2;
	u8g_DrawBox(&u8g, x + 5, y + 31, 4, 4);
	x += step-2;
	drawNum(&x, y, s, time_p->tm_mon+1);
	x += step-2;
	u8g_DrawBox(&u8g, x + 5, y + 31, 4, 4);
	x += step-2;
	drawDigit(x, y, s, 2);
	x += step;
	drawDigit(x, y, s, 0);
	x += step;
	drawNum(&x, y, s, time_p->tm_year-100);
}

/*******************************************************************************
 * Заставка для спящего режима в виде стильизованных часов
 ******************************************************************************/
void drawNum(uint8_t * x, uint8_t y, uint8_t s, uint8_t num) {
	uint8_t step = s*1.5;
	drawDigit(*x, y, s, num/10);
	*x += step;
	drawDigit(*x, y, s, num%10);
}

/*******************************************************************************
 * Выводит цифру стилизованную под ЖК
 ******************************************************************************/
void drawDigit(uint8_t x, uint8_t y, uint8_t s, uint8_t n) {
	uint8_t i, h, w, x2, y2, ls;
	uint8_t seg[11] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0x01 };
	ls=5;
	for (i = 0; i < 8; i++) {
		if (seg[n] & 128 >> i) {
			switch (i) {
			case 0:
				x2 = x + 2;
				y2 = y;
				h = ls;
				w = s - 4;
				break;
			case 1:
				x2 = x + s;
				y2 = y + 2;
				h = s - 4;
				w = ls;
				break;
			case 2:
				x2 = x + s;
				y2 = y + s + 2;
				h = s - 4;
				w = ls;
				break;
			case 3:
				x2 = x + 2;
				y2 = y + s * 2;
				h = ls;
				w = s - 4;
				break;
			case 4:
				x2 = x;
				y2 = y + s + 2;
				h = s - 4;
				w = ls;
				break;
			case 5:
				x2 = x;
				y2 = y + 2;
				h = s - 4;
				w = ls;
				break;
			case 6:
				x2 = x + 2;
				y2 = y + s;
				h = ls;
				w = s - 4;
				break;
			case 7:
				x2 = x + 2;
				y2 = y + 2 + s * 2;
				h = ls*2;
				w = ls*3;
				break;
			}
			if(h > w)
				w =1+ h/8;
			else
				h =1+ w/8;
			drawSegment(x2, y2, h, w);
		}
	}
}

/*******************************************************************************
 * Выводит сегмент стилизованный под ЖК
 ******************************************************************************/
void drawSegment(uint8_t x, uint8_t y, uint8_t h, uint8_t w) {
	uint8_t i;
	if (h > w)
		/*Вертикальный*/
		for (i = 0; i < w; i++) {
			u8g_DrawLine(&u8g, x + i, y + i, x + i, y + h - i);
			u8g_DrawLine(&u8g, x - i, y + i, x - i, y + h - i);
		}
	else
		for (i = 0; i < h; i++) {
			u8g_DrawLine(&u8g, x + i, y + i, x + w - i, y + i);
			u8g_DrawLine(&u8g, x + i, y - i, x + w - i, y - i);
		}
}

/*******************************************************************************
 * Диалог калибровки джойстика
 ******************************************************************************/
extern uint8_t keyReq;
void drawCalibration(void) {
	char sTemp[2];
	sTemp[1] = 0;
	u8g_SetFont(&u8g, u8g_font_elpaulo20);
	u8g_DrawStr(&u8g, 63, 60, "Calibration!");
	u8g_DrawStr(&u8g, 73, 100, "Push:");

	switch (keyReq) {
	case 0: {
		sTemp[0] = ARROW_UP;
	}
		break;
	case 1: {
		sTemp[0] = ARROW_DOWN;
	}
		break;
	case 2: {
		sTemp[0] = ARROW_LEFT;
	}
		break;
	case 3: {
		sTemp[0] = ARROW_RIGHT;
	}
		break;
	default:
		sTemp[0] = 0;
	}
	u8g_DrawStr(&u8g, 140, 100, sTemp);
}
