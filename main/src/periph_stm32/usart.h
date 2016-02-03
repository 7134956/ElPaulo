/*
 * Передача данных через USART запускается после поступления
 * байта в буффер. Работает по прерыванию до опустошения буффера.
 */

#ifndef _USART_H_
#define _USART_H_

void USARTInit(void);
void parseUSART(void);
void putcUSART(void*, char);

#endif /* _USART_H_ */
