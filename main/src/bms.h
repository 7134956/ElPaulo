#ifndef _BMS_H
#define _BMS_H

//#include "config.h"

typedef struct BMSconfig_t { //информация BMS
	uint8_t BMSVersion;		//Номер версии bms
	char batString[30];		//Описание батареи
	uint16_t Vmin;			//Минимальное напряжение ячейки
	uint16_t Inom;			//Номинальная сила тока ячейки
	uint16_t Imax;			//Максимальная сила тока ячейки
	uint16_t tImax;			//Допустимое время максимального тока
	uint16_t Tmax;			//Максимальная рабочая температура
	uint16_t Tmin;			//Мимимальная рабочая температура
} BMSconfig_t;

typedef struct BMSinfo_t { //информация BMS
	uint8_t BMSVersion; //Номер версии bms
	char batString[30]; //Описание батареи
	uint16_t cCount; //Счетчик зарядок
	uint8_t batNum; //Число банок
	uint16_t v[24]; //Напряжение на банках
	uint16_t vAbsMax[24]; //Зарегистрированый максимум на ячейке
	uint16_t vAbsMin[24]; //Зарегистрированый минимум на ячейке
	uint16_t vMin; //Разрешенный минимум на ячейке
	uint16_t vMax; //Разрешенный максимум на ячейке
	uint32_t mAHIN; //Сколько А*ч съела батарея всего
	uint32_t mAHOut; //Сколько А*ч отдала батарея всего
	uint8_t tAbsMax; //Замерянный максимум на ячейке
	uint8_t tAbsMin; //Замерянный минимум на ячейке
	uint16_t maxCap; //Емкость батареи А*ч от vMin до vMax
	uint32_t maxCurrent; //Максимальный потребляемый ток
} BMSinfo_t;

typedef struct BMS_t { //информация BMS
	uint32_t voltage; //Напряжение батареи в милливольтах
	uint32_t capacity; //Остаток заряда в миллиамер часах
	int32_t current; //Ток батареи в миллиамерах
	uint32_t ActiveShunt; //Активные шунты балансировки
} BMS_t;

void BMS_init(void);

#endif /* _BMS_H */
