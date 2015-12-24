#include "termo.h"
#include "stm32f10x.h"

/*******************************************************************************
 *Настройка ADC для термометра
 ******************************************************************************/
void term_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfChannel = 1;
        ADC_Init(ADC1, &ADC_InitStructure);
	
				ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_28Cycles5);
	
				ADC_TempSensorVrefintCmd(ENABLE); //Opening the internal temperature sensor
        ADC_Cmd(ADC1, ENABLE);

        ADC_ResetCalibration(ADC1);
        while(ADC_GetResetCalibrationStatus(ADC1));
        ADC_StartCalibration(ADC1);
        while(ADC_GetCalibrationStatus(ADC1));
        ADC_TempSensorVrefintCmd(ENABLE);

        
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
 //       while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
}

/*******************************************************************************
 *Взять температуру
 ******************************************************************************/
float temp_s(void)
{
	float V;
	float temp;
	uint16_t dt;
        float V25 = 1.41;
        float Avg_Slope = 4.3e-3;
        float Vref = 3.3;

				dt = ADC_GetConversionValue(ADC1);
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        
        V = dt/4096.0*Vref;
        temp = (V25 - V)/Avg_Slope + 25.0;
        return temp;
}
