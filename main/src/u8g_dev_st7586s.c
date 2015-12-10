/*

 u8g_dev_st7586s.c

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

//BW mode
//0b00011000, //Ч Б
//0b00000000, //Б Б
//0b00011000, //Ч Б
//0b11000000, //Б Ч
//0b11011000, //Ч Ч
//0b10010000, //Ч Ч
//0b01001000, //Б Б

//Gray mode
//0b00011000, //Ч Б
//0b00000000, //Б Б
//0b00011000, //Ч Б
//0b11000000, //Б Ч
//0b11011000, //Ч Ч
//0b10010000, //ТС ТС
//0b01001000, //СС СС

#include "u8g.h"

#define WIDTH 240
#define HEIGHT 160
#define PAGE_HEIGHT 8

static const uint8_t u8g_dev_st7586s_init_seq[] PROGMEM = {
		U8G_ESC_CS(0), /* disable chip */
		//U8G_ESC_RST(1), /* hardware reset */
		U8G_ESC_DLY(60), // Delay 
		U8G_ESC_CS(1), /* enable chip */

		//No need
		//U8G_ESC_ADR(0), 0xD7, // Disable Auto Read
		//U8G_ESC_ADR(1), 0x9F,
		//U8G_ESC_ADR(0), 0xE0, // Enable OTP Read
		//U8G_ESC_ADR(1), 0x00,
		//U8G_ESC_DLY(10),
		//U8G_ESC_ADR(0), 0xE3, // OTP Up-Load
		//U8G_ESC_DLY(20),
		//U8G_ESC_ADR(0), 0xE1, // OTP Control Out

		U8G_ESC_ADR(0), 0x01, // Soft reset
		U8G_ESC_DLY(60), // Delay 120 ms
		//U8G_ESC_DLY(60),

		//OK
		U8G_ESC_ADR(0), 0x11, // Sleep Out

		//OK
		//U8G_ESC_ADR(0), 0x28, // Display OFF
		//U8G_ESC_DLY(50),

		//OK
		U8G_ESC_ADR(0), 0xC0, // Vop Яркость дисплея
		U8G_ESC_ADR(1), 0x40, U8G_ESC_ADR(1), 0x01,

		//U8G_ESC_ADR(0), 0xC7, //Vop Offset 
		//U8G_ESC_ADR(1), 0x01,

		//OK
		U8G_ESC_ADR(0), 0xC3, // BIAS = 1/14
		U8G_ESC_ADR(1), 0x00,

		//OK By default
		//U8G_ESC_ADR(0), 0xC4, // Booster = x8
		//U8G_ESC_ADR(1), 0x07,

		//OK
		U8G_ESC_ADR(0), 0xD0, // Enable Analog Circuit
		U8G_ESC_ADR(1), 0x1D,

		//U8G_ESC_ADR(0), 0xB5, // N-Line = 0
		//U8G_ESC_ADR(1), 0x00,

		//OK Select mode
		U8G_ESC_ADR(0), 0x39, // Monochrome Mode FIXME
		//U8G_ESC_ADR(0), 0x38, // Gray Mode

		//OK
		U8G_ESC_ADR(0), 0x3A, // Enable DDRAM Interface
		U8G_ESC_ADR(1), 0x02, //2 пикселя из байта

		//OK
		U8G_ESC_ADR(0), 0x36, // Scan Direction Setting
		U8G_ESC_ADR(1), 0xc0, //COM:C160--C1   SEG: SEG384-SEG1
		//U8G_ESC_ADR(1), 0x40,   //COM:C1--C160   SEG: SEG384-SEG1
		//U8G_ESC_ADR(1), 0x80,   //COM:C160--C1   SEG: SEG1-SEG384

		//OK By default
		//U8G_ESC_ADR(0), 0xB0, // Duty Setting. Обрезка экрана
		//U8G_ESC_ADR(1), 0x0F,//1/16
		//U8G_ESC_ADR(1), 0x9F, //1/160

		//OK By default
		//U8G_ESC_ADR(0), 0x20, // Display Inversion OFF

		U8G_ESC_ADR(0), 0x2A, // Column Address Setting
		U8G_ESC_ADR(1), 0x00, // SEG0 -> SEG240
		U8G_ESC_ADR(1), 0x08, // SEG8*3=24
		U8G_ESC_ADR(1), 0x00,	//
		U8G_ESC_ADR(1), 0x7f, // SEG128*3=384  seg x(dont use)  seg n  seg n

		U8G_ESC_ADR(0), 0x2B, // Row Address Setting
		U8G_ESC_ADR(1), 0x00, // COM0 -> COM160
		U8G_ESC_ADR(1), 0x00,	//
		U8G_ESC_ADR(1), 0x00,	//
		U8G_ESC_ADR(1), 0x9F,	//HEIGHT-1

		//OK By default
		//U8G_ESC_ADR(0), 0xB1, //Термокомпенсация
		//U8G_ESC_ADR(1), 0x15, //
		//U8G_ESC_ADR(1), 0x15,	//
		//U8G_ESC_ADR(1), 0x15,	//
		//U8G_ESC_ADR(1), 0x15,	//

		//U8G_ESC_ADR(0), 0xB1, //Линия старта сканирования
		//U8G_ESC_ADR(1), 0x00, // Линия старта сканирования COM0

		U8G_ESC_ADR(0), 0x29, // Display ON
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st7586s_data_start[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x2C, /* cmd write display data to ram */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st7586s_sleep_on[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x28, /* Display off */
		0x22, /* all pixel off */
		0x10, /* set power save mode */
		U8G_ESC_CS(0), /* disable chip, bugfix 12 nov 2014 */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st7586s_sleep_off[] PROGMEM = {
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
uint8_t u8g_dev_st7586s_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_data_start);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		for (i = 0; i < (WIDTH * HEIGHT) / 2; i++) {
			u8g_WriteByte(u8g, dev, 0x00); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* cmd mode */
		u8g_WriteByte(u8g, dev, 0x2B); /* Row Address Setting */
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, 8 * pb->p.page);
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, 0x9F);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_data_start);
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
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_sleep_off);
		return 1;
	}
	return u8g_dev_pb32h1_base_fn(u8g, dev, msg, arg);
}

/*******************************************************************************
 *Speed driver 4x
 ******************************************************************************/
uint8_t u8g_dev_st7586s_4x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_data_start);
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
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_data_start);
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
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_sleep_off);
		return 1;
	}
	return u8g_dev_pb32h1_base_fn(u8g, dev, msg, arg);
}

/*******************************************************************************
 *Ultra speed driver 20x
 ******************************************************************************/
uint8_t u8g_dev_st7586s_20x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_data_start);
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
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_data_start);
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
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_sleep_off); //Fail. Need reinit
		return 1;
	}
	return u8g_dev_pb32h1_base_fn(u8g, dev, msg, arg);
}

U8G_PB_DEV(u8g_dev_st7586s_hw_spi, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_st7586s_fn, U8G_COM_HW_SPI);

uint8_t u8g_dev_st7586s_4x_buf[WIDTH * 4] U8G_NOCOMMON;
u8g_pb_t u8g_dev_st7586s_4x_pb = { { 32, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st7586s_4x_buf };
u8g_dev_t u8g_dev_st7586s_4x_hw_spi = { u8g_dev_st7586s_4x_fn, &u8g_dev_st7586s_4x_pb, U8G_COM_HW_SPI };

uint8_t u8g_dev_st7586s_20x_buf[WIDTH * HEIGHT / 8] U8G_NOCOMMON;
//Как-то не используется---------------------
//                                          |
//Размер вертикальной области отрисовки     |
//одного буффера в пикселях-----------      |
//                                   |      |
u8g_pb_t u8g_dev_st7586s_20x_pb = { { 160, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st7586s_20x_buf };
u8g_dev_t u8g_dev_st7586s_20x_hw_spi = { u8g_dev_st7586s_20x_fn, &u8g_dev_st7586s_20x_pb, U8G_COM_HW_SPI };
