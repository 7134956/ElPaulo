#include "config.h"
#include "job.h"
#include "rtc.h"

jobs_t jobs;

/*******************************************************************************
 * Дать задание или перенести на новое время
 ******************************************************************************/
void job_set(JOB_CALLBACK fp, uint32_t time) {
	uint8_t i, n = 0;
	if (jobs.count < JOB_SLOTS) {
		for (i = 0; jobs.count > i; i++) {
			if (jobs.slots[i].func == fp) {
				n = i;
				jobs.count--;
				break;
			} else {
				n = jobs.count;
			}
		}
		jobs.slots[n].func = fp;
		jobs.slots[n].time = time;
		jobs.count++;
		setAlarm(job_next()); //Установить будильник на следующее задание
	} else
		messageCall(NULL, "Jobs full!", POPUP_ERROR);
}

/*******************************************************************************
 * Удалить задание
 ******************************************************************************/
void job_del(JOB_CALLBACK fp) {
	uint8_t i;
	for (i = 0; i < jobs.count; i++) {
		if (jobs.slots[i].func == fp) {
			jobs.slots[i] = jobs.slots[jobs.count - 1];//В освободившееся место ставим последнюю
			jobs.count--; //Уменьшаем число задач
		}
	}
	setAlarm(job_next()); //Установить будильник на следующее задание
}

/*******************************************************************************
 * Выполнить задания для которых подошло время
 ******************************************************************************/
void job_exe(uint32_t time) {
	uint8_t i;
	if (jobs.count) {
		for (i = 0; i < jobs.count; i++) {
			if (jobs.slots[i].time <= time) {
				jobs.slots[i].func();
				jobs.slots[i] = jobs.slots[jobs.count]; //В освободившееся место ставим последнюю
				jobs.count--; //Уменьшаем число задач
			}
		}
	}
	setAlarm(job_next()); //Установить будильник на следующее задание
}

/*******************************************************************************
 * Узнать время задания
 ******************************************************************************/
uint32_t job_get(JOB_CALLBACK fp) {
	uint8_t i;
	for (i = 0; i < jobs.count; i++) {
		if (jobs.slots[i].func == fp) {
			return jobs.slots[i].time;
		}
	}
	return 0;
}

/*******************************************************************************
 * Узнать время следующего задания
 ******************************************************************************/
uint32_t job_next(void) {
	uint8_t i;
	uint32_t next = 0xFFFFFFFF;
	for (i = 0; i < jobs.count; i++) {
		if (jobs.slots[i].time < next)
			next = jobs.slots[i].time;
	}
	return next;
}
