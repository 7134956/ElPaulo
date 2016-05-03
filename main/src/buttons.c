#include "config.h"
#include "buttons.h"
#include "power.h"
#include "job.h"

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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

#endif
}

/*******************************************************************************
 * Прерывания от датчика оборота колеса
 ******************************************************************************/
#ifdef SYSTEM_STM32
void EXTI15_10_IRQHandler(void) {
	static uint16_t tics;
	if (EXTI_GetITStatus(EXTI_Line12) != RESET) { //Если прерывание пришло от колеса
		if(stateMain != STATE_SILENT) { // Если не в рижиме тихого счетчика пробега
			if (!(state.taskList & TASK_DRIVE)) { //Если не стоял флаг движения,
				RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//Включаем тактирование таймера
				TIM4->CNT = 0;//Обнуляем счетчик
				state.taskList |= TASK_DRIVE;// Запускаем движение
				state.taskList |= TASK_REDRAW;// Перерисуем экран
			} else {
//				RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//Включаем тактирование таймера на всякий случай
				tics = TIM4->CNT; //Считали значение счетчика
				TIM4->CNT = 0;//Обнуляем счетчик
				track.tics += tics;
				circleStep(tics);//Вызвали функцию рассчета скорости
				track.distance += track.circle;//Прибавляем к счетчику пути длину колеса
				state.taskList |= TASK_LIM_REDRAW;
			}
		}
		track.odometr += track.circle; //Прибавляем к общему счетчику длину колеса
		EXTI_ClearITPendingBit(EXTI_Line12);
	} else if (EXTI_GetITStatus(EXTI_Line10) != RESET) { //Если прерывание пришло от линии 10(UART1)
		EXTI_ClearITPendingBit(EXTI_Line10);//Сбросим флаг прерывания
		EXTI->IMR &= ~EXTI_Line10;//Отключаем линию внешенего прерывания 10
		state.taskList |= TASK_USER | TASK_UPDATETIME;
	}
}

/*******************************************************************************
 * Настройка таймера оборота колеса
 ******************************************************************************/
void CircleTimerInit() {
	uint16_t temp;
	uint8_t timOn = 0;
	static uint8_t TIM4Inited = 0;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	if(RCC->APB1ENR & RCC_APB1ENR_TIM4EN)	//Если таймер работает
		timOn = 1;
	else
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Включаем тактирование таймера 4
	TIM4->DIER &= ~ TIM_IT_Update;	//Выключаем прерывание TIM IT
	if(!TIM4Inited){
		temp = 0;
		TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/32768;	//Для 72Мгц это 2196;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period = 65536 - 1; //Максимальное значение счетчика переполнится за 2 секунды
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
		
		//Настроим прерывание от таймера
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		TIM4->SR = ~ TIM_IT_Update; //Сбрасываем бит обновления таймера
		TIM4->CR1 |= TIM_CR1_CEN; //Включаем таймер
		RCC->APB1ENR &= ~ RCC_APB1ENR_TIM4EN; //Выключаем тактирование таймера 4	
		TIM4Inited = 1;
	}else{
		if(timOn)
			temp = TIM4->CNT;
		else
			temp = 0;
		TIM4->PSC = SystemCoreClock/32768;
		TIM4->EGR = TIM_PSCReloadMode_Immediate;//Немедленно применить новый предделитель
		while(!(TIM4->SR & TIM_IT_Update));	/* Ожидаем обновления таймера */
		TIM4->SR = ~ TIM_IT_Update; //Сбрасываем бит обновления таймера
		TIM4->CNT = temp;
		TIM4->DIER |= TIM_IT_Update;	//Включаем TIM IT
		if(!timOn){
			RCC->APB1ENR &= ~ RCC_APB1ENR_TIM4EN; //Выключаем тактирование таймера 4
		}
	}
}

/*******************************************************************************
 * Обработка прерывания от таймера 4 (Счетчик времени оборота колеса)
 ******************************************************************************/
void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //Сбрасываем бит переполнения
		circleStep(0);//Обнулили показания скорости
		if(track.distance > 100000) //Если проехали больше 100 метров
			job_set(&saveTrack , RTC_GetCounter() + config.saveRace * 60);
		state.taskList |= TASK_REDRAW;	//Перерисовка
		state.taskList &= ~TASK_DRIVE; //Снимаем признак движения
		RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN; //Выключаем тактирование таймера
	}	
}
#endif
