#include "can.h"
#include "stm32f10x.h"

CanTxMsg TxMessage;
CanRxMsg RxMessage;
/*******************************************************************************
 *Настройка блока CAN
 ******************************************************************************/
void CAN_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	uint16_t baudrate = 125;
	/* CAN GPIOs configuration */

	/* Enable GPIO clockA */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

	/* Configure CAN RX and TX pins */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* CAN configuration */
	/* Enable CAN clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	/* CAN register init */
	CAN_DeInit(CAN1);

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = ENABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;

	/* CAN Baudrate = 125 kBps (CAN clocked at 24 MHz)*/
	switch (baudrate) {
	case 1000:
		CAN_InitStructure.CAN_Prescaler = 3;
		break; //1Mb
	case 500:
		CAN_InitStructure.CAN_Prescaler = 6;
		break; //500 kB
	case 250:
		CAN_InitStructure.CAN_Prescaler = 12;
		break; //250 kB
	case 125:
		CAN_InitStructure.CAN_Prescaler = 24;
		break; //125 kB
	case 100:
		CAN_InitStructure.CAN_Prescaler = 30;
		break; //100 kB
	case 50:
		CAN_InitStructure.CAN_Prescaler = 60;
		break; //50 kB
	case 20:
		CAN_InitStructure.CAN_Prescaler = 150;
		break; //20 kB
	case 10:
		CAN_InitStructure.CAN_Prescaler = 300;
		break; //10 kB
	default:
		CAN_InitStructure.CAN_Prescaler = 24;
		break;
	}

	CAN_Init(CAN1, &CAN_InitStructure);

	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* Transmit Structure preparation */
	TxMessage.StdId = 0x321;
	TxMessage.ExtId = 0x01;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 1;

	/* Enable FIFO 0 message pending Interrupt */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);

	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0xFF;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0xFF;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
 *
 ******************************************************************************/
void CAN1_TX_IRQHandler(void) {
	if (CAN_GetITStatus(CAN1, CAN_IT_TME)) {
		CAN_ClearITPendingBit(CAN1, CAN_IT_TME);
		//do smth
	}
}

/*******************************************************************************
 *
 ******************************************************************************/
void CAN1_RX0_IRQHandler(void) {
	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0)) {			    // message pending ?
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
		//do smth
	}
}
