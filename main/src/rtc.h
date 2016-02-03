#ifndef _DATETIME_H_
#define _DATETIME_H_

#ifdef SYSTEM_WIN
#include <time.h>
#endif

#include "config.h"

typedef struct tm tm_t;
//struct tm
//{
//	int	tm_sec;		/* Seconds: 0-59 (K&R says 0-61?) */
//	int	tm_min;		/* Minutes: 0-59 */
//	int	tm_hour;	/* Hours since midnight: 0-23 */
//	int	tm_mday;	/* Day of the month: 1-31 */
//	int	tm_mon;		/* Months *since* january: 0-11 */
//	int	tm_year;	/* Years since 1900 */
//	int	tm_wday;	/* Days since Sunday (0-6) */
//	int	tm_yday;	/* Days since Jan. 1: 0-365 */
//	int	tm_isdst;	/* +1 Daylight Savings Time, 0 No DST, * -1 don't know */
//};

#ifdef SYSTEM_STM32
typedef struct tm {
	uint8_t tm_sec;		/* Секунды: 0-59 */
	uint8_t tm_min; 	/* Минуты: 0-59 */
	uint8_t tm_hour; 	/* Часы: 0-23 */
	uint8_t tm_mday;	/* День месяца: 1-31 */
	uint8_t tm_mon;		/* Месяц 0-11 */
	uint8_t tm_year;	/* Год - 1900*/
	uint8_t tm_wday;	/* День недели с понедельника 1-7 */
}tm_t;
#endif

#ifdef SYSTEM_WIN
void RTC_IRQHandler(void);
uint32_t RTC_GetCounter(void);
#endif

void NVIC_GenerateSystemReset(void);
void CounterToFtime(uint32_t, tm_t *);
tm_t * timeGetSet(tm_t *);
void RTC_init(void);
uint8_t lastdayofmonth(uint16_t, uint8_t);
uint8_t weekDay(uint8_t, uint8_t, uint16_t);

#endif /* _DATETIME_H_ */
