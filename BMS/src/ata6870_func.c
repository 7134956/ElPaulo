/******************************************************************************
 Includes
******************************************************************************/
#include "ATA6870_func.h"
#include "stm32f10x_spi.h"
#include "stm32f10x.h"

/******************************************************************************
 Global variables.
******************************************************************************/
extern uint8_t ActiveCells[2];

extern uint32_t VBAT[2][6];
extern uint16_t Acquisition[2][6];
extern uint16_t Offset[2][6];

extern uint8_t ActiveTemp;
extern uint16_t Tacquisition[4];
extern int8_t Temp[4];

extern const uint16_t ADC_Lookup[];

extern uint8_t operation; 

// ----------------------------------------------------------------------------
// ################  SPI Funktions  #################
// ----------------------------------------------------------------------------

/*! \brief SPI_COM()
 *	
 *   Returns Miso Byte
 *
 *	\note	nothing
 *
 *	\param ucData 	- MOSI Byte
 *
 *  \retval MISO Byte
 */

unsigned char SPI_COM(unsigned char ucData){
	while (!(SPI1->SR & SPI_SR_TXE));
	SPI1->DR = ucData;
	while (!(SPI1->SR & SPI_SR_RXNE));
	return SPI1->DR;
}


/*! \brief ATA6870_SPI_COM()
 *	
 *   Sends complete commands to the ATA6870
 *
 *	\note	nothing
 *
 *	\param ucAdr2      			- Adress of �C (required)
 *  \param ucCommandCode1       - SPI Command Part 1
 *	\param ucCommandCode2		- SPI Command Part 2
 *
 *  \retval nothing
 */
void ATA6870_SPI_COM(uint8_t ucAdr2, uint8_t ucCommandCode1, uint8_t ucCommandCode2){
  
	unsigned char ucAdr1	= 0x00; // Only two Chips adressed
  	unsigned int j=0;	

  	switch(ucAdr2){
  		case 0x01:	  // IC1 Adressed
  		case 0x02:	  // IC2 Adressed
  		case 0x03:	  // Both IC Adressed
  		default: break;
  	}

  

  	// SPI_Enable
  	//CLEARBIT(NSS_PORTx, NSS);
		CS_ON();

  	// *********************************************
  	SPI_COM(ucAdr1);  	// SPI Command: Adr1
  	SPI_COM(ucAdr2);	// SPI Command: Adr2
  	// *********************************************

  	SPI_COM(ucCommandCode1);   // SPI Command: CODE2

	switch(operation){   
		case 0x01:		// Offset acq
  			
			while(j<6){
  				Offset[(ucAdr2-1)][j]    =	SPI_COM(0x00);
				Offset[(ucAdr2-1)][j]    <<= 8;
				Offset[(ucAdr2-1)][j++]  |=  SPI_COM(0x00);
			}
			operation=0x00;
			break;

		case 0x03:		// Voltage acq
  			while(j<6){
  				Acquisition[(ucAdr2-1)][j]    =	 SPI_COM(0x00);
				Acquisition[(ucAdr2-1)][j]    <<= 8;
				Acquisition[(ucAdr2-1)][j++]  |=  SPI_COM(0x00);
			}
			
			Tacquisition[ActiveTemp]  =		SPI_COM(0x00);	//Temperature acquisition
			Tacquisition[ActiveTemp] <<=	8;
			Tacquisition[ActiveTemp]  |=	SPI_COM(0x00);
		
			operation=0x00;
			break;
		default:
  			SPI_COM(ucCommandCode2);
			break;
  	}

	_delay_ms(10);
	// SPI_Disable;
	//SETBIT(NSS_PORTx, NSS);
	CS_OFF();

}

/*******************************************************************************
*Настройка SPI-шины контроллера и включение ATA6870
 ******************************************************************************/
void SPI_MasterInit(void){
	/* configure pins used by SPI1
   * 250kHz //FIXME in code
	* PA4 = PD_N Включение верхнего ATA6870
	 * PA5 = SCK
	 * PA6 = MISO
	 * PA7 = MOSI
	 * CPOL = 1
	 * CPHA = 1
	 */
	GPIO_InitTypeDef SPI_Pin_Init; //Настройка пинов SPI1.
	GPIO_InitTypeDef SPI_Pin_CS_Init; //CS.
	SPI_InitTypeDef SPI1_Init; //Настройка SPI1.

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //Вкл. тактирование порта с пинами SPI1.
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); //Вкл. тактирования SPI1.
	
	SPI_Pin_Init.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	SPI_Pin_Init.GPIO_Mode = GPIO_Mode_AF_PP; //Настраиваем PD_N, SPI1_SCK, SPI1_MOSI и SPI1_MOSI
	SPI_Pin_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &SPI_Pin_Init);
	
	//Настройка пина CS.
	SPI_Pin_CS_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	SPI_Pin_CS_Init.GPIO_Pin = GPIO_Pin_4;
	SPI_Pin_CS_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &SPI_Pin_CS_Init);

	CS_OFF(); //CS=1.

	SPI1_Init.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //Вход и выход.
	SPI1_Init.SPI_Mode = SPI_Mode_Master; //Мастер.
	SPI1_Init.SPI_DataSize = SPI_DataSize_8b; //Можно и 16!
	SPI1_Init.SPI_CPHA = SPI_CPHA_2Edge; //Со 2-го фронта.
	SPI1_Init.SPI_CPOL = SPI_CPOL_High; //В режиме ожидания SCK - 1.
	SPI1_Init.SPI_NSS = SPI_NSS_Soft; //Програмный NSS (в железе отключено).
	SPI1_Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; //Скорость.
	SPI1_Init.SPI_FirstBit = SPI_FirstBit_MSB; //Со старшего бита.
	SPI1_Init.SPI_CRCPolynomial = 7; //Фигня какая-то.

	SPI_Init(SPI1, &SPI1_Init);
	
	//SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE); //Включаем прерывание

	SPI_Cmd(SPI1, ENABLE); //Запуск SPI1.
	
	// ATA6870 Enable
	PD_N_ON();//Activate ATA6870
	
	// Поскольку сигнал NSS контролируется программно, установим его в единицу
	// Если сбросить его в ноль, то наш SPI модуль подумает, что
	// у нас мультимастерная топология и его лишили полномочий мастера.
	//SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);

}

// ----------------------------------------------------------------------------
// ################  Voltage Funktions  #################
// ----------------------------------------------------------------------------
/*! \brief CalculateV()
 *	
 *   Calculates the voltage of all Cells
 *
 *	\note	nothing
 *
 *	\param chipID	-	Indicates which chip should be calculated
 *
 *  \retval nothing
 */
void CalculateV(uint8_t chipID){
	
	uint8_t i=0;
	uint32_t var2, var3;

	  		for (i=0;i<6;i++){
				var2 = Acquisition[(chipID-1)][i];//casting data from adc
	  			var3 = Offset[(chipID-1)][i];
	  			VBAT[(chipID-1)][5-i] = (40000*(var2-var3))/(3031-var3);//calculate Vbat
			}
}
/*! \brief Undervoltage
 *	
 *   Detection of Undervoltage
 *
 *	\note	nothing
 *
 *	\param limit	- Undervoltage detection level*10000!
 *	\param ChipID	- Selects which chip should be used
 *
 *  \retval Undervoltage - Indicates which Cells of the chosen chip are below the limit
 */
unsigned char Undervoltage(uint16_t limit, uint8_t chipID){

	uint8_t Undervoltage = 0x00;	//Bit 0-5 for Cell 1-6
	uint8_t i=0;
	
	for(i=0;i<6;i++){
		if(VBAT[(chipID-1)][i]<limit)
			Undervoltage += (ActiveCells[chipID-1]&(1<<i));
	}

	if (Undervoltage&0x01){ // first cell is detected
	//Possible to program a warning, other protections or start charging		 
 	}
	if (Undervoltage&0x02){ // second cell is detected
	} 
	if (Undervoltage&0x04){ // third cell is detected
	}
	if (Undervoltage&0x08){ // fourth cell is detected
	} 
	if (Undervoltage&0x10){ // fifth cell is detected
	}
	if (Undervoltage&0x20){ // sixth cell is detected
	}
	
	return Undervoltage;
}
/*! \brief Overvoltage
 *	
 *   Detection of Overvoltage
 *
 *	\note	nothing
 *
 *	\param limit	- Overvoltage detection level*10000!
 *	\param ChipID	- Selects which chip should be used
 *
 *  \retval Undervoltage - Indicates which Cells of the chosen chip are above the limit
 */
unsigned char Overvoltage(uint16_t limit, uint8_t chipID){

	uint8_t Overvoltage = 0x00;	//Bit 0-5 for Cell 1-6
	uint8_t i=0;
		
	for(i=0;i<6;i++){
		if(VBAT[(chipID-1)][i]>limit)
			Overvoltage += (ActiveCells[chipID-1]&(1<<i));
	}
	
	if (Overvoltage&0x01){ // first cell is detected
	//Possible to program a warning, other protections or start discharging		 
 	}
	if (Overvoltage&0x02){ // second cell is detected
	} 
	if (Overvoltage&0x04){ // third cell is detected
	}
	if (Overvoltage&0x08){ // fourth cell is detected
	} 
	if (Overvoltage&0x10){ // fifth cell is detected
	}
	if (Overvoltage&0x20){ // sixth cell is detected
	}
	
	return Overvoltage;
}
/*! \brief Discharge
 *	
 *   Discharges selected Cells
 *
 *	\note	nothing
 *
 *	\param Cells	- Bits 1-2 selects chip, Bits 2-7 Cells 1-6
 *
 *  \retval nothing
 */
void Discharge(uint8_t Cells){

	ATA6870_SPI_COM((Cells&0x03),0x13,(Cells&0xFC)>>2);
	//TOGGLEBIT(LED_PORTx,LED3);

}
/*! \brief OpenCellcheck
 *	
 *   Checks for open Clamps
 *
 *	\note	nothing
 *
 *	\param nothing
 *
 *  \retval 0x01 if Open Cell found
 */
unsigned char OpenCellcheck(){
	uint8_t i=0,j=0;
	uint32_t VBAT2[2][6];

	//----------------------------- Vacq 1---------------------------------------//
	for(i=0;i<2;i++){
		_delay_ms(15);
		ATA6870_SPI_COM(0x01,0x0B,0x02);//wakeup irq surpressed
		_delay_ms(15);
		
		ActiveTemp=0x00;				//Set measured Temperature Channel
		ATA6870_SPI_COM(0x01,0x05,0x03);//Vacq Temp Channel 1
		_delay_ms(15);
		
		ATA6870_SPI_COM(0x01,0x0C,0x00);//Read Status Reg
		_delay_ms(15);
		
		operation=0x03;
		ATA6870_SPI_COM(0x01,0xFE,0x00);//Burstread

		_delay_ms(15);
		//------------------------------ Offset acq 1---------------------------------//	
		
		
		ATA6870_SPI_COM(0x01,0x05,0x01);//Offset
		_delay_ms(15);
		
		ATA6870_SPI_COM(0x01,0x0C,0x00);//Read Status Reg
		_delay_ms(15);
		
		operation=0x01;
		ATA6870_SPI_COM(0x01,0xFE,0x00);//Burstread
		_delay_ms(15);
		
		CalculateV(0x01);
		
		
		if(!i){
			for(j=0;j<6;j++){
				VBAT2[0][j]=VBAT[0][j];
			}
		}
		//--------------------------------- Vacq 2--------------------------------------//
		ATA6870_SPI_COM(0x02,0x0B,0x02);//wakeup irq surpressed
		_delay_ms(15);
		
		ATA6870_SPI_COM(0x02,0x05,0x03);//Vacq Temp Channel 1
		_delay_ms(15);
		
		ATA6870_SPI_COM(0x02,0x0C,0x00);//Read Status Reg
		_delay_ms(15);
		
		operation=0x03;
		ATA6870_SPI_COM(0x02,0xFE,0x00);//Burstread
		_delay_ms(15);
		
		//------------------------------ Offset acq 2----------------------------------//	
	
		
		ATA6870_SPI_COM(0x02,0x05,0x01);//Offset
		_delay_ms(15);
		
		ATA6870_SPI_COM(0x02,0x0C,0x00);//Read Status Reg
		_delay_ms(15);
		
		operation=0x01;
		ATA6870_SPI_COM(0x02,0xFE,0x00);//Burstread
		_delay_ms(15);
		
		//------------------------------------ Check 2----------------------------------//
		
		CalculateV(0x02);
		if(!i){
			for(j=0;j<6;j++){
				VBAT2[1][j]=VBAT[1][j];
			}
		}
		Discharge(0xFE);
		Discharge(0xFD);
	}
	_delay_ms(50);
	Discharge(0x01);	// Switches discharge off for all Cells
	Discharge(0x02);
	for(i=0;i<2;i++){
		for(j=0;j<6;j++){
			if(VBAT[i][j]>VBAT2[i][j]){
				if((VBAT[i][j]-VBAT2[i][j])>1000){
					return 0x01;
				}
			}
			else{
				if((VBAT2[i][j]-VBAT[i][j])>1000){
					return 0x01;
				}
			}

		}
	}
	return 0x00;
}

// ----------------------------------------------------------------------------
// ################  Additional Funktions  #################
// ----------------------------------------------------------------------------

/*! \brief Configure_Fet
 *	
 *   Enables/Disables the Fets
 *
 *	\note	nothing
 *
 *	\param Fet	- Bit 0 controls Fet 1(OD), Bit 1 controls Fet2(OC)
 *
 *  \retval nothing
 */
void Configure_Fet(uint8_t Fet){

//	if(Fet&0x01)
//		SETBIT(FCSR, (1<<DFE));
//	else
//		CLEARBIT(FCSR,(1<<DFE));

//	if(Fet&0x02)
//		SETBIT(FCSR,(1<<CFE));
//	else
//		CLEARBIT(FCSR,(1<<CFE));
}
/*! \brief ReadNTC
 *	
 *   Converts the measured ADC values to Temperatures
 *
 *	\note	nothing
 *
 *	\param nothing
 *
 *  \retval nothing
 */
void ReadNTC(){
	uint8_t i=0;

//	while(i<(T_TLE-T_TLS)&&Tacquisition[ActiveTemp]<pgm_read_word(&ADC_Lookup[i])){
//		i++;
//	}
	
	Temp[ActiveTemp]=(i*T_TLSZ)+T_TLS;
	
}
/*! \brief RCCInit
 *	
 *   Initializes the Coulombcounter functions
 *
 *	\note	Check the Appnote regarding timing!
 *
 *	\param nothing
 *
 *  \retval nothing
 */
void CCInit(){
	
//	CADRCC = RCC_CADRCC;						// Charge Threshold
//	while(CADCSRA & (1 << CADUB));				// Wait values to be written
//	
//	CADRDC = RDC_CADRDC;						// Discharge Threshold
//	while(CADCSRA & (1 << CADUB));				// Wait values to be written
//	
//	SETBIT(CADCSRB,1<<CADRCIE);					// Interrupt Enable
//	while(CADCSRA & (1 << CADUB));				// Wait values to be written
//	
//	SETBIT(CADCSRC,RCC_DIVIDEDSZ<<CADVSE);		// Voltage Scaling
//	while(CADCSRA & (1 << CADUB));				// Wait values to be written
//	
//	SETBIT(CADCSRA,((1<<CADEN)|(1<<CADSE)|(RCC_CONVERSIONPERIOD<<1)));// ADC Enable, RCC Mode, Sampling Interval
//	while(CADCSRA & (1 << CADUB));				// Wait values to be written
//	
}
/*! \brief TimerInit
 *	
 *   Initializes the Timer prescaler
 *
 *	\note nothing
 *
 *	\param nothing
 *
 *  \retval nothing
 */
/*******************************************************************************
 *set TIM1 to run at DELAY_TIM_FREQUENCY
 ******************************************************************************/
void TimerInit(uint32_t freq){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable timer clock  - use TIMER5 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	SystemCoreClockUpdate ();
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / freq) - 1;
	TIM_TimeBaseStructure.TIM_Period = UINT16_MAX;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Enable counter */
	TIM_Cmd(TIM1, ENABLE);
}

/*******************************************************************************
 *set TIM2 to gen CLK
 ******************************************************************************/
void CLK_init(uint32_t freq)
{
	//Настройка пинa CLK
	GPIO_InitTypeDef CLK_Pin_Init;
	//Настройка таймера
	TIM_TimeBaseInitTypeDef TIM_CLK_init;
	// Конфигурация выхода таймера
  TIM_OCInitTypeDef TIM_OCConfig;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //Вкл. тактирование порта с пинами SPI1.
		
	CLK_Pin_Init.GPIO_Pin = GPIO_Pin_6;
	CLK_Pin_Init.GPIO_Mode = GPIO_Mode_AF_PP;
	CLK_Pin_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &CLK_Pin_Init);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
		/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_CLK_init);
	SystemCoreClockUpdate ();
	TIM_CLK_init.TIM_Prescaler = (SystemCoreClock / (freq / 1000)) - 1;
	TIM_CLK_init.TIM_Period = 1000;
	TIM_CLK_init.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_CLK_init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_CLK_init);
	
  // Конфигурируем выход таймера, режим - PWM1
  TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
  // Собственно - выход включен
  TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
  // Пульс длинной 75 тактов => 75/150 = 50%
  TIM_OCConfig.TIM_Pulse = 500;
  // Полярность => пульс - это единица (+3.3V)
  TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// Инициализируем первый выход таймера №3 (у HD это PA6)
  TIM_OC1Init(TIM3, &TIM_OCConfig);

	// Как я понял - автоматическая перезарядка таймера, если неправ - поправте.
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	/* Enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

/******************************************************************************
 *Настройка прерываний
 *****************************************************************************/
void IRQ_init(void){
	GPIO_InitTypeDef GPIO_InitStructure; //Структура настройки GPIO
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //Это свободный вход
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;// Это PA0
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);// выбор порта на котором хотим получить внешнее прерывание
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;// выбираем линию порта
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// настраиваем на внешнее прерывание
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		//далее идут настройки приоритета прерываний.
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_EnableIRQ(EXTI0_IRQn);//разрешаем прерывание
}

/******************************************************************************
 *Прерывания
 *****************************************************************************/
void EXTI0_IRQHandler(void) {
	extern uint8_t stateMain;
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) { //Если прерывание пришло от линии 12
		EXTI_ClearITPendingBit(EXTI_Line0);//Сбросим флаг прерывания
		NVIC_DisableIRQ(EXTI0_IRQn);
	}
}
