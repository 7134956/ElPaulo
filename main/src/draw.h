#ifndef _DRAW_H_
#define _DRAW_H_

#include "config.h"

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

#define ARROW_RIGHT 10
#define ARROW_LEFT 11
#define ARROW_UP 12
#define ARROW_DOWN 13

#define MENU_MAIN_ITEMS 8

#define POPUP_NULL 0
#define POPUP_ALERT 1
#define POPUP_ERROR 2
#define POPUP_QUEST 3

typedef struct popup_t {
	uint8_t type; //Флани типа и ответа
	char * head; //Заголовок
	char * body; //Сообщение
} popup_t;

void drawInit(void);
void drawTask(void);//Запросить перерисовку экрана
void redrawDisplay(void);
void displayOff(void);
void displayOn(void);
uint32_t contrastGetSet(uint32_t *);
void message(void);

#endif /* _DRAW_H_ */
