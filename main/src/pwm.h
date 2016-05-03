#ifndef _PWM_H_
#define _PWM_H_

#include "config.h"

#define PWM_MAX 512
#define PWM_COUNT 2

void PWM_init(void);
void PWMSet(uint8_t, uint16_t);
uint16_t PWMGet(uint8_t);

#endif /* _PWM_H_ */
