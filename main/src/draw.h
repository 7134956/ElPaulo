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

#define MESSAGE_SLOTS 4
#define POPUP_NULL 0
#define POPUP_ALERT 1
#define POPUP_ERROR 2
#define POPUP_QUERY 3
//#define POPUP_SILENT 4

typedef struct popup_t {
	uint8_t type; //Флаги типа и ответа
	char * head; //Заголовок
	char * body; //Сообщение
} popup_t;

typedef struct message_t {
	popup_t popup[MESSAGE_SLOTS]; //Флаги типа и ответа
	uint8_t count; //Число сообщений в стеке
} message_t;

void drawInit(void);
void drawTask(void);//Запросить перерисовку экрана
void redrawDisplay(void);
void displayOff(void);
void displayOn(void);
uint32_t contrastGetSet(uint32_t *);
void messageCall(char *, char *, uint8_t);

#endif /* _DRAW_H_ */
