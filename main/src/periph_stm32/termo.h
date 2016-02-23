#ifndef _TERM_H_
#define _TERM_H_

#include "main.h" 
#define BUF_TERMO_SIZE 187 //размер буфера обязательно равен степени двойки!
#define BUF_TERMO_MASK (BUF_TERMO_SIZE-1)

typedef struct termo_t { //Глобальная структура для управления состояниями, задачами
	uint16_t buff[BUF_TERMO_SIZE]; //Буффер со значениями температуры
	uint8_t in; //Номер последней записанной ячейки
	uint8_t count; //Количество измерений в буффере
	uint8_t out; //
	uint16_t max, min; //Максимальная и минимальная температура в буффере
	uint8_t speed; //Сколько раз в секунду измерять температуру
} termo_t;

void term_init(void);
float temp_s(void);

#endif /* _TERM_H_ */
