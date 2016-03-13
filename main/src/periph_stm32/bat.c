#include "bat.h"
#include "main.h"
#include "stm32f10x.h"

extern config_t config;

bat_t bat;

/*******************************************************************************
 * Контроль заряда батареи
 ******************************************************************************/
void bat_measure(void) {

}

/*******************************************************************************
 * Настройка ацп батареи
 ******************************************************************************/
void batInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure; //Структура настройки GPIO
//	EXTI_InitTypeDef EXTI_InitStructure;
	ADC_InitTypeDef ADC_InitStructure; //Структура настройки АЦП
//	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //Включаем порт А
	//Настроим пин напряжения батареи
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//Это свободный вход
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;		// Это ADC1 нога PA1
	GPIO_Init(GPIOA, &GPIO_InitStructure);

//		RCC_ADCCLKConfig(RCC_PCLK2_Div2);//Частота ADC (max 14MHz --> 72/2=9MHz)

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//Включаем тактирование АЦП1

	//Определяем конфигурацию ADC
	//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//Работаем в режиме одноразового преобразования
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //Запуск по событию отключен //Fixme
	//ADC_InitStructure.ADC_ExternalTrigConv = FIXME по какому событию запускать
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);	//Применить конфигурацию ADC1

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);	//Время выборки АЦП

//Настроим прерывание
	NVIC_EnableIRQ(ADC1_2_IRQn); //Разрешили общие прерывания USART1
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE); //Прерывание по завершению преобразования

	ADC_Cmd(ADC1, ENABLE); //Включаем ADC. Необходимо для калибровки

	//	ADC calibration (optional, but recommended at power on)
	ADC_ResetCalibration(ADC1); // Reset previous calibration
	while (ADC_GetResetCalibrationStatus(ADC1))
		;
	ADC_StartCalibration(ADC1); // Start new calibration (ADC must be off at that time)
	while (ADC_GetCalibrationStatus(ADC1))
		;
}

/*******************************************************************************
 * Прерывание по завершению преобразования АЦП
 ******************************************************************************/
void ADC1_2_IRQHandler(void) {
	if (ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET) { //Если измерение завершено
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC); //Сбрасываем флаг прерывания
		bat.voltage = config.bat_kS * ADC_GetConversionValue(ADC1);
		bat.level = (bat.voltage - 3700) / 3;
		if (bat.level > 100)
			bat.level = 100;
	}
}
		
