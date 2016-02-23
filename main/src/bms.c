#include "config.h"
#include "bms.h"
#include "mtk.h"

void BMS_info(mtk_t * mtk);
void BMS_voltage(mtk_t * mtk);
void BMS_resist(mtk_t * mtk);
void BMS_cap(mtk_t * mtk);

extern char *sVoltage[2];
extern config_t config;

BMSconfig_t BMSconfig;
BMSinfo_t BMSinfo;
BMS_t BMS;

mtk_element_t
	mtk_BMS_info, //Общая информация по батарее
	mtk_BMS_statist,
	mtk_BMS_balanse,
	mtk_BMS_config,
	mtk_BMS_voltage, //Статистика мспользования
	mtk_BMS_cap,
	mtk_BMS_resist,
	mtk_BMS_charge,
	mtk_BMS_discharge,
	mtk_BMS_Vmin,
	mtk_BMS_Inom,
	mtk_BMS_Imax,
	mtk_BMS_tImax,
	mtk_BMS_Tmax,
	mtk_BMS_Tmin;

void BMS_init(void) {
	/*
	 Info
	 |
	 |
	 |
	 Statistic--------Voltage
	 |                  |
	 |                Емкостьти
	 |                  |
	 |                Сопротивления
	 |
	 Setup-----------Зарядка
	 |                  |
	 |               Разрядка

	 */

//---------Menu BMS
	//&Элемент, type, &массив строк, длина, флаги свойств, &куда ссылается, &следующий элемент
	//mtk_SetupElement(&, ELEMENT_,  NULL,  0, TYPE_NEEDOK, &pointer , &next);
//Информация по батарее
	mtk_SetupElement(&mtk_BMS_info, ELEMENT_GFUNC, NULL, 0, 0, &BMS_info, &mtk_BMS_statist);
//Статистика
	mtk_SetupElement(&mtk_BMS_statist, ELEMENT_MENU, NULL, 0, 0, &mtk_BMS_balanse, &mtk_BMS_config);
		mtk_SetupElement(&mtk_BMS_balanse, ELEMENT_GFUNC, NULL, 0, 0, &BMS_voltage, &mtk_BMS_cap);
		mtk_SetupElement(&mtk_BMS_cap, ELEMENT_GFUNC, NULL, 0, 0, &BMS_cap, &mtk_BMS_resist);
		mtk_SetupElement(&mtk_BMS_resist, ELEMENT_GFUNC, NULL, 0, 0, &BMS_resist, NULL);
//Настройки
	mtk_SetupElement(&mtk_BMS_config, ELEMENT_MENU, NULL, 0, TYPE_PRIVATE, &mtk_BMS_charge, NULL);
		mtk_SetupElement(&mtk_BMS_charge, ELEMENT_MENU, NULL, 0, 0, &mtk_BMS_Vmin, &mtk_BMS_discharge);
//			mtk_SetupElement(&mtk_BMS_, ELEMENT_NUM16, NULL, 4, TYPE_NEEDOK, &BMSconfig., &mtk_BMS_);
		mtk_SetupElement(&mtk_BMS_discharge, ELEMENT_MENU, NULL, 0, 0, &mtk_BMS_Vmin, NULL);
			mtk_SetupElement(&mtk_BMS_Vmin, ELEMENT_NUM16, NULL, 4, TYPE_NEEDOK, &BMSconfig.Vmin, &mtk_BMS_Inom);
			mtk_SetupElement(&mtk_BMS_Inom, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMSconfig.Inom, &mtk_BMS_Imax);
			mtk_SetupElement(&mtk_BMS_Imax, ELEMENT_NUM16, NULL, 3, TYPE_NEEDOK, &BMSconfig.Imax, &mtk_BMS_tImax);
			mtk_SetupElement(&mtk_BMS_tImax, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMSconfig.tImax, &mtk_BMS_Tmax);
			mtk_SetupElement(&mtk_BMS_Tmax, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMSconfig.Tmax, &mtk_BMS_Tmin);
			mtk_SetupElement(&mtk_BMS_Tmin, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMSconfig.Tmin, NULL);
//---------Menu odometr
}

/*******************************************************************************
 *Выводит
 ******************************************************************************/
void BMS_info(mtk_t * mtk) {
	char sTemp[30];
	u8g_t * u8g;
	uint8_t i, vStart, vStep, hStart;
	extern char *sBMSinfo[2][7];
	u8g = mtk->u8g;
	hStart = 0;
	vStep = 15;
	vStart = 36;
//	hStep = 0;
	u8g_SetFont(u8g, u8g_font_elpaulo20);
	for (i = 0; i < 7; i++) {
		u8g_DrawLine(u8g, 0, vStart + 3 + vStep * i, 239,
				vStart + 3 + vStep * i);
		u8g_DrawStr(u8g, hStart, vStart + i * vStep,
				sBMSinfo[config.lang][i]);
	}
//	u8g_DrawLine(u8g, 115, 18, 115, 159);
	//Максимальная скорость за заезд.
	sprintf(sTemp, "Headwey_40152s_24s1p");
	u8g_DrawStr(u8g, 38, vStart + 0 * vStep, sTemp);
	// Расход на километр
//	sprintf(sTemp, "%02d.%03d Ah/km", track.expense / 1000,
//			track.expense % 1000);
	u8g_DrawStr(u8g, 120, vStart + 1 * vStep, sTemp);
	// Время в пути до 36 часов
//	timeSec = track.tics / 32768;
//	sprintf(sTemp, "%02d:%02d:%02d", timeSec / 3600, (timeSec / 60) % 60,
//			timeSec % 60);
	u8g_DrawStr(u8g, 120, vStart + 2 * vStep, sTemp);
	// Потрачено емкости за заезд
//	sprintf(sTemp, "%02d.%03d Ah", track.discharge / 1000,
//			track.discharge % 1000);
	u8g_DrawStr(u8g, 120, vStart + 3 * vStep, sTemp);
	// Предпологаемый пробег до разряда
//	sprintf(sTemp, "%02d.%01d km", track.toCharging / 10,
//			track.toCharging % 10);
	u8g_DrawStr(u8g, 120, vStart + 4 * vStep, sTemp);
	//Средняя скорость.  32768 тиков в секунду.
//	sprintf(sTemp, "%02d.%02d km/h", track.averageSpeed / 100,
//			track.averageSpeed % 100);
	u8g_DrawStr(u8g, 120, vStart + 5 * vStep, sTemp);
	// Пройдено километров за все время
//	sprintf(sTemp, "%06lu.%02u km", (uint32_t) (track.odometr / 1000000),
//			(uint16_t) ((track.odometr % 1000000) / 10000));
	u8g_DrawStr(u8g, 120, vStart + 6 * vStep, sTemp);
}


void BMS_voltage(mtk_t * mtk){
	mtk_graph_t graph;
	//FIXME
	BMS.ActiveShunt = 8418334;
	BMSinfo.batNum = 24;
	BMSinfo.v[0] = 3252;
	BMSinfo.v[1] = 3296;
	BMSinfo.v[2] = 3283;
	BMSinfo.v[3] = 3284;
	BMSinfo.v[4] = 3296;
	BMSinfo.v[5] = 3253;
	BMSinfo.v[6] = 3250;
	BMSinfo.v[7] = 3237;
	BMSinfo.v[8] = 3234;
	BMSinfo.v[9] = 3265;
	BMSinfo.v[10] = 3285;
	BMSinfo.v[11] = 3252;
	BMSinfo.v[12] = 3297;
	BMSinfo.v[13] = 3298;
	BMSinfo.v[14] = 3297;
	BMSinfo.v[15] = 3268;
	BMSinfo.v[16] = 3236;
	BMSinfo.v[17] = 3232;
	BMSinfo.v[18] = 3255;
	BMSinfo.v[19] = 3254;
	BMSinfo.v[20] = 3232;
	BMSinfo.v[21] = 3260;
	BMSinfo.v[22] = 3239;
	BMSinfo.v[23] = 3285;

	graph.title = sVoltage[config.lang];
	graph.num = BMSinfo.batNum;
	graph.mas = &BMSinfo.v[0];
	graph.active = BMS.ActiveShunt;
	graphBar(mtk, &graph);
}

void BMS_cap(mtk_t * mtk){
	mtk_graph_t graph;
	//FIXME
	BMS.ActiveShunt = 8418334;
	BMSinfo.batNum = 24;
	BMSinfo.v[0] = 3252;
	BMSinfo.v[1] = 3296;
	BMSinfo.v[2] = 3283;
	BMSinfo.v[3] = 3284;
	BMSinfo.v[4] = 3296;
	BMSinfo.v[5] = 3253;
	BMSinfo.v[6] = 3250;
	BMSinfo.v[7] = 3237;
	BMSinfo.v[8] = 3234;
	BMSinfo.v[9] = 3265;
	BMSinfo.v[10] = 3285;
	BMSinfo.v[11] = 3252;
	BMSinfo.v[12] = 3297;
	BMSinfo.v[13] = 3298;
	BMSinfo.v[14] = 3297;
	BMSinfo.v[15] = 3268;
	BMSinfo.v[16] = 3236;
	BMSinfo.v[17] = 3232;
	BMSinfo.v[18] = 3255;
	BMSinfo.v[19] = 3254;
	BMSinfo.v[20] = 3232;
	BMSinfo.v[21] = 3260;
	BMSinfo.v[22] = 3239;
	BMSinfo.v[23] = 3285;

	graph.title = mtk_BMS_cap.label;
	graph.num = BMSinfo.batNum;
	graph.mas = &BMSinfo.v[0];
	graph.active = BMS.ActiveShunt;
	graphBar(mtk, &graph);
}

void BMS_resist(mtk_t * mtk){
	mtk_graph_t graph;
	//FIXME
	BMS.ActiveShunt = 8418334;
	BMSinfo.batNum = 24;
	BMSinfo.v[0] = 3252;
	BMSinfo.v[1] = 3296;
	BMSinfo.v[2] = 3283;
	BMSinfo.v[3] = 3284;
	BMSinfo.v[4] = 3296;
	BMSinfo.v[5] = 3253;
	BMSinfo.v[6] = 3250;
	BMSinfo.v[7] = 3237;
	BMSinfo.v[8] = 3234;
	BMSinfo.v[9] = 3265;
	BMSinfo.v[10] = 3285;
	BMSinfo.v[11] = 3252;
	BMSinfo.v[12] = 3297;
	BMSinfo.v[13] = 3298;
	BMSinfo.v[14] = 3297;
	BMSinfo.v[15] = 3268;
	BMSinfo.v[16] = 3236;
	BMSinfo.v[17] = 3232;
	BMSinfo.v[18] = 3255;
	BMSinfo.v[19] = 3254;
	BMSinfo.v[20] = 3232;
	BMSinfo.v[21] = 3260;
	BMSinfo.v[22] = 3239;
	BMSinfo.v[23] = 3285;

	graph.title = mtk_BMS_resist.label;
	graph.num = BMSinfo.batNum;
	graph.mas = &BMSinfo.v[0];
	graph.active = BMS.ActiveShunt;
	graphBar(mtk, &graph);
}
