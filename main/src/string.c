#include "mtk.h"

char *raceParams[2][7] = {
		{"Max. speed", "Expense", "Travel time", "Discharge", "To charging", "Aver. speed" ,"Odograph"},
		{"Макс. скор", "Ср. расход", "Время пути", "Потрачено", "До зарядки", "Сред. скор" , "Общ. пробег"} };
char *sBMSinfo[2][7] = {
		{"Name:", "", "", "", "", "" ,""},
		{"Имя:", "", "", "", "", "" , ""} };

char *month[2][12] = {
		{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" },
		{"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", " Сентябрь", "Октябрь", "Ноябрь", " Декабрь" } };

char *days[2][7] = {
		{ "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" },
		{ "Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс" } };

char *sVoltage[2] = { "(Voltage)", "(Напряжение)"};

extern mtk_element_t
		mtk_BMS_statist,
		mtk_BMS_balanse,
		mtk_BMS_info,	//Информация по батарее
		mtkPassword,	//Пароль
		mtkDisplay,		//Меню настройки дисплея
		mtkContrast,	//Настройка контрастности
		mtkAutoBright,	//Включение автояркости дисплея
		mtkMenuOdometr,	//Меню настройки одометра
		mtkCircle,		//Настройка длины окружности колеса
		mtkOdometr,	//Пройденное расстояние в мм
		mtkPin,			//Пароль стартового экрана
		mtkLang,
		mtkDateTime, mtkDate, mtkTime,
		mtkPower, mtkSecInTime, mtkMaxFPS, mtkSleepDisplayOff, mtkSleepSec, mtkMenuBMS, mtk_BMS_config, mtk_BMS_voltage, mtk_BMS_cap, mtk_BMS_resist,
		mtk_BMS_charge,
		mtk_BMS_discharge,
		mtk_BMS_Vmin,
		mtk_BMS_Inom,
		mtk_BMS_Imax,
		mtk_BMS_tImax,
		mtk_BMS_Tmax,
		mtk_BMS_Tmin,
		mtkAbout,

		mtkStopwatch,
		mtkTimer;

extern mtk_select_t mtkLangList;

void setStrings(uint8_t lang) {
		mtkDisplay.label[0] = "Display";
		mtkDisplay.label[1] = "Экран";
		mtkContrast.label[0] = "Contrast";
		mtkContrast.label[1] = "Контраст";
		mtkAutoBright.label[0] = "Autobright";
		mtkAutoBright.label[1] = "Автоподсветка";
		mtkMenuOdometr.label[0] = "Odometr";
		mtkMenuOdometr.label[1] = "Одометр";
		mtkCircle.label[0] = "Circle(mm)";
		mtkCircle.label[1] = "Колесо(mm)";
		mtkOdometr.label[0] = "Odometr(Km)";
		mtkOdometr.label[1] = "Одометр(Km)";
		mtkPassword.label[0] = "Password";
		mtkPassword.label[1] = "Пароль";
		mtkDateTime.label[0] = "Date, time";
		mtkDateTime.label[1] = "Дата, время";
		mtkDate.label[0] = "Date";
		mtkDate.label[1] = "Дата";
		mtkTime.label[0] = "Time";
		mtkTime.label[1] = "Время";
		mtkPin.label[0] = "";
		mtkPin.label[1] = "";
		mtkLang.label[0] = "Language";
		mtkLang.label[1] = "Язык";
		mtkLangList.string[0] = "English";
		mtkLangList.string[1] = "Русский";
		mtkPower.label[0]  = "PowerSave";
		mtkPower.label[1]  = "Сбережение";
		mtkSecInTime.label[0]  = "Draw sec";
		mtkSecInTime.label[1] = "Показ секунд";
		mtkSleepSec.label[0] = "Autosleep sec";
		mtkSleepSec.label[1] = "Aвтосон(сек)";
		mtkMaxFPS.label[0] = "Maximum FPS";
		mtkMaxFPS.label[1] = "Частота кадров";
		mtkSleepDisplayOff.label[0] = "Display off";
		mtkSleepDisplayOff.label[1] = "Выкл. экран";

		mtkMenuBMS.label[0] = "Battery";
		mtkMenuBMS.label[1] = "Батарея";
		mtk_BMS_statist.label[0] = "Statistic";
		mtk_BMS_statist.label[1] = "Статист.";
		mtk_BMS_balanse.label[0] = "Balance";
		mtk_BMS_balanse.label[1] = "Баланс";
		mtk_BMS_info.label[0] = "Info";
		mtk_BMS_info.label[1] = "Информ.";
		mtk_BMS_config.label[0] = "Configure";
		mtk_BMS_config.label[1] = "Настройка";
		mtk_BMS_voltage.label[0] = "Voltage";
		mtk_BMS_voltage.label[1] = "Напряжения";
		mtk_BMS_cap.label[0] = "Capacity";
		mtk_BMS_cap.label[1] = "Емкость";
		mtk_BMS_resist.label[0] = "Resistance";
		mtk_BMS_resist.label[1] = "Сопротивление";
		mtk_BMS_charge.label[0] = "Charge";
		mtk_BMS_charge.label[1] = "Зарядка";
		mtk_BMS_discharge.label[0] = "Discharge";
		mtk_BMS_discharge.label[1] = "Разрядка";
		mtk_BMS_Vmin.label[0] = "V min (mV)";
		mtk_BMS_Vmin.label[1] = "Напр. мин.(мВ)";
		mtk_BMS_Inom.label[0] = "I nom (A)";
		mtk_BMS_Inom.label[1] = "Ток ном. (А)";
		mtk_BMS_Imax.label[0] = "I max (A)";
		mtk_BMS_Imax.label[1] = "Ток пик. (А)";
		mtk_BMS_tImax.label[0] = "Time I max (Sec)";
		mtk_BMS_tImax.label[1] = "Время пика (Сек)";
		mtk_BMS_Tmax.label[0] = "Temp. max (°C)";
		mtk_BMS_Tmax.label[1] = "Темп. макс. (°C)";
		mtk_BMS_Tmin.label[0] = "Temp min (°C)";
		mtk_BMS_Tmin.label[1] = "Темп. мин. (°C)";

		mtkAbout.label[0] = "About";
		mtkAbout.label[1] = "Об этом";

		mtkStopwatch.label[0] = "Stopwatch";
		mtkStopwatch.label[1] = "Секундомер";
		mtkTimer.label[0] = "Timer";
		mtkTimer.label[1] = "Таймер";
}
