#include "dbg.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

//int sendchar (int ch)  {          
//  if (DEMCR0 & TRCENA) {
//    while (ITM_Port32(0) == 0);
//    ITM_Port8(0) = ch;
//  }
//  return(ch);
//} 

//void DBG_print(char * c){
//	while((uint8_t)*c) {
//		sendchar(*c++);
//	}
//}
