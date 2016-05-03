#include "mtk.h"
#include "string.h"

char *raceParams[7];
char *sBMSinfo[7];
char *month[12];
char *days[7];
char *sVoltage;

extern mtk_element_t
		mtk_BMS_statist,
		mtk_BMS_balanse,
		mtk_BMS_info,	//Информация по батарее
		mtkPassword,	//Пароль
		mtkDisplay,		//Меню настройки дисплея
		mtkContrast,	//Настройка контрастности
		mtkAutoBright,	//Включение автояркости дисплея
		mtkMenuOdometr,	//Меню настройки одометра
		mtkService,
		mtkSaveRace, 	//
		mtkCircle,		//Настройка длины окружности колеса
		mtkOdometr,		//Пройденное расстояние в мм
		mtkPin,			//Пароль стартового экрана
		mtkLang,
		mtkDateTime,
		mtkDate,
		mtkTime,
		mtkPower,
		mtkSecInTime,
		mtkMaxFPS,
		mtkSleepDisplayOff,
		mtkSleepSec,
		mtkAutoPowerOff,
		mtkBat_KS,
		mtkSleepOff,
		mtkMenuBMS,
		mtk_BMS_config,
		mtk_BMS_voltage,
		mtk_BMS_cap,
		mtk_BMS_resist,
		mtk_BMS_charge,
		mtk_BMS_discharge,
		mtk_BMS_DVmin,
		mtk_BMS_DInom,
		mtk_BMS_DImax,
		mtk_BMS_DtImax,
		mtk_BMS_DTmax,
		mtk_BMS_DTmin,
		mtkRacelist,
		mtkAbout,
		mtkStopwatch,
		mtkTimer,
		mtkCompass,
		mtkAlarmClock,
		mtkCountdownTime,
		mtkCountdownDst;

extern mtk_select_t mtkLangList, mtkRacelistList;
extern config_t config;

/******************************************************************************
 * Get/set current GUI language
 *****************************************************************************/
uint8_t setStrings(uint8_t * lang) {
	if(!lang)
		return config.lang;
	raceParams[2] = "Max. speed";
	raceParams[4] = "Expense";
	raceParams[0] = "Travel time";
	raceParams[3] = "Discharge";
	raceParams[5] = "To charging";
	raceParams[1] = "Aver. speed";
	raceParams[6] = "Odograph";

	sVoltage = "(Voltage)";

	sBMSinfo[0] = "Name:";
	sBMSinfo[1] = "";
	sBMSinfo[2] = "";
	sBMSinfo[3] = "";
	sBMSinfo[4] = "";
	sBMSinfo[5] = "";
	sBMSinfo[5] = "";

	month[0] = "January";
	month[1] = "February";
	month[2] = "March";
	month[3] = "April";
	month[4] = "May";
	month[5] = "June";
	month[6] = "July";
	month[7] = "August";
	month[8] = "September";
	month[9] = "October";
	month[10] = "November";
	month[11] = "December";

	days[0] = "Mo";
	days[1] = "Tu";
	days[2] = "We";
	days[3] = "Th";
	days[4] = "Fr";
	days[5] = "Sa";
	days[6] = "Su";

	mtkDisplay.label = "Display";
	mtkContrast.label = "Contrast";
	mtkAutoBright.label = "Autobright";
	mtkMenuOdometr.label = "Odometr";
	mtkCircle.label = "Circle(mm)";
	mtkOdometr.label = "Odometr(km)";
	mtkService.label = "To service(km)";
	mtkSaveRace.label = "Autosave(min)";
	mtkPassword.label = "Password";
	mtkDateTime.label = "Time";
	mtkDate.label = "Date";
	mtkTime.label = "Time";
	mtkPin.label = "";
	mtkLang.label = "Language";
	mtkPower.label  = "PowerSave";
	mtkSecInTime.label  = "Draw sec";
	mtkSleepSec.label = "Autosleep sec";
	mtkMaxFPS.label = "Maximum FPS";
	mtkSleepDisplayOff.label = "Display off";
	mtkAutoPowerOff.label = "AutoOff (min)";
	mtkBat_KS.label = "KS ADC Bat";
	mtkSleepOff.label = "Sleep off";
//	mtkSupply.label = "Bat calibr";
//	mtkSupply40.label = "ADC level 4.0V";
//	mtkSupply37.label = "ADC level 3.7V";
	mtkMenuBMS.label = "Battery";
	mtk_BMS_statist.label = "Statistic";
	mtk_BMS_balanse.label = "Balance";
	mtk_BMS_info.label = "Info";
	mtk_BMS_config.label = "Configure";
	mtk_BMS_voltage.label = "Voltage";
	mtk_BMS_cap.label = "Capacity";
	mtk_BMS_resist.label = "Resistance";
	mtk_BMS_charge.label = "Charge";
	mtk_BMS_discharge.label = "Discharge";
	mtk_BMS_DVmin.label = "V min (mV)";
	mtk_BMS_DInom.label = "I nom (A)";
	mtk_BMS_DImax.label = "I max (A)";
	mtk_BMS_DtImax.label = "Time I max (sec)";
	mtk_BMS_DTmax.label = "Temp. max (Сѓ)";
	mtk_BMS_DTmin.label = "Temp min (Сѓ)";
	mtkRacelist.label = "Racelist";
	mtkRacelistList.string[0] = "Calendar";
	mtkRacelistList.string[1] = "List";
	mtkAbout.label = "About";
	mtkStopwatch.label = "Stopwatch";
	mtkTimer.label = "Timer";
	mtkCompass.label = "Compass";
	mtkAlarmClock.label = "Alarm clock";
	mtkCountdownTime.label = "CDT";
	mtkCountdownDst.label = "CDD";
	switch (*lang) {
	case LANGUAGE_ENG:

		break;
	case LANGUAGE_RUS:
		raceParams[2] = "Макс. скор";
		raceParams[4] = "Ср. расход";
		raceParams[0] = "Время пути";
		raceParams[3] = "Потрачено";
		raceParams[5] = "До зарядки";
		raceParams[1] = "Сред. скор" ;
		raceParams[6] = "Общ. пробег";

		sVoltage = "(Напряжение)";

		sBMSinfo[0] = "Имя:";
		sBMSinfo[1] = "";
		sBMSinfo[2] = "";
		sBMSinfo[3] = "";
		sBMSinfo[4] = "";
		sBMSinfo[5] = "";
		sBMSinfo[5] = "";

		month[0] = "Январь";
		month[1] = "Февраль";
		month[2] = "Март";
		month[3] = "Апрель";
		month[4] = "Май";
		month[5] = "Июнь";
		month[6] = "Июль";
		month[7] =  "Август";
		month[8] = " Сентябрь";
		month[9] = "Октябрь";
		month[10] = "Ноябрь";
		month[11] = " Декабрь";

		days[0] ="Пн";
		days[1] ="Вт";
		days[2] ="Ср";
		days[3] ="Чт";
		days[4] = "Пт";
		days[5] = "Сб";
		days[6] = "Вс";

		mtkDisplay.label = "Экран";
		mtkContrast.label = "Контраст";
		mtkAutoBright.label = "Автоподсветка";
		mtkMenuOdometr.label = "Одометр";
		mtkCircle.label = "Колесо(мм)";
		mtkOdometr.label = "Одометр(км)";
		mtkService.label = "Тех. Обсл.(км)";
		mtkSaveRace.label = "Автосохр.(мин)";
		mtkPassword.label = "Пароль";
		mtkDateTime.label = "Часы";
		mtkDate.label = "Дата";
		mtkTime.label = "Время";
		mtkPin.label = "";
		mtkLang.label = "Язык";
		mtkPower.label  = "Питание";
		mtkSecInTime.label = "Показ секунд";
		mtkSleepSec.label = "Aвтосон(сек)";
		mtkMaxFPS.label = "Частота кадров";
		mtkSleepDisplayOff.label = "Выкл. экран";
		mtkAutoPowerOff.label = "Выключ. (мин.)";
//		mtkSupply.label = "Батар. калибр.";
//		mtkSupply40.label = "Уровень АЦП 4.0В";
//		mtkSupply37.label = "Уровень АЦП 3.7В";
		mtkMenuBMS.label = "Батарея";
		mtk_BMS_statist.label = "Статист.";
		mtk_BMS_balanse.label = "Баланс";
		mtk_BMS_info.label = "Информ.";
		mtk_BMS_config.label = "Настройка";
		mtk_BMS_voltage.label = "Напряжения";
		mtk_BMS_cap.label = "Емкость";
		mtk_BMS_resist.label = "Сопротивление";
		mtk_BMS_charge.label = "Зарядка";
		mtk_BMS_discharge.label = "Разрядка";
		mtk_BMS_DVmin.label = "Напр. мин.(мВ)";
		mtk_BMS_DInom.label = "Ток ном. (А)";
		mtk_BMS_DImax.label = "Ток пик. (А)";
		mtk_BMS_DtImax.label = "Время пика (сек)";
		mtk_BMS_DTmax.label = "Темп. макс. (°C)";
		mtk_BMS_DTmin.label = "Темп. мин. (°C)";
		mtkRacelist.label = "Заезды";
		mtkRacelistList.string[0] = "Календарь";
		mtkRacelistList.string[1] = "Список";
		mtkAbout.label = "Об этом";
		mtkStopwatch.label = "Секундомер";
		mtkTimer.label = "Таймер";
		mtkCompass.label = "Компас";
		mtkAlarmClock.label = "Будильник";
		mtkCountdownTime.label = "Отсчет (вр.)";
		mtkCountdownDst.label = "Отсчет (км)";
		break;
	}
	mtkLangList.string[0] = "English";
	mtkLangList.string[1] = "Русский";
	config.lang = *lang;
	return 0;
}
