#include "mtk.h"
//#include "bitmap.h"

/*******************************************************************************
 * Отрисовка гистограммы
 ******************************************************************************/
void graphBar(mtk_t * mtk, mtk_graph_t * graph) {
	char sTemp[30];
	uint8_t vStart, hStart, vStep, hStep;
	u8g_t * u8g;
	uint8_t x, y;
	uint8_t i;
	uint16_t vMax = 0;
	uint16_t vMin = 9999;
	uint8_t value;
	u8g = mtk->u8g;
	vStart = 35;
	hStart = 0;
	vStep = 93;
	hStep = 240 / graph->num;
	u8g_SetFont(u8g, u8g_font_elpaulo20);
	u8g_DrawLine(u8g, 0, vStart, 239, vStart);
	u8g_DrawLine(u8g, 0, vStart + vStep, 239, vStart + vStep);
	for (i = 0; i < graph->num; i++) //Находим минимум и максимум
			{
		if (graph->mas[i] < vMin)
			vMin = graph->mas[i];
		if (graph->mas[i] > vMax)
			vMax = graph->mas[i];
	}
	sprintf(sTemp, "%d.%d\x11%d.%d %s", vMax / 1000, vMax % 1000, vMin / 1000,
			vMin % 1000, graph->title);
	u8g_DrawStr(u8g, hStart, vStart - 2, sTemp);
	for (i = 0; i < graph->num; i++) {
		value = 3 + ((vStep - 5) * (graph->mas[i] - vMin) / (vMax - vMin));
		x = hStart + hStep * i;
		y = vStart + 1 + vStep - value;
		if (VB(graph->active, i)) //Если элемент помечен
			u8g_DrawBox(u8g, x, y, hStep - 1, value);
		else {
			u8g_DrawFrame(u8g, x, y, hStep - 1, value);
		}
		y = vStart + vStep + 16;
		if (i < 9) {
			sprintf(sTemp, "%d", i + 1);
			u8g_DrawStr(u8g, x, y, sTemp);
		} else {
			sprintf(sTemp, "%d", (i + 1) / 10);
			u8g_DrawStr(u8g, x, y, sTemp);
			sprintf(sTemp, "%d", (i + 1) % 10);
			u8g_DrawStr(u8g, x, y + 16, sTemp);
		}
	}
}
