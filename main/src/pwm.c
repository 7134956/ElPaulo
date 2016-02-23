#include "config.h"
#include "pwm.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

extern config_t config;
/*******************************************************************************
 *Начальная настройка ШИМ
 ******************************************************************************/
void PWM_init(void) {
#ifdef SYSTEM_STM32
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStructure;
	TIM_OCInitTypeDef TIM_OC_InitStructure;

	//Initialize clocks for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//Initialize clocks for GPIOA, AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//Configure pin TIM2 CH4 = PA3 as alternative function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Configure TIM2 time base
	TIM_TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	TIM_TimeBase_InitStructure.TIM_Period = 256 - 1;
	TIM_TimeBase_InitStructure.TIM_Prescaler = 0;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBase_InitStructure);

	//Configure TIM2 waveform
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC_InitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC_InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;

//	TIM_OC_InitStructure.TIM_Pulse = config.PWM[2];

	TIM_OC4Init(TIM2, &TIM_OC_InitStructure);

	TIM_Cmd(TIM2, ENABLE);
	
	TIM2->CCR2 = 0;
	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
#endif
}

/*******************************************************************************
 *Установка скважности заданного канала ШИМ
 ******************************************************************************/
void PWMSet(uint8_t num, uint8_t value) {
#ifdef SYSTEM_STM32
	if(value)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//	config.PWM[num] = value;
	switch (num) {
	case 0:
		TIM_SetCompare2(TIM2, value);
		break;
	case 1:
		TIM_SetCompare3(TIM2, value);
		break;
	case 2:
		TIM_SetCompare4(TIM2, value);
		break;
	}
	if(!TIM2->CCR2 & !TIM2->CCR3 & !TIM2->CCR4)
		RCC->APB1ENR &=~ RCC_APB1ENR_TIM2EN;
#endif
}

/*******************************************************************************
 *Взятие скважности заданного канала ШИМ
 ******************************************************************************/
uint8_t PWMGet(uint8_t num) {
	return config.PWM[num];
}
