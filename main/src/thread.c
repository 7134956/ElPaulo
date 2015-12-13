#include "thread.h"
#include "misc.h"

#define THREAD_RUN 1
#define THREAD_KILL 2

typedef struct thread_t{
	TASK_CALLBACK thread;
	uint8_t command;
}thread_t;

thread_t thread;

///*******************************************************************************
// *Програмное прерывание. Обслуживает потоки.
// ******************************************************************************/
//void PendSV_Handler(void){
//	switch(thread.command){
//		case THREAD_RUN:{
//			asm_thread_run(thread.thread);
//		}break;
//		case THREAD_KILL:{
//			thread_kill(thread.thread);
//		}break;
//	}
//}

/*******************************************************************************
 *Предварительная настройка
 ******************************************************************************/
void thread_init(void){
	NVIC_SetPriority(PendSV_IRQn, 0x3);   /* Lowest level */
}

/*******************************************************************************
 *Добавить поток на выполнение
 ******************************************************************************/
void thread_run(TASK_CALLBACK fp){
	thread.thread = fp;
	thread.command = THREAD_RUN;
	SCB->ICSR = SCB->ICSR | (1<<28); //Set PendSV pending status
}

/*******************************************************************************
 *Удалить поток
 ******************************************************************************/
void thread_kill(TASK_CALLBACK fp){
	thread.thread = fp;
	thread.command = THREAD_KILL;
	SCB->ICSR = SCB->ICSR | (1<<28); //Set PendSV pending status
}
