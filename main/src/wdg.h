#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

#include "config.h"

//void IWDG_Init(uint8_t, uint16_t);
void WWDG_Init(void);
void WWDG_Renew(void);
	 
#endif /* _WATCHDOG_H_ */
