#ifndef _BEEPER_H_
#define _BEEPER_H_
#include "main.h"

#define BEEP_BUF_SIZE 8 //размер буфера звуков.
#define BEEP_BUF_MASK (BEEP_BUF_SIZE-1)

void beep_init(void); //Настройка пищалки
void beep(uint16_t, uint16_t); //Вызов пищалки
uint8_t beep_timer_callback(void); //

#endif /* _BEEPER_H_ */
