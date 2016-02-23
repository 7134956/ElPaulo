#ifndef _POWER_H_
#define _POWER_H_

typedef struct power_t { //Глобальная структура с настройкой энергопотребления
	uint8_t freqMCU_prev;
	uint8_t freqMCU;
	uint8_t sleepMode_prev;
	uint8_t sleepMode;
	uint16_t countToSleep; //Отсчет времени ко сну
	uint16_t CloclLockTime; //Сколько секунд удерживать частоту
} power_t;

//Выбор режима сна процессора
#define POWERMODE_ACTIVE 0	//Не спать
#define POWERMODE_SLEEP 1	//Остановка только ядра до события
#define POWERMODE_STOP 2	//Остановка всего до внешнего прерывания или будильника.
#define POWERMODE_OFF 3		//Полное выключение

//Выбор частоты процессора
#define CLK_NULL 0	//Не была установлена частота
#define CLK_72M 1		//Максимальная
#define CLK_24M 2		//Средняя
#define CLK_8M 3		//Низкая

void SetClock(void);
void powerService(void); //Обслуживание системы после рабочего цыкла

#endif /* _POWER_H_ */
