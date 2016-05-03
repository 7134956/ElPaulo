#include "config.h"
#include "beeper.h"

typedef struct beep_t {
	uint16_t * buf;
	uint8_t pos;
} beep_t;

beep_t beepTask;

#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

void beep_systick_calback(void);

const uint16_t beepOn[] = {10465, 330, 13185, 330, 15680, 330};
const uint16_t beepOff[] = {15680, 330, 13185, 330,10465, 330};
const uint16_t beepBeep[] = {15680, 100};

/*******************************************************************************
 * Настройка бипера
 ******************************************************************************/
void beep_init() {
#ifdef SYSTEM_STM32
	//Структура инициализации порта
	GPIO_InitTypeDef GPIO_InitStructure;

	//Структуры инициализации таймера
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	//Включаем тактирование таймера порта и альтернативной функции
	RCC_APB2PeriphClockCmd(BEEP_RCC_PORT, ENABLE);
	RCC_APB1PeriphClockCmd(BEEP_RCC_TIM, ENABLE);

	//Настрока порта B0 = TIM3 на выход ШИМ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Настройка счетчика
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000)-1;//72 - 1; // предделение счётных импульсов (16-битный регистр)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;// направление счёта вверх
	TIM_TimeBaseStructure.TIM_Period = 65535;// счёт выполнять до значения 65535
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;// предделение счётных отсутствует
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//Запускаем настройку

	//Настройка ШИМ выходов
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;// режим работы ШИМ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;// разрешить выход ШИМ сигналов таймера
	TIM_OCInitStructure.TIM_Pulse = 0;//Ширина импульса
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;// настройка полярности выхода

	//Ввод значений переменной TIM_OCInitStructure в регистры ШИМ канала 3 таймера3
	TIM_OC3Init(BEEP_TIM, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(BEEP_TIM, TIM_OCPreload_Enable);

	//Включение счетчика TIM3
	TIM_Cmd(BEEP_TIM, ENABLE);
	
	/* Выключаем тактирование таймера */
	RCC_APB1PeriphClockCmd(BEEP_RCC_TIM, DISABLE);
#endif
}

/*******************************************************************************
 * Издать писк
 * Вход 1:	Частота(Гц)
 * 			вернуться(1)
 * 			тишина(2)
 * Вход 2:	длительность/
 * 			(на сколько шагов)
 ******************************************************************************/
void beep(uint16_t f, uint16_t t) {
#ifdef SYSTEM_STM32
//		if (!BEEP_TIM->BEEP_CCR) //Если пищалка свободна пускаем звук на нее
//		{
//			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
//			SysTick_task_add(&beep_timer_callback, t*10);
//			BEEP_TIM->BEEP_ARR = 10000 / f;
//			BEEP_TIM->BEEP_CCR = 1000 / f; //Устанавливаем скважность
//		} else //Если зянята откладываем звук
//		{
//			beepTask.buf[beepTask.idxIN].freq = f;
//			beepTask.buf[beepTask.idxIN++].time = t;
//			beepTask.idxIN &= BEEP_BUF_MASK;
//		}
#endif
}

/*******************************************************************************
 * Вызывается по таймеру после отработки писка
 ******************************************************************************/
void beep_timer_callback(void){
#ifdef SYSTEM_STM32
////	if (beepTask.idxIN == beepTask.idxOUT) {//Если звук отработал
////		BEEP_TIM->BEEP_CCR = 0; //Устанавливаем скважность 0
////		SysTick_task_del(&beep_timer_callback); //Удаляемся из планировщика
////		RCC->APB1ENR &= ~ RCC_APB1ENR_TIM3EN;
////	} else {//Запускаем отложенный звук
//		if(beepTask.buf[beepTask.pos].freq == 1)
//			beepTask.pos -= beepTask.buf[pos].time;
//		if(beepTask.buf[beepTask.pos].freq == 2)
//			BEEP_TIM->BEEP_CCR = 0;
//		else
//			BEEP_TIM->BEEP_CCR = 500000 / beepTask.buf[beepTask.pos].freq;//Устанавливаем скважность половина
//		BEEP_TIM->BEEP_ARR = 1000000 / beepTask.buf[beepTask.pos].freq;
//		SysTick_task_add(&beep_timer_callback, beepTask.buf[beepTask.pos++].time);
//		beepTask.idxOUT &= BEEP_BUF_MASK;
//	}
#endif
}

/*******************************************************************************
 * Играть мелодию из массива
 * Вход: Указатель на массив uint16_t melody[частота (Гц)][длительность (мс)]
 ******************************************************************************/
void beepPlay(const uint16_t * melody) {
#ifdef SYSTEM_STM32
//	if(melody)
//		beepTask.buf = melody;
//		SysTick_task_add(&beep_timer_callback, 0);
//	else
//		SysTick_task_del(&beep_timer_callback); //Удаляемся из планировщика
#endif
}

/*******************************************************************************
 * Остановить воспроизведение массива
 ******************************************************************************/
void beepStop(void) {
#ifdef SYSTEM_STM32
	SysTick_task_del(&beep_timer_callback); //Удаляемся из планировщика
#endif
}

