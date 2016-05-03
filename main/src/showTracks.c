#include "showTracks.h"
#include "memory.h"
#include <stdlib.h>

void selectTrackItem(uint8_t);
void histReadTrack(uint8_t);

extern config_t config;
extern state_t state;

racelistAll_t * racelistAllp;
track_t * pHistTrack;
mtk_element_t mtkShowTracks;

uint8_t win;

/*******************************************************************************
 * Отрисовка списка заездов с обработкой команд
 ******************************************************************************/
void showtracks(mtk_t * mtk) {
	char sTemp[10];
	uint8_t i, j, index;
	uint8_t vPos = 55, hPos = 55, vStep = 20, hStep = 62;
	char *col[4] = { "Date", "Time", "  Dst", "NN" };

	index = racelistAllp->index;
	if (config.racelistType) {	//Выбрано отображение без календаря
		if (mtk->command) {
			switch (mtk->command) {
			case COMMAND_NEXT: {
				if((racelistAllp->select != 64) && (win != 2)){
					loadHistItem();
					win = 2;
				}
				mtk->command = COMMAND_NULL;
			}
				break;
			case COMMAND_PREV: {
				if (win == 2) {
					win = config.racelistType;
				} else if( win == 1){
					racelistAllp->select = 64;
					mtk->pos = 0;
					mtk->select = 0;
				}
				mtk->command = COMMAND_NULL;
			}
				break;
			case COMMAND_UP: {
				selectTrackItem(HIST_NEXT);
				mtk->command = COMMAND_NULL;
			}
				break;
			case COMMAND_DOWN: {
				if(racelistAllp->select == 64){
					mtk->pos = 1;
					mtk->select = 1;
				}
				selectTrackItem(HIST_PREV);
				mtk->command = COMMAND_NULL;
			}
				break;
			}
		} else {

			switch (win) {
			case 1: {	//Отображать окно списка заездов
				u8g_DrawStr(mtk->u8g, hPos - 35, vPos - vStep, col[3]);
				for (i = 0; i < 3; i++) {
					u8g_DrawStr(mtk->u8g, hPos + hStep * i, vPos - 21, col[i]);
					u8g_DrawLine(mtk->u8g, hPos - 8 + hStep * i, vPos - 37, hPos - 8 + hStep * i, vPos - 18	+ (racelistAllp->items > 6 ? 6 : racelistAllp->items) * vStep);
				}
				u8g_DrawFrame(mtk->u8g, 0, vPos - 17, 240, 2);
				if(racelistAllp->select != 64){
					u8g_DrawStr(mtk->u8g, hPos - 50, vPos - 19 + (6 - (racelistAllp->select - racelistAllp->item)) * vStep, "\xA");
				}
				if (racelistAllp->items) {
					for (i = 0; i < (racelistAllp->items > 6 ? 6 : racelistAllp->items); i++) {
						if (--index > 5)
							index = 5;
						u8g_DrawLine(mtk->u8g, hPos - 35, vPos + 3 + vStep * i, 239, vPos + 3 + vStep * i);
						sprintf(sTemp, "%d", HIST_ITEM_COUNT - 5 - racelistAllp->item + i);
						u8g_DrawStr(mtk->u8g, hPos - 35, vPos + i * vStep, sTemp);
						if ((racelistAllp->distance[index] != 0xFFFF) && (racelistAllp->distance[index] != 0x0000)) {
							sprintf(sTemp, "%02d/%02d", racelistAllp->startDate[index] / 100, racelistAllp->startDate[index] % 100);
							u8g_DrawStr(mtk->u8g, hPos + hStep * 0, vPos + i * vStep, sTemp);
							sprintf(sTemp, "%02d:%02d", racelistAllp->startTime[index] / 100, racelistAllp->startTime[index] % 100);
							u8g_DrawStr(mtk->u8g, hPos + hStep * 1, vPos + i * vStep, sTemp);
							if(racelistAllp->distance[index] > 999999999)
								sprintf(sTemp, "%03d.%01d", racelistAllp->distance[index] / 1000000, (racelistAllp->distance[index] % 1000000) / 100000);
							else
								sprintf(sTemp, "%03d.%02d", racelistAllp->distance[index] / 1000000, (racelistAllp->distance[index] % 1000000) / 10000);
							u8g_DrawStr(mtk->u8g, hPos + hStep * 2, vPos + i * vStep, sTemp);
						} else {
							for(j = 0; j < 3; j++){
								u8g_DrawStr(mtk->u8g, hPos + hStep * j, vPos + i * vStep, "-----");
							}
						}
					}
					if (racelistAllp->items > 6) { //Если не все элементы влазят в экран отмечаем это
						if (racelistAllp->item > 0) {
							u8g_DrawStr(mtk->u8g, hPos - 55, vPos + vStep * 5, "\xD");
						}
						if (racelistAllp->item + 6 < racelistAllp->items) {
							u8g_DrawStr(mtk->u8g, hPos - 55, vPos, "\xC");
						}
					}
				}
				else
					u8g_DrawStr(mtk->u8g, hPos, vPos, "Empty");
			}
				break;
			case 0: {	//Отображать окно календаря

			}
				break;
			case 2: {	//Отображать окно подробностей заезда
				char sTemp[15];
				uint8_t i;
				extern char *raceParams[7];
				uint32_t timeSec;

				uint8_t hStart = 0;
				uint8_t vStart = 36;
				hStep = 0;
				u8g_SetFont(mtk->u8g, u8g_font_elpaulo20);
				for (i = 0; i < 5; i++) {
					u8g_DrawLine(mtk->u8g, 0, vStart + 3 + vStep * i, 239, vStart + 3 + vStep * i);
					u8g_DrawStr(mtk->u8g, hStart, vStart + i * vStep, raceParams[i]);
				}
				//Максимальная скорость за заезд.
				u8g_DrawLine(mtk->u8g, 115, 18, 115, 18 + vStep * i);
				sprintf(sTemp, "%02d.%02d km/h", pHistTrack->peakSpeed / 100, pHistTrack->peakSpeed % 100);
				u8g_DrawStr(mtk->u8g, 120, vStart + 2 * vStep, sTemp);
				// Расход на километр
				sprintf(sTemp, "%02d.%03d Ah/km", pHistTrack->expense / 1000, pHistTrack->expense % 1000);
				u8g_DrawStr(mtk->u8g, 120, vStart + 4 * vStep, sTemp);
				// Время в пути
				timeSec = pHistTrack->tics / 32768;
				sprintf(sTemp, "%02d:%02d:%02d", timeSec / 3600, (timeSec / 60) % 60, timeSec % 60);
				u8g_DrawStr(mtk->u8g, 120, vStart + 0 * vStep, sTemp);
				// Потрачено емкости за заезд
				sprintf(sTemp, "%02d.%03d Ah", pHistTrack->discharge / 1000, pHistTrack->discharge % 1000);
				u8g_DrawStr(mtk->u8g, 120, vStart + 3 * vStep, sTemp);
				//Средняя скорость.  32768 тиков в секунду.
				sprintf(sTemp, "%02d.%02d km/h", pHistTrack->averageSpeed / 100, pHistTrack->averageSpeed % 100);
				u8g_DrawStr(mtk->u8g, 120, vStart + 1 * vStep, sTemp);
			}
				break;
			}
		}
	}
}

/*******************************************************************************
 * Загрузка данных 6 последних из списка заездов
 ******************************************************************************/
void histReadInit(void) {
	uint8_t i;

	if (!racelistAllp)
		racelistAllp = (racelistAll_t *) malloc(sizeof(racelistAll_t));
	if (!pHistTrack)
		pHistTrack = (track_t *) malloc(sizeof(track_t));
	if (racelistAllp && pHistTrack) {
		win = config.racelistType;
		I2C_EE_BufferRead(&racelistAllp->histCell, HIST_INDEX_START, 1);
		racelistAllp->items = HIST_ITEM_COUNT;
		racelistAllp->item = HIST_ITEM_COUNT - 6;
		racelistAllp->select = HIST_ITEM_COUNT;
		racelistAllp->index = 5;
		for (i = 0; i < 6; i++) {
			histReadTrack(HIST_PREV);
		}
	} else
		messageCall("SYSTEM ERROR!", "HEAP END!", POPUP_ERROR);
}

/*******************************************************************************
 * Загрузка данных (6 последних/ следующего / предыдущего) из списка заездов
 *******************************************************************************/
void histReadTrack(uint8_t param) {
	uint8_t readBuff[HIST_UNINT_SIZE];
	tm_t dateTime;

	switch (param) {
	case HIST_NEXT: {
		racelistAllp->histCell += 7;
		racelistAllp->histCell &= HIST_BUF_MASK;
	}
		break;
	case HIST_PREV: {
		if (--racelistAllp->index > 5)
			racelistAllp->index = 5;
	}
		break;
	}
	racelistAllp->adres[racelistAllp->index] = HIST_CONTENT_START + HIST_UNINT_SIZE * racelistAllp->histCell;
	I2C_EE_BufferRead(readBuff, racelistAllp->adres[racelistAllp->index], HIST_UNINT_SIZE); //Считываем инфу по заезду
	racelistAllp->distance[racelistAllp->index] = *((uint32_t*) &readBuff[8]); //Пройденное расстояние
	CounterToFtime(*(uint32_t*) &readBuff[16], &dateTime);
	racelistAllp->startTime[racelistAllp->index] = dateTime.tm_hour * 100 + dateTime.tm_min; //Время старта;
	racelistAllp->startDate[racelistAllp->index] = (dateTime.tm_mon + 1) * 100 + dateTime.tm_mday; //Дата старта;
	switch (param) {
	case HIST_NEXT: {
		if (++racelistAllp->index > 5)
			racelistAllp->index = 0;
		racelistAllp->histCell -= 6;
		racelistAllp->histCell &= HIST_BUF_MASK;
	}
		break;
	case HIST_PREV: {
		racelistAllp->histCell--;
		racelistAllp->histCell &= HIST_BUF_MASK;
	}
		break;
	}
	state.taskList |= TASK_REDRAW;
}

/*******************************************************************************
 * Смещение по списку элементов
 ******************************************************************************/
void selectTrackItem(uint8_t direction) {
	if (racelistAllp)
		switch (direction) {
		case HIST_PREV: {
			if (racelistAllp->select > 0) {
				racelistAllp->select--;
				if (((racelistAllp->select - racelistAllp->item) == 1) && (racelistAllp->item)){
					histReadTrack(HIST_PREV);
					racelistAllp->item--;
				}
			}
		}
			break;
		case HIST_NEXT: {
			if (racelistAllp->select < racelistAllp->items) {
				racelistAllp->select++;
				if (((racelistAllp->select - racelistAllp->item) == 4) && (racelistAllp->items - racelistAllp->item > 6)){
					histReadTrack(HIST_NEXT);
					racelistAllp->item++;
				}
			}
		}
			break;
		}
	state.taskList |= TASK_REDRAW;
}

/*******************************************************************************
 * Освобождение памяти
 ******************************************************************************/
void trackExit(void) {
	free(racelistAllp);
	free(pHistTrack);
	racelistAllp = NULL;
	pHistTrack = NULL;
}

/*******************************************************************************
 * Заполняет структуру статистики заезда
 ******************************************************************************/
void loadHistItem(void) {
	uint8_t i, n, buffer[HIST_UNINT_SIZE];;
	n = racelistAllp->index;
	for(i = 0; i < racelistAllp->select - racelistAllp->item; i++){
		if (++n > 5)
			n = 0;
	}
	I2C_EE_BufferRead(buffer, racelistAllp->adres[n], HIST_UNINT_SIZE);
	memcpy(&pHistTrack->peakSpeed, &buffer[0], 2);
	memcpy(&pHistTrack->startCapacity, &buffer[2], 2);
	memcpy(&pHistTrack->endCapacity, &buffer[4], 2);
	memcpy(&pHistTrack->circle, &buffer[6], 2);
	memcpy(&pHistTrack->distance, &buffer[8], 4);
	memcpy(&pHistTrack->tics, &buffer[12], 4);
	memcpy(&pHistTrack->startTime, &buffer[16], 4);
}
