#ifndef _PWM_H_
#define _PWM_H_

#include "u8g.h"

#define PWM_MAX 255
#define PWM_COUNT 3

void PWM_init(void);
void PWMSet(uint8_t, uint8_t);
uint8_t PWMGet(uint8_t);

#endif /* _PWM_H_ */
