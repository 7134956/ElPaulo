#ifndef _POWER_H_
#define _POWER_H_

//#include "config.h"

#define CLK_72M 1
#define CLK_24M 2
#define CLK_8M 3

//Глобальный указатель энергорежима
#define POWERMODE_NULL 0 			//Режим после запуска
//#define POWERMODE_TURBO 1		//72МГц без отдыха
//#define POWERMODE_SAVE 3	 	// 8МГц
#define POWERMODE_NORMAL 2		//24МГц Спит ядром когда свободен
#define POWERMODE_SLEEP 4 	//Спит на ходу, будят прерывания
#define POWERMODE_OFF 5			//Выключается полностью

void setPowerMode(uint8_t); //Перейти программе в указанный режим работы
void powerService(void); //Обслуживание системы после рабочего цыкла

#endif /* _POWER_H_ */
