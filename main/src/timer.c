#include "main.h"
#include "timer.h"
#include "beeper.h"
#include "buttons.h"
#include "printf.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#include "wdg.h"
#endif

typedef struct slot_func_t {
	TIMER_CALLBACK func;
	uint32_t period;
	uint32_t counter;
} slot_func_t;

typedef struct systick_t {
	slot_func_t slots[SYSTICK_SLOTS];
	uint8_t taskCount;
} systick_t;

systick_t systick;

#ifdef SYSTEM_STM32
/*******************************************************************************
 *Настройка системного таймера
 ******************************************************************************/
void SysTickInit(uint16_t x) {
	SystemCoreClockUpdate ();
	SysTick_Config(SystemCoreClock / x); //x-число раз в секунду
}

/*******************************************************************************
 *Добавление задачи
 ******************************************************************************/
void SysTick_task_add(TIMER_CALLBACK fp, uint32_t period) {
	uint8_t i, n = 0;
	if (systick.taskCount < SYSTICK_SLOTS) {
		for (i = 0; systick.taskCount > i; i++) {
			if (systick.slots[i].func == fp) {
				n = i;
				systick.taskCount--;
				break;
			} else {
				n = systick.taskCount;
			}
		}
		systick.slots[n].func = fp;
		systick.slots[n].period = period;
		systick.slots[n].counter = 0;
		systick.taskCount++;
	}
}

/*******************************************************************************
 *Удаление задачи
 ******************************************************************************/
void SysTick_task_del(TIMER_CALLBACK fp) {
	uint8_t i;
	for (i = 0; i < systick.taskCount; i++) {
		if (systick.slots[i].func == fp) {
			systick.taskCount--; //Уменьшаем число задач
			systick.slots[i] = systick.slots[systick.taskCount];//В освободившееся место ставим последнюю
			systick.slots[systick.taskCount].func = NULL;//Стираем указатель на функцию
		}
	}
}

/*******************************************************************************
 *Осталось времени до запуска задачи
 ******************************************************************************/
uint32_t SysTick_task_check(TIMER_CALLBACK fp) {
	uint8_t i;
	for (i = 0; i < systick.taskCount; i++) {
		if (systick.slots[i].func == fp) 
			return systick.slots[i].period - systick.slots[i].counter;
	}
	return 0;
}

/*******************************************************************************
 *Прерывание от таймера(Задаю 100 раз в секунду)
 ******************************************************************************/
void SysTick_Handler(void) {
	uint8_t i;
	if (systick.taskCount)
	for (i = 0; i < systick.taskCount; i++) {
		systick.slots[i].counter += 10;
		if (systick.slots[i].counter >= systick.slots[i].period) {
			systick.slots[i].counter = 0;
			systick.slots[i].func();
		}
	}
	WWDG_Renew();
}
#endif
