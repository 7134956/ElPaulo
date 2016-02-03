#ifndef _DBG_H_
#define _DBG_H_

#include "config.h"

#define ITM_Port8(n) (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n) (*((volatile unsigned short *)(0xE0000000+4*n)))
#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000+4*n)))
	
void DBG_init(void);
void DBG_print(void *, char);

#endif /* _DBG_ */
