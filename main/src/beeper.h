#ifndef _BEEPER_H_
#define _BEEPER_H_

#include "main.h"
#include "config.h"

void beep_init(void); //Настройка пищалки
void beep(uint16_t, uint16_t); //Вызов пищалки
void beep_timer_callback(void); //

#endif /* _BEEPER_H_ */
