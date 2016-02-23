#include "config.h"
#include "buttons.h"
#include "power.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"

extern power_t powerControl;
extern track_t track;
extern state_t state;
extern config_t config;
extern uint8_t stateMain;
#endif

/*******************************************************************************
 *Функция инициализации портов кнопок
 ******************************************************************************/
void ButtonsInit(uint8_t mode) {
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
		ADC_InitStructure.ADC_NbrOfChannel = 0;

		ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5);//Время выборки АЦП
		ADC_Init(ADC2, &ADC_InitStructure);//Применить конфигурацию ADC1

		ADC_Cmd(ADC2, ENABLE);//Включаем ADC. Необходимо для калибровки

		//	ADC calibration (optional, but recommended at power on)
		ADC_ResetCalibration(ADC2);// Reset previous calibration
		while (ADC_GetResetCalibrationStatus(ADC2));
		ADC_StartCalibration(ADC2);// Start new calibration (ADC must be off at that time)
		while (ADC_GetCalibrationStatus(ADC2));

		// start conversion
		ADC_Cmd(ADC2, ENABLE);//enable ADC1
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);// start conversion (will be endless as we are in continuous mode)

		// debug information
//	RCC_ClocksTypeDef forTestOnly;
//	RCC_GetClocksFreq(&forTestOnly); //this could be used with debug to check to real speed of ADC clock
		SysTick_task_add(&readButtons, 10); //Заряжаем таймер на чтение кнопок через каждые 10 миллисекунд
	} else if(mode == MODE_INT) {
		SysTick_task_del(&readButtons); //Удаляем задачу чтения нажатий

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
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_EnableIRQ(EXTI0_IRQn);//разрешаем прерывание
	}
#endif
}

/*******************************************************************************
 *Функция чтения состояния кнопок
 ******************************************************************************/
void readButtons(void) {
#ifdef SYSTEM_STM32
	static uint8_t button_count = 0;//Счетчик цыклов чтения
	static uint8_t buttonPushed = BUTTON_NULL;//В данный момент нажато
	static uint8_t buttonPushedPrev = BUTTON_NULL;//Было нажато в прошлом цыкле
	static uint8_t buttonStatePrev = BUTTON_LOCK;//Тут предыдущее считанное подтвержденное нажатие
	uint16_t adc_res;
	adc_res = ADC_GetConversionValue(ADC2); //Считываем значение АЦП
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);// Запускаем преобразование. Пускай готовится новое значение
#ifdef DEBUG_KEYBOARD	
	printf("\r\n%d", adc_res); //Печатаем значение
#endif
	if (buttonStatePrev == BUTTON_LOCK) //Если клавиатура заблокирована (После включения устройства)
	{
		if (adc_res < 500)
		buttonStatePrev = BUTTON_NULL;
	} else { //Определяем текущее нажатие
		if (adc_res < 500) {
			buttonPushed = BUTTON_NULL;
		} else {
			powerControl.freqMCU = CLK_72M;
			SetClock(); //Разогнали микроконтроллер
			if ((adc_res > 1500) && (adc_res < 2500)) {
				buttonPushed = BUTTON_UP;
			} else if ((adc_res > 500) && (adc_res < 1500)) {
				buttonPushed = BUTTON_DOWN;
			} else if ((adc_res > 2500) && (adc_res < 3500)) {
				buttonPushed = BUTTON_LEFT;
			} else if (adc_res > 3500) {
				buttonPushed = BUTTON_RIGHT;
			}
		}
		//Если нажатие продолжается увеличиваем счетчик. Иначе обнуляем
		if (buttonPushed == buttonPushedPrev)//Сравниваем с предыдущим цыклом
		{
			button_count++; //Если совпала прибавляем счетчик
		} else {
			buttonPushedPrev = buttonPushed; // Иначе сохраняем новое значение
			button_count = 0;//и сбрасываем счетчик
		}

		if (button_count >= BUTTON_VERIF_COUNT) //Заданное число раз считалось одно значение
		{
			if (buttonPushed == BUTTON_NULL) {
				buttonStatePrev = buttonPushed;
				button_count = 0; //Обнуляем счетчик циклов считывания
			}
			if (buttonStatePrev == BUTTON_NULL) {
				state.button = buttonPushed; //Записываем подтвержденное нажатие
				buttonStatePrev = state.button;
			}
			if (button_count >= BUTTON_REPEAT_DELAY) {
				state.button = buttonPushed;
				button_count -= BUTTON_REPEAT_FREQ;
			}
		}
	}
}

/*******************************************************************************
 *Инициализация входа от датчика оборотов
 ******************************************************************************/
void CircleSensorInit() {
	GPIO_InitTypeDef GPIO_InitStructure; //Структура настройки GPIO
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//Включаем тактирование порта B и альтернативной функции

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//Это вход с подтяжкой к плюсу
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;// Это PB12
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);// выбор порта на котором хотим получить внешнее прерывание
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;// выбираем линию порта
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// настраиваем на внешнее прерывание
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//Настройка приоритетов прерываний
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_EnableIRQ(EXTI15_10_IRQn);//Разрешаем прерывание
#endif
}

/*******************************************************************************
 *Прерывания от датчика оборота колеса
 ******************************************************************************/
#ifdef SYSTEM_STM32
void EXTI15_10_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line12) != RESET) { //Если прерывание пришло от линии 12
		EXTI_ClearITPendingBit(EXTI_Line12);//Сбросим флаг прерывания
		if(stateMain != STATE_SILENT) { // Если не в рижиме тихого счетчика пробега
			if (!(state.taskList & TASK_DRIVE)) { //Если не стоял флаг движения,
				RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//Включаем тактирование таймера
				TIM4->CNT = 0;//Обнуляем счетчик
				circleStep(0);//Обнулили показания скорости
				state.taskList |= TASK_DRIVE;// Запускаем движение
				state.taskList |= TASK_REDRAW;// Перерисуем экран
			} else {
				track.circleTics = TIM_GetCounter(TIM4); //Считали значение счетчика
				TIM4->CNT = 0;//Обнуляем счетчик
				track.tics += track.circleTics;
				circleStep(track.circleTics);//Вызвали функцию рассчета скорости
				state.taskList |= TASK_LIM_REDRAW;
			}
		}
		track.odometr += track.circle; //Прибавляем к общему счетчику длину колеса
		track.distance += track.circle;//Прибавляем к счетчику пути длину колеса
	}
}

/*******************************************************************************
 * Настройка таймера оборота колеса
 ******************************************************************************/
void CircleTimerInit() {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //Включаем тактирование таймера 4

	//Настроим прерывание от таймера
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	//Настройка таймера
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/32768;	//Для 72Мгц это 2196;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 65536 - 1; //Максимальное значение счетчика переполнится за 2 секунды
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
//	TIM_ARRPreloadConfig(TIM4, ENABLE); //Включаем автоматический перезапуск таймера
//	TIM_SetAutoreload(TIM4, 0); //Задаем значение автоперезапуска таймера

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //Включаем TIM IT
	
	TIM_Cmd(TIM4, ENABLE); //Включаем таймер

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, DISABLE); //Выключаем тактирование таймера 4
}

/*******************************************************************************
 *Обработка прерывания от таймера 4
 ******************************************************************************/
void TIM4_IRQHandler(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Включаем тактирование таймера
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //Сбрасываем бит переполнения
		state.taskList &= ~ TASK_DRIVE; //Снимаем признак движения
		TIM4->CR1 |= TIM_CR1_CEN; //Включаем таймер
		state.taskList |= TASK_REDRAW;	//Перерисовка
	}
			RCC->APB1ENR &= ~ RCC_APB1ENR_TIM4EN; //Выключаем тактирование таймера
}

/*******************************************************************************
 *Прерывания от кнопки при выходе из спящего режима
 ******************************************************************************/
void EXTI0_IRQHandler(void) {
	extern uint8_t stateMain;
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) { //Если прерывание пришло от линии 12
		EXTI_ClearITPendingBit(EXTI_Line0);//Сбросим флаг прерывания
		NVIC_DisableIRQ(EXTI0_IRQn);
		state.taskList |= TASK_USER | TASK_UPDATETIME;
	}
}
#endif

/*******************************************************************************
 *Забирает нажатие кнопки
 ******************************************************************************/
#ifdef SYSTEM_WIN
uint8_t getButton(void) {
	int8_t key = BUTTON_NULL;
	key = u8g_sdl_get_key() - 16;
	if (key > 0) {
		printf("Key:  %d\n", key);
		return key;
	}
	return BUTTON_NULL;
}
#endif
