#ifndef _THREAD_H_
#define _THREAD_H_

#include "main.h"
#include "asm.h"

typedef void(*TASK_CALLBACK)(void);

void thread_init(void);
void thread_run(TASK_CALLBACK fp);
void thread_kill(TASK_CALLBACK fp);

#endif /* _THREAD_H_ */
