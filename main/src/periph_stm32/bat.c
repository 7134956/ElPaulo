/* 
 PB7 - B_STDBY
 PB1 - B_CHRG

 */

#include "bat.h"
#include "main.h"
#include "stm32f10x.h"

extern config_t config;

bat_t bat;
extern state_t state;

#define BAT_MEAS_ENABLE() GPIO_ResetBits (GPIOA, GPIO_Pin_8)
#define BAT_MEAS_DISABLE() GPIO_SetBits (GPIOA, GPIO_Pin_8)

/*******************************************************************************
 * Запрос контроля батареи
 ******************************************************************************/
void bat_query(void) {
	state.taskList |= TASK_BAT_MEASURE;
}
/*******************************************************************************
 * Контроль батареи
 ******************************************************************************/
void bat_measure(void) {
	RCC->APB1ENR |= RCC_APB2ENR_ADC1EN;
	BAT_MEAS_ENABLE();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
		bat.state = BAT_FULL;
	else if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		bat.state = BAT_CHARGE;
	else
		bat.state = BAT_DISCHARGE;
	state.taskList &= ~TASK_BAT_MEASURE;
}

/*******************************************************************************
 * Настройка ацп батареи (PA6)
 ******************************************************************************/
void batInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	//Настроим пин напряжения батареи
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//Включаем тактирование АЦП1

	//Определяем конфигурацию ADC
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//Работаем в режиме одноразового преобразования
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //Запуск по событию отключен //Fixme
	//ADC_InitStructure.ADC_ExternalTrigConv = FIXME по какому событию запускать
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);	//Применить конфигурацию ADC1

	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_41Cycles5);

//Настроим прерывание
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); //Прерывание по завершению преобразования

	ADC_Cmd(ADC1, ENABLE); //Включаем ADC. Необходимо для калибровки

	//	ADC calibration (optional, but recommended at power on)
	ADC_ResetCalibration(ADC1); // Reset previous calibration
	while (ADC_GetResetCalibrationStatus(ADC1))
		;
	ADC_StartCalibration(ADC1); // Start new calibration (ADC must be off at that time)
	while (ADC_GetCalibrationStatus(ADC1))
		;
	bat_query(); //Измеряем напряжение
	SysTick_task_add(&bat_query, 60000);
}

/*******************************************************************************
 * Прерывание по завершению преобразования АЦП
 ******************************************************************************/
void ADC1_2_IRQHandler(void) {
	if (ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET) { //Если измерение завершено
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC); //Сбрасываем флаг прерывания
		bat.value = ADC_GetConversionValue(ADC1);
		RCC->APB1ENR &=~ RCC_APB2ENR_ADC1EN;
		bat.voltage = (config.bat_KS * bat.value) / 1000;
		bat.level = (bat.voltage - 3600) / 5;
		if (bat.level > 100)
			bat.level = 100;
		BAT_MEAS_DISABLE();
		state.taskList |= TASK_REDRAW;
	}
}
