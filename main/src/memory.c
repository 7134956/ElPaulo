/*
 * memory
 *
 *  Created on: 29 янв. 2016 г.
 *      Author: 7134956
 */
#include "config.h"
#include "memory.h"

/*******************************************************************************
 * Копирование участков памяти
 ******************************************************************************/
void *memcpy(void *dst, const void *src, size_t n) {
	uint16_t len;
	const char *p = src;
	char *q = dst;
	len = n / 4;
	while (len--) {
		*(uint32_t*)q++ = *(uint32_t*)p++;
	}
	while (n-- & 3) {
		*q++ = *p++;
	}
	return dst;
}
