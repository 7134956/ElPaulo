#include "mtk.h"
#include "string.h"

char *raceParams[2][7] = { { "Max. speed", "Expense", "Travel time", "Discharge", "To charging", "Odograph", "Aver. speed" },
		{ "����. ����", "��. ������", "����� ����", "���������", "�� �������", "���. ������", "����. ����" } };

char *month[2][12] = { { "January", "February", "March", "April", "May", "June", "July", "August", " September", "October", "November", " December" },
		{"������", "�������", "����", "������", "���", "����", "����", "������", " ��������", "�������", "������", " �������" } };

char *days[2][7] = { { "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" }, { "��", "��", "��", "��", "��", "��", "��" } };

extern mtk_element_t mtkPassword,	//������
		mtkDisplay,		//���� ��������� �������
		mtkContrast,	//��������� �������������
		mtkAutoBright,	//��������� ����������� �������
		mtkMenuOdometr,	//���� ��������� ��������
		mtkCircle,		//��������� ����� ���������� ������
		mtkOdometr,	//���������� ���������� � ��
		mtkPin,			//������ ���������� ������
		mtkLang,
		mtkDateTime, mtkDate, mtkTime,
		mtkPower, mtkSecInTime, mtkSleepDisplayOff, mtkSleepSec, mtkAbout;

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
		mtkDateTime.label[0] = "Date, Time";
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
		mtkSleepDisplayOff.label[0] = "Display off";
		mtkSleepDisplayOff.label[1] = "����. �����";
		mtkAbout.label[0] = "About";
		mtkAbout.label[1] = "�� ����";
}
