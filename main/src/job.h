#ifndef _JOB_H_
#define _JOB_H_

#include "config.h"

#define JOB_SLOTS 10
typedef void(*JOB_CALLBACK)(void);

typedef struct job_func_t {
	JOB_CALLBACK func;
	uint32_t time;
} job_func_t;

typedef struct jobs_t {
	job_func_t slots[JOB_SLOTS];
	uint8_t count;
} jobs_t;

void job_set(JOB_CALLBACK, uint32_t);
uint32_t job_get(JOB_CALLBACK);
void job_del(JOB_CALLBACK);
uint32_t job_next(void);
void job_exe(uint32_t);

#endif /* _JOB_H_ */
