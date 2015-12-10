#ifndef _POWER_H_
#define _POWER_H_

#include "main.h"

//Глобальный указатель энергорежима
#define POWERMODE_TURBO 0	//Разгон до максимальной частоты
#define POWERMODE_ACTIVE 1	//Режм без отдыха
#define POWERMODE_NORMAL 2 //Нормальный режим работы с отдыхом ядра
#define POWERMODE_SLEEP 3 //Спит на ходу, будят прерывания
#define POWERMODE_OFF 5	//Выключается

//Выбор режима процессора
#define POWER_STOP 1
#define POWER_OFF 2
#define POWER_SLEEP 3
#define POWER_NORMAL 4
#define POWER_MAX 5

#define CLK_72M 1
#define CLK_24M 2
#define CLK_8M 3

void initMCU (uint8_t);
void setPowerMode(uint8_t);
void setPowerState(uint8_t);
void SetSysClock(uint8_t);

#endif /* _POWER_H_ */
