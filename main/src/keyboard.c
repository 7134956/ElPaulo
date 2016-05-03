#include "keyboard.h"
#include "config.h"
#include "main.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"

extern state_t state;
extern uint8_t stateMain;
#endif

uint16_t keyVal[4]; /* Отсортированные по возрастанию,
значения ADC границ между кнопками 6:4 биты, назначенное действие 3:0 биты */

/*******************************************************************************
 * Инициализация портов кнопок
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

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);//Включаем тактирование АЦП

		//Определяем конфигурацию ADC
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//Работаем в режиме одноразового преобразования
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
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
		SysTick_task_add(&readKey, 10);//Заряжаем таймер на чтение кнопок через каждые 10 миллисекунд
	} else if(mode == MODE_INT) {
		SysTick_task_del(&readKey); //Удаляем задачу чтения нажатий

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//Включаем тактирование порта A и альтернативной функции

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//Это свободный вход
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
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	}
	state.button = BUTTON_LOCK; //Блокируем первое нажатие клавиши
#endif
}

/*******************************************************************************
 * Загрузить значения кнопок
 ******************************************************************************/
void keyInitVal(void) {
#ifdef SYSTEM_STM32
	uint8_t i;

	for (i = 0; i < 4; i++) {
		keyVal[i] = BKP_ReadBackupRegister(BKP_DR3 + i * 4);
		if (!keyVal[i]) {
			stateMain = STATE_CALIB;
			keyAdjust();
			break;
		}
	}
#endif
}

/*******************************************************************************
 * Прерывания от кнопки при выходе из спящего режима
 ******************************************************************************/
#ifdef SYSTEM_STM32
void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) { //Если прерывание пришло от линии 0
		EXTI_ClearITPendingBit(EXTI_Line0);//Сбросим флаг прерывания
		EXTI->IMR &= ~EXTI_Line0;//Отключаем линию внешенего прерывания 10
		NVIC_DisableIRQ(EXTI0_IRQn);
		state.taskList |= TASK_USER | TASK_UPDATETIME;
	}
}
#endif

/*******************************************************************************
 * Процесс калибровки джойстика
 ******************************************************************************/
uint8_t keyReq = 0;
void keyAdjust(void) {
#ifdef SYSTEM_STM32
#define ADC_BUF_SIZE 8
#define ADC_BUF_MASK (ADC_BUF_SIZE-1)
	uint8_t i, j;	//Счетчики циклов
	uint16_t tmp;	//Буфер для перестановки
	static uint8_t count = 0;	//Сколько раз повторилось значение
	static uint8_t stage = 0;	//Этапы обработки
	static uint32_t value;	//Значение АЦП
	static uint16_t valuePrev;	//Предыдущее значение АЦП
	static uint8_t act[4] = { BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT }; //Действия для значений
	static uint16_t refer[5] = { 0, 0, 0, 0, 0 }; //Считанные значения кнопок
	static uint16_t measBuff[ADC_BUF_SIZE]; //Значения последних измерений
	static uint8_t index = 0;

	state.taskList |= TASK_USER; // Не спать пока не откалибруешь
	value = ADC_GetConversionValue(ADC2); //Считываем значение АЦП
	ADC_SoftwareStartConvCmd(ADC2, ENABLE); // Запускаем преобразование. Пускай готовится новое значение
	switch (stage) {
	case 0: { //Ничанаем калибровку
		SysTick_task_del(&readKey);
		SysTick_task_add(&keyAdjust, 10);
		stage = 1;
	}
		break;
	case 1: { //Запоминаем значение кнопки и привязываем к ней действие
		if (keyReq == 4) {
			stage = 3;
			break;
		}
		if (value > 8192) {
			measBuff[index++] = value;
			index &= ADC_BUF_MASK;
			if (value > valuePrev)
				tmp = value - valuePrev;
			else
				tmp = valuePrev - value;
			if (tmp < 500) {
				if (count > 100) {
					count = 0;
					stage = 2;
					value = 0;
					for (i = 0; i < 8; i++) {
						value += measBuff[i];
					}
					refer[++keyReq] = value / 8;
					beep(1000, 100);
					state.taskList |= TASK_REDRAW;
				} else {
					count++;
				}
			}
		} else {
			count = 0;
		}
		valuePrev = value;
	}
		break;
	case 2: { // Ждем отпускания кнопки
		if (value < 8192)
			stage = 1;
	}
		break;
	case 3: { //Сортируем значения АЦП кнопок
		for (i = 1; i < 6 - 1; i++) {
			for (j = 1; j < 6 - i - 1; j++) {
				if (refer[j] > refer[j + 1]) {
					tmp = refer[j];	refer[j] = refer[j + 1];	refer[j + 1] = tmp;
					tmp = act[j - 1];	act[j - 1] = act[j];	act[j] = tmp;
				}
			}
		}
		//Сохраняем в память значение границ между кнопок и привязываем действие
		for (i = 0; i < 4; i++) {
			BKP_WriteBackupRegister(BKP_DR3 + i * 4, (((refer[i] + refer[i + 1]) / 2) & (uint16_t) ~0xF) + act[i]);
		}
		keyInitVal();
		SysTick_task_del(&keyAdjust);
		SysTick_task_add(&readKey, 10); //Заряжаем таймер на чтение кнопок через каждые 10 миллисекунд
		stateMain = STATE_START;
		state.taskList |= TASK_REDRAW;
	}
		break;
	}
#endif
}

/*******************************************************************************
 * Чтение состояния кнопок
 ******************************************************************************/
void readKey(void) {
#ifdef SYSTEM_STM32
	uint8_t i;
	static uint8_t button_count = 0; //Счетчик цыклов чтения
	static uint8_t buttonPushed = BUTTON_NULL;//В данный момент нажато
	static uint8_t buttonPushedPrev = BUTTON_NULL;//Было нажато в прошлом цыкле
	uint16_t adc_res;
	
	adc_res = ADC_GetConversionValue(ADC2);//Считываем значение АЦП
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);// Запускаем преобразование. Пускай готовится новое значение
//  printf("\r\n%d", adc_res); //Печатаем значение
	if (adc_res < keyVal[0]) {
		buttonPushedPrev = BUTTON_NULL;
		button_count = 0;
		if(state.button == BUTTON_LOCK)
		state.button = BUTTON_NULL; //Разрешаем работу
	} else {
		i = 4;
		do {
			i--;
			if(adc_res > keyVal[i]) {//Первые 12 байт значение границы между кнопками
				buttonPushed = keyVal[i] & 0xF;//В последних 4 байтай действие кнопки
				break;
			}
		}while(i);
		//Если нажатие продолжается увеличиваем счетчик. Иначе обнуляем
		if (buttonPushed == buttonPushedPrev) { //Сравниваем с предыдущим цыклом
			button_count++;//Если совпала прибавляем счетчик
		} else {
			buttonPushedPrev = buttonPushed; // Иначе сохраняем новое значение
			button_count = 0;//и сбрасываем счетчик
		}
		if (button_count == BUTTON_VERIF_COUNT) { //Заданное число раз считалось одно значение
			if(state.button != BUTTON_LOCK)
			state.button = buttonPushed;//Записываем подтвержденное нажатие
			state.taskList |= TASK_USER;
		//	powerControl.freqMCU = CLK_24M;
		 // SetClock(); //Разогнали микроконтроллер
		}
		if (button_count == BUTTON_REPEAT_DELAY) {
			state.button = buttonPushed;
			button_count -= BUTTON_REPEAT_FREQ;
		}
	}
#endif
}

/*******************************************************************************
 * Забирает нажатие кнопки
 ******************************************************************************/
#ifdef SYSTEM_WIN
uint8_t getButton(void) {
	int8_t key = BUTTON_NULL;
	
	key = u8g_sdl_get_key() - 16;
	switch (key) {
	case 1:
		return BUTTON_UP;
	case 2:
		return BUTTON_DOWN;
	case 3:
		return BUTTON_RIGHT;
	case 4:
		return BUTTON_LEFT;
	}
	if (key > 0) {
		printf("Key:  %d\n", key);
		return key;
	}
	return BUTTON_NULL;
}
#endif
