#ifndef _BEEPER_H_
#define _BEEPER_H_

#include "config.h"

void beep_init(void); //Настройка пищалки
void beep(uint16_t, uint16_t); //Вызов пищалки
void beepPlay(const uint16_t *);
void beepStop(void);
void beep_timer_callback(void); //

extern const uint16_t beepOn[];
extern const uint16_t beepOff[];
extern const uint16_t beepBeep[];

#endif /* _BEEPER_H_ */
