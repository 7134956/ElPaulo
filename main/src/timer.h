#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

typedef uint8_t(*TIMER_CALLBACK)(void);
	
#define SYSTICK_SLOTS 10

void SysTick_task_add(TIMER_CALLBACK, uint32_t);
void SysTick_task_del(TIMER_CALLBACK fp);

void SysTickInit(uint16_t);

#endif /* _TIMER_H_ */
