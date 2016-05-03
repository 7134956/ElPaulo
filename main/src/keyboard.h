#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "config.h"

#define BUTTON_VERIF_COUNT 5 //Число циклов для подтверждения нажатия
#define BUTTON_REPEAT_DELAY 50 //Число циклов перед автоповтором нажатия
#define BUTTON_REPEAT_FREQ 20 //Число циклов между автоповторами
//#define CIRCLE_SENSOR_DELAY 2 //Задержка перед повторным срабатыванием датчика колеса
#define BUTTON_NULL 0 //Состояния нажатий клавиатуры
#define BUTTON_LOCK 1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 3
#define BUTTON_UP 4
#define BUTTON_DOWN 5

//Режимы настройки кнопок
#define MODE_INT 1
#define MODE_ADC 2

void keyInit(uint8_t);
void keyInitVal(void);
void keyAdjust(void);
void readKey(void);
//void USART2Init(void);

#endif /* _KEYBOARD_H_ */
