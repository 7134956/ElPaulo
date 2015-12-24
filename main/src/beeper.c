#include "main.h"
#include "timer.h"
#include "beeper.h"
#ifdef SYSTEM_STM32
#include "stm32f10x.h"
#endif

typedef struct beep_buffer_t{
	uint16_t time;
	uint16_t freq;
}beep_buffer_t;

typedef struct beep_t {
	beep_buffer_t buf[BEEP_BUF_SIZE];
	uint8_t idxIN;
	uint8_t idxOUT;
} beep_t;

beep_t beepTask;

uint8_t beep_systick_calback(void);

/*******************************************************************************
 *Настройка бипера
 ******************************************************************************/
void beep_init() {
#ifdef SYSTEM_STM32
	//Структура инициализации порта
	GPIO_InitTypeDef GPIO_InitStructure;

	//Структуры инициализации таймера
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	//Включаем тактирование TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//Включаем тактирование порта B и альтернативной функции
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	//Включаем тактирование порта B
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//Настрока порта B0 = TIM3 на выход ШИМ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
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
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	//Включение счетчика TIM3
	TIM_Cmd(TIM3, ENABLE);
#endif
}

/*******************************************************************************
 *Издать писк
 *Вход: Частота(Гц), длительность(мс)
 ******************************************************************************/
void beep(uint16_t f, uint16_t t) {
#ifdef SYSTEM_STM32
		if (!TIM3->CCR3) //Если пищалка свободна пускаем звук на нее
		{
			SysTick_task_add(&beep_timer_callback, t);
			TIM3->ARR = 1000000 / f;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			TIM3->CCR3 = 100000 / f; //Устанавливаем скважность половина
		} else //Если зянята откладываем звук
		{
			beepTask.buf[beepTask.idxIN].freq = f;
			beepTask.buf[beepTask.idxIN++].time = t;
			beepTask.idxIN &= BEEP_BUF_MASK;
		}
#endif
}

/*******************************************************************************
 *Вызывается по таймеру после отработки писка
 ******************************************************************************/
uint8_t beep_timer_callback(void){
#ifdef SYSTEM_STM32
	if (beepTask.idxIN == beepTask.idxOUT) {//Если звук отработал
		TIM3->CCR3 = 0; //Устанавливаем скважность 0
		return 0;
	} else //Запускаем отложенный звук
	{
		TIM3->ARR = 1000000 / beepTask.buf[beepTask.idxOUT].freq;
		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		TIM3->CCR3 = 500000 / beepTask.buf[beepTask.idxOUT].freq;//Устанавливаем скважность половина

		SysTick_task_add(&beep_timer_callback, beepTask.buf[beepTask.idxOUT++].time);
		beepTask.idxOUT &= BEEP_BUF_MASK;
	}
#endif
	return 1;
}
