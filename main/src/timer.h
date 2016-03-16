#ifndef _TIMER_H_
#define _TIMER_H_

#include "config.h"

typedef void(*TIMER_CALLBACK)(void);
	
#define SYSTICK_SLOTS 10

typedef struct slot_func_t {
	TIMER_CALLBACK func;
	uint32_t period;
	uint32_t counter;
} slot_func_t;

typedef struct systick_t {
	slot_func_t slots[SYSTICK_SLOTS];
	uint8_t taskCount;
} systick_t;

void SysTick_task_add(TIMER_CALLBACK, uint32_t);
uint32_t SysTick_task_check(TIMER_CALLBACK fp);
void SysTick_task_del(TIMER_CALLBACK fp);

void SysTickInit(uint16_t);

#endif /* _TIMER_H_ */
