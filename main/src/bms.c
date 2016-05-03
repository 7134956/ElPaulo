#include "config.h"
#include "bms.h"
#include "mtk.h"

void BMS_show_info(mtk_t * mtk);
void BMS_voltage(mtk_t * mtk);
void BMS_resist(mtk_t * mtk);
void BMS_cap(mtk_t * mtk);

extern char *sVoltage[2];
extern config_t config;

BMS_C_conf_t BMS_C_conf;
BMS_D_conf_t BMS_D_conf;
BMS_info_t BMS_info;
BMS_t BMS;
BMS_C_data_t BMS_C_data;

mtk_element_t
	mtk_BMS_info, //Общая информация по батарее
	mtk_BMS_statist,
	mtk_BMS_balanse,
	mtk_BMS_config,
	mtk_BMS_voltage, //Статистика использования
	mtk_BMS_cap,
	mtk_BMS_resist,
	mtk_BMS_charge,

	mtk_BMS_discharge,
	mtk_BMS_DVmin,
	mtk_BMS_DInom,
	mtk_BMS_DImax,
	mtk_BMS_DtImax,
	mtk_BMS_DTmax,
	mtk_BMS_DTmin;

void BMS_init(void) {
	BMS.state = BMS_NOTFOUND;
	//Проверить подачу внешнего питания
	//Включить кан шину
	//Загрузить данные из BMS
//	if(BMS.state != BMS_NOTFOUND)
		//FIXME Спросить состояние у бмс
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
		mtk_SetupElement(&mtk_BMS_charge, ELEMENT_MENU, NULL, 0, 0, &mtk_BMS_DVmin, &mtk_BMS_discharge);	//Меню настроек зарядки
//			mtk_SetupElement(&mtk_BMS_, ELEMENT_NUM16, NULL, 4, TYPE_NEEDOK, &BMSconfig., &mtk_BMS_);
		mtk_SetupElement(&mtk_BMS_discharge, ELEMENT_MENU, NULL, 0, 0, &mtk_BMS_DVmin, NULL);	//Меню настроек разрядки
			mtk_SetupElement(&mtk_BMS_DVmin, ELEMENT_NUM16, NULL, 4, TYPE_NEEDOK, &BMS_D_conf.DVmin, &mtk_BMS_DInom);
			mtk_SetupElement(&mtk_BMS_DInom, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMS_D_conf.DInom, &mtk_BMS_DImax);
			mtk_SetupElement(&mtk_BMS_DImax, ELEMENT_NUM16, NULL, 3, TYPE_NEEDOK, &BMS_D_conf.DImax, &mtk_BMS_DtImax);
			mtk_SetupElement(&mtk_BMS_DtImax, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMS_D_conf.DtImax, &mtk_BMS_DTmax);
			mtk_SetupElement(&mtk_BMS_DTmax, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMS_D_conf.DTmax, &mtk_BMS_DTmin);
			mtk_SetupElement(&mtk_BMS_DTmin, ELEMENT_NUM16, NULL, 2, TYPE_NEEDOK, &BMS_D_conf.DTmin, NULL);
//---------Menu odometr
}

/*******************************************************************************
 *Выводит
 ******************************************************************************/
void BMS_show_info(mtk_t * mtk) {
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
	BMS_C_data.ActiveShunt = 8418334;
	BMS_info.batNum = 24;
	BMS_info.v[0] = 3252;
	BMS_info.v[1] = 3296;
	BMS_info.v[2] = 3283;
	BMS_info.v[3] = 3284;
	BMS_info.v[4] = 3296;
	BMS_info.v[5] = 3253;
	BMS_info.v[6] = 3250;
	BMS_info.v[7] = 3237;
	BMS_info.v[8] = 3234;
	BMS_info.v[9] = 3265;
	BMS_info.v[10] = 3285;
	BMS_info.v[11] = 3252;
	BMS_info.v[12] = 3297;
	BMS_info.v[13] = 3298;
	BMS_info.v[14] = 3297;
	BMS_info.v[15] = 3268;
	BMS_info.v[16] = 3236;
	BMS_info.v[17] = 3232;
	BMS_info.v[18] = 3255;
	BMS_info.v[19] = 3254;
	BMS_info.v[20] = 3232;
	BMS_info.v[21] = 3260;
	BMS_info.v[22] = 3239;
	BMS_info.v[23] = 3285;

	graph.title = sVoltage[config.lang];
	graph.num = BMS_info.batNum;
	graph.mas = &BMS_info.v[0];
	graph.active = BMS_C_data.ActiveShunt;
	graphBar(mtk, &graph);
}

void BMS_cap(mtk_t * mtk){
	mtk_graph_t graph;
	//FIXME
	BMS_C_data.ActiveShunt = 8418334;
	BMS_info.batNum = 24;
	BMS_info.v[0] = 3252;
	BMS_info.v[1] = 3296;
	BMS_info.v[2] = 3283;
	BMS_info.v[3] = 3284;
	BMS_info.v[4] = 3296;
	BMS_info.v[5] = 3253;
	BMS_info.v[6] = 3250;
	BMS_info.v[7] = 3237;
	BMS_info.v[8] = 3234;
	BMS_info.v[9] = 3265;
	BMS_info.v[10] = 3285;
	BMS_info.v[11] = 3252;
	BMS_info.v[12] = 3297;
	BMS_info.v[13] = 3298;
	BMS_info.v[14] = 3297;
	BMS_info.v[15] = 3268;
	BMS_info.v[16] = 3236;
	BMS_info.v[17] = 3232;
	BMS_info.v[18] = 3255;
	BMS_info.v[19] = 3254;
	BMS_info.v[20] = 3232;
	BMS_info.v[21] = 3260;
	BMS_info.v[22] = 3239;
	BMS_info.v[23] = 3285;

	graph.title = mtk_BMS_cap.label;
	graph.num = BMS_info.batNum;
	graph.mas = &BMS_info.v[0];
	graph.active = BMS_C_data.ActiveShunt;
	graphBar(mtk, &graph);
}

void BMS_resist(mtk_t * mtk){
	mtk_graph_t graph;
	//FIXME
	BMS_C_data.ActiveShunt = 8418334;
	BMS_info.batNum = 24;
	BMS_info.v[0] = 3252;
	BMS_info.v[1] = 3296;
	BMS_info.v[2] = 3283;
	BMS_info.v[3] = 3284;
	BMS_info.v[4] = 3296;
	BMS_info.v[5] = 3253;
	BMS_info.v[6] = 3250;
	BMS_info.v[7] = 3237;
	BMS_info.v[8] = 3234;
	BMS_info.v[9] = 3265;
	BMS_info.v[10] = 3285;
	BMS_info.v[11] = 3252;
	BMS_info.v[12] = 3297;
	BMS_info.v[13] = 3298;
	BMS_info.v[14] = 3297;
	BMS_info.v[15] = 3268;
	BMS_info.v[16] = 3236;
	BMS_info.v[17] = 3232;
	BMS_info.v[18] = 3255;
	BMS_info.v[19] = 3254;
	BMS_info.v[20] = 3232;
	BMS_info.v[21] = 3260;
	BMS_info.v[22] = 3239;
	BMS_info.v[23] = 3285;

	graph.title = mtk_BMS_resist.label;
	graph.num = BMS_info.batNum;
	graph.mas = &BMS_info.v[0];
	graph.active = BMS_C_data.ActiveShunt;
	graphBar(mtk, &graph);
}
