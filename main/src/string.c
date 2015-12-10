#include "mtk.h"
#include "string.h"

char *raceParams[2][7] = { { "Max. speed", "Expense", "Travel time", "Discharge", "To charging", "Odograph", "Aver. speed" },
		{ "Макс. скор", "Ср. расход", "Время пути", "Потрачено", "До зарядки", "Общ. пробег", "Сред. скор" } };

char *month[2][12] = { { "January", "February", "March", "April", "May", "June", "July", "August", " September", "October", "November", " December" },
		{"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", " Сентябрь", "Октябрь", "Ноябрь", " Декабрь" } };

char *days[2][7] = { { "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" }, { "Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс" } };

extern mtk_element_t mtkPassword,	//Пароль
		mtkDisplay,		//Меню настройки дисплея
		mtkContrast,	//Настройка контрастности
		mtkAutoBright,	//Включение автояркости дисплея
		mtkMenuOdometr,	//Меню настройки одометра
		mtkCircle,		//Настройка длины окружности колеса
		mtkOdometr,	//Пройденное расстояние в мм
		mtkPin,			//Пароль стартового экрана
		mtkLang,
		mtkDateTime, mtkDate, mtkTime,
		mtkPower, mtkSecInTime, mtkSleepDisplayOff, mtkSleepSec, mtkAbout;

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
		mtkDateTime.label[0] = "Date, Time";
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
		mtkSleepDisplayOff.label[0] = "Display off";
		mtkSleepDisplayOff.label[1] = "Выкл. экран";
		mtkAbout.label[0] = "About";
		mtkAbout.label[1] = "Об этом";
}
