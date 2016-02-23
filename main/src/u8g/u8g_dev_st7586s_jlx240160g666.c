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
		U8G_ESC_ADR(0),
		0x11, // Sleep Out

		/*
		//OK
		U8G_ESC_ADR(0),
		0x28, // Display OFF
		U8G_ESC_DLY(50),
		*/

		//OK
		U8G_ESC_ADR(0), 0xC0, // Vop Яркость дисплея
		U8G_ESC_ADR(1),
		0x40,
		0x01,

		/*
		U8G_ESC_ADR(0),
		0xC7, //Vop Offset
		U8G_ESC_ADR(1),
		0x01,
		*/

		//OK
		U8G_ESC_ADR(0),
		0xC3, // BIAS = 1/14
		U8G_ESC_ADR(1),
		0x00,

		/*
		//OK By default
		U8G_ESC_ADR(0),
		0xC4, // Booster = x8
		U8G_ESC_ADR(1),
		0x07,
		*/

		//OK
		U8G_ESC_ADR(0),
		0xD0, // Enable Analog Circuit
		U8G_ESC_ADR(1),
		0x1D,

		/*
		U8G_ESC_ADR(0),
		0xB5, // N-Line = 0
		U8G_ESC_ADR(1),
		0x00,
		*/

		//OK Select mode
		U8G_ESC_ADR(0), 0x39, // 0x39 Monochrome mode. 0x38 - gray Mode

		//OK
		U8G_ESC_ADR(0),
		0x3A, // Enable DDRAM Interface
		U8G_ESC_ADR(1),
		0x02, //2 пикселя из байта

		//OK
		U8G_ESC_ADR(0),
		0x36, // Scan Direction Setting
		U8G_ESC_ADR(1),
		0xc0, //COM:C160--C1   SEG: SEG384-SEG1
		//0x40,   //COM:C1--C160   SEG: SEG384-SEG1
		//0x80,   //COM:C160--C1   SEG: SEG1-SEG384

		/*
		//OK By default
		U8G_ESC_ADR(0),
		0xB0, // Duty Setting. Обрезка экрана
		U8G_ESC_ADR(1),
		0x0F,//1/16
		0x9F, //1/160
		*/

		/*
		//OK By default
		U8G_ESC_ADR(0),
		0x20, // Display Inversion OFF
		*/

		U8G_ESC_ADR(0),
		0x2A, // Column Address Setting
		U8G_ESC_ADR(1),
		0x00, // SEG0 -> SEG240
		0x08, // SEG8*3=24
		0x00,
		0x7f, // SEG128*3=384  seg x(dont use)  seg n  seg n

		0x2B, // Row Address Setting
		0x00, // COM0 -> COM160
		0x00, //
		0x00, //
		0x9F, //HEIGHT-1

		/*
		//OK By default
		U8G_ESC_ADR(0),
		0xB1, //Термокомпенсация
		U8G_ESC_ADR(1),
		0x15,
		0x15,
		0x15,
		0x15,
		*/

		/*
		U8G_ESC_ADR(0),
		0xB1, //Линия старта сканирования
		U8G_ESC_ADR(1),
		0x00, // Линия старта сканирования COM0
		*/

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
		U8G_ESC_CS(0),
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st7586s_sleep_off[] PROGMEM = {
		U8G_ESC_ADR(0), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x29,/* display on */
		0x11, //Sleep out
		U8G_ESC_DLY(50), /* delay 50 ms */
		U8G_ESC_CS(0),
		U8G_ESC_END /* end of sequence */
};

/*******************************************************************************
 *Driver for jlx240160g-666
 ******************************************************************************/
uint8_t u8g_dev_st7586s_jlx240160g666_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, 0);
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
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st7586s_sleep_off);//Need reinit after sleep out
		return 1;
	}
	return u8g_dev_pb8h1_base_fn(u8g, dev, msg, arg);
}

/*******************************************************************************
 * jlx240160g-666 4x peed driver. More ram.
 ******************************************************************************/
uint8_t u8g_dev_st7586s_jlx240160g666_4x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, 0);
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
 * jlx240160g-666 20x speed driver. Full frame buffer.
 ******************************************************************************/
uint8_t u8g_dev_st7586s_jlx240160g666_20x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, 0);
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

U8G_PB_DEV(u8g_dev_st7586s_jlx240160g666_hw_spi, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_st7586s_jlx240160g666_fn, U8G_COM_HW_SPI);

uint8_t u8g_dev_st7586s_jlx240160g666_4x_buf[WIDTH * 4] U8G_NOCOMMON;
u8g_pb_t u8g_dev_st7586s_jlx240160g666_4x_pb = { { 32, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st7586s_jlx240160g666_4x_buf };
u8g_dev_t u8g_dev_st7586s_jlx240160g666_4x_hw_spi = { u8g_dev_st7586s_jlx240160g666_4x_fn, &u8g_dev_st7586s_jlx240160g666_4x_pb, U8G_COM_HW_SPI };

uint8_t u8g_dev_st7586s_jlx240160g666_20x_buf[WIDTH * HEIGHT / 8] U8G_NOCOMMON;
u8g_pb_t u8g_dev_st7586s_jlx240160g666_20x_pb = { { 160, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st7586s_jlx240160g666_20x_buf };
u8g_dev_t u8g_dev_st7586s_jlx240160g666_20x_hw_spi = { u8g_dev_st7586s_jlx240160g666_20x_fn, &u8g_dev_st7586s_jlx240160g666_20x_pb, U8G_COM_HW_SPI };
