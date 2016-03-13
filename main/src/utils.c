/*
 * utils.c
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: 7134956
 */

#include "config.h"
#include "utils.h"
#include "timer.h"
#include "rtc.h"
#include "draw.h"
#include <math.h>

void compass(mtk_t * mtk);

extern uint8_t stateMain;
extern state_t state;
mtk_element_t mtkStopwatch,	//Секундомер
		mtkTimer,		//Таймер
		mtkCompass;		//Компас

stopwatch_t sWatch;

tm_t * timerGetSet(tm_t * t);

void utilInit(void) {
	mtk_SetRootElement(&mtkStopwatch);
	mtk_SetupElement(&mtkStopwatch, ELEMENT_GFUNC, NULL, 0, TYPE_CMD_ACCEPT, &stopwatch, &mtkTimer);
	mtk_SetupElement(&mtkTimer, ELEMENT_TIME, NULL, 3, TYPE_FUNC | TYPE_NEEDOK, &timerGetSet, &mtkCompass);
	mtk_SetupElement(&mtkCompass, ELEMENT_GFUNC, NULL, 0, TYPE_CMD_ACCEPT, &compass, NULL);
}

/*******************************************************************************
 * Отрисовка и обрадотка команд секундомера
 ******************************************************************************/
void stopwatch(mtk_t * mtk) {
	uint8_t i, x, y;
	uint32_t count;
	char sTemp[11];
	count = sWatch.dsH[sWatch.nums];
	if (mtk->command) {
		switch (mtk->command) {
		case COMMAND_NEXT: {
			if (!sWatch.nums) {
				state.taskList |= TASK_STOPWATCH;//Для отображения на главном экране
				SysTick_task_add(stopwatchTick, 100); //Задача считать время
				sWatch.nums = 1;
				sWatch.select = 1;
				sWatch.dsH[sWatch.nums] = 0;
			} else {
				if (!SysTick_task_check(stopwatchTick)
						&& sWatch.nums == sWatch.select) {
					SysTick_task_add(stopwatchTick, 100);
					state.taskList |= TASK_STOPWATCH;
				} else if (sWatch.select < 9) {
					sWatch.select++;
					if (sWatch.select > sWatch.nums) {
						sWatch.dsH[sWatch.nums + 1] = sWatch.dsH[sWatch.nums];
						sWatch.nums++;
					}
				}
			}
			mtk->command = COMMAND_NULL;
		}
			break;
		case COMMAND_PREV:
			if (sWatch.select > 1) {
				sWatch.select--;
				mtk->command = COMMAND_NULL;
			}
			break;
		case COMMAND_UP: {
			if (sWatch.nums) {
				if (SysTick_task_check(stopwatchTick)) {
					SysTick_task_del(stopwatchTick);
				} else {
					SysTick_task_add(stopwatchTick, 100);
					sWatch.select = sWatch.nums;
				}
				state.taskList ^= TASK_STOPWATCH;
			}
			mtk->command = COMMAND_NULL;
		}
			break;
		case COMMAND_DOWN: {
			SysTick_task_del(stopwatchTick);
			sWatch.nums = 0;
			sWatch.select = 0;
			state.taskList |= TASK_REDRAW;
			state.taskList &= ~ TASK_STOPWATCH;
			mtk->command = COMMAND_NULL;
		}
			break;
		}
	} else {
		u8g_DrawLine(mtk->u8g, 0, 38, 239, 38);

		x = 8, y = 35;
		for (i = 0; i < sWatch.nums; i++) {
			sprintf(sTemp, "%d", i + 1);
			if (sWatch.select == i + 1) {
				u8g_DrawRBox(mtk->u8g, x - 4, y - 16, 18, 18, 3);
				u8g_SetDefaultBackgroundColor(mtk->u8g);
				u8g_DrawStr(mtk->u8g, x, y, sTemp);
				u8g_SetDefaultForegroundColor(mtk->u8g);
			} else
				u8g_DrawStr(mtk->u8g, x, y, sTemp);
			x += 18;
		}
		if (state.taskList & TASK_STOPWATCH)
			u8g_DrawStr(mtk->u8g, 190, y, "RUN");
		else if (!sWatch.nums)
			u8g_DrawStr(mtk->u8g, 188, y, "STOP");
		else
			u8g_DrawStr(mtk->u8g, 180, y, "PAUSE");
		y = 57;
		if (sWatch.select > 1) {
			y -= 6;
			u8g_DrawLine(mtk->u8g, 0, 105, 239, 105);
		}
//Отрисовка верхнего счетчика интервалов.
		count = sWatch.dsH[sWatch.select] - sWatch.dsH[sWatch.select - 1];
		u8g_SetFont(mtk->u8g, u8g_font_elpaulo32n);
		u8g_SetScale2x2(mtk->u8g);
		sprintf(sTemp, "%02d:%02d", (count / 600) % 60, (count / 10) % 60);
		u8g_DrawStr(mtk->u8g, 0, y, sTemp);
		u8g_UndoScale(mtk->u8g);
		sprintf(sTemp, ".%01d", count % 10);
		u8g_DrawStr(mtk->u8g, 205, y * 2, sTemp);
	}
//Отрисовка нижнего/полного счета.
	if (sWatch.select > 1) {
		count = sWatch.dsH[sWatch.select];
		sprintf(sTemp, "%01d:%02d:%02d:%01d", (count / 36000),
				((count / 600) % 60), ((count / 10) % 60), (count % 10));
		if(count/360000)
			x = 43;
		else
			x = 67;
		u8g_DrawStr(mtk->u8g, x, 138, sTemp);
		u8g_SetFont(mtk->u8g, u8g_font_elpaulo20);
		u8g_DrawStr(mtk->u8g, 3, 138, "Total:");
	}
	/* Нарисуем подскуазку*/
	u8g_SetFont(mtk->u8g, u8g_font_elpaulo20);
	x = 0, y = 158;
	u8g_DrawStr(mtk->u8g, x, y, "\x0AStart");
	u8g_DrawStr(mtk->u8g, x + 80, y, "\x0CPause");
	u8g_DrawStr(mtk->u8g, x + 160, y, "\x0DReset");
	u8g_DrawLine(mtk->u8g, 0, 140, 239, 140);
	x = 75;
	for (i = 0; i < 2; i++) {
		u8g_DrawLine(mtk->u8g, x, 141, x, 159);
		x += 80;
	}
}

/*******************************************************************************
 * Задача отсчетов секундомера
 ******************************************************************************/
void stopwatchTick(void) {
	sWatch.dsH[sWatch.nums]++;
	if ((sWatch.nums == sWatch.select) || (stateMain == STATE_MAIN))
		state.taskList |= TASK_LIM_REDRAW;
}

uint32_t timer;
/*******************************************************************************
 * Задача отсчетов таймера
 ******************************************************************************/
void timerTick(void) {
	if(timer){
		timer--;
		state.taskList |= TASK_LIM_REDRAW;
	}else{
		SysTick_task_del(timerTick);
		state.taskList |= TASK_REDRAW;
		state.taskList &= ~ TASK_TIMER;
		messageCall(NULL, "Timer: Time is over!", POPUP_ALERT);
	}
}

tm_t tempTimer;
tm_t * timerGetSet(tm_t * t) {
	if (!t) { //Взять значение таймера
		CounterToFtime(timer, &tempTimer);
		return  &tempTimer;
	} else {//Установить значение таймера
		timer = FtimeToCounter(t);
		SysTick_task_add(timerTick, 1000);
		state.taskList |= TASK_TIMER;
		return NULL;
	}
}

uint16_t angle;
void rotate(uint8_t x, uint8_t y, uint8_t * x1, uint8_t * y1, uint16_t angle);
/*******************************************************************************
* Рисуем компас
 ******************************************************************************/
void compass(mtk_t * mtk) {
	char sTemp[10];
	uint8_t x, y, x1, y1, x2, y2, x3, y3;

	x = 60;
	y = 80;
	x1 = 60;
	y1 = 30;
	x2 = 50;
	y2 = 60;
	x3 = 70;
	y3 = 60;

	u8g_DrawCircle(mtk->u8g, 60, 80, 50, U8G_DRAW_ALL);
	u8g_DrawCircle(mtk->u8g, 60, 80, 20, U8G_DRAW_ALL);
	u8g_DrawStr(mtk->u8g, 55, 87, "N");

	rotate(x, y, &x1, &y1, angle);
	rotate(x, y, &x2, &y2, angle);
	rotate(x, y, &x3, &y3, angle);

	u8g_DrawTriangle(mtk->u8g, x1,y1, x2,y2, x3,y3);
	sprintf(sTemp, "Degree: %d", angle);
	u8g_DrawStr(mtk->u8g, 120, 40, sTemp);
}

/*******************************************************************************
* Поворот точки
 ******************************************************************************/
void rotate(uint8_t x, uint8_t y, uint8_t * x1, uint8_t * y1, uint16_t angle) {
	float rad = angle / ( 180 / 3.1415926535897932384626433832795 );
	uint8_t xt=x+(*x1-x)*cos(rad)-(*y1-y)*sin(rad);
	*y1=y+(*x1-x)*sin(rad)+(*y1-y)*cos(rad);
	*x1 = xt;
}
