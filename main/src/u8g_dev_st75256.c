/*

 u8g_dev_st75256.c

 Universal 8bit Graphics Library

 Copyright (c) 2011, olikraus@gmail.com
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this list
 of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice, this
 list of conditions and the following disclaimer in the documentation and/or other
 materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "u8g.h"

#define WIDTH 240
#define HEIGHT 160
#define PAGE_HEIGHT 8

static const uint8_t u8g_dev_st75256_init_seq[] PROGMEM = {
		U8G_ESC_CS(0), /* disable chip */
		U8G_ESC_RST(1), /* hardware reset. Min 1 ms */
		U8G_ESC_DLY(1), // Delay max 1 ms
		U8G_ESC_CS(1), /* enable chip */

		U8G_ESC_ADR(0),
		0x30, // EXT=0
		0x94, // Sleep Out
		0x31, // EXT=1

		0xD7, // Autoread disable
		U8G_ESC_ADR(1),
		0x9F, //

		U8G_ESC_ADR(0),
		0x32, // Analog set
		U8G_ESC_ADR(1),
		0x00, // OSC Frequency adjustment
		0x9F, // Frequency on booster capacitors -> 6KHz
		0x9F, // Bias = 1/11

		U8G_ESC_ADR(0),
		0x20, // Настройки оттенков серого
		U8G_ESC_ADR(1),
		0x01, //
		0x02, //
		0x05, //
		0x07, //
		0x09, //
		0x0b, //
		0x0d, //
		0x10, //
		0x11, //
		0x13, //
		0x15, //
		0x17, //
		0x19, //
		0x1B, //
		0x1D, //
		0x1F, //

		U8G_ESC_ADR(0),
		0x30, // EXT1 = 0, EXT0 = 0 "Расширенные инструкции"
		0x75, // Установить адрес страницы
		U8G_ESC_ADR(1),
		0x00, // Главный адрес: YS=0X00
		0x14, // Последний адрес страницы: YE = 0x1F один раз в четыре актов, первый 0-3 Поведение 0, 124 до 127 Поведение 31 (31 = 0x1f)

		U8G_ESC_ADR(0),
		0x15, // Установить адрес столбца
		U8G_ESC_ADR(1),
		0x00, // Начальный адрес столбца: XS = 0
		0xFF, // Адрес последнего столбца: XE = 256 (0xFF)

		U8G_ESC_ADR(0),
		0xBC, // Направление сканирования
		U8G_ESC_ADR(1),
		0x01, // MX.MY=Normal
		0xA6, //

		U8G_ESC_ADR(0),
		0x0C, // Выбор формата данных, 0x0C младший - старший D0-D7, 0x08 старший - младший D7-D0

		0xCA, // Настройка отображения
		U8G_ESC_ADR(1),
		0x00, // Установить частоту привода CL: CLD = 0
		0x9F, // Рабочий цикл: Duty=160
		0x20, // N линия по борьбе значительным: Nline=off

		U8G_ESC_ADR(0),
		0xF0, // Режим отображения
		U8G_ESC_ADR(1),
		0x10, // Если установлено в 0x11: 4 уровней серого указанием режима выбора, если установлен в 0x10: представляет выбрать черно-белый режим

		U8G_ESC_ADR(0),
		0x81, // Установить контраст, "0x81" негибкой, а затем двух данных может быть изменен, но "после первого тримминга грубой" Этот порядок Замерзание
		U8G_ESC_ADR(1),
		0x3F, // Обрезать Контраст, регулируемый диапазон 0x00 ~ 0x3f в общей сложности 64
		0x03, // Грубый контраст, регулируемый диапазон 0x00 0x07 ~, в общей сложности восемь

		U8G_ESC_ADR(0),
		0x20, // Управление питанием
		U8G_ESC_ADR(1),
		0x0B, // D0=regulator ; D1=follower ; D3=booste, on:1 off:0

		U8G_ESC_DLY(1), // Delay 0,1 ms

		U8G_ESC_ADR(0),
		0xAF, // Открыть Показать

		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st75256_data_start[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x30,
		0x5C, /*  */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st75256_sleep_on[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x28, /* Display off */
		0x22, /* all pixel off */
		0x10, /* set power save mode */
		U8G_ESC_CS(0), /* disable chip, bugfix 12 nov 2014 */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st75256_sleep_off[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x29,/* display on */
		0x11, //Sleep out
		U8G_ESC_DLY(50), /* delay 50 ms */
		U8G_ESC_CS(0), /* disable chip, bugfix 12 nov 2014 */
		U8G_ESC_END /* end of sequence */
};

/*******************************************************************************
 *Minimal RAM driver
 ******************************************************************************/
uint8_t u8g_dev_st75256_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		for (i = 0; i < (WIDTH * HEIGHT) / 2; i++) {
			u8g_WriteByte(u8g, dev, 0x00); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
//		u8g_SetAddress(u8g, dev, 0); /* cmd mode */
//		u8g_WriteByte(u8g, dev, 0x15); //Set Column Address
//		u8g_SetAddress(u8g, dev, 1); /* data mode */
//		u8g_WriteByte(u8g, dev, 0x00); //Set start x
//		u8g_WriteByte(u8g, dev, 0xF0); //Set end x
		u8g_SetAddress(u8g, dev, 0); /* cmd mode */
		u8g_WriteByte(u8g, dev, 0x75); //Set Page Address
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, pb->p.page); // Set start page
		u8g_WriteByte(u8g, dev, 0x14);	// Set end page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		if (u8g_pb_WriteBuffer(pb, u8g, dev) == 0)
			return 0;
		u8g_SetChipSelect(u8g, dev, 0);
	}
		break;
	case U8G_DEV_MSG_CONTRAST:
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* instruction mode */
		u8g_WriteByte(u8g, dev, 0xC0);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, *(uint8_t *) arg);
		u8g_WriteByte(u8g, dev, 1);
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_off);
		return 1;
	}
	return u8g_dev_pb8v1_base_fn(u8g, dev, msg, arg);
}

/*******************************************************************************
 *Speed driver 4x
 ******************************************************************************/
uint8_t u8g_dev_st75256_4x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		for (i = 0; i < (WIDTH * HEIGHT) / 2; i++) {
			u8g_WriteByte(u8g, dev, 0x00); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		uint8_t y, i;
		uint8_t *ptr;
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
		y = pb->p.page_y0;
		ptr = pb->buf;
		u8g_SetAddress(u8g, dev, 0); /* cmd mode */
		u8g_WriteByte(u8g, dev, 0x2B); /* Row Address Setting */
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, y);
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, 0x9F);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		for (i = 0; i < 32; i++) {
			u8g_WriteSequence(u8g, dev, WIDTH / 8, ptr);
			ptr += WIDTH / 8;
			y++;
		}
		u8g_SetChipSelect(u8g, dev, 0);
	}
		break;
	case U8G_DEV_MSG_CONTRAST:
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* instruction mode */
		u8g_WriteByte(u8g, dev, 0xC0);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, *(uint8_t *) arg);
		u8g_WriteByte(u8g, dev, 1);
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_off);
		return 1;
	}
	return u8g_dev_pb32h1_base_fn(u8g, dev, msg, arg);
}

/*******************************************************************************
 *Ultra speed driver 20x
 ******************************************************************************/
uint8_t u8g_dev_st75256_20x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start);
		u8g_SetAddress(u8g, dev, 1); // data mode
		for (i = 0; i < (WIDTH * HEIGHT) / 2; i++) {
			u8g_WriteByte(u8g, dev, 0x00); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		uint8_t i;
		uint8_t *ptr;
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
		ptr = pb->buf;
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start);
		u8g_SetAddress(u8g, dev, 1); // data mode 
		for (i = 0; i < 160; i++) {
			u8g_WriteSequence(u8g, dev, WIDTH / 8, ptr);
			ptr += WIDTH / 8;
		}
		u8g_SetChipSelect(u8g, dev, 0);
	}
		break;
	case U8G_DEV_MSG_CONTRAST:
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* instruction mode */
		u8g_WriteByte(u8g, dev, 0xC0);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, *(uint8_t *) arg);
		u8g_WriteByte(u8g, dev, 1);
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_off); //Fail. Need reinit
		return 1;
	}
	return u8g_dev_pb32h1_base_fn(u8g, dev, msg, arg);
}

U8G_PB_DEV(u8g_dev_st75256_hw_spi, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_st75256_fn, U8G_COM_HW_SPI);

uint8_t u8g_dev_st75256_4x_buf[WIDTH * 4] U8G_NOCOMMON;
u8g_pb_t u8g_dev_st75256_4x_pb = { { 32, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st75256_4x_buf };
u8g_dev_t u8g_dev_st75256_4x_hw_spi = { u8g_dev_st75256_4x_fn, &u8g_dev_st75256_4x_pb, U8G_COM_HW_SPI };

uint8_t u8g_dev_st75256_20x_buf[WIDTH * HEIGHT / 8] U8G_NOCOMMON;
//Как-то не используется---------------------
//                                          |
//Размер вертикальной области отрисовки     |
//одного буффера в пикселях-----------      |
//                                   |      |
u8g_pb_t u8g_dev_st75256_20x_pb = { { 160, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st75256_20x_buf };
u8g_dev_t u8g_dev_st75256_20x_hw_spi = { u8g_dev_st75256_20x_fn, &u8g_dev_st75256_20x_pb, U8G_COM_HW_SPI };
