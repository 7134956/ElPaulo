#ifndef BAT_H_
#define BAT_H_

#include "config.h"

#define BAT_NULL 0			//Нет состояния
#define BAT_RESERVE 1		//Не используется
#define BAT_DISCHARGE 2		//Используется
#define BAT_CHARGE 3		//Заряжается
#define BAT_FULL 4			//Заряд окончен

void batInit(void);
	
typedef struct bat_t {	//Глобальная структура состояния батарейки
	uint16_t voltage;	//Напряжение на батарейке
	uint8_t level;		//Уровень заряда батареи
	uint8_t state;		//Состоянии батарейки
	float kS;			//Размах чувствительности АЦП
} bat_t;

#endif /* BAT_H_ */
