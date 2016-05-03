#ifndef _BMS_H
#define _BMS_H

//#include "config.h"

#define BMS_NOTFOUND 0
#define BMS_USE 1
#define BMS_CHARGE 2
#define BMS_FULL 3
#define BMS_AVAILABLE 4

typedef struct BMS_D_conf_t { //Настройки разрядки BMS
	uint16_t DVmin;			//Минимальное напряжение ячейки
	uint16_t DInom;			//Номинальная сила тока ячейки
	uint16_t DImax;			//Максимальная сила тока ячейки
	uint16_t DtImax;		//Допустимое время максимального тока
	uint16_t DTmax;			//Максимальная рабочая температура
	uint16_t DTmin;			//Мимимальная рабочая температура
} BMS_D_conf_t;

typedef struct BMS_C_conf_t { //Настройки зарядки BMS
	uint16_t CVmin;			//Минимальное напряжение ячейки
	uint16_t CVmax;			//Максимальное напряжение ячейки
	uint16_t CInom;			//Номинальная сила тока ячейки
	uint16_t CTmax;			//Максимальная рабочая температура
	uint16_t CTmin;			//Мимимальная рабочая температура
} BMS_C_conf_t;

typedef struct BMS_info_t {	//Информация из BMS
	uint8_t BMSVersion;		//Номер версии bms
	char batString[30];		//Описание батареи
	uint16_t cCount;		//Счетчик зарядок
	uint8_t batNum;			//Число банок
	uint16_t v[24];			//Напряжение на банках
	uint16_t vAbsMax[24];	//Зарегистрированый максимум на ячейке
	uint16_t vAbsMin[24];	//Зарегистрированый минимум на ячейке
	uint32_t mAHIN;			//Сколько А*ч съела батарея всего
	uint32_t mAHOut;		//Сколько А*ч отдала батарея всего
	uint16_t maxCap;		//Емкость батареи А*ч от vMin до vMax
	uint32_t maxCurrent;	//Максимальный потребляемый ток в мА
} BMS_info_t;

typedef struct BMS_C_data_t {	//Данные по зярядке
	uint32_t ActiveShunt;		//Включенные шунты
} BMS_C_data_t;

typedef struct BMS_t {	//Текущие параметры
	uint8_t state; 		//Состояние BMS
	uint32_t voltage;	//Напряжение батареи в милливольтах
	uint32_t capacity;	//Остаток заряда в миллиамер часах
	uint8_t percents;	//Остаток заряда в %
	int32_t current;	//Ток батареи в мА
} BMS_t;

void BMS_init(void);

#endif /* _BMS_H */
