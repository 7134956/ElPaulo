#include "config.h"
#include "buttons.h"
#include "power.h"

#ifdef SYSTEM_STM32
#include "stm32f10x.h"

extern track_t track;
extern config_t config;
extern uint8_t stateMain;
extern state_t state;
#endif

/*******************************************************************************
 *Инициализация входа от датчика оборотов
 ******************************************************************************/
void CircleSensorInit() {
	#ifdef SYSTEM_STM32
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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

	//Настройка таймера
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/32768;	//Для 72Мгц это 2196;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 65536 - 1; //Максимальное значение счетчика переполнится за 2 секунды
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
//	TIM_ARRPreloadConfig(TIM4, ENABLE); //Включаем автоматический перезапуск таймера
//	TIM_SetAutoreload(TIM4, 0); //Задаем значение автоперезапуска таймера

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //Включаем TIM IT

	//Настроим прерывание от таймера
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
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
