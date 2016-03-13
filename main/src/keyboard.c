#include "keyboard.h"
#include "config.h"
#include "main.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"

extern state_t state;
#endif

/*******************************************************************************
 *Функция инициализации портов кнопок
 ******************************************************************************/
void keyInit(uint8_t mode) {
#ifdef SYSTEM_STM32
	GPIO_InitTypeDef GPIO_InitStructure; //Структура настройки GPIO
	EXTI_InitTypeDef EXTI_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;//Структура настройки АЦП
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//Включаем порт А

	if(mode == MODE_ADC) {
		//Настроим пин джойстика АЦП
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//Это свободный вход
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;// Это ADC2 нога PA0
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		RCC_ADCCLKConfig(RCC_PCLK2_Div2);//Частота ADC (max 14MHz --> 72/2=9MHz)

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);//Включаем тактирование АЦП

		//Определяем конфигурацию ADC
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//Работаем в режиме одноразового преобразования
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;

		ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5);//Время выборки АЦП
		ADC_Init(ADC2, &ADC_InitStructure);//Применить конфигурацию ADC2

		ADC_Cmd(ADC2, ENABLE);//Включаем ADC. Необходимо для калибровки

		//	ADC calibration (optional, but recommended at power on)
		ADC_ResetCalibration(ADC2);// Reset previous calibration
		while (ADC_GetResetCalibrationStatus(ADC2));
		ADC_StartCalibration(ADC2);// Start new calibration (ADC must be off at that time)
		while (ADC_GetCalibrationStatus(ADC2));

		// start conversion
		ADC_Cmd(ADC2, ENABLE);//enable ADC2
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);// start conversion (will be endless as we are in continuous mode)

		SysTick_task_add(&readKey, 10); //Заряжаем таймер на чтение кнопок через каждые 10 миллисекунд
	} else if(mode == MODE_INT) {
		SysTick_task_del(&readKey); //Удаляем задачу чтения нажатий

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//Включаем тактирование порта A и альтернативной функции

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
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_EnableIRQ(EXTI0_IRQn);//разрешаем прерывание
	}
	state.button = BUTTON_LOCK; //Блокируем первое нажатие клавиши
#endif
}

/*******************************************************************************
 *Прерывания от кнопки при выходе из спящего режима
 ******************************************************************************/
#ifdef SYSTEM_STM32
void EXTI0_IRQHandler(void) {
//	extern uint8_t stateMain;
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) { //Если прерывание пришло от линии 0
		EXTI_ClearITPendingBit(EXTI_Line0);//Сбросим флаг прерывания
		EXTI->IMR &= ~EXTI_Line0;//Отключаем линию внешенего прерывания 10
		NVIC_DisableIRQ(EXTI0_IRQn);
		state.taskList |= TASK_USER | TASK_UPDATETIME;
	}
}
#endif
/*******************************************************************************
 *Функция чтения состояния кнопок
 ******************************************************************************/
void readKey(void) {
#ifdef SYSTEM_STM32
	static uint8_t button_count = 0; //Счетчик цыклов чтения
	static uint8_t buttonPushed = BUTTON_NULL; //В данный момент нажато
	static uint8_t buttonPushedPrev = BUTTON_NULL; //Было нажато в прошлом цыкле
	uint16_t adc_res;
	adc_res = ADC_GetConversionValue(ADC2); //Считываем значение АЦП
	ADC_SoftwareStartConvCmd(ADC2, ENABLE); // Запускаем преобразование. Пускай готовится новое значение
#ifdef DEBUG_KEYBOARD
			printf("\r\n%d", adc_res); //Печатаем значение
#endif
//Определяем текущее нажатие
	if (adc_res < 500) {
		buttonPushedPrev = BUTTON_NULL;
		button_count = 0; //Сбрасываем счетчик
		if(state.button == BUTTON_LOCK)
				state.button = BUTTON_NULL; //Разрешаем работу
	} else {
		if ((adc_res > 1500) && (adc_res < 2500)) {
			buttonPushed = BUTTON_UP;
		} else if ((adc_res > 500) && (adc_res < 1500)) {
			buttonPushed = BUTTON_DOWN;
		} else if ((adc_res > 2500) && (adc_res < 3500)) {
			buttonPushed = BUTTON_LEFT;
		} else if (adc_res > 3500) {
			buttonPushed = BUTTON_RIGHT;
		}
		//Если нажатие продолжается увеличиваем счетчик. Иначе обнуляем
		if (buttonPushed == buttonPushedPrev) { //Сравниваем с предыдущим цыклом
			button_count++; //Если совпала прибавляем счетчик
		} else {
			button_count = 0; //и сбрасываем счетчик
			buttonPushedPrev = buttonPushed; // Иначе сохраняем новое значение
		}
		if (button_count == BUTTON_VERIF_COUNT) { //Заданное число раз считалось одно значение
			if(state.button != BUTTON_LOCK)
				state.button = buttonPushed; //Записываем подтвержденное нажатие
		}
		if (button_count == BUTTON_REPEAT_DELAY) {
			state.button = buttonPushed;
			button_count -= BUTTON_REPEAT_FREQ;
		}
	}
#endif
}

/*******************************************************************************
 *Забирает нажатие кнопки
 ******************************************************************************/
#ifdef SYSTEM_WIN
uint8_t getButton(void) {
	int8_t key = BUTTON_NULL;
	key = u8g_sdl_get_key() - 16;
	switch(key){
	case 1: return BUTTON_UP;
	case 2: return BUTTON_DOWN;
	case 3: return BUTTON_RIGHT;
	case 4: return BUTTON_LEFT;
	}
	if (key > 0) {
		printf("Key:  %d\n", key);
		return key;
	}
	return BUTTON_NULL;
}
#endif

/*******************************************************************************
 *Настройка последовательного порта клавиатуры
 ******************************************************************************/
#ifdef SYSTEM_STM32
void USART2Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Enable USART2 clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// Enable GPIOA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	// Configure USART2 Rx (PA3) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 configured as follow:
	 - BaudRate = 18000 baud
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
	USART_InitStructure.USART_BaudRate = 18000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStructure);

	NVIC_EnableIRQ(USART2_IRQn); //Разрешили общие прерывания USART1
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //Прерывание по приходу байта

	//далее идут настройки приоритета прерываний.
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 14;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 14;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2, ENABLE);
}

/*******************************************************************************
 *Обработка прерывания USART2
 ******************************************************************************/
void USART2_IRQHandler(void) {
	uint8_t byte;
	static uint8_t lock = 0; 		//Клавиша еще нажата
	static uint8_t byteCount = 0;	//Счетчик байт в пакете
	static uint8_t comCount = 0;	//Счетчик команд
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) { //Если пришел байт
		SetClock(); //Разогнали микроконтроллер
		state.taskList |= TASK_USER; // Отметим активность пользователя
		byte = USART_ReceiveData(USART2);
		switch (byteCount) {
		case 0:
			if (byte == 0xFF)
				byteCount = 1;
			break;
		case 1:
			if (byte == 0x55)
				byteCount = 2;
			else
				byteCount = 0;
			break;
		case 2:
			if (byte == 0x03)
				byteCount = 3;
			else
				byteCount = 0;
			break;
		case 3:
			if (byte == 0x02)
				byteCount = 4;
			else
				byteCount = 0;
			break;
		case 4:
			if (byte == 0x00)
				byteCount = 5;
			else
				byteCount = 0;
			break;
		case 5:
			if ((!lock || comCount == 5) && !state.button) {
				comCount = 0;
				switch (byte) {
				case 0x02:
					state.button = BUTTON_UP;
					break;
				case 0x04:
					state.button = BUTTON_DOWN;
					break;
				case 0x08:
					state.button = BUTTON_RIGHT;
					break;
				case 0x10:
					state.button = BUTTON_LEFT;
					break;
				}
				if (byte)
					lock = 1;
			} else if (!byte) {
				lock = 0;
			} else
				comCount++;
			byteCount = 6;
			break;
		case 6:
			byteCount = 0;
			break;
		}
	}
}
#endif

