/*
 * Передача данных через USART запускается после поступления
 * байта в буффер. Работает по прерыванию до опустошения буффера.
 */

#include "config.h"
#include "stm32f10x.h"
#include "usart.h"
#include "keyboard.h"
//#include "printf.h"

char transBuff[256] = { "\n\n\rElPaulo 0.1!\n\r" };
uint8_t transIN = 18, transOUT = 0; //Куда складывать, откуда передавать
char reciveBuff[256];
uint8_t reciveIN = 0, reciveOUT = 0; //Куда принимать, откуда брать

extern state_t state;

/*******************************************************************************
 *Настройка последовательного порта
 ******************************************************************************/
void USARTInit() {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// Enable GPIOA and GPIOA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	// Configure USART1 Tx (PA9) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure USART1 Rx (PA10) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 - USART Clock disabled
	 - USART CPOL: Clock is active low
	 - USART CPHA: Data is captured on the middle
	 - USART LastBit: The clock pulse of the last data bit is not output to
	 the SCLK pin
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	NVIC_EnableIRQ(USART1_IRQn); //Разрешили общие прерывания USART1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);
}

/*******************************************************************************
 *Обработка прерывания USART1
 ******************************************************************************/
void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_TXE) == SET) { //Если байт передан
		USART_ClearITPendingBit(USART1, USART_IT_TXE); //Сбрасываем флаг прерывания
		if (transIN != transOUT) { //Если счетчик непереданных не пустой
			USART_SendData(USART1, transBuff[transOUT++]); //Отправляем байт в USART//Смещаем позицию неотправленных
		} else { //Если все уже передано
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE); //Отключаем прерывание
		}
	}
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) { //Если пришел байт
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //Сбрасываем флаг прерывания
		reciveBuff[reciveIN++] = USART_ReceiveData(USART1); //Копируем байт в буффер //Смещаем указатель вперед
	}
}

/*******************************************************************************
 *Помещение символа в буффер отправки USART
 ******************************************************************************/
void putcUSART(void* p, char c) {
	transBuff[transIN++] = c;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //Включаем прерывание и дальше работаем по нему
}

/*******************************************************************************
 *Разбор команд из буфера USART
 ******************************************************************************/
void parseUSART(void) {
	if (reciveOUT != reciveIN) {
		if (reciveBuff[reciveOUT] == '8') {
			printf("%s", "\n\rBUTTON_UP");
			state.button = BUTTON_UP;
		} else if (reciveBuff[reciveOUT] == '2') {
			printf("%s", "\n\rBUTTON_DOWN");
			state.button = BUTTON_DOWN;
		} else if (reciveBuff[reciveOUT] == '4') {
			printf("%s", "\n\rBUTTON_LEFT");
			state.button = BUTTON_LEFT;
		} else if (reciveBuff[reciveOUT] == '6') {
			printf("%s", "\n\rBUTTON_RIGHT");
			state.button = BUTTON_RIGHT;
		} else if (reciveBuff[reciveOUT] == 27) {
			reciveOUT++;
			if (reciveBuff[reciveOUT] == 91) {
				reciveOUT++;
				if (reciveBuff[reciveOUT] == 65) {
					printf("%s", "\n\rBUTTON_UP");
					state.button = BUTTON_UP;
				} else if (reciveBuff[reciveOUT] == 66) {
					printf("%s", "\n\rBUTTON_DOWN");
					state.button = BUTTON_DOWN;
				} else if (reciveBuff[reciveOUT] == 68) {
					printf("%s", "\n\rBUTTON_LEFT");
					state.button = BUTTON_LEFT;
				} else if (reciveBuff[reciveOUT] == 67) {
					printf("%s", "\n\rBUTTON_RIGHT");
					state.button = BUTTON_RIGHT;
				}
			}
		} else {
			printf("\n\r%X ", reciveBuff[reciveOUT]);
			printf("%d ", reciveBuff[reciveOUT]);
		}
		reciveOUT++;
	}
}
