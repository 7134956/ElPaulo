#ifndef _SHOWTRACKS_H_
#define _SHOWTRACKS_H_

#include "config.h"
#include "mtk.h"

#define HIST_MORE 0
#define HIST_PREV 1
#define HIST_NEXT 2

typedef struct racelistAll_t { //64 байта рамер
	uint8_t items;	//Количество элементов в списке заездов всего (0 - 64)
	uint8_t item;	//Номер первого отображаемого элемента (0 - 63)
	uint8_t select;	//Выбранный элемент (1 - 64)
	uint8_t index;	//Первый элемент кольцевого буффера списка заездов (0 - 5)
	uint8_t histCell; //Номер ячейки для заезда в EEPROM (Указывает на номер ячейки элемента перед первым элементом колцефого буффера)
	uint16_t startTime[6];	//Время старта (hh*100+mm)
	uint16_t startDate[6];	//Дата старта (mm*100+dd)
	uint32_t distance[6];	//Пройденное расстояние в миллиметрах (4294.967295)km
	uint16_t adres[6];		//Расположение найденого элемента в EEPROM
} racelistAll_t;

void showtracks(mtk_t *);
void histReadInit(void);
void loadTrackItems(uint8_t);
void trackExit(void);

#endif /* _SHOWTRACKS_H_ */
