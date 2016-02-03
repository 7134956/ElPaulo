#include "dbg.h"

void DBG_print(void * p, char c){
		while (ITM_Port32(0) == 0);
		ITM_Port8(0) = c;
}
