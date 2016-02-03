#include "mtk.h"

char *raceParams[2][7] = {
		{"Max. speed", "Expense", "Travel time", "Discharge", "To charging", "Aver. speed" ,"Odograph"},
		{"����. ����", "��. ������", "����� ����", "���������", "�� �������", "����. ����" , "���. ������"} };
char *sBMSinfo[2][7] = {
		{"Name:", "", "", "", "", "" ,""},
		{"���:", "", "", "", "", "" , ""} };

char *month[2][12] = {
		{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" },
		{"������", "�������", "����", "������", "���", "����", "����", "������", " ��������", "�������", "������", " �������" } };

char *days[2][7] = {
		{ "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" },
		{ "��", "��", "��", "��", "��", "��", "��" } };

char *sVoltage[2] = { "(Voltage)", "(����������)"};

extern mtk_element_t
		mtk_BMS_statist,
		mtk_BMS_balanse,
		mtk_BMS_info,	//���������� �� �������
		mtkPassword,	//������
		mtkDisplay,		//���� ��������� �������
		mtkContrast,	//��������� �������������
		mtkAutoBright,	//��������� ����������� �������
		mtkMenuOdometr,	//���� ��������� ��������
		mtkCircle,		//��������� ����� ���������� ������
		mtkOdometr,	//���������� ���������� � ��
		mtkPin,			//������ ���������� ������
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
		mtkDisplay.label[1] = "�����";
		mtkContrast.label[0] = "Contrast";
		mtkContrast.label[1] = "��������";
		mtkAutoBright.label[0] = "Autobright";
		mtkAutoBright.label[1] = "�������������";
		mtkMenuOdometr.label[0] = "Odometr";
		mtkMenuOdometr.label[1] = "�������";
		mtkCircle.label[0] = "Circle(mm)";
		mtkCircle.label[1] = "������(mm)";
		mtkOdometr.label[0] = "Odometr(Km)";
		mtkOdometr.label[1] = "�������(Km)";
		mtkPassword.label[0] = "Password";
		mtkPassword.label[1] = "������";
		mtkDateTime.label[0] = "Date, time";
		mtkDateTime.label[1] = "����, �����";
		mtkDate.label[0] = "Date";
		mtkDate.label[1] = "����";
		mtkTime.label[0] = "Time";
		mtkTime.label[1] = "�����";
		mtkPin.label[0] = "";
		mtkPin.label[1] = "";
		mtkLang.label[0] = "Language";
		mtkLang.label[1] = "����";
		mtkLangList.string[0] = "English";
		mtkLangList.string[1] = "�������";
		mtkPower.label[0]  = "PowerSave";
		mtkPower.label[1]  = "����������";
		mtkSecInTime.label[0]  = "Draw sec";
		mtkSecInTime.label[1] = "����� ������";
		mtkSleepSec.label[0] = "Autosleep sec";
		mtkSleepSec.label[1] = "A������(���)";
		mtkMaxFPS.label[0] = "Maximum FPS";
		mtkMaxFPS.label[1] = "������� ������";
		mtkSleepDisplayOff.label[0] = "Display off";
		mtkSleepDisplayOff.label[1] = "����. �����";

		mtkMenuBMS.label[0] = "Battery";
		mtkMenuBMS.label[1] = "�������";
		mtk_BMS_statist.label[0] = "Statistic";
		mtk_BMS_statist.label[1] = "�������.";
		mtk_BMS_balanse.label[0] = "Balance";
		mtk_BMS_balanse.label[1] = "������";
		mtk_BMS_info.label[0] = "Info";
		mtk_BMS_info.label[1] = "������.";
		mtk_BMS_config.label[0] = "Configure";
		mtk_BMS_config.label[1] = "���������";
		mtk_BMS_voltage.label[0] = "Voltage";
		mtk_BMS_voltage.label[1] = "����������";
		mtk_BMS_cap.label[0] = "Capacity";
		mtk_BMS_cap.label[1] = "�������";
		mtk_BMS_resist.label[0] = "Resistance";
		mtk_BMS_resist.label[1] = "�������������";
		mtk_BMS_charge.label[0] = "Charge";
		mtk_BMS_charge.label[1] = "�������";
		mtk_BMS_discharge.label[0] = "Discharge";
		mtk_BMS_discharge.label[1] = "��������";
		mtk_BMS_Vmin.label[0] = "V min (mV)";
		mtk_BMS_Vmin.label[1] = "����. ���.(��)";
		mtk_BMS_Inom.label[0] = "I nom (A)";
		mtk_BMS_Inom.label[1] = "��� ���. (�)";
		mtk_BMS_Imax.label[0] = "I max (A)";
		mtk_BMS_Imax.label[1] = "��� ���. (�)";
		mtk_BMS_tImax.label[0] = "Time I max (Sec)";
		mtk_BMS_tImax.label[1] = "����� ���� (���)";
		mtk_BMS_Tmax.label[0] = "Temp. max (�C)";
		mtk_BMS_Tmax.label[1] = "����. ����. (�C)";
		mtk_BMS_Tmin.label[0] = "Temp min (�C)";
		mtk_BMS_Tmin.label[1] = "����. ���. (�C)";

		mtkAbout.label[0] = "About";
		mtkAbout.label[1] = "�� ����";

		mtkStopwatch.label[0] = "Stopwatch";
		mtkStopwatch.label[1] = "����������";
		mtkTimer.label[0] = "Timer";
		mtkTimer.label[1] = "������";
}
