/*
 * utils.h
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: 7134956
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "mtk.h"

typedef struct stopwatch_t { //Глобальная структура с настройками сохраняется в EEPROM
	uint8_t nums;
	uint32_t dsH[10]; //Сохраненные времена. Считаем в последнюю не занятую
	uint8_t select;
} stopwatch_t;

void utilInit(void);
void stopwatch(mtk_t *);
void stopwatchTick(void);
void timer(mtk_t *);

#endif /* UTILS_H_ */
