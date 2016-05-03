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
		mtk_BMS_info,	//���������� �� �������
		mtkPassword,	//������
		mtkDisplay,		//���� ��������� �������
		mtkContrast,	//��������� �������������
		mtkAutoBright,	//��������� ����������� �������
		mtkMenuOdometr,	//���� ��������� ��������
		mtkService,
		mtkSaveRace, 	//
		mtkCircle,		//��������� ����� ���������� ������
		mtkOdometr,		//���������� ���������� � ��
		mtkPin,			//������ ���������� ������
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
	mtk_BMS_DTmax.label = "Temp. max (у)";
	mtk_BMS_DTmin.label = "Temp min (у)";
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
		raceParams[2] = "����. ����";
		raceParams[4] = "��. ������";
		raceParams[0] = "����� ����";
		raceParams[3] = "���������";
		raceParams[5] = "�� �������";
		raceParams[1] = "����. ����" ;
		raceParams[6] = "���. ������";

		sVoltage = "(����������)";

		sBMSinfo[0] = "���:";
		sBMSinfo[1] = "";
		sBMSinfo[2] = "";
		sBMSinfo[3] = "";
		sBMSinfo[4] = "";
		sBMSinfo[5] = "";
		sBMSinfo[5] = "";

		month[0] = "������";
		month[1] = "�������";
		month[2] = "����";
		month[3] = "������";
		month[4] = "���";
		month[5] = "����";
		month[6] = "����";
		month[7] =  "������";
		month[8] = " ��������";
		month[9] = "�������";
		month[10] = "������";
		month[11] = " �������";

		days[0] ="��";
		days[1] ="��";
		days[2] ="��";
		days[3] ="��";
		days[4] = "��";
		days[5] = "��";
		days[6] = "��";

		mtkDisplay.label = "�����";
		mtkContrast.label = "��������";
		mtkAutoBright.label = "�������������";
		mtkMenuOdometr.label = "�������";
		mtkCircle.label = "������(��)";
		mtkOdometr.label = "�������(��)";
		mtkService.label = "���. ����.(��)";
		mtkSaveRace.label = "��������.(���)";
		mtkPassword.label = "������";
		mtkDateTime.label = "����";
		mtkDate.label = "����";
		mtkTime.label = "�����";
		mtkPin.label = "";
		mtkLang.label = "����";
		mtkPower.label  = "�������";
		mtkSecInTime.label = "����� ������";
		mtkSleepSec.label = "A������(���)";
		mtkMaxFPS.label = "������� ������";
		mtkSleepDisplayOff.label = "����. �����";
		mtkAutoPowerOff.label = "������. (���.)";
//		mtkSupply.label = "�����. ������.";
//		mtkSupply40.label = "������� ��� 4.0�";
//		mtkSupply37.label = "������� ��� 3.7�";
		mtkMenuBMS.label = "�������";
		mtk_BMS_statist.label = "�������.";
		mtk_BMS_balanse.label = "������";
		mtk_BMS_info.label = "������.";
		mtk_BMS_config.label = "���������";
		mtk_BMS_voltage.label = "����������";
		mtk_BMS_cap.label = "�������";
		mtk_BMS_resist.label = "�������������";
		mtk_BMS_charge.label = "�������";
		mtk_BMS_discharge.label = "��������";
		mtk_BMS_DVmin.label = "����. ���.(��)";
		mtk_BMS_DInom.label = "��� ���. (�)";
		mtk_BMS_DImax.label = "��� ���. (�)";
		mtk_BMS_DtImax.label = "����� ���� (���)";
		mtk_BMS_DTmax.label = "����. ����. (�C)";
		mtk_BMS_DTmin.label = "����. ���. (�C)";
		mtkRacelist.label = "������";
		mtkRacelistList.string[0] = "���������";
		mtkRacelistList.string[1] = "������";
		mtkAbout.label = "�� ����";
		mtkStopwatch.label = "����������";
		mtkTimer.label = "������";
		mtkCompass.label = "������";
		mtkAlarmClock.label = "���������";
		mtkCountdownTime.label = "������ (��.)";
		mtkCountdownDst.label = "������ (��)";
		break;
	}
	mtkLangList.string[0] = "English";
	mtkLangList.string[1] = "�������";
	config.lang = *lang;
	return 0;
}
