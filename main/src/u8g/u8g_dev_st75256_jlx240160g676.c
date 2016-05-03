#include "u8g.h"

#define CMD 0
#define DAT 1

#define WIDTH 240
#define HEIGHT 160
#define PAGE_HEIGHT 8

static const uint8_t u8g_dev_st75256_init_seq[] PROGMEM = {
		U8G_ESC_CS(0),	/* disable chip */
		U8G_ESC_RST(1),	/* hardware reset. Min 1 ms */
		U8G_ESC_DLY(1),	/* Delay max 1 ms */
		U8G_ESC_CS(1),	/* enable chip */

		U8G_ESC_ADR(CMD),
		0x30, // EXT=0

		0x94, // Sleep Out

		0x31, // EXT=1

//		0xD7, // Autoread disable
//		U8G_ESC_ADR(DAT),
//		0x9F, //

		U8G_ESC_ADR(CMD),
		0x32, // Analog set
		U8G_ESC_ADR(DAT),
		0x00, /* OSC Frequency adjustment */
		0x01, /* Booster Efficiency =Level 1 */
		0x03, /* Bias = 1/11 */

//		U8G_ESC_ADR(CMD), /* Booster Level x10 */
//		0x51,
//		U8G_ESC_ADR(DAT),
//		0xFB,
		
//		U8G_ESC_ADR(CMD),
//		0x20, // Gray levels tune for 4-gray mode
//		U8G_ESC_ADR(DAT),
//		0x01, //
//		0x02, //
//		0x05, //
//		0x07, //
//		0x09, //
//		0x0b, //
//		0x0d, //
//		0x10, //
//		0x11, //
//		0x13, //
//		0x15, //
//		0x17, //
//		0x19, //
//		0x1B, //
//		0x1D, //
//		0x1F, //

		U8G_ESC_ADR(CMD),
		0x30, // EXT1 = 0, EXT0 = 0 "Расширенные инструкции"
		0x75, // Установить адрес страницы
		U8G_ESC_ADR(DAT),
		0x01, // Start page
		0x15, // End page

		U8G_ESC_ADR(CMD),
		0x15, // Установить адрес столбца
		U8G_ESC_ADR(DAT),
		0x00, // Начальный адрес столбца: XS = 0
		0xEF, // Адрес последнего столбца: XE = 240 (0xF0)

		U8G_ESC_ADR(CMD),
		0xBC, // Направление сканирования
		U8G_ESC_ADR(DAT),
		0x01, // MX.MY=Normal
		0xA6, //

		U8G_ESC_ADR(CMD),
		0x08, // Выбор формата данных, 0x0C младший - старший D0-D7, 0x08 старший - младший D7-D0

		0xCA, // Настройка отображения
		U8G_ESC_ADR(DAT),
		0x00, // Установить частоту привода CL: CLD = 0
		0x9F, // Рабочий цикл: Duty=160
		0x20, // N линия по борьбе значительным: Nline=off

		U8G_ESC_ADR(CMD),
		0xF0, // Режим отображения
		U8G_ESC_ADR(DAT),
		0x10, // 0x11: 4-lever.  0x10: 2-level

		U8G_ESC_ADR(CMD),
		0x81, // Установить контраст, "0x81" негибкой, а затем двух данных может быть изменен, но "после первого тримминга грубой" Этот порядок Замерзание
		U8G_ESC_ADR(DAT),
		0x3F, // Точный контраст, регулируемый диапазон 0x00 ~ 0x3f в общей сложности 64
		0x03, // Грубый контраст, регулируемый диапазон 0x00 0x07 ~, в общей сложности восемь

		U8G_ESC_ADR(CMD),
		0x20, // Управление питанием
		U8G_ESC_ADR(DAT),
		0x0B, // D0=regulator ; D1=follower ; D3=booste, on:1 off:0

		U8G_ESC_DLY(1), // Delay 0,1 ms

		U8G_ESC_ADR(CMD),
		0xAF, // Открыть Показать

		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st75256_data_start1[] PROGMEM = {
		U8G_ESC_ADR(CMD), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
//		0x30, /* Set extension command 1 */
//		0x15, //Set Column Address
//		U8G_ESC_ADR(DAT), /* data mode */
//		0x00, //Set start x
//		0xEF, //Set end x
//		U8G_ESC_ADR(CMD), /* instruction mode */
		0x75, //Set Page Address
		U8G_ESC_ADR(DAT), /* data mode */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st75256_data_start2[] PROGMEM = {
		0x15,// Set end page
		U8G_ESC_ADR(CMD), /* instruction mode */
		0x5C, /* Write data to DDRAM */
		U8G_ESC_ADR(DAT),
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st75256_sleep_on[] PROGMEM = {
		U8G_ESC_ADR(CMD), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x95, /* Sleep in mode */
		U8G_ESC_CS(0), /* disable chip */
		U8G_ESC_END /* end of sequence */
};

static const uint8_t u8g_dev_st75256_sleep_off[] PROGMEM = {
		U8G_ESC_ADR(CMD), /* instruction mode */
		U8G_ESC_CS(1), /* enable chip */
		0x94, /* Sleep out mode */
		U8G_ESC_DLY(50), /* delay 50 ms */
		U8G_ESC_CS(0), /* disable chip */
		U8G_ESC_END /* end of sequence */
};

/*******************************************************************************
 * Driver for jlx240160g-676
 ******************************************************************************/
uint8_t u8g_dev_st75256_jlx240160g676_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		for (i = 0; i < (WIDTH * HEIGHT/PAGE_HEIGHT); i++) {
			u8g_WriteByte(u8g, dev, 0x00); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1 + pb->p.page); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		if (u8g_pb_WriteBuffer(pb, u8g, dev) == 0)
			return 0;
		u8g_SetChipSelect(u8g, dev, 0);
	}
		break;
	case U8G_DEV_MSG_CONTRAST:
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* instruction mode */
		u8g_WriteByte(u8g, dev, 0x81);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, (*(uint8_t *) arg % 64));
		u8g_WriteByte(u8g, dev, 3 + (*(uint8_t *) arg / 64));
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
 * jlx240160g-676 4x peed driver. More ram.
 ******************************************************************************/
uint8_t u8g_dev_st75256_jlx240160g676_4x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		for (i = 0; i < (WIDTH * HEIGHT/PAGE_HEIGHT); i++) {
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
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1 + y); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		for (i = 0; i < 4; i++) {
			u8g_WriteSequence(u8g, dev, WIDTH, ptr);
			ptr += WIDTH;
			y++;
		}
		u8g_SetChipSelect(u8g, dev, 0);
	}
		break;
	case U8G_DEV_MSG_CONTRAST:
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* instruction mode */
		u8g_WriteByte(u8g, dev, 0x81);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, (*(uint8_t *) arg % 64));
		u8g_WriteByte(u8g, dev, 3 + (*(uint8_t *) arg / 64));
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_off);
		return 1;
	}
	return u8g_dev_pb32v1_base_fn(u8g, dev, msg, arg);
}

/*******************************************************************************
 * jlx240160g-676 20x speed driver. Full frame buffer.
 ******************************************************************************/
uint8_t u8g_dev_st75256_jlx240160g676_20x_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		for (i = 0; i < (WIDTH * HEIGHT/PAGE_HEIGHT); i++) {
			u8g_WriteByte(u8g, dev, 0x00); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		uint8_t *ptr;
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
		ptr = pb->buf;
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		for (i = 0; i < HEIGHT/PAGE_HEIGHT; i++) {
			u8g_WriteSequence(u8g, dev, WIDTH, ptr);
			ptr += WIDTH;
		}
		u8g_SetChipSelect(u8g, dev, 0);
	}
		break;
	case U8G_DEV_MSG_CONTRAST:
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* instruction mode */
		u8g_WriteByte(u8g, dev, 0x81);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, (*(uint8_t *) arg % 64));
		u8g_WriteByte(u8g, dev, 3 + (*(uint8_t *) arg / 64));
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_off);
		return 1;
	}
	return u8g_dev_pb160v1_base_fn(u8g, dev, msg, arg);
}

/*******************************************************************************
 * jlx240160g-676 20x DMA. Full frame buffer.
 ******************************************************************************/
uint8_t u8g_dev_st75256_jlx240160g676_20x_dma_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg) {
	uint16_t i;
	switch (msg) {
	case U8G_DEV_MSG_INIT:
		u8g_InitCom(u8g, dev, NULL);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_init_seq);
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		for (i = 0; i < (WIDTH * HEIGHT/PAGE_HEIGHT); i++) {
			u8g_WriteByte(u8g, dev, 0x00); //Заполняем дисплей белым
		}
		break;
	case U8G_DEV_MSG_PAGE_NEXT: {
		uint8_t *ptr;
		u8g_pb_t *pb = (u8g_pb_t *) (dev->dev_mem);
		u8g_SetChipSelect(u8g, dev, 1);
		ptr = pb->buf;
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start1);
		u8g_WriteByte(u8g, dev, 1); // Set start page
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_data_start2);
		u8g_WriteSequence(u8g, dev, WIDTH/PAGE_HEIGHT, ptr);
	}
		break;
	case U8G_DEV_MSG_CONTRAST:
		u8g_SetChipSelect(u8g, dev, 1);
		u8g_SetAddress(u8g, dev, 0); /* instruction mode */
		u8g_WriteByte(u8g, dev, 0x81);
		u8g_SetAddress(u8g, dev, 1); /* data mode */
		u8g_WriteByte(u8g, dev, (*(uint8_t *) arg % 64));
		u8g_WriteByte(u8g, dev, 3 + (*(uint8_t *) arg / 64));
		u8g_SetChipSelect(u8g, dev, 0);
		return 1;
	case U8G_DEV_MSG_SLEEP_ON:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_on);
		return 1;
	case U8G_DEV_MSG_SLEEP_OFF:
		u8g_WriteEscSeqP(u8g, dev, u8g_dev_st75256_sleep_off);
		return 1;
	}
	return u8g_dev_pb160v1_base_fn(u8g, dev, msg, arg);
}

U8G_PB_DEV(u8g_dev_st75256_jlx240160g676_hw_spi, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_st75256_jlx240160g676_fn, U8G_COM_HW_SPI);

uint8_t u8g_dev_st75256_jlx240160g676_4x_buf[WIDTH * 4] U8G_NOCOMMON;
u8g_pb_t u8g_dev_st75256_jlx240160g676_4x_pb = { { 32, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st75256_jlx240160g676_4x_buf };
u8g_dev_t u8g_dev_st75256_jlx240160g676_4x_hw_spi = { u8g_dev_st75256_jlx240160g676_4x_fn, &u8g_dev_st75256_jlx240160g676_4x_pb, U8G_COM_HW_SPI };

uint8_t u8g_dev_st75256_jlx240160g676_20x_buf[WIDTH * HEIGHT / 8] U8G_NOCOMMON;
u8g_pb_t u8g_dev_st75256_jlx240160g676_20x_pb = { { 160, HEIGHT, 0, 0, 0 }, WIDTH, u8g_dev_st75256_jlx240160g676_20x_buf };
u8g_dev_t u8g_dev_st75256_jlx240160g676_20x_hw_spi = { u8g_dev_st75256_jlx240160g676_20x_fn, &u8g_dev_st75256_jlx240160g676_20x_pb, U8G_COM_HW_SPI };
u8g_dev_t u8g_dev_st75256_jlx240160g676_20x_dma_hw_spi = { u8g_dev_st75256_jlx240160g676_20x_dma_fn, &u8g_dev_st75256_jlx240160g676_20x_pb, U8G_COM_HW_SPI };
