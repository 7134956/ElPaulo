/*
 * utils.c
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: 7134956
 */

#include "config.h"
#include "utils.h"
#include "timer.h"

extern uint8_t stateMain;
extern state_t state;
mtk_element_t mtkStopwatch,	//Секундомер
		mtkTimer;		//Таймер

stopwatch_t sWatch;

void utilInit(void) {
	mtk_SetRootElement(&mtkStopwatch);
	mtk_SetupElement(&mtkStopwatch, ELEMENT_GFUNC, NULL, 0, TYPE_CMD_ACCEPT, &stopwatch, &mtkTimer);
	mtk_SetupElement(&mtkTimer, ELEMENT_GFUNC, NULL, 0, TYPE_CMD_ACCEPT, &timer, NULL);
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
			x += 17;
		}
		if (state.taskList & TASK_STOPWATCH)
			u8g_DrawStr(mtk->u8g, 180, y, " RUN");
		else if (!sWatch.nums)
			u8g_DrawStr(mtk->u8g, 180, y, " STOP");
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

uint32_t timerSec;
uint32_t timerStart;

void timer(mtk_t * mtk) {
	char sTemp[10];
//	uint8_t i, x, y;
	timerSec = 86399;
	u8g_SetFont(mtk->u8g, u8g_font_elpaulo32n);

	sprintf(sTemp, "%02d:%02d:%02d", timerSec / 3600, (timerSec / 60) % 60,
			timerSec % 60);
	u8g_DrawStr(mtk->u8g, 38, 100, sTemp);
}
