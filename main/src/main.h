//#define SYSTEM_WIN

#define DEBUG_DISPLAY
#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef SYSTEM_WIN
#define SYSTEM_STM32
#endif

#ifdef SYSTEM_WIN
#include <stdio.h>
#include <math.h>
#endif

#ifdef SYSTEM_STM32
#define NULL 0
#include "printf.h"
#endif

#define PASSWORD_LENGHT 4

#define ACTION_INC 0
#define ACTION_DEC 1
#define ACTION_IS 2

#define STATE_NULL 0
#define STATE_CALENDAR 2
#define STATE_LIGHT 1
#define STATE_SETUP 4
#define STATE_BAT 7
#define STATE_STAT 8
#define STATE_MAIN 9
#define STATE_TERMO 6
#define STATE_START 20
#define STATE_CLOCK_SETUP 21
#define STATE_SLEEP 24
#define STATE_OFF 23

#define FALSE 0
#define TRUE 1

//Редактирование числа
#define EDIT_NULL 0
#define EDIT_OK 1
#define EDIT_CANSEL 2
#define EDIT_PROCESS 3

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;

//Операции с битами
#define B(bit_no)         (1 << (bit_no))
#define CB(reg, bit_no)   (reg) &=~ B(bit_no)	//снять бит
#define SB(reg, bit_no)   (reg) |= B(bit_no)	//установить бит
#define VB(reg, bit_no)   ( (reg) & B(bit_no) ) //проверить бит
#define TB(reg, bit_no)   (reg) ^= B(bit_no)	//инвертировать бит
//void drawStart(void);
//void draw(void);
//void drawClock(void);
//void drawClockEditor(void);
//void buttonsParse(void);
void circleStep(uint16_t);
uint8_t addTermItem(void);
//void drawMain(void);

typedef struct config_t { //Глобальная структура с настройками сохраняется в EEPROM
	uint8_t lang;		//Выбор языка интерфейса
	uint8_t SecInTime;	//Отрисовывать секунды
	uint16_t SleepSec;	//Спящий режим через
	uint8_t SleepDisplayOff;	//Выключение экрана после автозасыпания
	uint16_t password; //Пароль устройства
	uint8_t contrast; //Контрастность дисплея
	uint8_t PWM[3]; //Контрастность дисплея
	uint32_t crc; //Контрольная сумма массива настроек
} config_t;

//Глобальный флаг текущих задач
#define TASK_DRIVE 1 //Признак движения
#define TASK_REDRAW 2 //Флаг запроса перерисовки экрана
#define TASK_UPDATETIME 4
#define TASK_TIMESETUP 8
#define TASK_SAVEPARAMS 16

typedef struct calendar_t {
	uint16_t year; //Год
	uint8_t month; //Месяц
	uint8_t day; //День
	uint8_t cursor; //Позиция курсора (день)
} calendar_t;

typedef struct count_t { //Глобальная структура для управления состояниями, задачами
	uint16_t toSleep; //Сколько секунд осталось до сна
} count_t;

typedef struct state_t { //Глобальная структура для управления состояниями, задачами
	uint8_t powerMode; //Глобальный флаг энергостостояния
	uint8_t taskList; //Флаги невыполненых задач
	uint8_t button;	//Считанное необработанное нажатие кнопки
} state_t;

typedef struct track_t {
	uint32_t distance; //Последний путь в мм (0 ... 4 294 967 295)
	uint16_t speed; //Текущая скорость в 10м/ч (от 0 до 65535)
	uint16_t startCapacity; //Емкость на старте мАч (от 0 до 65535)
	uint16_t endCapacity; //Остаток емкости мАч (от 0 до 65535)
	uint32_t startTime; //Время начала движения в виде счетчика секунд с ...
	uint16_t circle; //Окружность колеса в мм (от 0 до 65535)
	uint16_t circleTics; //Число тиков за оборот (от 0 до 65535)

	uint16_t peakSpeed; //Пиковая скорость в 10м/ч (от 0 до 65535)
	uint16_t averageSpeed; //Средняя скорость в 10м/ч (от 0 до 65535)
	uint32_t tics; //Время в пути в тиках (0...4 294 967 295). До полутора суток. 131071 секунд или 2184 минут или 36 часов
	uint16_t discharge; //Затраченная емкость в мАч (от 0 до 65535)
	uint32_t toCharging; //Рассчетный оставшийся пробег до зарядки в 10м (от 0 до 4 294 967 295)
	uint64_t odometr; //Общий путь в мм (0 ... 18446744073709551615)
	uint16_t expense; //Расход электроэнергии мА*ч/км (от 0 до 65535)
} track_t;

typedef struct racelist_t {
//	uint8_t items[32]; //Количество элементов в списке заездов для каждого дня в месяце. Нулевой без дела, остальные соответствуют дням
	uint8_t itemsDisplay; //Количество элементов в списке заездов для текущего отображения на дисплее
	uint32_t dayActiv_f; //Флажки ездовых дней в календаре в выбраном месяце. Первый бит указывает что данные есть.
	/*Шесть значений для списка заездов*/
	uint16_t startTime[6]; //Время старта (hh*100+mm)
	uint32_t distance[6]; //Пройденное расстояние в миллиметрах (4294.967295)km
	uint16_t averSpeed[6]; //Средняя скорость (655.35)km/h
	uint16_t adres[6]; //Расположение найденого элемента
} racelist_t;

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
} BMS_t;

#endif /* _MAIN_H_ */
