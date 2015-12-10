#ifndef _DRAW_H_
#define _DRAW_H_

#include "u8g.h"

#define ARROW_RIGHT 10
#define ARROW_LEFT 11
#define ARROW_UP 12
#define ARROW_DOWN 13

#define MENU_MAIN_ITEMS 8

void drawInit(void);
void redrawDisplay(void);
void displayOff(void);
void displayOn(void);
uint32_t contrastGetSet(uint32_t *);

#endif /* _DRAW_H_ */
