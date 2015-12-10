#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include "main.h"

#define BUTTON_VERIF_COUNT 3 //Число циклов для подтверждения нажатия
#define BUTTON_REPEAT_DELAY 50 //Число циклов перед автоповтором нажатия
#define BUTTON_REPEAT_FREQ 10 //Число циклов между автоповторами
//#define CIRCLE_SENSOR_DELAY 2 //Задержка перед повторным срабатыванием датчика колеса
#define BUTTON_NULL 0 //Состояния нажатий клавиатуры
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_RIGHT 3
#define BUTTON_LEFT 4
#define BUTTON_LOCK 5

//Режимы настройки кнопок
#define MODE_INT 1
#define MODE_ADC 2

void ButtonsInit(uint8_t );
uint8_t readButtons(void);
void CircleSensorInit(void);
void CircleTimerInit(void);
void WakeupInit(void);

#endif /* _BUTTONS_H_ */
