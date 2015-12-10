/*

 u8g_dev_st7669a.c

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

static const uint8_t u8g_dev_st7669a_init_seq[] PROGMEM = {
		U8G_ESC_CS(0), /* disable chip */
		U8G_ESC_RST(1), /* do reset low pulse with (1*16)+2 milliseconds */
		U8G_ESC_DLY(60), // Delay 120 ms
		U8G_ESC_DLY(60), //
		U8G_ESC_DLY(60), //
		U8G_ESC_CS(1), /* enable chip */

		U8G_ESC_ADR(0), 0x01, // Soft reset
		U8G_ESC_DLY(60), // Delay 120 ms
		U8G_ESC_DLY(60), //

		//-----------disable autoread + Manual read once -------------------------------
		U8G_ESC_ADR(0), 0xd7, // Auto Load Set
		U8G_ESC_ADR(1), 0xdf, // Auto Load Disable
		U8G_ESC_ADR(0), 0xE0, // EE Read/write mode
		U8G_ESC_ADR(1), 0x00, // Set read mode
		U8G_ESC_DLY(50), // Delay 10ms
		U8G_ESC_ADR(0), 0xE3, // Read active
		U8G_ESC_DLY(50), // Delay 20ms
		U8G_ESC_ADR(0), 0xE1, // Cancel control
		//---------------------------------- Sleep OUT ---------------------------------------------
		U8G_ESC_ADR(0), 0x11, // Sleep Out
		U8G_ESC_ADR(0), 0x28, // Display OFF
		U8G_ESC_DLY(60), U8G_ESC_DLY(60),
		//--------------------------------Vop setting------------------------------------------------
		U8G_ESC_ADR(0), 0xC0, //Set Vop by initial Module
		U8G_ESC_ADR(1), 0x04, //Vop = 14V
		U8G_ESC_ADR(1), 0x01, // base on Module
		//----------------------------Set Register------------------------------------------
		U8G_ESC_ADR(0), 0xC3, // Bias select
		U8G_ESC_ADR(1), 0x05, // 1/9 Bias, base on Module
		U8G_ESC_ADR(0), 0xC4, // Setting Booster times
		U8G_ESC_ADR(1), 0x07, // Booster X 8
		U8G_ESC_ADR(0), 0xC5, // Booster eff
		U8G_ESC_ADR(1), 0x21, // BE = 0x01 (Level 2)
		U8G_ESC_ADR(0), 0xCB, // Vg with booster x2 control
		U8G_ESC_ADR(1), 0x01, // Vg from Vdd2
		U8G_ESC_ADR(0), 0xCC, // ID1 = 00
		U8G_ESC_ADR(1), 0x00, //
		U8G_ESC_ADR(0), 0xCE, // ID3 = 00
		U8G_ESC_ADR(1), 0x00, U8G_ESC_ADR(0), 0xB7, // COM/SEG Direction for glass //
		U8G_ESC_ADR(1), 0x48, // Setting by LCD module
//		Downloaded from Elcodis.com electronic components distributor
//		ST7669
//		Ver 1.3a 206/216 3/2/2009
		U8G_ESC_ADR(0), 0xD0, // Analog circuit setting
		U8G_ESC_ADR(1), 0x1D, //
		U8G_ESC_ADR(0), 0xB5, // N-Line
		U8G_ESC_ADR(1), 0x8D, // Non-RST, 14-line inversion
		U8G_ESC_ADR(0), 0xD7, //Auto read Set
		U8G_ESC_ADR(1), 0x9F, //OTP Disable

		U8G_ESC_ADR(0), 0xB4, //PTL Mode Select
		U8G_ESC_ADR(1), 0x18, //PTLMOD  Normal Mode
		U8G_ESC_ADR(0), 0x3A, // Color mode = 65k
		U8G_ESC_ADR(1), 0x05, //
		U8G_ESC_ADR(0), 0x36, // Memory Access Control //
		U8G_ESC_ADR(1), 0xC8, // Setting by LCD module

		U8G_ESC_ADR(0), 0xB0, // Duty = 160 duty
		U8G_ESC_ADR(1), 0x9F,

		U8G_ESC_ADR(0), 0x20, // Display Inversion OFF

		U8G_ESC_ADR(0), 0xF7, // command for temp sensitivity.
		U8G_ESC_ADR(0), 0x06, //
//		1. Set Gamma table for Module, please refer spec ch 9.1.73.
//		2. Set Temp compensation for Module, please refer spec ch 9.1.71.

		U8G_ESC_ADR(0), 0x2A, // COL//
		U8G_ESC_ADR(1), 0x00, // 0~127
		U8G_ESC_ADR(1), 0x00, U8G_ESC_ADR(1), 0x00, U8G_ESC_ADR(1), 0x7F,

		U8G_ESC_ADR(0), 0x2B, // Page //
		U8G_ESC_ADR(1), 0x00, // 0~159
		U8G_ESC_ADR(1), 0x00, U8G_ESC_ADR(1), 0x00, U8G_ESC_ADR(1), 0x9F,

		U8G_ESC_ADR(0), 0x29, // Display ON
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st7669a_data_start[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x2C, /* cmd write display data to ram */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st7669a_sleep_on[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x28, /* Display off */
//		0x22, /* all pixel off */
		0x10, /* set power save mode */
		U8G_ESC_CS(0), /* disable chip, bugfix 12 nov 2014 */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st7669a_sleep_off[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x11, /* display on */
		U8G_ESC_DLY(50), /* delay 50 ms */
		U8G_ESC_CS(0), /* disable chip, bugfix 12 nov 2014 */
		U8G_ESC_END /* end of sequence */
};

/*******************************************************************************
 *Mini RAM driver
 ******************************************************************************/
uint8_t u8g_dev_st7669a_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, U8G_SPI_CLK_CYCLE_400NS);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_init_seq);
		for (i = 0; i < (WIDTH * HEIGHT); i++) {
			u8g_WriteByte(u8g, dev, 0); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_STOP:
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* cmd mode */
		u8g_WriteByte(u8g, dev, 0x2B); // Row Address Setting
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, 8 * pb->p.page);
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, 0x9F);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_data_start);
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
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_sleep_off);
		return 1;
	}
	return u8g_dev_pb32h1_base_fn(u8g, dev, msg, arg);
}
/*******************************************************************************
 *Speed driver
 ******************************************************************************/
uint8_t u8g_dev_st7669a_4x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg,
		void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, U8G_SPI_CLK_CYCLE_400NS);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_init_seq);
		for (i = 0; i < (WIDTH * HEIGHT); i++) {
			u8g_WriteByte(u8g, dev, 0); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_STOP:
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		uint8_t y, i;
		uint8_t *ptr;
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
		y = pb->p.page_y0;
		ptr = pb->buf;
		u8g_SetAddress(u8g, dev, 0); /* cmd mode */
		u8g_WriteByte(u8g, dev, 0x2B); // Row Address Setting
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, y);
		u8g_WriteByte(u8g, dev, 0x00);
		u8g_WriteByte(u8g, dev, 0x9F);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_data_start);
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
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7669a_sleep_off);
		return 1;
	}
	return u8g_dev_pb32h1_base_fn(u8g, dev, msg, arg);
}

#define QWIDTH (WIDTH*4)
uint8_t u8g_dev_st7669a_4x_buf[QWIDTH] U8G_NOCOMMON;
u8g_pb_t u8g_dev_st7669a_4x_pb = { { 32, HEIGHT, 0, 0, 0 }, WIDTH,
		u8g_dev_st7669a_4x_buf };
u8g_dev_t u8g_dev_st7669a_4x_hw_spi = { u8g_dev_st7669a_4x_fn,
		&u8g_dev_st7669a_4x_pb, U8G_COM_HW_SPI };
U8G_PB_DEV(u8g_dev_st7669a_hw_spi, WIDTH, HEIGHT, PAGE_HEIGHT,
		u8g_dev_st7669a_fn, U8G_COM_HW_SPI);
