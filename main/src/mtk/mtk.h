#ifndef _MTK_H_
#define _MTK_H_

#define LANG_COUNT 2

#include "u8g.h"
#include "../rtc.h"

#define COMMAND_NULL 0
#define COMMAND_PREV 2
#define COMMAND_NEXT 3
#define COMMAND_UP 4
#define COMMAND_DOWN 5

#define MTK_ACTION_INC 1
#define MTK_ACTION_DEC 2

//#define UNLOCK_CLOSE 0
//#define UNLOCK_OPEN 1
//#define UNLOCK_RETURN 2

/*
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;
*/

typedef struct _mtk_struct_t mtk_t;
typedef struct _mtk_element_t mtk_element_t;
typedef struct _mtk_element_t *mtk_element_p;
typedef struct _mtk_select_t *mtk_select_p;
typedef struct _mtk_select_t mtk_select_t;
typedef struct _mtk_graph_t mtk_graph_t;

//Флаги свойств
#define TYPE_NULL 0			//Нередактируемый элемент
#define TYPE_FUNC 1			//Редактирование параметра через вызов функции
#define TYPE_NEEDOK 2		//Редактирование  параметра с подтверждением
#define TYPE_LOCK 4			//Редактирование без возможности выхода
#define TYPE_CMD_ACCEPT 8	//GFUNC сама обрабатывает команды
#define TYPE_PRIVATE 16		//Защищено паролем
//Флаги состояния
#define EDITING_UNLOCK 32	//Ввод пароля начат
#define EDITING_PROCESS 64 //Редактирование начато(Выделен редактируемый разряд или активирована графическая функция)
#define EDITING_EDITED 128 //Требуется сохранение (число изменено) Выставляется только для TYPE_NEEDOK

//Тип элемента
#define ELEMENT_NULL 0
#define ELEMENT_NUM8 1 //Редактирование 8 битного числа
#define ELEMENT_NUM16 2//Редактирование 16 битного числа
#define ELEMENT_NUM32 3 //Редактирование 32 битного числа
#define ELEMENT_NUM64X1M 8 //Делит на миллион редактирует умножает и сохряняет
#define ELEMENT_FLAG 4 //Изминение бинарного пароаметра
#define ELEMENT_MENU 5 //Элемент меню с подэлементами
#define ELEMENT_DATE 6	//Редактирование дня месяца года в структуре tm
#define ELEMENT_TIME 7 //Редактирование часа минут секунд в структуре tm
#define ELEMENT_SEL 9	//Выбор значения из списка с подписями
#define ELEMENT_GFUNC 10	//Ссылка на графическую функцию

struct _mtk_struct_t {
 	uint8_t pos_x;			//Позиция меню горизонтиальная
	uint8_t pos_y;			//Позиция меню вертикуальная
	uint8_t size_x;			//Размер горизоньальный
	uint8_t size_y;			//Размер вертикальный
	uint8_t step_x;			//Шаг горизонтальный
	uint8_t step_y;			//Шаг вертикальный
	uint8_t glyph_y;		//Размер символа вертикальный
	uint8_t ascent;			//Смешение вверх от базовой линии шрифта
	u8g_t * u8g;			//Ссылка на графическую структуру
	uint8_t command;		//Комманда для меню
	mtk_element_p element;	//Текущий элемент
	uint8_t pos;			//Позиция курсора при редактировании числа
//	uint8_t skip;			//Сколько пунктов меню пропустить не рисуя
	uint8_t count;			//Какой элемент(строку) по счету рисуем/нарисовали
	uint8_t select;			//Какой элемент(строка) по счету выбран
	uint8_t indexHist;		//Указатель на позицию в истории переходов в глубь
	mtk_element_p rootHist[10];	//Массив указателей для возврата по меню
	uint8_t selectHist[10];	//Массив указателей на номера пунктов меню с которых вошли
	uint32_t tempNum;		//Тут редактируем число до сохранения
	tm_t tempTime;			//Тут редактируем время до сохранения
	uint8_t	flags;			//Глобальные флаги для меню
};

struct _mtk_element_t {
	uint8_t type;	//Тип элемента
	char *label;	//Текстовая метка
	void * pointer;	//Указатель то что будем изменять
	uint8_t length;	//Количество значащих знаков в числе или число элементов в селекторе
	uint8_t flags;	//Флаги для свойств и состояний элемента
	void * next;	//Следующий элемент или NULL
};

struct _mtk_select_t {
	char * string[2];	//Массив строк с именами пунктов селектора
	void * pointer;	//Указатель на номер селектора или функцию взятия/установки параметра
};

struct _mtk_graph_t {
	char * title;			//Коментарий к графику
	uint8_t num;		//Число элементов
	uint16_t * mas;		//Массив значений
	uint32_t active;	//Помеченные элементы
};


void mtk_Init(u8g_t *);
void mtk_Draw(void);
uint8_t mtk_Command(uint8_t);
void mtk_Pos(uint8_t, uint8_t);
void mtk_SetRootElement(mtk_element_p);
void mtk_SelectElement(uint8_t);
void mtk_SetupElement(mtk_element_p, uint8_t, char *, uint8_t, uint8_t, void *, mtk_element_p);
void graphBar(mtk_t *, mtk_graph_t *);

void mtk_drawLL(mtk_t *);
void mtk_elementNum(mtk_t *);
void mtk_elementFlag(mtk_t *);
void mtk_elementDateTime(mtk_t *);
void mtk_elementSelect(mtk_t *);
void mtk_elementGfunc(mtk_t *);
void mtk_commandLL(mtk_t *);
void mtk_commandNum(mtk_t *);
void mtk_commandMenu(mtk_t *);
void mtk_commandFlag(mtk_t *);
void mtk_commandDateTime(mtk_t *);
void mtk_commandSelect(mtk_t *);
void mtk_commamdGfunc(mtk_t *);
void mtk_editDateTime(mtk_t *, uint8_t);
void mtk_changeVal(uint8_t *, uint16_t, uint16_t, uint8_t);
void mtk_findStartElement(mtk_t *);
void unlock(mtk_t *);
uint32_t power(uint8_t, uint8_t);

#endif /* _MTK_H_ */
