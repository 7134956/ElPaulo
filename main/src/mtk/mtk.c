#include "config.h"
#include "main.h"
#include "mtk.h"
#include "rtc.h"
#include "bitmap.h"

mtk_t mtk;
mtk_element_t mtkUnlock;

extern config_t config;

void mtk_Init(u8g_t * u8g) {

	mtk_SetupElement(&mtkUnlock, ELEMENT_NUM16, NULL, PASSWORD_LENGHT, EDITING_PROCESS, &mtk.tempNum, NULL);
	mtkUnlock.label = 0;

	mtk.pos_x = 0;
	mtk.pos_y = 0;
	mtk.size_x = 0;
	mtk.size_y = 0;
	mtk.u8g = u8g;
	mtk.command = COMMAND_NULL;
	mtk.rootHist[0] = NULL;
	mtk.indexHist = 0;
}

void mtk_Draw(void) {
	mtk_drawLL(&mtk);
}

uint8_t mtk_Command(uint8_t command) {
	mtk.command = command;
	mtk_commandLL(&mtk);
	if (!mtk.select)
		return 0;
	else
		return 1;
}

void mtk_Pos(uint8_t x, uint8_t y) {
	mtk.pos_x = x;
	mtk.pos_y = y;
}

void mtk_Size(uint8_t x, uint8_t y) {
	mtk.size_x = x;
	mtk.size_y = y;
}

void mtk_SetRootElement(mtk_element_p element) {
	mtk.rootHist[0] = element;
	mtk.indexHist = 0;
}

void mtk_SelectElement(uint8_t select) {
	mtk.select = select;
}

/*******************************************************************************
 *Сборка дерева меню подключением элементов
 ******************************************************************************/
void mtk_SetupElement(mtk_element_p element, uint8_t type, char * string, uint8_t lenght, uint8_t flags, void * pointer, mtk_element_p next) {
	element->type = type;
	//element->label[0] = string;
	element->length = lenght;
	element->pointer = pointer;
	element->flags = flags;
	element->next = next;
}

/*******************************************************************************
 *Отрисовка меню и элементов
 ******************************************************************************/
void mtk_drawLL(mtk_t *mtk) {
	char arrow[2] = { 187, 0 };
	volatile uint8_t maxSize = 0, temp = 0;	//Максимальный размер строки меню
	mtk_element_p tempElement_p, temp2Element;
	mtk->step_x = u8g_GetStrWidth(mtk->u8g, "0");
	mtk->step_y = 1 + u8g_GetFontAscent(mtk->u8g);
	mtk->glyph_y = u8g_GetFontAscent(mtk->u8g) - u8g_GetFontDescent(mtk->u8g);
	mtk->ascent = u8g_GetFontAscent(mtk->u8g);
	mtk->count = 0;
	mtk->element = mtk->rootHist[mtk->indexHist];
	tempElement_p = mtk->element;
	while (1) { //Найдем длину самой длинной строки и выставим начало отрисовки по ее размеру
		temp = u8g_GetStrWidth(mtk->u8g, tempElement_p->label);
		if (temp > maxSize)
			maxSize = temp;
		if (tempElement_p->next)
			tempElement_p = tempElement_p->next;
		else
			break;
	}
	maxSize += u8g_GetStrWidth(mtk->u8g, " ");

	while (1) {  //Цикл отрисовки всех пунктов меню
		if (!mtk->element)  //Если нет элемента выходим из цикла
			break;
		if ((mtk->element->type == ELEMENT_GFUNC) && (mtk->element->flags & EDITING_PROCESS)) {
			mtk_elementGfunc(mtk);
			break; //Если графика активна, остальные пункты не рисуем
		} else {			//Иначе рисуем строку
			//Рисуем указатель на выбраную строку если ее элемент не в процессе редактирования
			if ((mtk->select == mtk->count + 1) && !(mtk->element->flags & EDITING_PROCESS))
				u8g_DrawStr(mtk->u8g, 0, mtk->pos_y, arrow);
			//Рисуем саму строку
			u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, mtk->element->label);
			temp = mtk->pos_x;
			mtk->pos_x += maxSize;

			if (mtk->element->flags & TYPE_PRIVATE) {
				if (mtk->element->flags & EDITING_PROCESS) {
					temp2Element = mtk->element;
					mtk->element = &mtkUnlock;
					mtk_elementNum(mtk);
					mtk->element = temp2Element;
				} else{
					u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, "\x0E");
				}
				mtk->pos_x += mtk->step_x;

			} else
			switch (mtk->element->type) {
			case ELEMENT_NUM8:
			case ELEMENT_NUM16:
			case ELEMENT_NUM32:
			case ELEMENT_NUM64X1M: {
				mtk_elementNum(mtk);
			}
				break;
			case ELEMENT_MENU: {
				u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, arrow);
			}
				break;
			case ELEMENT_FLAG: {
				mtk_elementFlag(mtk);
			}
				break;
			case ELEMENT_DATE:
			case ELEMENT_TIME: {
				mtk_elementDateTime(mtk);
			}
				break;
			case ELEMENT_SEL: {
				mtk_elementSelect(mtk);
			}
				break;
			case ELEMENT_GFUNC: {
				mtk_elementGfunc(mtk);
			}
				break;
			}
			if ((mtk->element->flags & TYPE_NEEDOK) && (mtk->element->flags & EDITING_EDITED)) //Если нужно подтверждение
				u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, arrow);
			mtk->pos_x = temp;
			mtk->element = mtk->element->next;
			mtk->count++;
		}
		mtk->pos_y += mtk->step_y;
	}
}

/*******************************************************************************
 *Отрисовка элемента типа NUM
 ******************************************************************************/
void mtk_elementNum(mtk_t *mtk) {
	uint32_t x;
	uint8_t i;
	uint32_t (*fp)(uint32_t *);
	char sTemp[10];
	char sTemp1[8];
	uint8_t type = mtk->element->type; //Тип элемента
	void * pointer = mtk->element->pointer; //Указатель на элемент
	mtk->step_x = u8g_GetStrWidth(mtk->u8g, "0");
	if (mtk->element->flags & EDITING_EDITED) {
		x = mtk->tempNum;
	} else if (mtk->element->flags & TYPE_FUNC) {
		fp = (uint32_t (*)(uint32_t*)) mtk->element->pointer;
		x = (*fp)(NULL);
	} else {
		if (type == ELEMENT_NUM8)
			x = *((uint8_t*) pointer);
		else if (type == ELEMENT_NUM16)
			x = *((uint16_t*) pointer);
		else if (type == ELEMENT_NUM32)
			x = *((uint32_t*) pointer);
		else if (type == ELEMENT_NUM64X1M)
			x = *((uint64_t*) pointer) / 1000000;
	}
	sprintf(sTemp1, "%s%u%c", "%0", mtk->element->length, 'u');
	sprintf(sTemp, sTemp1, x);

	for (i = 0; mtk->element->length > i; i++) {
		if ((i == mtk->pos) && (mtk->element->flags & EDITING_PROCESS)) {
			u8g_DrawBox(mtk->u8g, mtk->pos_x, mtk->pos_y - mtk->ascent, mtk->step_x, mtk->glyph_y); // draw cursor bar
			u8g_SetDefaultBackgroundColor(mtk->u8g);
		} else
			u8g_SetDefaultForegroundColor(mtk->u8g);
		sTemp1[0] = sTemp[i];
		sTemp1[1] = 0;
		u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, sTemp1);
		mtk->pos_x += mtk->step_x; //Нарисовали символ, смещаем позицию
	}
	u8g_SetDefaultForegroundColor(mtk->u8g);
}

/*******************************************************************************
 *Отрисовка элемента типа FLAG
 ******************************************************************************/
void mtk_elementFlag(mtk_t *mtk) {
	uint8_t whide = 2;
	char *sTemp = "\x0F";
	uint8_t flag;
	if (mtk->element->flags & EDITING_EDITED)
		flag = mtk->tempNum;
	else
		flag = *(uint8_t*) mtk->element->pointer;
	if (flag) {
		sTemp = "\x10";
	}
	mtk->step_x = u8g_GetStrWidth(mtk->u8g, sTemp);
	if (mtk->element->flags & EDITING_PROCESS) {
		u8g_DrawBox(mtk->u8g, mtk->pos_x, mtk->pos_y - mtk->ascent, mtk->step_x, mtk->glyph_y); // draw cursor bar
		u8g_SetDefaultBackgroundColor(mtk->u8g);
	} else
		u8g_SetDefaultForegroundColor(mtk->u8g);
	u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, sTemp);

	u8g_SetDefaultForegroundColor(mtk->u8g);

	mtk->pos_x += mtk->step_x * whide;
}

/*******************************************************************************
 *Отрисовка элементов DATE, TIME
 ******************************************************************************/
void mtk_elementDateTime(mtk_t *mtk) {
	char sTemp[20]; //Переменная для строки
	uint8_t i;
	tm_t * tm;
	tm_t* (*p)(tm_t *);

	if (mtk->element->flags & EDITING_EDITED) //Если значение изменено
		tm = &mtk->tempTime; //Ставим указатель на временную структуру
	else //Не в процессе редактирования или редактируется непрерывно
	if (mtk->element->flags & TYPE_FUNC) {
		p = (tm_t* (*)(tm_t *)) mtk->element->pointer;
		tm = (*p)(NULL);
	} else
		tm = mtk->element->pointer;
	mtk->step_x = u8g_GetStrWidth(mtk->u8g, "00");
	for (i = 0; i < 3; i++) {
		if ((mtk->pos == i) && (mtk->element->flags & EDITING_PROCESS)) {
			u8g_DrawBox(mtk->u8g, mtk->pos_x, mtk->pos_y - mtk->ascent, mtk->step_x, mtk->glyph_y); // draw cursor bar
			u8g_SetDefaultBackgroundColor(mtk->u8g);
		} else
			u8g_SetDefaultForegroundColor(mtk->u8g);
		if (mtk->element->type == ELEMENT_DATE) {
			switch (i) {
			case 0:
				sprintf(sTemp, "%02d", tm->tm_mday);
				break;
			case 1:
				sprintf(sTemp, "%02d", tm->tm_mon + 1);
				break;
			case 2:
				sprintf(sTemp, "%02d", tm->tm_year - 100);
				break;
			}
		}
		if (mtk->element->type == ELEMENT_TIME) {
			switch (i) {
			case 0:
				sprintf(sTemp, "%02d", tm->tm_hour);
				break;
			case 1:
				sprintf(sTemp, "%02d", tm->tm_min);
				break;
			case 2:
				sprintf(sTemp, "%02d", tm->tm_sec);
				break;
			}
		}
		u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, sTemp);
		u8g_SetDefaultForegroundColor(mtk->u8g);
		if (i < 2) {
			if (mtk->element->type == ELEMENT_TIME)
				sprintf(sTemp, "%s", ":");
			if (mtk->element->type == ELEMENT_DATE)
				sprintf(sTemp, "%s", "/");
			u8g_DrawStr(mtk->u8g, mtk->pos_x + mtk->step_x, mtk->pos_y, sTemp);
		}
		mtk->pos_x += (mtk->step_x*20)/13;
	}
}

/*******************************************************************************
 *Отрисовка элемента типа SELECT
 ******************************************************************************/
void mtk_elementSelect(mtk_t *mtk) {
	uint8_t (*fp)(uint8_t *);
	char *sTemp;
	uint8_t selectNum;
	mtk_select_p pointer = mtk->element->pointer;
	if (mtk->element->flags & EDITING_EDITED) {
		selectNum = mtk->tempNum;
	} else if (mtk->element->flags & TYPE_FUNC) {
		fp = (uint8_t (*)(uint8_t*))pointer->pointer;
		selectNum = (*fp)(NULL);
	} else {
		selectNum = *(uint8_t *)(pointer->pointer);
	}
	sTemp = pointer->string[selectNum];
	mtk->step_x = u8g_GetStrWidth(mtk->u8g, sTemp);
	if (mtk->element->flags & EDITING_PROCESS) {
		u8g_DrawBox(mtk->u8g, mtk->pos_x, mtk->pos_y - mtk->ascent, mtk->step_x, mtk->glyph_y); // draw cursor bar
		u8g_SetDefaultBackgroundColor(mtk->u8g);
	} else
		u8g_SetDefaultForegroundColor(mtk->u8g);
	u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->pos_y, sTemp);
	u8g_SetDefaultForegroundColor(mtk->u8g);
}

/*******************************************************************************
 *Отрисовка элемента типа GFUNC
 ******************************************************************************/
void mtk_elementGfunc(mtk_t *mtk) {
	if (mtk->element->flags & EDITING_PROCESS) {
		void (*fp)(mtk_t *);
		fp = (void (*)(mtk_t *)) mtk->element->pointer;
		fp(mtk);
	} else
		u8g_DrawStr(mtk->u8g, mtk->pos_x, mtk->step_y * (mtk->count + 2), ":");
}

/*******************************************************************************
 *Обработчик команд
 ******************************************************************************/
void mtk_commandLL(mtk_t *mtk) {
	mtk_element_t *temp;
	uint8_t i;
	mtk->element = mtk->rootHist[mtk->indexHist]; //Взяли первый элемент выбранного меню
	i = mtk->select;
	for (; i > 1; i--)	//Переходим на выбраную строку
		mtk->element = mtk->element->next;
//Разблокировщик залоченных пунктов меню
	if ((mtk->element->flags & TYPE_PRIVATE)
			&& (mtk->element->flags & EDITING_PROCESS)) //Если заблокированый элемент редактируется
			{
		temp = mtk->element;
		mtk->element = &mtkUnlock;
		if ((mtk->command == COMMAND_PREV) && (mtk->pos == 0))
			temp->flags &= ~ EDITING_PROCESS;
		else {
			mtk_commandNum(mtk);
			if (!(mtk->element->flags & EDITING_PROCESS))
				temp->flags &= ~ EDITING_PROCESS;
		}
		mtk->command = 0;
		mtk->element = temp;
		if (config.password == mtk->tempNum)
			mtk->element->flags &= ~(TYPE_PRIVATE | EDITING_PROCESS);
	}
///
	if (!(mtk->element->flags & EDITING_PROCESS) || (mtk->element->type == ELEMENT_MENU)) //Если редактирование пераметра не запущено или текщий элемент MENU
		mtk_commandMenu(mtk); //Обрабатываем команду для меню
	else {
		if ((!mtk->pos) && mtk->command == COMMAND_PREV) { //Если нажали назад но позиция нулевая(курсор на первом разряде)
			if (mtk->element->flags & TYPE_LOCK)
				mtk->pos = mtk->rootHist[mtk->indexHist]->length - 1;
			else
				mtk->element->flags &= ~(EDITING_PROCESS | EDITING_EDITED);
		} else {
			switch (mtk->element->type) {
			case ELEMENT_NUM8:
			case ELEMENT_NUM16:
			case ELEMENT_NUM32:
			case ELEMENT_NUM64X1M: {
				mtk_commandNum(mtk); //Обрабатываем команду для числа
			}
				break;
			case ELEMENT_FLAG: {
				mtk_commandFlag(mtk); //Обрабатываем команду для флага
			}
				break;
			case ELEMENT_DATE:
			case ELEMENT_TIME: {
				mtk_commandDateTime(mtk); //Обрабатываем команду для флага
			}
				break;
			case ELEMENT_SEL: {
				mtk_commandSelect(mtk); //Обрабатываем команду для флага
			}
				break;
			case ELEMENT_GFUNC: {
				mtk_commamdGfunc(mtk); //Обрабатываем команду для функции
			}
				break;
			}
		}
	}
	mtk->command = COMMAND_NULL;
}

/*******************************************************************************
 *Обработчик команд навигации в меню
 ******************************************************************************/
void mtk_commandMenu(mtk_t *mtk) {
	switch (mtk->command) {
	case COMMAND_NEXT: {
		if (mtk->element->flags & TYPE_PRIVATE)	//Если заблокированый элемент
		{
			mtk->element->flags |= EDITING_PROCESS;
			mtkUnlock.flags |= EDITING_PROCESS;
		} else {
			if (mtk->element->type == ELEMENT_MENU) {
				mtk->indexHist++;
				mtk->selectHist[mtk->indexHist] = mtk->select; //Запомнили с какой строки вход
				mtk->rootHist[mtk->indexHist] = mtk->element->pointer; //Запомнили нынешний корень меню
				mtk->select = 1;
			} else {
				mtk->element->flags |= EDITING_PROCESS;
				if (mtk->element->type == ELEMENT_GFUNC) {
					mtk->indexHist++;
					mtk->selectHist[mtk->indexHist] = mtk->select; //Запомнили с какой строки вход
					mtk->rootHist[mtk->indexHist] = mtk->element; //Запомнили нынешний корень меню
					mtk->pos = 2;
					mtk->select = 1;
				}
			}
		}
	}
		break;
	case COMMAND_PREV: {
		mtk->element->flags &= ~ EDITING_PROCESS;
		if (mtk->indexHist) {
			mtk->select = mtk->selectHist[mtk->indexHist]; //Вернулись на предыдущую строку
			mtk->indexHist--;
		} else {
			mtk->select = 0;
		}
	}
		break;
	case COMMAND_UP: {
		if (mtk->select > 0)
			mtk->select--;
		else
			mtk->select = mtk->count;
	}
		break;
	case COMMAND_DOWN: {
		if (mtk->select < mtk->count)
			mtk->select++;			//Какой элемент по счету выбран
		else
			mtk->select = 0;
	}
		break;
	}
}

/*******************************************************************************
 *Обработчик команд редактирования числа
 ******************************************************************************/
void mtk_commandNum(mtk_t *mtk) {
	uint32_t x;
	uint8_t y, rank;
	uint32_t (*fp)(uint32_t *);
	uint8_t type = mtk->element->type; //Тип элемента
	void * pointer = mtk->element->pointer; //Указатель на подэлемент
	rank = mtk->element->length - (mtk->pos + 1);
	if (mtk->element->flags & EDITING_EDITED)
		x = mtk->tempNum;
	else if (mtk->element->flags & TYPE_FUNC) {
		fp = (uint32_t (*)(uint32_t *)) mtk->element->pointer;
		x = (*fp)(NULL);
	} else {
		if (type == ELEMENT_NUM8)
			x = *((uint8_t*) pointer);
		else if (type == ELEMENT_NUM16)
			x = *((uint16_t*) pointer);
		else if (type == ELEMENT_NUM32)
			x = *((uint32_t*) pointer);
		else if (type == ELEMENT_NUM64X1M)
			x = (*((uint64_t*) pointer)) / 1000000;
	}
	y = (x % power(10, rank + 1)) / power(10, rank); //Переполнится ли
	switch (mtk->command) {
	case COMMAND_NEXT: {
		if (mtk->pos < mtk->element->length - 1)
			mtk->pos++;
		else {
			if (mtk->element->flags & TYPE_LOCK) {
				mtk->pos = 0;
			} else {
				mtk->pos = 0;
				mtk->element->flags &= ~(EDITING_EDITED | EDITING_PROCESS);
			}
		}
	}
		break;
	case COMMAND_PREV: {
		mtk->pos--;
	}
		break;
	case COMMAND_UP: {
		if (y > 8)
			x -= 9 * power(10, rank);
		else
			x += power(10, rank);
		if (mtk->element->flags & TYPE_NEEDOK)
			mtk->element->flags |= EDITING_EDITED;
	}
		break;
	case COMMAND_DOWN: {
		if (y < 1)
			x += 9 * power(10, rank);
		else
			x -= power(10, rank);
		if (mtk->element->flags & TYPE_NEEDOK)
			mtk->element->flags |= EDITING_EDITED;
	}
		break;
	}
	if (mtk->element->flags & EDITING_EDITED) {
		mtk->tempNum = x;
	} else {
		if (mtk->element->flags & TYPE_FUNC) {
			(*fp)(&x);
		} else {
			if (type == ELEMENT_NUM8)
				*((uint8_t*) pointer) = x;
			else if (type == ELEMENT_NUM16)
				*((uint16_t*) pointer) = x;
			else if (type == ELEMENT_NUM32)
				*((uint32_t*) pointer) = x;
			else if (type == ELEMENT_NUM64X1M)
				*((uint64_t*) pointer) = x * (uint64_t) 1000000;
		}
	}
}

/*******************************************************************************
 *Обработчик команд для FLAG
 ******************************************************************************/
void mtk_commandFlag(mtk_t *mtk) {
	uint32_t x;
	if (mtk->element->flags & EDITING_EDITED)
		x = mtk->tempNum;
	else
		x = *(uint8_t *) mtk->element->pointer;
	switch (mtk->command) {
	case COMMAND_UP:
	case COMMAND_DOWN: {
		if (x)
			x = 0;
		else
			x = 1;
		if (mtk->element->flags & TYPE_NEEDOK)
			mtk->element->flags |= EDITING_EDITED;
	}
		break;
	case COMMAND_NEXT: {
		if (mtk->element->flags & EDITING_EDITED)
			mtk->element->flags &= ~EDITING_EDITED;
		break;
	}
	}
	if ((mtk->element->flags & TYPE_NEEDOK) && (mtk->element->flags & EDITING_EDITED))
		mtk->tempNum = x;
	else
		*(uint8_t *) mtk->element->pointer = x;
}

/*******************************************************************************
 *Обработчик команд редактирования селектора
 ******************************************************************************/
void mtk_commandSelect(mtk_t *mtk) {
	uint8_t x;
	uint8_t(*fp)(uint8_t *);
	mtk_select_p pointer = mtk->element->pointer;
	if (mtk->element->flags & EDITING_EDITED)
		x = mtk->tempNum;
	else if (mtk->element->flags & TYPE_FUNC) {
		fp = (uint8_t (*)(uint8_t *))pointer->pointer;
		x = (*fp)(NULL);
	} else {
			x = *(uint8_t*)pointer->pointer;
	}
	switch (mtk->command) {
	case COMMAND_NEXT: {
		if (mtk->element->flags & EDITING_EDITED)
			mtk->element->flags &= ~EDITING_EDITED;
	}
		break;
	case COMMAND_PREV: {
		;
	}
		break;
	case COMMAND_UP: {
		if (x < mtk->element->length - 1)
			x++;
		else
			x = 0;
		if (mtk->element->flags & TYPE_NEEDOK)
			mtk->element->flags |= EDITING_EDITED;
	}
		break;
	case COMMAND_DOWN: {
		if (x > 0)
			x--;
		else
			x = mtk->element->length - 1;
		if (mtk->element->flags & TYPE_NEEDOK)
			mtk->element->flags |= EDITING_EDITED;
	}
		break;
	}
	if (mtk->element->flags & EDITING_EDITED) {
		mtk->tempNum = x;
	} else {
		if (mtk->element->flags & TYPE_FUNC) {
			(*fp)(&x);
		} else
				(*(uint8_t *)pointer->pointer) = x;
	}
}

/*******************************************************************************
 *Обработчик команд редактирования даты и времени
 ******************************************************************************/
void mtk_commandDateTime(mtk_t *mtk) {
	tm_t* (*fp)(tm_t *);
	tm_t * tm;
	switch (mtk->command) {
	case COMMAND_NEXT: {
		if (mtk->pos < mtk->element->length - 1)
			mtk->pos++;
		else {
			mtk->pos = 0;
			mtk->element->flags &= ~ EDITING_PROCESS;
			if (mtk->element->flags & EDITING_EDITED) { //Изменено. Будем сохранять
				if (mtk->element->flags & TYPE_FUNC) { //Если время устанавливается через функцию
					fp = (tm_t* (*)(tm_t *)) mtk->element->pointer;
					tm = fp(NULL); //Взяли актуальное время
				} else {
					tm = mtk->element->pointer;
				}
				if (mtk->element->type == ELEMENT_DATE) { //Если меняли дату актуализируем время в структуре
					mtk->tempTime.tm_hour = tm->tm_hour;
					mtk->tempTime.tm_min = tm->tm_min;
					mtk->tempTime.tm_sec = tm->tm_sec;
				}
				if (mtk->element->flags & TYPE_FUNC) {
					fp(&mtk->tempTime); //Установили часы
				} else {
					(*(tm_t *) mtk->element->pointer) = mtk->tempTime;
				}
//				if (mtk->element->flags & TYPE_NEEDOK)
					mtk->element->flags &= ~ (EDITING_EDITED | EDITING_PROCESS); //Значение сохранено, редактирование завершено
			}
		}
	}
		break;
	case COMMAND_PREV: {
		mtk->pos--;
	}
		break;
	case COMMAND_UP: {
		mtk_editDateTime(mtk, MTK_ACTION_INC);
	}
		break;
	case COMMAND_DOWN: {
		mtk_editDateTime(mtk, MTK_ACTION_DEC);
	}
		break;
	}
}

/*******************************************************************************
 *Обработчик редактора времени
 ******************************************************************************/
void mtk_editDateTime(mtk_t * mtk, uint8_t action) {
	uint16_t min = 0, max = 59;
	uint8_t *p = NULL;
	tm_t * tm;
	tm_t* (*fp)(tm_t *);

	if (mtk->element->flags & (TYPE_NEEDOK | TYPE_FUNC)) { //Если редактирование не прямое
		tm = &mtk->tempTime; //Ставим указатель на временную структуру
		if (!(mtk->element->flags & EDITING_EDITED)) { //Редактирование еще не начато
			if (mtk->element->flags & TYPE_FUNC) {
				fp = (tm_t* (*)(tm_t *)) mtk->element->pointer;
				mtk->tempTime = *(tm_t*) (*fp)(NULL);
			} else
				mtk->tempTime = *(tm_t*) mtk->element->pointer;
			mtk->element->flags |= EDITING_EDITED; //Редактирование началось, значение сейчас будет изменено
		}
	} else
		tm = mtk->element->pointer; //Ставим указатель на редактируемую структуру

	if (mtk->element->type == ELEMENT_DATE) {
		switch (mtk->pos) {
		case 0: {
			min = 1;
			max = 31;
			p = (uint8_t *)&tm->tm_mday;
		}
			break;
		case 1: {
			max = 11;
			p =(uint8_t *) &tm->tm_mon;
		}
			break;
		case 2: {
			min = 116;
			max = 199;
			p = (uint8_t *)&tm->tm_year;
		}
			break;
		}
	}
	if (mtk->element->type == ELEMENT_TIME) {
		switch (mtk->pos) {
		case 0: {
			max = 23;
			p = (uint8_t *)&tm->tm_hour;
		}
			break;
		case 1: {
			p = (uint8_t *)&tm->tm_min;
		}
			break;
		case 2: {
			p = (uint8_t *)&tm->tm_sec;
		}
			break;
		}
	}
		switch (action) {
	case MTK_ACTION_INC: {
		if (*p >= max) {
			*p = min;
		} else
			*p = *p + 1;
	}
		break;
	case MTK_ACTION_DEC: {
		if (*p <= min) {
			*p = max;
		} else
			*p = *p - 1;
	}
		break;
	}
}

/*******************************************************************************
 *Обработчик типа GFUNC
 ******************************************************************************/
void mtk_commamdGfunc(mtk_t *mtk) {
	//Если вошли в граффическую функцию и она способна обработать команды
	if ((mtk->element->flags & EDITING_PROCESS)
			&& (mtk->element->flags & TYPE_CMD_ACCEPT)) {
		void (*fp)(mtk_t *);
		fp = (void (*)(mtk_t *)) mtk->element->pointer;
		fp(mtk);
	}
	if (mtk->command) //Ecли команда не обработана
	{
		switch (mtk->command) {
		case COMMAND_NEXT: {
			mtk->element->flags |= EDITING_PROCESS;
		}
			break;
		case COMMAND_PREV:
		case COMMAND_UP:
		case COMMAND_DOWN: {
			mtk->pos = 0;
			mtk->element->flags &= ~ EDITING_PROCESS;
			mtk->select = mtk->selectHist[mtk->indexHist]; //Вернулись на предыдущую строку
			mtk->indexHist--; //Вернулись в предыдущее меню
		}
			break;
		}
	}
}

/*******************************************************************************
 *Возведение числа в степень
 ******************************************************************************/
uint32_t power(uint8_t x, uint8_t y) {
	uint8_t i;
	uint32_t rez = 1;
	for (i = 1; i <= y; ++i) {
		rez *= x;
	}
	return rez;
}
