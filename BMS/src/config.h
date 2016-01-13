/*
Частота процессора и шин пускай 8MHz
CELLS 24
Number of ATA6870N 4
SCK Frequency (kHz) 250
CLK Frequency(kHz) 500
Получение напряжения всех ячеек 11.5ms
Будем считывать напряжение 10 раз в секунду
Балансировочное сопротивление 33 Ом
Ток до 110ма
*/


#ifndef CONFIG_H
#define CONFIG_H

#include "stdint.h"

#define SELLS 24

#define CLK_PORT 
#define CLK_PIN 
#define CHIP_CLK 500000
#define CHIPS 4

#define DELAY_TIM_FREQUENCY 1000 /* = 1KHZ -> timer runs in milliseconds */

//!< Cells IC 1 Bits 0-5 -> Cells 1-6
#define CELLSIC1 0x3F
//!< Cells IC 2	Bits 0-5 -> Cells 1-6
#define CELLSIC2 0x3F
//!< Cells IC 3 Bits 0-5 -> Cells 1-6
#define CELLSIC3 0x3F
//!< Cells IC 4	Bits 0-5 -> Cells 1-6
#define CELLSIC4 0x3F

//!< Temperature reference resistance in Ohm
#define RES_REF1                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF2                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF3                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF4                (3300)

//!< Temperature Lookup Start
#define T_TLS                   (-20)
//!< Temperature Lookup End
#define T_TLE                   (80)
//!< Temperature Lookup Stepsize
#define T_TLSZ                  (1)

//!< Temperature Lower Threshold
#define T_LOWERTRESHOLD         (-20)
//!< Temperature Upper Threshold
#define T_UPPERTHRESHOLD        (+60)

//!< Shunt resistance in mOhm
#define SHUNT_RESISTANCE        (10)
//!< RCC Conversion Period 0x00 - 256ms, 0x01 - 512ms, 0x02 - 1s, 0x03 - 2s
#define RCC_CONVERSIONPERIOD    (0x00)
//!< RCC Divide Stepsize
#define RCC_DIVIDEDSZ           (0)
//!< RCC Charge Threshold in mA
#define RCC_CHARGETHRESHOLD     (50)
//!< RCC Discharge Threshold in mA
#define RDC_DISCHARGETHRESHOLD  (50)

//!< CC-ADC Regular Current Condition voltage step size in V
#define RCC_STEP_SIZE_uV        (26.855)
//!< RCC steps size in mA (with a given \ref SHUNT_RESISTANCE)
#define RCC_STEP_SIZE_mA        (RCC_STEP_SIZE_uV/SHUNT_RESISTANCE)
//!< RCC CADRCC Value
#define RCC_CADRCC (~((int)((float)RCC_CHARGETHRESHOLD/RCC_STEP_SIZE_mA)))+1
//!< RDC CADRDC Value
#define RDC_CADRDC (~((int)((float)RDC_DISCHARGETHRESHOLD/RCC_STEP_SIZE_mA)))+1


//!< F_CPU Value in Hz
#define F_CPU 8000000UL //Should not be changed!(See Applicationnote for further info)

//Sell default params
#define SELL_CAPACITY_REF	15000			//Номинальная емкость ячейки
#define SELL_VOLATEGE_MIN	2000			//Минимальное напряжение ячейки 2.0V
#define SELL_VOLATEGE_MAX	3650			//Максимальное напряжение ячейки 3.65V
#define SELL_CURRENT_NOM	75000			//Номинальный ток разряда 5C (75A)
#define SELL_CURRENT_MAX	100000			//Пиковый ток разряда 10C (150A)
#define SELL_CURRENT_MAX_TIME 10000			//Допустимая продолжительность пикового тока 10 Сек

#define SELL_DISCHARGE_VOLATEGE_END	2500	//Разряжать до напряжения 2.5V
#define SELL_CHARGE_CURRENT_MAX		45000	//Максимальный ток зарядки 3C (45A)
#define SELL_CHARGE_VOLATEGE_END	36000	//Максимальное напряжение зарядки 3.6V
#define SELL_BALANCE_VOLATEGE		3500	//Начало балансировки 3.5V

#define SELL_TEMP_CHARGE_MIN	0000	//Минимальная температуру для зарядки 0℃
#define SELL_TEMP_CHARGE_MAX	4500	//Миаксимальная температуру для зарядки 45℃
#define SELL_TEMP_DISCHARGE_MIN	-2000	//Минимальная температуру работы -20℃
#define SELL_TEMP_DISCHARGE_MAX	6000	//Миаксимальная температуру работы 60℃

config_t config;
BMSinfo_t BMSinfo;
BMS_t BMS;
sell_t sell[24];

typedef struct config_t { //Глобальная структура с настройками сохраняется в EEPROM
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
} config_t;

typedef struct BMSinfo_t {	//информация BMS
	uint8_t BMSVersion;		//Номер версии bms
	char batString[30];		//Описание батареи
	uint16_t cCount;		//Счетчик зарядок
	uint8_t batNum;			//Число банок
	uint16_t v[24];			//Напряжение на банках
	uint16_t vAbsMax[24];	//Зарегистрированый максимум на ячейке
	uint16_t vAbsMin[24];	//Зарегистрированый минимум на ячейке
	uint16_t vMin;			//Разрешенный минимум на ячейке
	uint16_t vMax;			//Разрешенный максимум на ячейке
	uint32_t mAHIN;			//Сколько А*ч съела батарея всего
	uint32_t mAHOut;		//Сколько А*ч отдала батарея всего
	uint8_t tAbsMax;		//Замерянный максимум на ячейке
	uint8_t tAbsMin;		//Замерянный минимум на ячейке
	uint16_t maxCap;		//Емкость батареи А*ч от vMin до vMax
	uint32_t maxCurrent;	//Максимальный потребляемый ток
} BMSinfo_t;

typedef struct BMS_t {	//информация BMS
	uint32_t voltage;	//Напряжение батареи в милливольтах
	uint32_t capacity;	//Остаток заряда в миллиамер часах
	int32_t current;	//Ток батареи в миллиамерах
} BMS_t;

typedef struct sell_t {	//Глобальная структура с настройками сохраняется в EEPROM
	uint16_t vCurr;	//Текущее напряжение на ячейке
	uint16_t rCurr;	//Текущее сопротивление ячейки
	uint16_t vMin;	//Зарегистрированый минимум на ячейке
	uint16_t vMax;	//Зарегистрированый максимум на ячейке
	uint32_t over;	//Потрачено времени на балансировку(разрядку ячейки)
} sell_t;

#endif
