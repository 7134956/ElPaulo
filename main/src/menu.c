#include "mtk.h"
#include "bitmap.h"

void about(mtk_t * mtk) {
	u8g_SetColorIndex(mtk->u8g, 3);
	u8g_SetFont(mtk->u8g, u8g_font_helvR24);
	u8g_DrawRFrame(mtk->u8g, 0, 20, 240, 140, 5);
	u8g_DrawRFrame(mtk->u8g, 5, 25, 230, 130, 5);
	u8g_DrawStr(mtk->u8g, 54, 63, "El   Paulo");
	u8g_DrawXBM(mtk->u8g, 86, 24, 24, 63, u8g_logo_bits);
	u8g_DrawRFrame(mtk->u8g, 10, 130, 220, 20, 5);
	u8g_SetFont(mtk->u8g, u8g_font_ncenR10);
	u8g_DrawStr(mtk->u8g, 95, 145, "v.0.1.5");
	u8g_DrawStr(mtk->u8g, 50, 110, "7134956@gmail.com");
}
