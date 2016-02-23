#ifndef _DBG_H_
#define _DBG_H_

#include "config.h"

#define ITM_Port8(n) (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n) (*((volatile unsigned short *)(0xE0000000+4*n)))
#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000+4*n)))
	
#define DEMCR0				(*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000
	
void DBG_init(void);
void DBG_print(char *);

#endif /* _DBG_ */
