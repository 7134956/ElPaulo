/* Макро для использования двоичного формата чисел */

#define _BITSET(bits) \
  ((uint16_t) ( \
  (bits % 010) | \
  (bits / 010 % 010) << 1 | \
  (bits / 0100 % 010) << 2 | \
  (bits / 01000 % 010) << 3 | \
  (bits / 010000 % 010) << 4 | \
  (bits / 0100000 % 010) << 5 | \
  (bits / 01000000 % 010) << 6 | \
  (bits / 010000000 % 010) << 7 | \
  (bits / 0100000000 % 010) << 8 | \
  (bits / 01000000000 % 010) << 9 | \
  (bits / 010000000000 % 010) << 10 | \
  (bits / 0100000000000 % 010) << 11 | \
  (bits / 01000000000000 % 010) << 12 | \
  (bits / 010000000000000 % 010) << 13 | \
  (bits / 0100000000000000 % 010) << 14 | \
  (bits / 01000000000000000 % 010) << 15))
#define BIN(bits) _BITSET(0##bits)



/*
  Fontname: elpaulo32n
  Copyright: Created with Fony 1.4.6
  Capital A Height: 0, '1' Height: 30
  Calculated Max Values w=20 h=30 x= 5 y=14 dx=24 dy= 0 ascent=30 len=90
  Font Bounding box     w=24 h=31 x= 0 y=-1
  Calculated Min Values           x= 0 y= 0 dx= 0 dy= 0
  Pure Font   ascent =30 descent= 0
  X Font      ascent =31 descent=-1
  Max Font    ascent =30 descent= 0
*/
#include "u8g.h"
const u8g_fntpgm_uint8_t u8g_font_elpaulo32n[776] U8G_FONT_SECTION("u8g_font_elpaulo32n") = {
  0x03, 0x18, 0x1F, 0x00, 0xFF, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x5F, 0x00, 0x1E, 0x00, 0x1F, 0xFF, //Descriptor

17, 17, 23, 21, 2, 8, //BBX

0x79, 0x9E, //Mask

//Bitmap: " "
0x01, 0xC0, 0x00,
0x03, 0xE0, 0x00,
0x7F, 0xFF, 0x00,
0xFF, 0xFF, 0x80,
0x7F, 0xFF, 0x00,
0x03, 0xE0, 0x00,
0x01, 0xC0, 0x00,

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "!"

16, 5, 7, 20, 2, 14, //BBX

0x60, //Mask

//Bitmap: """
0x7F, 0xFE,
0xFF, 0xFF,
0x7F, 0xFE,

5, 5, 4, 9, 2, 0, //BBX

0x60, //Mask

//Bitmap: "#"
0x70, 0xF8,
0x70,

18, 30, 55, 22, 2, 0, //BBX

0x2A, 0xAA, 0xAA, 0xA0, //Mask

//Bitmap: "$"
0x00, 0x07, 0x80,
0x00, 0x07, 0xC0,
0x00, 0x0F, 0xC0,
0x00, 0x1F, 0x80,
0x00, 0x3F, 0x00,
0x00, 0x7E, 0x00,
0x00, 0xFC, 0x00,
0x01, 0xF8, 0x00,
0x03, 0xF0, 0x00,
0x07, 0xE0, 0x00,
0x0F, 0xC0, 0x00,
0x1F, 0x80, 0x00,
0x3F, 0x00, 0x00,
0x7E, 0x00, 0x00,
0xFC, 0x00, 0x00,
0xF8, 0x00, 0x00,
0x78, 0x00, 0x00,

20, 30, 37, 24, 2, 0, //BBX

0x23, 0xFF, 0xFE, 0x20, //Mask

//Bitmap: "%"
0x0F, 0xFF, 0x00,
0x3F, 0xFF, 0xC0,
0x7F, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0xFC, 0x03, 0xF0,
0xF8, 0x01, 0xF0,
0xFC, 0x03, 0xF0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xE0,
0x3F, 0xFF, 0xC0,
0x0F, 0xFF, 0x00,

12, 30, 32, 24, 5, 0, //BBX

0x00, 0x07, 0xFF, 0xF8, //Mask

//Bitmap: "&"
0x01, 0xF0,
0x03, 0xF0,
0x07, 0xF0,
0x0F, 0xF0,
0x1F, 0xF0,
0x3F, 0xF0,
0x7F, 0xF0,
0xFF, 0xF0,
0xFD, 0xF0,
0xF9, 0xF0,
0xF1, 0xF0,
0xE1, 0xF0,
0xC1, 0xF0,
0x01, 0xF0,

20, 30, 70, 24, 2, 0, //BBX

0x21, 0xC0, 0x00, 0x78, //Mask

//Bitmap: "'"
0x0F, 0xFF, 0x00,
0x3F, 0xFF, 0xC0,
0x7F, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0xFC, 0x03, 0xF0,
0xF8, 0x01, 0xF0,
0x00, 0x01, 0xF0,
0x00, 0x03, 0xF0,
0x00, 0x07, 0xF0,
0x00, 0x0F, 0xE0,
0x00, 0x1F, 0xE0,
0x00, 0x3F, 0xC0,
0x00, 0x7F, 0x80,
0x00, 0xFF, 0x00,
0x01, 0xFE, 0x00,
0x03, 0xFC, 0x00,
0x07, 0xF8, 0x00,
0x0F, 0xF0, 0x00,
0x1F, 0xE0, 0x00,
0x3F, 0xC0, 0x00,
0x7F, 0x80, 0x00,
0xFF, 0xFF, 0xF0,

20, 30, 67, 24, 2, 0, //BBX

0x21, 0x8A, 0x1C, 0x20, //Mask

//Bitmap: "("
0x0F, 0xFF, 0x00,
0x3F, 0xFF, 0xC0,
0x7F, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0xFC, 0x03, 0xF0,
0xF8, 0x01, 0xF0,
0x00, 0x01, 0xF0,
0x00, 0x03, 0xF0,
0x00, 0x07, 0xF0,
0x03, 0xFF, 0xE0,
0x03, 0xFF, 0xC0,
0x03, 0xFF, 0xE0,
0x00, 0x07, 0xE0,
0x00, 0x03, 0xF0,
0x00, 0x01, 0xF0,
0xF8, 0x03, 0xF0,
0xFC, 0x07, 0xF0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xE0,
0x3F, 0xFF, 0xC0,
0x0F, 0xFF, 0x00,

20, 30, 40, 24, 2, 0, //BBX

0xAA, 0xAA, 0x9E, 0xF8, //Mask

//Bitmap: ")"
0x00, 0x7F, 0x80,
0x00, 0xFF, 0x80,
0x01, 0xFF, 0x80,
0x03, 0xFF, 0x80,
0x07, 0xEF, 0x80,
0x0F, 0xCF, 0x80,
0x1F, 0x8F, 0x80,
0x3F, 0x0F, 0x80,
0x7E, 0x0F, 0x80,
0xFC, 0x0F, 0x80,
0xFF, 0xFF, 0xF0,
0x00, 0x0F, 0x80,

20, 30, 46, 24, 2, 0, //BBX

0xF7, 0xE2, 0x3C, 0x20, //Mask

//Bitmap: "*"
0xFF, 0xFF, 0xF0,
0xF8, 0x00, 0x00,
0xFF, 0xFF, 0x00,
0xFF, 0xFF, 0xC0,
0xFF, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0x00, 0x03, 0xF0,
0x00, 0x01, 0xF0,
0xF8, 0x01, 0xF0,
0xFC, 0x03, 0xF0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xE0,
0x3F, 0xFF, 0xC0,
0x0F, 0xFF, 0x00,

20, 30, 58, 24, 2, 0, //BBX

0x21, 0xE2, 0x3E, 0x20, //Mask

//Bitmap: "+"
0x0F, 0xFF, 0x00,
0x3F, 0xFF, 0xC0,
0x7F, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0xFC, 0x03, 0xF0,
0xF8, 0x01, 0xF0,
0xF8, 0x00, 0x00,
0xFF, 0xFF, 0x00,
0xFF, 0xFF, 0xC0,
0xFF, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0xFC, 0x03, 0xF0,
0xF8, 0x01, 0xF0,
0xFC, 0x03, 0xF0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xE0,
0x3F, 0xFF, 0xC0,
0x0F, 0xFF, 0x00,

20, 30, 46, 24, 2, 0, //BBX

0xF2, 0xAA, 0xAA, 0xA8, //Mask

//Bitmap: ","
0xFF, 0xFF, 0xF0,
0x00, 0x03, 0xF0,
0x00, 0x07, 0xE0,
0x00, 0x0F, 0xC0,
0x00, 0x1F, 0x80,
0x00, 0x3F, 0x00,
0x00, 0x7E, 0x00,
0x00, 0xFC, 0x00,
0x01, 0xF8, 0x00,
0x03, 0xF0, 0x00,
0x07, 0xE0, 0x00,
0x0F, 0xC0, 0x00,
0x1F, 0x80, 0x00,
0x3F, 0x00, 0x00,

20, 30, 58, 24, 2, 0, //BBX

0x23, 0xC4, 0x9E, 0x20, //Mask

//Bitmap: "-"
0x07, 0xFE, 0x00,
0x1F, 0xFF, 0x80,
0x3F, 0xFF, 0xC0,
0x7F, 0xFF, 0xE0,
0x7E, 0x07, 0xE0,
0x7C, 0x03, 0xE0,
0x7E, 0x07, 0xE0,
0x3F, 0xFF, 0xC0,
0x1F, 0xFF, 0x80,
0x3F, 0xFF, 0xC0,
0x7F, 0xFF, 0xE0,
0xFC, 0x03, 0xF0,
0xF8, 0x01, 0xF0,
0xFC, 0x03, 0xF0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xE0,
0x3F, 0xFF, 0xC0,
0x0F, 0xFF, 0x00,

20, 30, 58, 24, 2, 0, //BBX

0x23, 0xE2, 0x3C, 0x20, //Mask

//Bitmap: "."
0x0F, 0xFF, 0x00,
0x3F, 0xFF, 0xC0,
0x7F, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0xFC, 0x03, 0xF0,
0xF8, 0x01, 0xF0,
0xFC, 0x03, 0xF0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xF0,
0x3F, 0xFF, 0xF0,
0x0F, 0xFF, 0xF0,
0x00, 0x01, 0xF0,
0xF8, 0x01, 0xF0,
0xF8, 0x03, 0xF0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xE0,
0x3F, 0xFF, 0xC0,
0x0F, 0xFF, 0x00,

5, 20, 10, 9, 2, 4, //BBX

0x67, 0xFC, 0xC0, //Mask

//Bitmap: "/"
0x70, 0xF8,
0x70,
0x00,
0x70,
0xF8,
0x70,

0xFF, //Empty glyph 1
0xFF, //Empty glyph 2
0xFF, //Empty glyph 3
0xFF, //Empty glyph 4
0xFF, //Empty glyph 5
0xFF, //Empty glyph 6
0xFF, //Empty glyph 7
0xFF, //Empty glyph 8
0xFF, //Empty glyph 9
0xFF, //Empty glyph 10
0xFF, //Empty glyph 11
0xFF, //Empty glyph 12
0xFF, //Empty glyph 13
0xFF, //Empty glyph 14
0xFF, //Empty glyph 15
0xFF, //Empty glyph 16
0xFF, //Empty glyph 17
0xFF, //Empty glyph 18
0xFF, //Empty glyph 19
0xFF, //Empty glyph 20
0xFF, //Empty glyph 21
0xFF, //Empty glyph 22
0xFF, //Empty glyph 23
0xFF, //Empty glyph 24
0xFF, //Empty glyph 25
0xFF, //Empty glyph 26
0xFF, //Empty glyph 27
0xFF, //Empty glyph 28
0xFF, //Empty glyph 29
0xFF, //Empty glyph 30
0xFF, //Empty glyph 31
0xFF, //Empty glyph 32
0xFF, //Empty glyph 33
0xFF, //Empty glyph 34
0xFF, //Empty glyph 35
0xFF, //Empty glyph 36
20, 4, 10, 24, 2, 0, //BBX

0x40, //Mask

//Bitmap: "T"
0x7F, 0xFF, 0xE0,
0xFF, 0xFF, 0xF0,
0x7F, 0xFF, 0xE0,

};

/*
  Fontname: elpaulo20
  Copyright: Public domain font.  Share and enjoy.
  Capital A Height: 13, '1' Height: 13
  Calculated Max Values w=16 h=16 x= 4 y=13 dx=18 dy= 0 ascent=15 len=30
  Font Bounding box     w=18 h=19 x= 0 y=-4
  Calculated Min Values           x= 0 y=-4 dx= 0 dy= 0
  Pure Font   ascent =13 descent=-4
  X Font      ascent =16 descent=-4
  Max Font    ascent =15 descent=-4
*/
#include "u8g.h"
const u8g_fntpgm_uint8_t u8g_font_elpaulo20[3424] U8G_FONT_SECTION("u8g_font_elpaulo32n") = {
  0x03, 0x12, 0x13, 0x00, 0xFC, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0x0F, 0xFC, 0x10, 0xFC, //Descriptor

8, 13, 9, 10, 1, 0, //BBX

0x56, 0xA0, //Mask

//Bitmap: "*"
0xE7, 0x81,
0x00,
0x81,
0x00,
0x81,
0xE7,

14, 14, 28, 18, 1, 0, //BBX

0x02, 0x00, //Mask

//Bitmap: "+"
0x07, 0x00,
0x1D, 0x80,
0x32, 0xB8,
0x62, 0x80,
0x42, 0x80,
0xC2, 0x9C,
0xC2, 0x80,
0xC2, 0x9C,
0x42, 0x80,
0x62, 0x80,
0x32, 0xB8,
0x1D, 0x80,
0x07, 0x00,

14, 14, 30, 18, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: ","
0x15, 0x50,
0x3F, 0xF8,
0x55, 0x54,
0x40, 0x04,
0x40, 0x34,
0x7F, 0x34,
0x88, 0x84,
0x82, 0xB4,
0x84, 0xB4,
0xC9, 0x84,
0x84, 0xB4,
0x82, 0xB4,
0x88, 0x84,
0x7F, 0x78,

14, 14, 30, 18, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "-"
0x80, 0x0C,
0xC0, 0x08,
0x80, 0x18,
0x80, 0x10,
0xC4, 0x30,
0x8E, 0x20,
0x8A, 0x20,
0xDB, 0x60,
0x91, 0xC0,
0x90, 0x80,
0xD0, 0x00,
0x80, 0x00,
0x92, 0x48,
0xFF, 0xFC,

14, 14, 30, 18, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "."
0x01, 0xE0,
0x03, 0xC0,
0x07, 0x80,
0x07, 0x04,
0x07, 0x0C,
0x07, 0x1C,
0x0F, 0xFC,
0x1F, 0xF8,
0x3B, 0xF0,
0x77, 0x00,
0xEE, 0x00,
0xDC, 0x00,
0xF8, 0x00,
0x70, 0x00,

14, 14, 20, 18, 1, 0, //BBX

0x1D, 0x20, //Mask

//Bitmap: "/"
0x7F, 0xF8,
0xC0, 0x0C,
0x83, 0x04,
0x87, 0x84,
0x83, 0x04,
0x80, 0x04,
0x83, 0x04,
0xC0, 0x0C,
0x7F, 0xF8,

14, 14, 28, 18, 1, 0, //BBX

0x02, 0x00, //Mask

//Bitmap: "0"
0x3C, 0x00,
0x66, 0xF0,
0x42, 0x00,
0x42, 0xF0,
0x5A, 0x00,
0x5A, 0xF0,
0x5A, 0x00,
0xDB, 0x40,
0xBD, 0x18,
0xBD, 0x24,
0xBD, 0x20,
0xC3, 0x24,
0x7E, 0x18,

14, 8, 17, 18, 1, 3, //BBX

0x00, //Mask

//Bitmap: "1"
0xFF, 0xF0,
0xFF, 0x90,
0xFF, 0x1C,
0xFE, 0x14,
0xFC, 0x14,
0xF8, 0x1C,
0xF0, 0x10,
0xFF, 0xF0,

14, 14, 20, 18, 1, 0, //BBX

0x25, 0xA0, //Mask

//Bitmap: "2"
0x7F, 0xF8,
0xC0, 0x0C,
0x87, 0x84,
0x80, 0x04,
0x8F, 0x84,
0x87, 0x84,
0x8F, 0xC4,
0xC0, 0x0C,
0x7F, 0xF8,

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "3"

8, 16, 17, 16, 4, 255, //BBX

0x01, 0x00, //Mask

//Bitmap: "4"
0x80, 0xC0,
0xE0,
0xF0,
0xF8,
0xFC,
0xFE,
0xFF,
0xFE,
0xFC,
0xF8,
0xF0,
0xE0,
0xC0,
0x80,

8, 16, 17, 16, 4, 255, //BBX

0x01, 0x00, //Mask

//Bitmap: "5"
0x01, 0x03,
0x07,
0x0F,
0x1F,
0x3F,
0x7F,
0xFF,
0x7F,
0x3F,
0x1F,
0x0F,
0x07,
0x03,
0x01,

16, 8, 17, 16, 0, 3, //BBX

0x00, //Mask

//Bitmap: "6"
0x01, 0x80,
0x03, 0xC0,
0x07, 0xE0,
0x0F, 0xF0,
0x1F, 0xF8,
0x3F, 0xFC,
0x7F, 0xFE,
0xFF, 0xFF,

16, 8, 17, 16, 0, 3, //BBX

0x00, //Mask

//Bitmap: "7"
0xFF, 0xFF,
0x7F, 0xFE,
0x3F, 0xFC,
0x1F, 0xF8,
0x0F, 0xF0,
0x07, 0xE0,
0x03, 0xC0,
0x01, 0x80,

12, 14, 20, 16, 2, 0, //BBX

0x1B, 0x08, //Mask

//Bitmap: "8"
0x1F, 0x80,
0x3F, 0xC0,
0x70, 0xE0,
0x60, 0x60,
0xFF, 0xF0,
0xF9, 0xF0,
0xF0, 0xF0,
0xF9, 0xF0,
0xFF, 0xF0,

14, 14, 16, 16, 1, 0, //BBX

0x1F, 0xC0, //Mask

//Bitmap: "9"
0x7F, 0xF8,
0xFF, 0xFC,
0xE0, 0x1C,
0xC0, 0x0C,
0xE0, 0x1C,
0xFF, 0xFC,
0x7F, 0xF8,

14, 14, 30, 16, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: ":"
0x7F, 0xF8,
0xFF, 0xFC,
0xE0, 0x1C,
0xC0, 0x3C,
0xC0, 0x7C,
0xC0, 0xEC,
0xF1, 0xCC,
0xFB, 0x8C,
0xDF, 0x0C,
0xCE, 0x0C,
0xC4, 0x0C,
0xE0, 0x1C,
0xFF, 0xFC,
0x7F, 0xF8,

8, 2, 2, 12, 2, 0, //BBX

0x80, //Mask

//Bitmap: ";"
0xDB,
0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "<"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "="

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: ">"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "?"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "@"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "A"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "B"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "C"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "D"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "E"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "F"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "G"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "H"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "I"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "J"

2, 13, 5, 6, 2, 0, //BBX

0xFF, 0x90, //Mask

//Bitmap: "K"
0xC0, 0x00,
0xC0,

6, 4, 3, 10, 2, 9, //BBX

0xC0, //Mask

//Bitmap: "L"
0xCC, 0x48,

9, 11, 12, 10, 1, 1, //BBX

0xCC, 0xC0, //Mask

//Bitmap: "M"
0x1B, 0x00,
0x7F, 0x80,
0x36, 0x00,
0xFF, 0x00,
0x6C, 0x00,

8, 13, 11, 10, 1, 0, //BBX

0x19, 0x80, //Mask

//Bitmap: "N"
0x18, 0x7E,
0xDB,
0xD8,
0x7E,
0x1B,
0xDB,
0x7E,
0x18,

9, 12, 22, 10, 1, 0, //BBX

0x0A, 0x00, //Mask

//Bitmap: "O"
0x73, 0x00,
0xDB, 0x00,
0xDE, 0x00,
0x76, 0x00,
0x0C, 0x00,
0x18, 0x00,
0x37, 0x00,
0x3D, 0x80,
0x6D, 0x80,
0x67, 0x00,

9, 13, 24, 10, 1, 0, //BBX

0x60, 0x00, //Mask

//Bitmap: "P"
0x38, 0x00,
0x6C, 0x00,
0x78, 0x00,
0x30, 0x00,
0x70, 0x00,
0xD8, 0x00,
0xCD, 0x80,
0xC7, 0x00,
0xC6, 0x00,
0xEF, 0x00,
0x79, 0x80,

2, 5, 3, 10, 4, 8, //BBX

0xE0, //Mask

//Bitmap: "Q"
0xC0, 0x80,

5, 13, 9, 10, 3, 0, //BBX

0x2F, 0x40, //Mask

//Bitmap: "R"
0x18, 0x30,
0x60,
0xC0,
0x60,
0x30,
0x18,

5, 13, 9, 10, 2, 0, //BBX

0x2F, 0x40, //Mask

//Bitmap: "S"
0xC0, 0x60,
0x30,
0x18,
0x30,
0x60,
0xC0,

8, 7, 6, 10, 1, 3, //BBX

0x84, //Mask

//Bitmap: "T"
0x66, 0x3C,
0xFF,
0x3C,
0x66,

8, 8, 4, 10, 1, 3, //BBX

0xD6, //Mask

//Bitmap: "U"
0x18, 0xFF,
0x18,

3, 4, 3, 10, 3, 255, //BBX

0xC0, //Mask

//Bitmap: "V"
0x60, 0xC0,

8, 2, 2, 10, 1, 6, //BBX

0x80, //Mask

//Bitmap: "W"
0xFF,
2, 3, 2, 6, 2, 0, //BBX

0xC0, //Mask

//Bitmap: "X"
0xC0,
7, 12, 8, 10, 2, 0, //BBX

0xAA, 0xA0, //Mask

//Bitmap: "Y"
0x06, 0x0C,
0x18,
0x30,
0x60,
0xC0,

8, 13, 9, 10, 1, 0, //BBX

0x1F, 0x80, //Mask

//Bitmap: "Z"
0x3C, 0x7E,
0xE7,
0xC3,
0xE7,
0x7E,
0x3C,

4, 13, 6, 10, 3, 0, //BBX

0x2F, 0xF0, //Mask

//Bitmap: "["
0x30, 0x70,
0xF0,
0x30,

8, 13, 13, 10, 1, 0, //BBX

0x20, 0x10, //Mask

//Bitmap: "\"
0x7E, 0xFF,
0xC3,
0x03,
0x07,
0x0E,
0x1C,
0x38,
0x70,
0xE0,
0xFF,

8, 13, 12, 10, 1, 0, //BBX

0x21, 0x40, //Mask

//Bitmap: "]"
0x7E, 0xFF,
0xC3,
0x03,
0x0E,
0x0F,
0x03,
0xC3,
0xFF,
0x7E,

8, 13, 12, 10, 1, 0, //BBX

0x00, 0xB0, //Mask

//Bitmap: "^"
0x03, 0x07,
0x0F,
0x1F,
0x3B,
0x73,
0xE3,
0xC3,
0xFF,
0x03,

8, 13, 11, 10, 1, 0, //BBX

0xA1, 0x80, //Mask

//Bitmap: "_"
0xFF, 0xC0,
0xFE,
0xFF,
0xC3,
0x03,
0xC3,
0xFF,
0x7E,

8, 13, 11, 10, 1, 0, //BBX

0x03, 0xC0, //Mask

//Bitmap: "`"
0x7E, 0xFF,
0xC3,
0xC0,
0xFE,
0xFF,
0xC3,
0xFF,
0x7E,

8, 13, 14, 10, 1, 0, //BBX

0x80, 0x00, //Mask

//Bitmap: "a"
0xFF, 0xC3,
0x03,
0x07,
0x06,
0x0E,
0x0C,
0x1C,
0x18,
0x38,
0x30,
0x70,

8, 13, 10, 10, 1, 0, //BBX

0x31, 0xC0, //Mask

//Bitmap: "b"
0x7E, 0xFF,
0xC3,
0x7E,
0xFF,
0xC3,
0xFF,
0x7E,

8, 13, 11, 10, 1, 0, //BBX

0x38, 0x80, //Mask

//Bitmap: "c"
0x7E, 0xFF,
0xC3,
0xFF,
0x7F,
0x03,
0xC3,
0xFF,
0x7E,

2, 10, 5, 6, 2, 0, //BBX

0xDD, 0x80, //Mask

//Bitmap: "d"
0xC0, 0x00,
0xC0,

3, 11, 6, 7, 1, 255, //BBX

0xDD, 0x80, //Mask

//Bitmap: "e"
0x60, 0x00,
0x60,
0xC0,

7, 13, 15, 10, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "f"
0x02, 0x06,
0x0C,
0x18,
0x30,
0x60,
0xC0,
0x60,
0x30,
0x18,
0x0C,
0x06,
0x02,

8, 7, 4, 10, 1, 3, //BBX

0xB4, //Mask

//Bitmap: "g"
0xFF, 0x00,
0xFF,

7, 13, 15, 10, 2, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "h"
0x80, 0xC0,
0x60,
0x30,
0x18,
0x0C,
0x06,
0x0C,
0x18,
0x30,
0x60,
0xC0,
0x80,

8, 13, 12, 10, 1, 0, //BBX

0x10, 0x90, //Mask

//Bitmap: "i"
0x3C, 0x7E,
0xE7,
0xC3,
0x07,
0x0E,
0x1C,
0x18,
0x00,
0x18,

8, 13, 13, 10, 1, 0, //BBX

0x06, 0x00, //Mask

//Bitmap: "j"
0x3C, 0x66,
0xC3,
0xCF,
0xDF,
0xDB,
0xDE,
0xCC,
0xC0,
0x63,
0x3E,

8, 13, 8, 10, 1, 0, //BBX

0x2C, 0xF0, //Mask

//Bitmap: "k"
0x18, 0x3C,
0x66,
0xC3,
0xFF,
0xC3,

8, 13, 11, 10, 1, 0, //BBX

0x30, 0xC0, //Mask

//Bitmap: "l"
0xF8, 0xCC,
0xC6,
0xCC,
0xFC,
0xC6,
0xC3,
0xC6,
0xFC,

8, 13, 9, 10, 1, 0, //BBX

0x1F, 0x80, //Mask

//Bitmap: "m"
0x3C, 0x66,
0xC3,
0xC0,
0xC3,
0x66,
0x3C,

8, 13, 7, 10, 1, 0, //BBX

0x3F, 0xC0, //Mask

//Bitmap: "n"
0xFC, 0xC6,
0xC3,
0xC6,
0xFC,

8, 13, 7, 10, 1, 0, //BBX

0x79, 0xE0, //Mask

//Bitmap: "o"
0xFF, 0xC0,
0xFC,
0xC0,
0xFF,

8, 13, 6, 10, 1, 0, //BBX

0x79, 0xF0, //Mask

//Bitmap: "p"
0xFF, 0xC0,
0xFC,
0xC0,

8, 13, 10, 10, 1, 0, //BBX

0x19, 0xC0, //Mask

//Bitmap: "q"
0x3C, 0x66,
0xC3,
0xC0,
0xCF,
0xC3,
0x67,
0x3D,

8, 13, 5, 10, 1, 0, //BBX

0xF9, 0xF0, //Mask

//Bitmap: "r"
0xC3, 0xFF,
0xC3,

8, 13, 5, 10, 1, 0, //BBX

0x7F, 0xE0, //Mask

//Bitmap: "s"
0xFF, 0x18,
0xFF,

9, 13, 12, 10, 1, 0, //BBX

0x7F, 0x40, //Mask

//Bitmap: "t"
0x1F, 0x80,
0x06, 0x00,
0xC6, 0x00,
0x6C, 0x00,
0x38, 0x00,

8, 13, 9, 10, 1, 0, //BBX

0xA9, 0x50, //Mask

//Bitmap: "u"
0xC3, 0xC6,
0xCC,
0xF8,
0xCC,
0xC6,
0xC3,

8, 13, 4, 10, 1, 0, //BBX

0xFF, 0xE0, //Mask

//Bitmap: "v"
0xC0, 0xFF,

8, 13, 7, 10, 1, 0, //BBX

0xA7, 0x70, //Mask

//Bitmap: "w"
0xC3, 0xE7,
0xFF,
0xDB,
0xC3,

8, 13, 9, 10, 1, 0, //BBX

0x55, 0x50, //Mask

//Bitmap: "x"
0xC3, 0xE3,
0xF3,
0xDB,
0xCF,
0xC7,
0xC3,

8, 13, 7, 10, 1, 0, //BBX

0x3F, 0xC0, //Mask

//Bitmap: "y"
0x3C, 0x66,
0xC3,
0x66,
0x3C,

8, 13, 8, 10, 1, 0, //BBX

0x38, 0xF0, //Mask

//Bitmap: "z"
0xFC, 0xC6,
0xC3,
0xC6,
0xFC,
0xC0,

8, 14, 10, 10, 1, 255, //BBX

0x3F, 0x00, //Mask

//Bitmap: "{"
0x3C, 0x66,
0xC3,
0xDB,
0xCF,
0x66,
0x3E,
0x03,

8, 13, 10, 10, 1, 0, //BBX

0x38, 0x50, //Mask

//Bitmap: "|"
0xFC, 0xC6,
0xC3,
0xC6,
0xFC,
0xCC,
0xC6,
0xC3,

8, 13, 13, 10, 1, 0, //BBX

0x10, 0x80, //Mask

//Bitmap: "}"
0x3C, 0x66,
0xC3,
0xC0,
0x60,
0x3C,
0x06,
0x03,
0xC3,
0x66,
0x3C,

8, 13, 4, 10, 1, 0, //BBX

0x7F, 0xF0, //Mask

//Bitmap: "~"
0xFF, 0x18,

8, 13, 5, 10, 1, 0, //BBX

0xFF, 0xC0, //Mask

//Bitmap: ""
0xC3, 0x66,
0x3C,

8, 13, 6, 10, 1, 0, //BBX

0xED, 0xB0, //Mask

//Bitmap: "Ђ"
0xC3, 0x66,
0x3C,
0x18,

8, 13, 6, 10, 1, 0, //BBX

0xF7, 0x50, //Mask

//Bitmap: "Ѓ"
0xC3, 0xDB,
0xE7,
0xC3,

8, 13, 9, 10, 1, 0, //BBX

0xA9, 0x50, //Mask

//Bitmap: "‚"
0xC3, 0x66,
0x3C,
0x18,
0x3C,
0x66,
0xC3,

8, 13, 6, 10, 1, 0, //BBX

0xAB, 0xF0, //Mask

//Bitmap: "ѓ"
0xC3, 0x66,
0x3C,
0x18,

8, 13, 11, 10, 1, 0, //BBX

0x49, 0x20, //Mask

//Bitmap: "„"
0xFF, 0x03,
0x06,
0x0C,
0x18,
0x30,
0x60,
0xC0,
0xFF,

6, 13, 5, 10, 2, 0, //BBX

0x7F, 0xE0, //Mask

//Bitmap: "…"
0xFC, 0xC0,
0xFC,

7, 12, 8, 10, 2, 0, //BBX

0xAA, 0xA0, //Mask

//Bitmap: "†"
0xC0, 0x60,
0x30,
0x18,
0x0C,
0x06,

6, 13, 5, 10, 2, 0, //BBX

0x7F, 0xE0, //Mask

//Bitmap: "‡"
0xFC, 0x0C,
0xFC,

8, 4, 5, 10, 1, 9, //BBX

0x00, //Mask

//Bitmap: "€"
0x18, 0x3C,
0x66,
0xC3,

9, 1, 2, 10, 1, 255, //BBX

//Mask

//Bitmap: "‰"
0xFF, 0x80,

4, 3, 4, 10, 3, 10, //BBX

0x00, //Mask

//Bitmap: "Љ"
0xC0, 0x60,
0x30,

8, 8, 7, 10, 1, 0, //BBX

0x0C, //Mask

//Bitmap: "‹"
0x3E, 0x63,
0x03,
0x7F,
0xC3,
0x7D,

8, 13, 8, 10, 1, 0, //BBX

0xF1, 0xC0, //Mask

//Bitmap: "Њ"
0xC0, 0xDC,
0xE6,
0xC3,
0xE6,
0xDC,

8, 8, 6, 10, 1, 0, //BBX

0x38, //Mask

//Bitmap: "Ќ"
0x3E, 0x63,
0xC0,
0x63,
0x3E,

8, 13, 8, 10, 1, 0, //BBX

0xF1, 0xC0, //Mask

//Bitmap: "Ћ"
0x03, 0x3B,
0x67,
0xC3,
0x67,
0x3B,

8, 8, 8, 10, 1, 0, //BBX

0x08, //Mask

//Bitmap: "Џ"
0x3C, 0x66,
0xC3,
0xFF,
0xC0,
0x63,
0x3E,

8, 13, 7, 10, 1, 0, //BBX

0x53, 0xF0, //Mask

//Bitmap: "ђ"
0x1E, 0x33,
0x30,
0xFC,
0x30,

8, 12, 10, 10, 1, 252, //BBX

0x30, 0xC0, //Mask

//Bitmap: "‘"
0x7D, 0xC7,
0xC6,
0x7C,
0xC0,
0x7E,
0xC3,
0x7E,

8, 13, 6, 10, 1, 0, //BBX

0xF1, 0xF0, //Mask

//Bitmap: "’"
0xC0, 0xDC,
0xE6,
0xC3,

8, 11, 7, 10, 1, 0, //BBX

0x8F, 0x80, //Mask

//Bitmap: "“"
0x18, 0x00,
0x78,
0x18,
0xFF,

7, 15, 8, 10, 2, 252, //BBX

0x8F, 0xD8, //Mask

//Bitmap: "”"
0x06, 0x00,
0x1E,
0x06,
0xC6,
0x7C,

8, 13, 11, 10, 1, 0, //BBX

0xF0, 0x00, //Mask

//Bitmap: "•"
0xC0, 0xC6,
0xCC,
0xD8,
0xF0,
0xF8,
0xCC,
0xC6,
0xC3,

8, 13, 5, 10, 1, 0, //BBX

0x7F, 0xE0, //Mask

//Bitmap: "–"
0x78, 0x18,
0xFF,

8, 8, 4, 10, 1, 0, //BBX

0x3E, //Mask

//Bitmap: "—"
0xB6, 0xFF,
0xDB,

8, 8, 4, 10, 1, 0, //BBX

0x3E, //Mask

//Bitmap: "�"
0xDC, 0xE6,
0xC3,

8, 8, 6, 10, 1, 0, //BBX

0x38, //Mask

//Bitmap: "™"
0x3C, 0x66,
0xC3,
0x66,
0x3C,

8, 12, 8, 10, 1, 252, //BBX

0x38, 0xE0, //Mask

//Bitmap: "љ"
0xDC, 0xE6,
0xC3,
0xE6,
0xDC,
0xC0,

8, 12, 8, 10, 1, 252, //BBX

0x38, 0xE0, //Mask

//Bitmap: "›"
0x3B, 0x67,
0xC3,
0x67,
0x3B,
0x03,

8, 8, 4, 10, 1, 0, //BBX

0x3E, //Mask

//Bitmap: "њ"
0xDE, 0x73,
0x60,

8, 8, 8, 10, 1, 0, //BBX

0x08, //Mask

//Bitmap: "ќ"
0x7E, 0xC3,
0xC0,
0x7E,
0x03,
0xC3,
0x7E,

8, 11, 7, 10, 1, 0, //BBX

0xCF, 0x00, //Mask

//Bitmap: "ћ"
0x30, 0xFC,
0x30,
0x33,
0x1E,

8, 8, 4, 10, 1, 0, //BBX

0xF8, //Mask

//Bitmap: "џ"
0xC3, 0x67,
0x3B,

8, 8, 5, 10, 1, 0, //BBX

0xAA, //Mask

//Bitmap: " "
0xC3, 0x66,
0x3C,
0x18,

8, 8, 5, 10, 1, 0, //BBX

0xD8, //Mask

//Bitmap: "Ў"
0xC3, 0xDB,
0xFF,
0x66,

8, 8, 8, 10, 1, 0, //BBX

0x10, //Mask

//Bitmap: "ў"
0xC3, 0x66,
0x3C,
0x18,
0x3C,
0x66,
0xC3,

8, 12, 9, 10, 1, 252, //BBX

0xF8, 0x00, //Mask

//Bitmap: "Ј"
0xC3, 0x67,
0x3B,
0x03,
0xC3,
0x66,
0x3C,

7, 8, 9, 10, 2, 0, //BBX

0x00, //Mask

//Bitmap: "¤"
0xFE, 0x06,
0x0C,
0x18,
0x30,
0x60,
0xC0,
0xFE,

8, 13, 7, 10, 1, 0, //BBX

0x79, 0xE0, //Mask

//Bitmap: "Ґ"
0x0F, 0x18,
0xF0,
0x18,
0x0F,

2, 13, 3, 10, 4, 0, //BBX

0xFF, 0xF0, //Mask

//Bitmap: "¦"
0xC0,
8, 13, 7, 10, 1, 0, //BBX

0x79, 0xE0, //Mask

//Bitmap: "§"
0xF0, 0x18,
0x0F,
0x18,
0xF0,

8, 3, 4, 10, 1, 10, //BBX

0x00, //Mask

//Bitmap: "Ё"
0x73, 0xDB,
0xCE,

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "©"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Є"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "«"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "¬"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "­"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "®"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Ї"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "°"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "±"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "І"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "і"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "ґ"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "µ"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "¶"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "·"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "ё"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "№"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "є"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "»"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "ј"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Ѕ"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "ѕ"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "ї"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "А"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Б"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "В"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Г"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Д"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Е"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Ж"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "З"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "И"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "Й"

0, 0, 0, 0, 0, 0, //BBX

//Mask

//Bitmap: "К"

2, 13, 5, 10, 4, 0, //BBX

0x9F, 0xF0, //Mask

//Bitmap: "Л"
0xC0, 0x00,
0xC0,

7, 12, 11, 10, 1, 0, //BBX

0x84, 0x20, //Mask

//Bitmap: "М"
0x18, 0x3C,
0x66,
0xC2,
0xC0,
0xC2,
0x66,
0x3C,
0x18,

9, 12, 18, 10, 1, 0, //BBX

0x53, 0x00, //Mask

//Bitmap: "Н"
0x1E, 0x00,
0x33, 0x00,
0x30, 0x00,
0xFC, 0x00,
0x30, 0x00,
0xF8, 0x00,
0xAD, 0x80,
0xE7, 0x00,

9, 9, 15, 10, 0, 1, //BBX

0x18, //Mask

//Bitmap: "О"
0x80, 0x80,
0xDD, 0x80,
0x7F, 0x00,
0x63, 0x00,
0x7F, 0x00,
0xDD, 0x80,
0x80, 0x80,

8, 11, 10, 10, 1, 0, //BBX

0x01, 0xC0, //Mask

//Bitmap: "П"
0x81, 0xC3,
0x66,
0x3C,
0x7E,
0x18,
0x7E,
0x18,

2, 13, 5, 10, 4, 0, //BBX

0xF6, 0xF0, //Mask

//Bitmap: "Р"
0xC0, 0x00,
0xC0,

8, 13, 15, 10, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "С"
0x3C, 0x66,
0xC6,
0x60,
0x78,
0xCC,
0x66,
0x33,
0x1E,
0x06,
0x63,
0x66,
0x3C,

8, 15, 9, 10, 1, 0, //BBX

0x1E, 0x78, //Mask

//Bitmap: "Т"
0x66, 0x00,
0xFF,
0xC0,
0xFC,
0xC0,
0xFF,

8, 11, 13, 10, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "У"
0x3C, 0x66,
0xC3,
0xBD,
0xA5,
0xA1,
0xA5,
0xBD,
0xC3,
0x66,
0x3C,

8, 9, 9, 10, 1, 4, //BBX

0x08, //Mask

//Bitmap: "Ф"
0x3E, 0x43,
0x03,
0x7F,
0xC3,
0x7D,
0x00,
0xFF,

9, 11, 24, 10, 0, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "Х"
0x04, 0x80,
0x0D, 0x80,
0x1B, 0x00,
0x36, 0x00,
0x6C, 0x00,
0xD8, 0x00,
0x6C, 0x00,
0x36, 0x00,
0x1B, 0x00,
0x0D, 0x80,
0x04, 0x80,

8, 4, 3, 10, 1, 4, //BBX

0xA0, //Mask

//Bitmap: "Ц"
0xFF, 0x03,

6, 1, 1, 10, 2, 6, //BBX

//Mask

//Bitmap: "Ч"
0xFC,
8, 11, 13, 10, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "Ш"
0x3C, 0x66,
0xC3,
0xBD,
0xA5,
0xBD,
0xA9,
0xAD,
0xC3,
0x66,
0x3C,

8, 1, 1, 10, 1, 13, //BBX

//Mask

//Bitmap: "Щ"
0xFF,
6, 6, 6, 10, 2, 7, //BBX

0x20, //Mask

//Bitmap: "Ъ"
0x30, 0x78,
0xCC,
0x78,
0x30,

8, 7, 6, 10, 1, 2, //BBX

0x90, //Mask

//Bitmap: "Ы"
0x18, 0xFF,
0x18,
0x00,
0xFF,

5, 7, 8, 10, 2, 6, //BBX

0x00, //Mask

//Bitmap: "Ь"
0x70, 0xD8,
0x18,
0x30,
0x60,
0xC0,
0xF8,

5, 7, 8, 10, 2, 6, //BBX

0x00, //Mask

//Bitmap: "Э"
0x70, 0xD8,
0x18,
0x30,
0x18,
0xD8,
0x70,

4, 3, 4, 10, 3, 10, //BBX

0x00, //Mask

//Bitmap: "Ю"
0x30, 0x60,
0xC0,

7, 10, 6, 10, 1, 253, //BBX

0xF1, 0x80, //Mask

//Bitmap: "Я"
0xC6, 0xEE,
0xFA,
0xC0,

8, 13, 7, 10, 1, 0, //BBX

0x33, 0xF0, //Mask

//Bitmap: "а"
0x7F, 0xFF,
0xFB,
0x7B,
0x1B,

3, 3, 2, 10, 4, 5, //BBX

0xC0, //Mask

//Bitmap: "б"
0xE0,
8, 11, 11, 10, 1, 0, //BBX

0x81, 0x00, //Mask

//Bitmap: "в"
0x66, 0x00,
0x3C,
0x66,
0xC3,
0xFF,
0xC0,
0x63,
0x3E,

4, 7, 5, 10, 2, 6, //BBX

0x38, //Mask

//Bitmap: "г"
0x60, 0xE0,
0x60,
0xF0,

7, 9, 8, 10, 1, 4, //BBX

0x30, //Mask

//Bitmap: "д"
0x38, 0x6C,
0xC6,
0x6C,
0x38,
0x00,
0xFE,

9, 11, 24, 10, 1, 0, //BBX

0x00, 0x00, //Mask

//Bitmap: "е"
0x90, 0x00,
0xD8, 0x00,
0x6C, 0x00,
0x36, 0x00,
0x1B, 0x00,
0x0D, 0x80,
0x1B, 0x00,
0x36, 0x00,
0x6C, 0x00,
0xD8, 0x00,
0x90, 0x00,

8, 12, 13, 10, 1, 1, //BBX

0x00, 0x20, //Mask

//Bitmap: "ж"
0x40, 0xC0,
0x41,
0x42,
0xE4,
0x08,
0x12,
0x26,
0x4A,
0x9E,
0x02,

8, 12, 14, 10, 1, 1, //BBX

0x00, 0x00, //Mask

//Bitmap: "з"
0x40, 0xC0,
0x41,
0x42,
0xE4,
0x08,
0x16,
0x29,
0x41,
0x82,
0x04,
0x0F,

8, 12, 13, 10, 1, 1, //BBX

0x00, 0x20, //Mask

//Bitmap: "и"
0xE0, 0x10,
0x61,
0x12,
0xE4,
0x08,
0x12,
0x26,
0x4A,
0x9F,
0x02,

8, 13, 10, 10, 1, 0, //BBX

0x98, 0xC0, //Mask

//Bitmap: "й"
0x18, 0x00,
0x18,
0x30,
0x60,
0xC3,
0x66,
0x3C,

8, 13, 8, 10, 1, 0, //BBX

0x2C, 0xF0, //Mask

//Bitmap: "к"
0x18, 0x3C,
0x66,
0xC3,
0xFF,
0xC3,

8, 13, 9, 10, 1, 0, //BBX

0x78, 0xC0, //Mask

//Bitmap: "л"
0xFF, 0xC0,
0xFC,
0xC6,
0xC3,
0xC6,
0xFC,

8, 13, 11, 10, 1, 0, //BBX

0x30, 0xC0, //Mask

//Bitmap: "м"
0xF8, 0xCC,
0xC6,
0xCC,
0xFC,
0xC6,
0xC3,
0xC6,
0xFC,

8, 13, 4, 10, 1, 0, //BBX

0x7F, 0xF0, //Mask

//Bitmap: "н"
0xFF, 0xC0,

8, 13, 9, 10, 1, 0, //BBX

0x1B, 0x30, //Mask

//Bitmap: "о"
0x0E, 0x1E,
0x16,
0x36,
0x66,
0xFF,
0xC3,

8, 13, 7, 10, 1, 0, //BBX

0x79, 0xE0, //Mask

//Bitmap: "п"
0xFF, 0xC0,
0xFC,
0xC0,
0xFF,

14, 13, 16, 16, 1, 0, //BBX

0xA9, 0x50, //Mask

//Bitmap: "р"
0xC3, 0x0C,
0x63, 0x18,
0x33, 0x30,
0x1F, 0xE0,
0x33, 0x30,
0x63, 0x18,
0xC3, 0x0C,

8, 13, 13, 10, 1, 0, //BBX

0x10, 0x80, //Mask

//Bitmap: "с"
0x3C, 0x66,
0x43,
0x03,
0x06,
0x3C,
0x06,
0x03,
0x83,
0xC6,
0x7C,

8, 13, 9, 10, 1, 0, //BBX

0x55, 0x50, //Mask

//Bitmap: "т"
0xC3, 0xC7,
0xCF,
0xDB,
0xF3,
0xE3,
0xC3,

8, 15, 11, 10, 1, 0, //BBX

0x15, 0x54, //Mask

//Bitmap: "у"
0x3C, 0x00,
0xC3,
0xC7,
0xCF,
0xDB,
0xF3,
0xE3,
0xC3,

8, 13, 9, 10, 1, 0, //BBX

0xA9, 0x50, //Mask

//Bitmap: "ф"
0xC3, 0xC6,
0xCC,
0xF8,
0xCC,
0xC6,
0xC3,

8, 13, 9, 10, 1, 0, //BBX

0xAA, 0x90, //Mask

//Bitmap: "х"
0x1F, 0x13,
0x33,
0x23,
0x63,
0x43,
0xC3,

8, 13, 7, 10, 1, 0, //BBX

0xA7, 0x70, //Mask

//Bitmap: "ц"
0xC3, 0xE7,
0xFF,
0xDB,
0xC3,

8, 13, 5, 10, 1, 0, //BBX

0xF9, 0xF0, //Mask

//Bitmap: "ч"
0xC3, 0xFF,
0xC3,

8, 13, 7, 10, 1, 0, //BBX

0x3F, 0xC0, //Mask

//Bitmap: "ш"
0x3C, 0x66,
0xC3,
0x66,
0x3C,

8, 13, 4, 10, 1, 0, //BBX

0x7F, 0xF0, //Mask

//Bitmap: "щ"
0xFF, 0xC3,

8, 13, 8, 10, 1, 0, //BBX

0x38, 0xF0, //Mask

//Bitmap: "ъ"
0xFC, 0xC6,
0xC3,
0xC6,
0xFC,
0xC0,

8, 13, 9, 10, 1, 0, //BBX

0x1F, 0x80, //Mask

//Bitmap: "ы"
0x3C, 0x66,
0xC3,
0xC0,
0xC3,
0x66,
0x3C,

8, 13, 4, 10, 1, 0, //BBX

0x7F, 0xF0, //Mask

//Bitmap: "ь"
0xFF, 0x18,

8, 13, 10, 10, 1, 0, //BBX

0xAA, 0x80, //Mask

//Bitmap: "э"
0xC3, 0x66,
0x3C,
0x18,
0x30,
0x20,
0x60,
0x40,

8, 13, 9, 10, 1, 0, //BBX

0x8F, 0x10, //Mask

//Bitmap: "ю"
0x18, 0x3C,
0x7E,
0xDB,
0x7E,
0x3C,
0x18,

8, 13, 9, 10, 1, 0, //BBX

0xA9, 0x50, //Mask

//Bitmap: "я"
0xC3, 0x66,
0x3C,
0x18,
0x3C,
0x66,
0xC3,

8, 15, 5, 10, 1, 254, //BBX

0xFF, 0xE4, //Mask

//Bitmap:
0xC6, 0xFF,
0x03,

7, 13, 5, 10, 1, 0, //BBX

0xF9, 0xF0, //Mask

//Bitmap: ""
0xC6, 0x7E,
0x06,

10, 13, 6, 12, 1, 0, //BBX

0xFF, 0xE0, //Mask

//Bitmap: ""
0xCC, 0xC0,
0xFF, 0xC0,

11, 15, 8, 12, 1, 254, //BBX

0xFF, 0xE4, //Mask

//Bitmap: ""
0xCC, 0xC0,
0xFF, 0xE0,
0x00, 0x60,

8, 13, 9, 10, 1, 0, //BBX

0xB8, 0xC0, //Mask

//Bitmap: ""
0xF0, 0x30,
0x3C,
0x36,
0x33,
0x36,
0x3C,

9, 13, 14, 11, 1, 0, //BBX

0xF8, 0xC0, //Mask

//Bitmap: ""
0xC1, 0x80,
0xF1, 0x80,
0xD9, 0x80,
0xCD, 0x80,
0xD9, 0x80,
0xF1, 0x80,

8, 13, 8, 10, 1, 0, //BBX

0xF8, 0xC0, //Mask

//Bitmap: ""
0xC0, 0xFC,
0xC6,
0xC3,
0xC6,
0xFC,

8, 13, 11, 10, 1, 0, //BBX

0x19, 0x80, //Mask

//Bitmap: ""
0x3C, 0x66,
0xC3,
0x03,
0x1F,
0x03,
0xC3,
0x66,
0x3C,

9, 13, 12, 11, 1, 0, //BBX

0xBA, 0xD0, //Mask

//Bitmap: ""
0xCF, 0x00,
0xD9, 0x80,
0xF9, 0x80,
0xD9, 0x80,
0xCF, 0x00,

8, 13, 10, 10, 1, 0, //BBX

0x38, 0x50, //Mask

//Bitmap: "	"
0x3F, 0x63,
0xC3,
0x63,
0x3F,
0x33,
0x63,
0xC3,

8, 8, 7, 10, 1, 0, //BBX

0x0C, //Mask

//Bitmap: " "
0x3E, 0x63,
0x03,
0x7F,
0xC3,
0x7D,

7, 8, 6, 9, 1, 0, //BBX

0x4C, //Mask

//Bitmap: ""
0xFE, 0xC0,
0xFC,
0xC6,
0xFC,

7, 8, 6, 9, 1, 0, //BBX

0x4C, //Mask

//Bitmap: ""
0xFC, 0xC6,
0xFC,
0xC6,
0xFC,

6, 8, 3, 8, 1, 0, //BBX

0x7E, //Mask

//Bitmap: " "
0xFC, 0xC0,

8, 10, 8, 10, 1, 254, //BBX

0x2C, 0x80, //Mask

//Bitmap: ""
0x0E, 0x1E,
0x36,
0x66,
0xFF,
0xC3,

8, 8, 8, 10, 1, 0, //BBX

0x08, //Mask

//Bitmap: ""
0x3C, 0x66,
0xC3,
0xFF,
0xC0,
0x63,
0x3E,

8, 8, 8, 10, 1, 0, //BBX

0x10, //Mask

//Bitmap: ""
0x99, 0xDB,
0x7E,
0x3C,
0x7E,
0xDB,
0x99,

8, 8, 8, 10, 1, 0, //BBX

0x10, //Mask

//Bitmap: ""
0x3C, 0x66,
0xC3,
0x0E,
0xC3,
0x66,
0x3C,

8, 8, 6, 10, 1, 0, //BBX

0x54, //Mask

//Bitmap: ""
0xC7, 0xCF,
0xDB,
0xF3,
0xE3,

8, 10, 9, 10, 1, 0, //BBX

0x15, 0x00, //Mask

//Bitmap: ""
0x3C, 0x00,
0xC7,
0xCF,
0xDB,
0xF3,
0xE3,

7, 8, 9, 9, 1, 0, //BBX

0x00, //Mask

//Bitmap: ""
0xC6, 0xCC,
0xD8,
0xF0,
0xF8,
0xCC,
0xC6,
0xC2,

8, 8, 6, 10, 1, 0, //BBX

0x2A, //Mask

//Bitmap: ""
0x0F, 0x1F,
0x33,
0x63,
0xC3,

8, 8, 5, 10, 1, 0, //BBX

0x56, //Mask

//Bitmap: ""
0xC3, 0xE7,
0xDB,
0xC3,

8, 8, 4, 10, 1, 0, //BBX

0xE6, //Mask

//Bitmap: ""
0xC3, 0xFF,
0xC3,

8, 8, 6, 10, 1, 0, //BBX

0x38, //Mask

//Bitmap: ""
0x3C, 0x66,
0xC3,
0x66,
0x3C,

7, 8, 3, 9, 1, 0, //BBX

0x7E, //Mask

//Bitmap: ""
0xFE, 0xC6,

8, 11, 8, 10, 1, 253, //BBX

0x38, 0xC0, //Mask

//Bitmap: 
0xFC, 0xE6,
0xC3,
0xE6,
0xFC,
0xC0,

7, 8, 6, 10, 1, 0, //BBX

0x38, //Mask

//Bitmap: ""
0x3C, 0x66,
0xC0,
0x66,
0x3C,

8, 8, 3, 10, 1, 0, //BBX

0x7E, //Mask

//Bitmap: ""
0xFF, 0x18,

8, 11, 9, 10, 1, 253, //BBX

0xF0, 0x00, //Mask

//Bitmap: ""
0xC3, 0x67,
0x3F,
0x03,
0xC3,
0x66,
0x3C,

8, 11, 8, 10, 1, 253, //BBX

0x38, 0xC0, //Mask

//Bitmap: ""
0x3C, 0x7E,
0xDB,
0x7E,
0x3C,
0x18,

8, 8, 8, 10, 1, 0, //BBX

0x10, //Mask

//Bitmap: ""
0xC3, 0x66,
0x3C,
0x18,
0x3C,
0x66,
0xC3,

8, 10, 5, 10, 1, 254, //BBX

0xFC, 0x80, //Mask

//Bitmap: " "
0xC6, 0xFF,
0x03,

8, 11, 7, 10, 1, 253, //BBX

0xF0, 0xC0, //Mask

//Bitmap: "!"
0xC3, 0x67,
0x7F,
0x1B,
0x03,

10, 8, 5, 12, 1, 0, //BBX

0xFC, //Mask

//Bitmap: """
0xCC, 0xC0,
0xFF, 0xC0,

11, 10, 8, 13, 1, 254, //BBX

0xFC, 0x80, //Mask

//Bitmap: "#"
0xCC, 0xC0,
0xFF, 0xE0,
0x00, 0x60,

8, 8, 6, 10, 1, 0, //BBX

0x4C, //Mask

//Bitmap: "$"
0xF0, 0x30,
0x3E,
0x33,
0x3E,

8, 8, 5, 10, 1, 0, //BBX

0xCC, //Mask

//Bitmap: "%"
0xC3, 0xF3,
0xDB,
0xF3,

7, 8, 5, 9, 1, 0, //BBX

0xCC, //Mask

//Bitmap: "&"
0xC0, 0xFC,
0xC6,
0xFC,

8, 8, 8, 10, 1, 0, //BBX

0x10, //Mask

//Bitmap: "'"
0x3C, 0x66,
0xC3,
0x0F,
0xC3,
0x66,
0x3C,

10, 8, 15, 12, 1, 0, //BBX

0x20, //Mask

//Bitmap: "("
0xC7, 0x00,
0xCD, 0x80,
0xD8, 0xC0,
0xF8, 0xC0,
0xD8, 0xC0,
0xCD, 0x80,
0xC7, 0x00,

6, 8, 7, 8, 1, 0, //BBX

0x60, //Mask

//Bitmap: ")"
0x7C, 0xCC,
0x7C,
0x3C,
0x6C,
0xCC,

};




const unsigned char u8g_logo_bits[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x10, 0x00, 0x00,
		0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x60, 0x00, 0x00, 0xE0, 0x00, 0x00,
		0xE0, 0x00, 0x00, 0xC0, 0x01, 0x00, 0xC0, 0x03, 0x00, 0xC0, 0x03, 0x00,
		0x80, 0x07, 0x00, 0x80, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x1F, 0x00,
		0x00, 0x3F, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xFE, 0x00,
		0x00, 0xFC, 0x00, 0x00, 0xFC, 0x01, 0x00, 0xFC, 0x03, 0x00, 0xF8, 0x03,
		0xFC, 0xFF, 0x07, 0xF8, 0xFF, 0x0F, 0xF8, 0xFF, 0x0F, 0xF0, 0xFF, 0x1F,
		0xE0, 0xFF, 0x3F, 0xE0, 0x1F, 0x00, 0xC0, 0x3F, 0x00, 0xC0, 0x3F, 0x00,
		0x80, 0x3F, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x7E, 0x00,
		0x00, 0x7E, 0x00, 0x00, 0x7C, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xF8, 0x00,
		0x00, 0xF8, 0x01, 0x00, 0xF0, 0x01, 0x00, 0xF0, 0x01, 0x00, 0xE0, 0x01,
		0x00, 0xC0, 0x03, 0x00, 0xC0, 0x03, 0x00, 0x80, 0x03, 0x00, 0x80, 0x07,
		0x00, 0x00, 0x07, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x04,
		0x00, 0x00, 0x0C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00 };

//Ближний свет
const unsigned char u8g_neighbor_bits[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
		0x03, 0x00, 0x00, 0x3C, 0x0E, 0x00, 0x00, 0xA7, 0x12, 0x00, 0x80, 0x24,
		0x22, 0x00, 0xC0, 0xA4, 0x22, 0x00, 0xA0, 0xA4, 0x62, 0x00, 0xB0, 0xA4,
		0x42, 0x03, 0x98, 0x24, 0x42, 0x06, 0x94, 0xA4, 0x42, 0x0C, 0x96, 0xA4,
		0x42, 0x18, 0x96, 0xA4, 0x42, 0x30, 0x96, 0xA4, 0x42, 0x60, 0x96, 0xA4,
		0x42, 0x03, 0x96, 0xA4, 0x42, 0x06, 0x94, 0xA4, 0x42, 0x0C, 0x98, 0x24,
		0x42, 0x18, 0xB0, 0xA4, 0x42, 0x30, 0xA0, 0xA4, 0x62, 0x60, 0xC0, 0xA4,
		0x22, 0x03, 0xC0, 0x24, 0x22, 0x06, 0x60, 0xA7, 0x12, 0x0C, 0x30, 0x3E,
		0x0E, 0x18, 0x18, 0xF8, 0x03, 0x30, 0x6C, 0x0C, 0x00, 0x60, 0x82, 0x06,
		0x00, 0x00, 0xBA, 0x03, 0x00, 0x00, 0xAA, 0x01, 0x00, 0x00, 0xBA, 0x00,
		0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00 };

//Дальний свет
const unsigned char u8g_farthest_bits[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
		0x03, 0x00, 0x00, 0x3C, 0x0E, 0x00, 0x00, 0xA7, 0x12, 0x00, 0x80, 0x24,
		0xA2, 0x0F, 0xC0, 0xA4, 0x22, 0x00, 0xA0, 0xA4, 0x62, 0x00, 0xB0, 0xA4,
		0x42, 0x00, 0x98, 0x24, 0x42, 0x3F, 0x94, 0xA4, 0x42, 0x00, 0x96, 0xA4,
		0x42, 0x00, 0x96, 0xA4, 0x42, 0x00, 0x96, 0xA4, 0x42, 0x7F, 0x96, 0xA4,
		0x42, 0x00, 0x96, 0xA4, 0x42, 0x00, 0x94, 0xA4, 0x42, 0x00, 0x98, 0x24,
		0x42, 0x3F, 0xB0, 0xA4, 0x42, 0x00, 0xA0, 0xA4, 0x62, 0x00, 0xC0, 0xA4,
		0x22, 0x00, 0xC0, 0x24, 0xA2, 0x0F, 0x60, 0xA7, 0x12, 0x00, 0x30, 0x3E,
		0x0E, 0x00, 0x18, 0xF8, 0x03, 0x00, 0x6C, 0x0C, 0x00, 0x00, 0x82, 0x06,
		0x00, 0x00, 0xBA, 0x03, 0x00, 0x00, 0xAA, 0x01, 0x00, 0x00, 0xBA, 0x00,
		0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00 };

//Подсветка дисплея
const unsigned char u8g_lightdisplay_bits[] = { 0x00, 0x00, 0x00, 0x00, 0xE0,
		0xFF, 0xFF, 0x1F, 0x10, 0x00, 0x00, 0x20, 0xE8, 0xFF, 0xFF, 0x5F, 0x28,
		0x00, 0x00, 0x50, 0x08, 0x00, 0xF4, 0x57, 0xC0, 0x03, 0x00, 0x54, 0x30,
		0x0C, 0xC0, 0x55, 0x08, 0x10, 0x00, 0x55, 0x04, 0x20, 0x00, 0x55, 0x04,
		0x22, 0x00, 0x55, 0x02, 0x45, 0x00, 0x54, 0x02, 0x42, 0x00, 0x54, 0x02,
		0x40, 0x00, 0x54, 0x02, 0x40, 0x00, 0x50, 0x02, 0x40, 0x00, 0x54, 0x04,
		0x20, 0x00, 0x50, 0x04, 0x20, 0x00, 0x50, 0x08, 0x90, 0xFF, 0x5F, 0xF0,
		0x0F, 0x00, 0x20, 0xF0, 0xEF, 0xFF, 0x1F, 0x10, 0x08, 0x00, 0x00, 0xE0,
		0x07, 0x00, 0x30, 0x10, 0x08, 0x00, 0x36, 0xE0, 0x07, 0xC0, 0x36, 0x10,
		0x08, 0xD8, 0x36, 0xE0, 0x07, 0xDB, 0x36, 0x40, 0x62, 0xDB, 0x36, 0x80,
		0x61, 0xDB, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00 };

/*
 Fontname: elpaulo16n
 Copyright: Created with Fony 1.4.6
 Capital A Height: 0, '1' Height: 15
 Calculated Max Values w=10 h=15 x= 1 y=16 dx=12 dy= 0 ascent=16 len=30
 Font Bounding box     w=12 h=15 x= 0 y= 0
 Calculated Min Values           x= 0 y= 0 dx= 0 dy= 0
 Pure Font   ascent =15 descent= 0
 X Font      ascent =15 descent= 0
 Max Font    ascent =16 descent= 0
 */
#include "u8g.h"
const u8g_fntpgm_uint8_t u8g_font_elpaulo16n[450] U8G_FONT_SECTION("u8g_font_elpaulo16n")
		= { 0, 12, 15, 0, 0, 15, 0, 0, 0, 0, 43, 57, 0, 16, 0, 15, 0, 8, 8, 8,
				10, 1, 5, 24, 24, 24, 255, 255, 24, 24, 24, 0, 0, 0, 1, 0, 16,
				8, 2, 2, 10, 1, 8, 255, 255, 3, 3, 3, 4, 1, 0, 224, 224, 224, 9,
				15, 30, 10, 1, 0, 3, 128, 3, 128, 7, 128, 7, 0, 15, 0, 14, 0,
				30, 0, 28, 0, 60, 0, 56, 0, 120, 0, 112, 0, 240, 0, 224, 0, 224,
				0, 10, 15, 30, 12, 1, 0, 63, 0, 127, 128, 243, 192, 225, 192,
				225, 192, 225, 192, 225, 192, 225, 192, 225, 192, 225, 192, 225,
				192, 225, 192, 243, 192, 127, 128, 63, 0, 10, 15, 30, 12, 1, 0,
				7, 0, 15, 0, 31, 0, 63, 0, 63, 0, 55, 0, 39, 0, 7, 0, 7, 0, 7,
				0, 7, 0, 7, 0, 7, 0, 7, 0, 255, 192, 10, 15, 30, 12, 1, 0, 63,
				0, 127, 128, 255, 192, 227, 192, 1, 192, 1, 192, 3, 192, 7, 128,
				15, 0, 30, 0, 60, 0, 120, 0, 255, 192, 255, 192, 255, 192, 10,
				15, 30, 12, 1, 0, 63, 0, 127, 128, 255, 192, 227, 192, 1, 192,
				3, 192, 31, 192, 31, 128, 3, 192, 1, 192, 1, 192, 227, 192, 255,
				192, 127, 128, 63, 0, 10, 15, 30, 12, 1, 0, 7, 128, 15, 128, 15,
				128, 31, 128, 31, 128, 59, 128, 59, 128, 115, 128, 115, 128,
				255, 192, 255, 192, 255, 192, 3, 128, 3, 128, 3, 128, 10, 15,
				30, 12, 1, 0, 255, 192, 255, 192, 255, 192, 224, 0, 224, 0, 255,
				0, 255, 128, 255, 192, 3, 192, 1, 192, 1, 192, 227, 192, 255,
				192, 127, 128, 63, 0, 10, 15, 30, 12, 1, 0, 63, 0, 127, 128,
				255, 192, 225, 192, 224, 0, 224, 0, 255, 0, 255, 128, 255, 192,
				243, 192, 225, 192, 243, 192, 255, 192, 127, 128, 63, 0, 10, 15,
				30, 12, 1, 0, 255, 192, 255, 192, 255, 192, 1, 192, 3, 192, 3,
				128, 7, 128, 7, 0, 15, 0, 14, 0, 30, 0, 28, 0, 60, 0, 56, 0,
				120, 0, 10, 15, 30, 12, 1, 0, 30, 0, 63, 0, 127, 128, 115, 128,
				115, 128, 115, 128, 127, 128, 63, 0, 127, 128, 225, 192, 225,
				192, 225, 192, 255, 192, 127, 128, 63, 0, 10, 15, 30, 12, 1, 0,
				63, 0, 127, 128, 255, 192, 243, 192, 225, 192, 243, 192, 255,
				192, 127, 192, 63, 192, 1, 192, 1, 192, 225, 192, 255, 192, 127,
				128, 63, 0 };

/*
  Fontname: elpaulo20
  Copyright: Public domain font.  Share and enjoy.
  Capital A Height: 13, '1' Height: 13
  Calculated Max Values w=16 h=16 x= 4 y=16 dx=18 dy= 0 ascent=16 len=30
  Font Bounding box     w=18 h=19 x= 0 y=-4
  Calculated Min Values           x= 0 y=-4 dx= 0 dy= 0
  Pure Font   ascent =13 descent=-4
  X Font      ascent =13 descent=-4
  Max Font    ascent =16 descent=-4
*/
#include "u8g.h"
const u8g_fntpgm_uint8_t u8g_font_elpaulo20o[4138] U8G_FONT_SECTION("u8g_font_elpaulo20") = {
//0,18,19,0,252,13,4,137,6,216,0,255,252,16,252,16,
  0,18,19,0,252,13,4,137,6,216,0,255,252,16,252,16,
  252,8,13,13,10,1,0,231,129,129,0,0,129,129,129,0,
  0,129,129,231,14,14,28,18,1,0,7,0,29,128,50,184,
  98,128,66,128,194,156,194,128,194,128,194,156,66,128,98,128,
  50,184,29,128,7,0,14,14,28,18,1,0,21,80,63,248,
  85,84,64,4,64,52,127,52,136,132,130,180,132,180,201,132,
  132,180,130,180,136,132,127,120,14,14,28,18,1,0,128,12,
  192,8,128,24,128,16,196,48,142,32,138,32,219,96,145,192,
  144,128,208,0,128,0,146,72,255,252,14,14,28,18,1,0,
  1,224,3,192,7,128,7,4,7,12,7,28,15,252,31,248,
  59,240,119,0,238,0,220,0,248,0,112,0,14,14,28,18,
  1,0,127,248,192,12,131,4,135,132,135,132,135,132,135,132,
  131,4,131,4,128,4,131,4,131,4,192,12,127,248,14,14,
  28,18,1,0,60,0,102,240,66,0,66,240,90,0,90,240,
  90,0,90,0,219,64,189,24,189,36,189,32,195,36,126,24,
  14,8,16,18,1,3,255,240,255,144,255,28,254,20,252,20,
  248,28,240,16,255,240,14,14,28,18,1,0,127,248,192,12,
  135,132,135,132,128,4,143,132,143,132,135,132,135,132,135,132,
  143,196,143,196,192,12,127,248,0,0,0,16,0,16,8,16,
  16,16,4,255,128,192,224,240,248,252,254,255,255,254,252,248,
  240,224,192,128,8,16,16,16,4,255,1,3,7,15,31,63,
  127,255,255,127,63,31,15,7,3,1,16,8,16,16,0,3,
  1,128,3,192,7,224,15,240,31,248,63,252,127,254,255,255,
  16,8,16,16,0,3,255,255,127,254,63,252,31,248,15,240,
  7,224,3,192,1,128,12,14,28,16,2,0,31,128,63,192,
  112,224,96,96,96,96,96,96,255,240,255,240,255,240,249,240,
  240,240,249,240,255,240,255,240,14,14,28,16,1,0,127,248,
  255,252,224,28,192,12,192,12,192,12,192,12,192,12,192,12,
  192,12,192,12,224,28,255,252,127,248,14,14,28,16,1,0,
  127,248,255,252,224,28,192,60,192,124,192,236,241,204,251,140,
  223,12,206,12,196,12,224,28,255,252,127,248,8,2,2,12,
  2,0,219,219,0,0,0,1,0,16,0,0,0,1,0,16,
  0,0,0,1,0,16,0,0,0,1,0,16,0,0,0,1,
  0,16,0,0,0,1,0,16,0,0,0,1,0,16,0,0,
  0,1,0,16,0,0,0,1,0,16,0,0,0,1,0,16,
  0,0,0,1,0,16,0,0,0,16,0,16,0,0,0,16,
  0,16,0,0,0,16,0,16,0,0,0,12,0,16,2,13,
  13,6,2,0,192,192,192,192,192,192,192,192,192,192,0,192,
  192,6,4,4,10,2,9,204,204,204,72,9,11,22,10,1,
  1,27,0,27,0,27,0,127,128,54,0,54,0,54,0,255,
  0,108,0,108,0,108,0,8,13,13,10,1,0,24,126,219,
  216,216,216,126,27,27,27,219,126,24,9,12,24,10,1,0,
  115,0,219,0,222,0,118,0,12,0,12,0,24,0,24,0,
  55,0,61,128,109,128,103,0,9,13,26,10,1,0,56,0,
  108,0,108,0,108,0,120,0,48,0,112,0,216,0,205,128,
  199,0,198,0,239,0,121,128,2,5,5,10,4,8,192,192,
  192,192,128,5,13,13,10,3,0,24,48,96,96,192,192,192,
  192,192,96,96,48,24,5,13,13,10,2,0,192,96,48,48,
  24,24,24,24,24,48,48,96,192,8,7,7,10,1,3,102,
  102,60,255,60,102,102,8,8,8,10,1,3,24,24,24,255,
  255,24,24,24,3,4,4,10,3,255,96,96,96,192,8,2,
  2,10,1,6,255,255,2,3,3,6,2,0,192,192,192,7,
  12,12,10,2,0,6,6,12,12,24,24,48,48,96,96,192,
  192,8,13,13,10,1,0,60,126,231,195,195,195,195,195,195,
  195,231,126,60,4,13,13,10,3,0,48,112,240,240,48,48,
  48,48,48,48,48,48,48,8,13,13,10,1,0,126,255,195,
  195,3,7,14,28,56,112,224,255,255,8,13,13,10,1,0,
  126,255,195,195,3,14,15,3,3,195,195,255,126,8,13,13,
  10,1,0,3,7,15,31,59,115,227,195,255,255,3,3,3,
  8,13,13,10,1,0,255,255,192,192,254,255,195,3,3,3,
  195,255,126,8,13,13,10,1,0,126,255,195,192,254,255,195,
  195,195,195,195,255,126,8,13,13,10,1,0,255,255,195,3,
  7,6,14,12,28,24,56,48,112,8,13,13,10,1,0,126,
  255,195,195,195,126,255,195,195,195,195,255,126,8,13,13,10,
  1,0,126,255,195,195,195,195,255,127,3,3,195,255,126,2,
  10,10,6,2,0,192,192,192,0,0,0,0,192,192,192,3,
  11,11,7,1,255,96,96,96,0,0,0,0,96,96,96,192,
  7,13,13,10,1,0,2,6,12,24,48,96,192,96,48,24,
  12,6,2,8,7,7,10,1,3,255,255,0,0,0,255,255,
  7,13,13,10,2,0,128,192,96,48,24,12,6,12,24,48,
  96,192,128,8,13,13,10,1,0,60,126,231,195,195,7,14,
  28,24,24,0,24,24,8,13,13,10,1,0,60,102,195,207,
  223,219,219,219,222,204,192,99,62,8,13,13,10,1,0,24,
  60,102,102,195,195,195,255,195,195,195,195,195,8,13,13,10,
  1,0,248,204,198,198,198,204,252,198,195,195,195,198,252,8,
  13,13,10,1,0,60,102,195,192,192,192,192,192,192,192,195,
  102,60,8,13,13,10,1,0,252,198,195,195,195,195,195,195,
  195,195,195,198,252,8,13,13,10,1,0,255,192,192,192,192,
  192,252,192,192,192,192,192,255,8,13,13,10,1,0,255,192,
  192,192,192,192,252,192,192,192,192,192,192,8,13,13,10,1,
  0,60,102,195,192,192,192,207,195,195,195,195,103,61,8,13,
  13,10,1,0,195,195,195,195,195,195,255,195,195,195,195,195,
  195,8,13,13,10,1,0,255,24,24,24,24,24,24,24,24,
  24,24,24,255,9,13,26,10,1,0,31,128,6,0,6,0,
  6,0,6,0,6,0,6,0,6,0,6,0,198,0,198,0,
  108,0,56,0,8,13,13,10,1,0,195,195,198,198,204,204,
  248,204,204,198,198,195,195,8,13,13,10,1,0,192,192,192,
  192,192,192,192,192,192,192,192,192,255,8,13,13,10,1,0,
  195,195,231,231,255,219,219,219,219,195,195,195,195,8,13,13,
  10,1,0,195,227,227,243,243,219,219,207,207,199,199,195,195,
  8,13,13,10,1,0,60,102,195,195,195,195,195,195,195,195,
  195,102,60,8,13,13,10,1,0,252,198,195,195,195,195,198,
  252,192,192,192,192,192,8,14,14,10,1,255,60,102,195,195,
  195,195,195,195,195,219,207,102,62,3,8,13,13,10,1,0,
  252,198,195,195,195,195,198,252,204,198,198,195,195,8,13,13,
  10,1,0,60,102,195,192,192,96,60,6,3,3,195,102,60,
  8,13,13,10,1,0,255,24,24,24,24,24,24,24,24,24,
  24,24,24,8,13,13,10,1,0,195,195,195,195,195,195,195,
  195,195,195,195,102,60,8,13,13,10,1,0,195,195,195,195,
  102,102,102,60,60,60,24,24,24,8,13,13,10,1,0,195,
  195,195,195,195,219,219,219,219,231,231,195,195,8,13,13,10,
  1,0,195,195,102,102,60,60,24,60,60,102,102,195,195,8,
  13,13,10,1,0,195,195,102,102,60,60,24,24,24,24,24,
  24,24,8,13,13,10,1,0,255,3,3,6,12,12,24,48,
  48,96,192,192,255,6,13,13,10,2,0,252,192,192,192,192,
  192,192,192,192,192,192,192,252,7,12,12,10,2,0,192,192,
  96,96,48,48,24,24,12,12,6,6,6,13,13,10,2,0,
  252,12,12,12,12,12,12,12,12,12,12,12,252,8,4,4,
  10,1,9,24,60,102,195,9,1,2,10,1,255,255,128,4,
  3,3,10,3,10,192,96,48,8,8,8,10,1,0,62,99,
  3,127,195,195,195,125,8,13,13,10,1,0,192,192,192,192,
  192,220,230,195,195,195,195,230,220,8,8,8,10,1,0,62,
  99,192,192,192,192,99,62,8,13,13,10,1,0,3,3,3,
  3,3,59,103,195,195,195,195,103,59,8,8,8,10,1,0,
  60,102,195,255,192,192,99,62,8,13,13,10,1,0,30,51,
  51,48,48,252,48,48,48,48,48,48,48,8,12,12,10,1,
  252,125,199,198,198,198,124,192,126,195,195,195,126,8,13,13,
  10,1,0,192,192,192,192,192,220,230,195,195,195,195,195,195,
  8,11,11,10,1,0,24,24,0,120,24,24,24,24,24,24,
  255,7,15,15,10,2,252,6,6,0,30,6,6,6,6,6,
  6,6,198,198,198,124,8,13,13,10,1,0,192,192,192,192,
  192,198,204,216,240,248,204,198,195,8,13,13,10,1,0,120,
  24,24,24,24,24,24,24,24,24,24,24,255,8,8,8,10,
  1,0,182,255,219,219,219,219,219,219,8,8,8,10,1,0,
  220,230,195,195,195,195,195,195,8,8,8,10,1,0,60,102,
  195,195,195,195,102,60,8,12,12,10,1,252,220,230,195,195,
  195,195,230,220,192,192,192,192,8,12,12,10,1,252,59,103,
  195,195,195,195,103,59,3,3,3,3,8,8,8,10,1,0,
  222,115,96,96,96,96,96,96,8,8,8,10,1,0,126,195,
  192,126,3,3,195,126,8,11,11,10,1,0,48,48,48,252,
  48,48,48,48,48,51,30,8,8,8,10,1,0,195,195,195,
  195,195,195,103,59,8,8,8,10,1,0,195,195,102,102,60,
  60,24,24,8,8,8,10,1,0,195,195,195,219,219,219,255,
  102,8,8,8,10,1,0,195,102,60,24,24,60,102,195,8,
  12,12,10,1,252,195,195,195,195,195,195,103,59,3,195,102,
  60,7,8,8,10,2,0,254,6,12,24,48,96,192,254,8,
  13,13,10,1,0,15,24,24,24,24,24,240,24,24,24,24,
  24,15,2,13,13,10,4,0,192,192,192,192,192,192,192,192,
  192,192,192,192,192,8,13,13,10,1,0,240,24,24,24,24,
  24,15,24,24,24,24,24,240,8,3,3,10,1,10,115,219,
  206,0,0,0,1,0,16,0,0,0,1,0,16,0,0,0,
  1,0,16,0,0,0,1,0,16,0,0,0,1,0,16,0,
  0,0,1,0,16,0,0,0,1,0,16,0,0,0,1,0,
  16,0,0,0,1,0,16,0,0,0,1,0,16,0,0,0,
  1,0,16,0,0,0,1,0,16,0,0,0,1,0,16,0,
  0,0,1,0,16,0,0,0,1,0,16,0,0,0,1,0,
  16,0,0,0,1,0,16,0,0,0,1,0,16,0,0,0,
  1,0,16,0,0,0,1,0,16,0,0,0,1,0,16,0,
  0,0,1,0,16,0,0,0,1,0,16,0,0,0,1,0,
  16,0,0,0,1,0,16,0,0,0,1,0,16,0,0,0,
  1,0,16,0,0,0,1,0,16,0,0,0,1,0,16,0,
  0,0,1,0,16,0,0,0,1,0,16,0,0,0,1,0,
  16,0,0,0,1,0,16,0,0,0,10,0,16,2,13,13,
  10,4,0,192,192,0,192,192,192,192,192,192,192,192,192,192,
  7,12,12,10,1,0,24,24,60,102,194,192,192,194,102,60,
  24,24,9,12,24,10,1,0,30,0,51,0,51,0,48,0,
  48,0,252,0,48,0,48,0,48,0,248,0,173,128,231,0,
  9,9,18,10,0,1,128,128,221,128,127,0,99,0,99,0,
  99,0,127,0,221,128,128,128,8,11,11,10,1,0,129,195,
  102,60,126,24,126,24,24,24,24,2,13,13,10,4,0,192,
  192,192,192,192,0,0,0,192,192,192,192,192,8,13,13,10,
  1,0,60,102,198,96,120,204,102,51,30,6,99,102,60,8,
  15,15,10,1,0,102,0,255,192,192,192,192,192,252,192,192,
  192,192,192,255,8,11,11,10,1,0,60,102,195,189,165,161,
  165,189,195,102,60,8,9,9,10,1,4,62,67,3,127,195,
  195,125,0,255,9,11,22,10,0,0,4,128,13,128,27,0,
  54,0,108,0,216,0,108,0,54,0,27,0,13,128,4,128,
  8,4,4,10,1,4,255,255,3,3,6,1,1,10,2,6,
  252,8,11,11,10,1,0,60,102,195,189,165,189,169,173,195,
  102,60,8,1,1,10,1,13,255,6,6,6,10,2,7,48,
  120,204,204,120,48,8,7,7,10,1,2,24,24,255,24,24,
  0,255,5,7,7,10,2,6,112,216,24,48,96,192,248,5,
  7,7,10,2,6,112,216,24,48,24,216,112,4,3,3,10,
  3,10,48,96,192,7,10,10,10,1,253,198,198,198,198,198,
  238,250,192,192,192,8,13,13,10,1,0,127,255,251,251,251,
  123,27,27,27,27,27,27,27,3,3,3,10,4,5,224,224,
  224,8,11,11,10,1,0,102,102,0,60,102,195,255,192,192,
  99,62,4,7,7,10,2,6,96,224,96,96,96,96,240,7,
  9,9,10,1,4,56,108,198,198,198,108,56,0,254,9,11,
  22,10,1,0,144,0,216,0,108,0,54,0,27,0,13,128,
  27,0,54,0,108,0,216,0,144,0,8,12,12,10,1,1,
  64,192,65,66,228,8,18,38,74,158,2,2,8,12,12,10,
  1,1,64,192,65,66,228,8,22,41,65,130,4,15,8,12,
  12,10,1,1,224,16,97,18,228,8,18,38,74,159,2,2,
  8,13,13,10,1,0,24,24,0,24,24,24,48,96,195,195,
  195,102,60,8,13,13,10,1,0,24,60,102,102,195,195,195,
  255,195,195,195,195,195,8,13,13,10,1,0,255,192,192,192,
  192,192,252,198,195,195,195,198,252,8,13,13,10,1,0,248,
  204,198,198,198,204,252,198,195,195,195,198,252,8,13,13,10,
  1,0,255,192,192,192,192,192,192,192,192,192,192,192,192,8,
  13,13,10,1,0,14,30,22,54,54,54,102,102,102,255,195,
  195,195,8,13,13,10,1,0,255,192,192,192,192,192,252,192,
  192,192,192,192,255,14,13,26,16,1,0,195,12,195,12,99,
  24,99,24,51,48,51,48,31,224,51,48,51,48,99,24,99,
  24,195,12,195,12,8,13,13,10,1,0,60,102,67,3,3,
  6,60,6,3,3,131,198,124,8,13,13,10,1,0,195,199,
  199,207,207,219,219,243,243,227,227,195,195,8,15,15,10,1,
  0,60,0,195,199,199,207,207,219,219,243,243,227,227,195,195,
  8,13,13,10,1,0,195,195,198,198,204,204,248,204,204,198,
  198,195,195,8,13,13,10,1,0,31,31,19,19,51,51,35,
  35,99,99,67,195,195,8,13,13,10,1,0,195,195,231,231,
  255,219,219,219,219,195,195,195,195,8,13,13,10,1,0,195,
  195,195,195,195,195,255,195,195,195,195,195,195,8,13,13,10,
  1,0,60,102,195,195,195,195,195,195,195,195,195,102,60,8,
  13,13,10,1,0,255,195,195,195,195,195,195,195,195,195,195,
  195,195,8,13,13,10,1,0,252,198,195,195,195,195,198,252,
  192,192,192,192,192,8,13,13,10,1,0,60,102,195,192,192,
  192,192,192,192,192,195,102,60,8,13,13,10,1,0,255,24,
  24,24,24,24,24,24,24,24,24,24,24,8,13,13,10,1,
  0,195,195,102,102,60,60,24,24,48,48,32,96,64,8,13,
  13,10,1,0,24,24,60,126,219,219,219,219,219,126,60,24,
  24,8,13,13,10,1,0,195,195,102,102,60,60,24,60,60,
  102,102,195,195,8,15,15,10,1,254,198,198,198,198,198,198,
  198,198,198,198,198,198,255,3,3,7,13,13,10,1,0,198,
  198,198,198,198,198,126,6,6,6,6,6,6,10,13,26,12,
  1,0,204,192,204,192,204,192,204,192,204,192,204,192,204,192,
  204,192,204,192,204,192,204,192,204,192,255,192,11,15,30,12,
  1,254,204,192,204,192,204,192,204,192,204,192,204,192,204,192,
  204,192,204,192,204,192,204,192,204,192,255,224,0,96,0,96,
  8,13,13,10,1,0,240,240,48,48,48,48,60,54,51,51,
  51,54,60,9,13,26,11,1,0,193,128,193,128,193,128,193,
  128,193,128,193,128,241,128,217,128,205,128,205,128,205,128,217,
  128,241,128,8,13,13,10,1,0,192,192,192,192,192,192,252,
  198,195,195,195,198,252,8,13,13,10,1,0,60,102,195,3,
  3,3,31,3,3,3,195,102,60,9,13,26,11,1,0,207,
  0,207,0,217,128,217,128,217,128,217,128,249,128,249,128,217,
  128,217,128,217,128,207,0,207,0,8,13,13,10,1,0,63,
  99,195,195,195,195,99,63,51,99,99,195,195,8,8,8,10,
  1,0,62,99,3,127,195,195,195,125,7,8,8,9,1,0,
  254,192,192,252,198,198,198,252,7,8,8,9,1,0,252,198,
  198,252,198,198,198,252,6,8,8,8,1,0,252,192,192,192,
  192,192,192,192,8,10,10,10,1,254,14,30,54,54,102,102,
  102,255,195,195,8,8,8,10,1,0,60,102,195,255,192,192,
  99,62,8,8,8,10,1,0,153,219,126,60,60,126,219,153,
  8,8,8,10,1,0,60,102,195,14,14,195,102,60,8,8,
  8,10,1,0,199,207,207,219,219,243,243,227,8,10,10,10,
  1,0,60,0,199,207,207,219,219,243,243,227,7,8,8,9,
  1,0,198,204,216,240,248,204,198,194,8,8,8,10,1,0,
  15,31,51,51,99,99,195,195,8,8,8,10,1,0,195,231,
  231,219,219,195,195,195,8,8,8,10,1,0,195,195,195,195,
  255,195,195,195,8,8,8,10,1,0,60,102,195,195,195,195,
  102,60,7,8,8,9,1,0,254,198,198,198,198,198,198,198,
  8,11,11,10,1,253,252,230,195,195,195,195,230,252,192,192,
  192,7,8,8,10,1,0,60,102,192,192,192,192,102,60,8,
  8,8,10,1,0,255,24,24,24,24,24,24,24,8,11,11,
  10,1,253,195,195,195,195,195,103,63,3,195,102,60,8,11,
  11,10,1,253,60,126,219,219,219,219,126,60,24,24,24,8,
  8,8,10,1,0,195,102,60,24,24,60,102,195,8,10,10,
  10,1,254,198,198,198,198,198,198,198,255,3,3,8,11,11,
  10,1,253,195,195,195,195,195,103,127,27,3,3,3,10,8,
  16,12,1,0,204,192,204,192,204,192,204,192,204,192,204,192,
  204,192,255,192,11,10,20,13,1,254,204,192,204,192,204,192,
  204,192,204,192,204,192,204,192,255,224,0,96,0,96,8,8,
  8,10,1,0,240,48,48,62,51,51,51,62,8,8,8,10,
  1,0,195,195,195,243,219,219,219,243,7,8,8,9,1,0,
  192,192,192,252,198,198,198,252,8,8,8,10,1,0,60,102,
  195,15,15,195,102,60,10,8,16,12,1,0,199,0,205,128,
  216,192,216,192,248,192,216,192,205,128,199,0,6,8,8,8,
  1,0,124,204,204,204,124,60,108,204};

/*
 Fontname: -Adobe-Helvetica-Medium-R-Normal--34-240-100-100-P-176-ISO10646-1
 Copyright: Copyright (c) 1984, 1987 Adobe Systems Incorporated. All Rights Reserved. Copyright (c) 1988, 1991 Digital Equipment Corporation. All Rights Reserved.
 Capital A Height: 25, '1' Height: 24
 Calculated Max Values w=29 h=32 x= 4 y=22 dx=34 dy= 0 ascent=31 len=120
 Font Bounding box     w=39 h=48 x=-5 y=-11
 Calculated Min Values           x=-1 y=-7 dx= 0 dy= 0
 Pure Font   ascent =25 descent=-7
 X Font      ascent =25 descent=-7
 Max Font    ascent =31 descent=-7
 */
#include "u8g.h"
const u8g_fntpgm_uint8_t u8g_font_helvR24[10931] U8G_FONT_SECTION("u8g_font_helvR24")
		= { 0, 39, 48, 251, 245, 25, 5, 215, 14, 105, 32, 255, 249, 31, 249, 25,
				249, 0, 0, 0, 9, 0, 1, 3, 25, 25, 9, 4, 0, 224, 224, 224, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				64, 64, 0, 0, 224, 224, 224, 224, 8, 8, 8, 12, 2, 15, 231, 231,
				231, 231, 231, 231, 66, 66, 17, 23, 69, 19, 1, 0, 3, 135, 0, 3,
				135, 0, 3, 6, 0, 3, 6, 0, 7, 14, 0, 7, 14, 0, 127, 255, 128,
				127, 255, 128, 127, 255, 128, 14, 28, 0, 14, 28, 0, 12, 24, 0,
				28, 56, 0, 28, 56, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 56,
				112, 0, 56, 112, 0, 48, 96, 0, 48, 96, 0, 112, 224, 0, 112, 224,
				0, 16, 31, 62, 18, 1, 252, 1, 128, 1, 128, 1, 128, 15, 240, 31,
				248, 61, 188, 113, 142, 113, 142, 225, 142, 225, 128, 225, 128,
				113, 128, 125, 128, 63, 192, 31, 240, 7, 252, 1, 254, 1, 158, 1,
				143, 1, 135, 225, 135, 225, 135, 113, 142, 113, 142, 61, 188,
				63, 248, 15, 240, 1, 128, 1, 128, 1, 128, 1, 128, 26, 24, 96,
				29, 1, 0, 0, 0, 48, 0, 31, 0, 112, 0, 127, 128, 96, 0, 115, 192,
				224, 0, 224, 192, 192, 0, 192, 225, 192, 0, 192, 225, 128, 0,
				192, 227, 128, 0, 224, 195, 0, 0, 115, 199, 0, 0, 127, 134, 0,
				0, 31, 14, 0, 0, 0, 12, 0, 0, 0, 28, 62, 0, 0, 24, 127, 128, 0,
				56, 243, 128, 0, 48, 193, 192, 0, 113, 192, 192, 0, 97, 192,
				192, 0, 225, 192, 192, 0, 192, 193, 192, 1, 192, 227, 128, 1,
				128, 127, 128, 3, 128, 62, 0, 18, 23, 69, 22, 2, 0, 7, 192, 0,
				15, 224, 0, 30, 112, 0, 60, 56, 0, 56, 56, 0, 56, 56, 0, 60,
				112, 0, 30, 240, 0, 15, 224, 0, 7, 192, 0, 15, 128, 0, 63, 192,
				0, 121, 199, 0, 112, 231, 0, 224, 246, 0, 224, 126, 0, 224, 60,
				0, 224, 28, 0, 240, 62, 0, 120, 127, 0, 127, 247, 128, 63, 227,
				192, 15, 0, 0, 3, 8, 8, 6, 2, 15, 224, 224, 224, 224, 224, 224,
				224, 64, 7, 31, 31, 11, 2, 249, 6, 12, 12, 24, 24, 56, 48, 112,
				112, 112, 96, 224, 224, 224, 224, 224, 224, 224, 224, 224, 96,
				112, 112, 112, 48, 56, 24, 24, 12, 12, 6, 7, 31, 31, 11, 1, 249,
				192, 96, 96, 48, 48, 56, 24, 28, 28, 28, 12, 14, 14, 14, 14, 14,
				14, 14, 14, 12, 12, 28, 28, 24, 24, 56, 48, 112, 96, 96, 192,
				10, 11, 22, 13, 1, 15, 12, 0, 12, 0, 76, 128, 237, 192, 127,
				128, 63, 0, 30, 0, 63, 0, 115, 128, 225, 192, 64, 128, 17, 16,
				48, 19, 1, 1, 1, 192, 0, 1, 192, 0, 1, 192, 0, 1, 192, 0, 1,
				192, 0, 1, 192, 0, 1, 192, 0, 255, 255, 128, 255, 255, 128, 255,
				255, 128, 1, 192, 0, 1, 192, 0, 1, 192, 0, 1, 192, 0, 1, 192, 0,
				1, 192, 0, 3, 9, 9, 9, 3, 251, 224, 224, 224, 224, 32, 96, 96,
				192, 128, 8, 2, 2, 11, 1, 8, 255, 255, 3, 4, 4, 9, 3, 0, 224,
				224, 224, 224, 9, 24, 48, 9, 0, 0, 1, 128, 1, 128, 1, 128, 3, 0,
				3, 0, 3, 0, 6, 0, 6, 0, 6, 0, 12, 0, 12, 0, 12, 0, 8, 0, 24, 0,
				24, 0, 24, 0, 48, 0, 48, 0, 48, 0, 96, 0, 96, 0, 96, 0, 192, 0,
				192, 0, 15, 24, 48, 18, 1, 0, 7, 192, 31, 240, 63, 248, 60, 120,
				120, 60, 112, 28, 112, 28, 224, 14, 224, 14, 224, 14, 224, 14,
				224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 112, 28,
				112, 28, 112, 60, 60, 120, 63, 248, 31, 240, 7, 192, 8, 24, 24,
				18, 3, 0, 3, 7, 7, 15, 63, 255, 255, 7, 7, 7, 7, 7, 7, 7, 7, 7,
				7, 7, 7, 7, 7, 7, 7, 7, 15, 24, 48, 18, 1, 0, 7, 192, 31, 240,
				63, 248, 120, 60, 112, 28, 240, 14, 224, 14, 224, 14, 0, 14, 0,
				28, 0, 60, 0, 120, 0, 240, 3, 224, 7, 192, 31, 0, 60, 0, 120, 0,
				112, 0, 224, 0, 224, 0, 255, 254, 255, 254, 255, 254, 15, 24,
				48, 18, 1, 0, 7, 192, 31, 240, 63, 248, 56, 56, 112, 28, 112,
				28, 112, 28, 112, 28, 0, 28, 0, 56, 3, 248, 3, 240, 3, 248, 0,
				60, 0, 30, 0, 14, 224, 14, 224, 14, 224, 14, 112, 28, 120, 60,
				63, 248, 31, 240, 7, 192, 16, 24, 48, 18, 0, 0, 0, 24, 0, 56, 0,
				120, 0, 120, 0, 248, 1, 248, 3, 184, 3, 184, 7, 56, 14, 56, 14,
				56, 28, 56, 56, 56, 56, 56, 112, 56, 224, 56, 255, 255, 255,
				255, 255, 255, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 15, 24, 48,
				18, 1, 0, 63, 252, 63, 252, 63, 252, 56, 0, 56, 0, 56, 0, 112,
				0, 112, 0, 119, 192, 127, 240, 127, 248, 120, 124, 112, 28, 0,
				30, 0, 14, 0, 14, 0, 14, 224, 14, 224, 30, 240, 28, 120, 124,
				127, 248, 63, 240, 15, 128, 15, 24, 48, 18, 1, 0, 3, 192, 15,
				240, 31, 248, 60, 56, 56, 28, 112, 28, 112, 0, 112, 0, 96, 0,
				227, 192, 239, 240, 255, 248, 248, 60, 240, 28, 240, 14, 224,
				14, 224, 14, 96, 14, 112, 14, 112, 28, 56, 60, 63, 248, 31, 240,
				7, 192, 15, 24, 48, 18, 1, 0, 255, 254, 255, 254, 255, 254, 0,
				14, 0, 28, 0, 24, 0, 56, 0, 112, 0, 112, 0, 224, 0, 224, 1, 192,
				1, 192, 3, 128, 3, 128, 7, 0, 7, 0, 7, 0, 14, 0, 14, 0, 14, 0,
				28, 0, 28, 0, 28, 0, 15, 24, 48, 18, 1, 0, 7, 192, 31, 240, 63,
				248, 56, 60, 112, 28, 112, 28, 112, 28, 112, 28, 120, 60, 60,
				120, 31, 240, 15, 224, 63, 248, 120, 60, 112, 28, 224, 14, 224,
				14, 224, 14, 224, 14, 240, 28, 120, 60, 63, 248, 31, 240, 7,
				192, 15, 24, 48, 18, 1, 0, 7, 192, 31, 240, 63, 248, 120, 124,
				112, 60, 240, 28, 224, 30, 224, 14, 224, 14, 224, 14, 224, 30,
				224, 30, 112, 62, 127, 254, 63, 238, 15, 206, 0, 14, 0, 28, 224,
				28, 240, 60, 120, 120, 63, 240, 63, 224, 15, 128, 3, 18, 18, 9,
				4, 0, 224, 224, 224, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224,
				224, 224, 224, 3, 22, 22, 9, 4, 251, 224, 224, 224, 224, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 224, 224, 224, 224, 32, 96, 96, 192, 128,
				16, 16, 32, 19, 2, 0, 0, 3, 0, 15, 0, 63, 1, 252, 7, 224, 31,
				128, 254, 0, 240, 0, 240, 0, 254, 0, 31, 128, 7, 224, 1, 252, 0,
				127, 0, 15, 0, 3, 15, 9, 18, 19, 2, 4, 255, 254, 255, 254, 255,
				254, 0, 0, 0, 0, 0, 0, 255, 254, 255, 254, 255, 254, 16, 16, 32,
				19, 1, 0, 192, 0, 240, 0, 254, 0, 63, 128, 7, 224, 1, 248, 0,
				127, 0, 15, 0, 15, 0, 127, 1, 248, 7, 224, 63, 128, 254, 0, 240,
				0, 192, 0, 14, 25, 50, 18, 2, 0, 7, 192, 31, 240, 63, 248, 120,
				56, 112, 28, 240, 28, 224, 28, 224, 28, 0, 28, 0, 56, 0, 56, 0,
				112, 0, 224, 1, 224, 1, 192, 3, 128, 3, 128, 3, 128, 3, 128, 0,
				0, 0, 0, 3, 128, 3, 128, 3, 128, 3, 128, 29, 30, 120, 34, 1,
				251, 0, 7, 192, 0, 0, 63, 248, 0, 0, 255, 254, 0, 3, 240, 63,
				128, 7, 192, 7, 192, 15, 0, 3, 224, 30, 0, 1, 224, 28, 0, 0,
				240, 56, 15, 140, 112, 56, 31, 220, 56, 112, 60, 252, 56, 112,
				112, 124, 56, 96, 224, 56, 24, 224, 224, 56, 24, 225, 224, 56,
				24, 225, 192, 112, 56, 225, 192, 112, 56, 225, 192, 112, 112,
				225, 192, 224, 112, 225, 224, 224, 224, 112, 243, 243, 192, 112,
				255, 127, 128, 120, 62, 127, 0, 60, 0, 0, 0, 30, 0, 0, 0, 31, 0,
				0, 0, 15, 128, 0, 0, 3, 224, 120, 0, 1, 255, 248, 0, 0, 127,
				224, 0, 20, 25, 75, 22, 1, 0, 0, 240, 0, 0, 240, 0, 0, 248, 0,
				1, 248, 0, 1, 248, 0, 3, 156, 0, 3, 156, 0, 3, 156, 0, 7, 158,
				0, 7, 14, 0, 7, 14, 0, 15, 15, 0, 15, 15, 0, 14, 7, 0, 30, 7,
				128, 31, 255, 128, 31, 255, 128, 63, 255, 192, 60, 3, 192, 56,
				1, 192, 120, 1, 224, 120, 1, 224, 112, 0, 224, 240, 0, 240, 240,
				0, 240, 17, 25, 75, 22, 3, 0, 255, 240, 0, 255, 252, 0, 255,
				254, 0, 224, 62, 0, 224, 15, 0, 224, 15, 0, 224, 7, 0, 224, 7,
				0, 224, 15, 0, 224, 14, 0, 224, 62, 0, 255, 252, 0, 255, 252, 0,
				255, 254, 0, 224, 31, 0, 224, 7, 128, 224, 3, 128, 224, 3, 128,
				224, 3, 128, 224, 3, 128, 224, 7, 128, 224, 15, 0, 255, 254, 0,
				255, 254, 0, 255, 248, 0, 20, 25, 75, 24, 2, 0, 1, 252, 0, 7,
				255, 0, 15, 255, 128, 31, 7, 192, 60, 1, 224, 56, 0, 224, 112,
				0, 240, 112, 0, 112, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 112, 240, 0,
				112, 112, 0, 240, 120, 0, 224, 60, 1, 224, 63, 7, 192, 31, 255,
				128, 7, 254, 0, 1, 248, 0, 18, 25, 75, 24, 3, 0, 255, 240, 0,
				255, 252, 0, 255, 254, 0, 224, 31, 0, 224, 15, 0, 224, 7, 128,
				224, 3, 128, 224, 3, 128, 224, 1, 192, 224, 1, 192, 224, 1, 192,
				224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192,
				224, 3, 192, 224, 3, 128, 224, 3, 128, 224, 7, 128, 224, 15, 0,
				224, 30, 0, 255, 254, 0, 255, 252, 0, 255, 240, 0, 17, 25, 75,
				22, 3, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224,
				0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 255, 255, 128, 255, 255, 128, 255, 255, 128, 16,
				25, 50, 20, 3, 0, 255, 255, 255, 255, 255, 255, 224, 0, 224, 0,
				224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 255, 252, 255,
				252, 255, 252, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0,
				224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 22, 25, 75, 25, 1, 0, 0,
				254, 0, 3, 255, 128, 15, 255, 192, 31, 131, 240, 62, 0, 240, 60,
				0, 120, 120, 0, 56, 112, 0, 56, 240, 0, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 224, 15, 252, 224, 15, 252, 224, 15, 252, 224, 0, 28,
				240, 0, 28, 112, 0, 28, 120, 0, 60, 56, 0, 60, 60, 0, 252, 31,
				1, 252, 15, 255, 220, 7, 255, 28, 1, 252, 28, 18, 25, 75, 24, 3,
				0, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 255, 255, 192, 255, 255, 192, 255, 255, 192,
				224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192,
				224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192,
				224, 1, 192, 3, 25, 25, 9, 3, 0, 224, 224, 224, 224, 224, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				224, 224, 224, 224, 224, 224, 13, 25, 50, 16, 1, 0, 0, 56, 0,
				56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
				56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 224, 56, 224, 56, 224,
				56, 224, 56, 240, 120, 120, 240, 127, 240, 63, 224, 31, 128, 20,
				25, 75, 22, 3, 0, 224, 3, 192, 224, 7, 128, 224, 15, 0, 224, 30,
				0, 224, 60, 0, 224, 120, 0, 224, 240, 0, 225, 224, 0, 227, 192,
				0, 231, 192, 0, 239, 128, 0, 255, 192, 0, 255, 192, 0, 249, 224,
				0, 240, 240, 0, 224, 112, 0, 224, 120, 0, 224, 60, 0, 224, 28,
				0, 224, 30, 0, 224, 15, 0, 224, 7, 128, 224, 3, 192, 224, 3,
				224, 224, 1, 240, 14, 25, 50, 18, 3, 0, 224, 0, 224, 0, 224, 0,
				224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0,
				224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0,
				224, 0, 224, 0, 224, 0, 255, 252, 255, 252, 255, 252, 21, 25,
				75, 27, 3, 0, 240, 0, 120, 240, 0, 120, 248, 0, 248, 248, 0,
				248, 252, 1, 248, 252, 1, 248, 252, 1, 248, 236, 1, 184, 238, 3,
				184, 238, 3, 184, 230, 3, 56, 231, 7, 56, 231, 7, 56, 227, 6,
				56, 227, 142, 56, 227, 142, 56, 227, 142, 56, 225, 140, 56, 225,
				220, 56, 225, 220, 56, 224, 216, 56, 224, 248, 56, 224, 248, 56,
				224, 112, 56, 224, 112, 56, 19, 25, 75, 24, 2, 0, 240, 0, 224,
				240, 0, 224, 248, 0, 224, 252, 0, 224, 252, 0, 224, 254, 0, 224,
				239, 0, 224, 231, 0, 224, 231, 128, 224, 227, 192, 224, 227,
				192, 224, 225, 224, 224, 224, 224, 224, 224, 240, 224, 224, 120,
				224, 224, 56, 224, 224, 60, 224, 224, 28, 224, 224, 30, 224,
				224, 15, 224, 224, 7, 224, 224, 7, 224, 224, 3, 224, 224, 1,
				224, 224, 1, 224, 23, 25, 75, 25, 1, 0, 0, 254, 0, 3, 255, 128,
				15, 239, 224, 31, 1, 240, 62, 0, 248, 60, 0, 120, 120, 0, 60,
				112, 0, 28, 240, 0, 30, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224,
				0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14, 240, 0, 30, 240, 0,
				30, 120, 0, 60, 60, 0, 120, 62, 0, 248, 31, 1, 240, 15, 239,
				224, 3, 255, 128, 0, 254, 0, 17, 25, 75, 22, 3, 0, 255, 248, 0,
				255, 254, 0, 255, 255, 0, 224, 15, 0, 224, 7, 128, 224, 3, 128,
				224, 3, 128, 224, 3, 128, 224, 3, 128, 224, 3, 128, 224, 7, 128,
				224, 15, 0, 255, 255, 0, 255, 254, 0, 255, 248, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 23, 26, 78, 26, 1, 255, 0,
				254, 0, 3, 255, 128, 15, 239, 224, 31, 1, 240, 62, 0, 248, 60,
				0, 120, 120, 0, 60, 112, 0, 28, 240, 0, 30, 224, 0, 14, 224, 0,
				14, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14,
				240, 0, 30, 240, 2, 30, 120, 7, 60, 60, 7, 184, 62, 3, 248, 31,
				1, 240, 15, 239, 248, 3, 255, 188, 0, 254, 30, 0, 0, 12, 19, 25,
				75, 24, 3, 0, 255, 252, 0, 255, 255, 0, 255, 255, 128, 224, 7,
				128, 224, 3, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 3, 192, 224, 3, 128, 224, 15, 128, 255, 255, 0, 255,
				254, 0, 255, 255, 0, 224, 15, 128, 224, 7, 128, 224, 3, 128,
				224, 3, 192, 224, 3, 192, 224, 3, 192, 224, 1, 192, 224, 1, 192,
				224, 1, 192, 224, 1, 224, 19, 25, 75, 22, 1, 0, 3, 248, 0, 15,
				254, 0, 31, 255, 0, 60, 15, 128, 56, 3, 192, 112, 1, 192, 112,
				1, 192, 112, 0, 0, 120, 0, 0, 124, 0, 0, 63, 192, 0, 31, 248, 0,
				7, 255, 0, 0, 127, 128, 0, 15, 192, 0, 1, 224, 0, 0, 224, 224,
				0, 224, 240, 0, 224, 112, 1, 224, 120, 1, 192, 62, 7, 192, 63,
				255, 128, 15, 254, 0, 3, 248, 0, 19, 25, 75, 20, 0, 0, 255, 255,
				224, 255, 255, 224, 255, 255, 224, 0, 224, 0, 0, 224, 0, 0, 224,
				0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224,
				0, 0, 224, 0, 0, 224, 0, 18, 25, 75, 24, 3, 0, 224, 1, 192, 224,
				1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224,
				1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224,
				1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224,
				1, 192, 224, 1, 192, 224, 1, 192, 240, 3, 192, 120, 7, 128, 124,
				15, 128, 63, 255, 0, 31, 254, 0, 3, 240, 0, 19, 25, 75, 22, 1,
				0, 240, 1, 224, 240, 1, 224, 240, 1, 224, 112, 1, 192, 120, 3,
				192, 120, 3, 192, 56, 3, 128, 56, 3, 128, 60, 7, 128, 28, 7, 0,
				28, 7, 0, 30, 15, 0, 14, 14, 0, 14, 14, 0, 15, 14, 0, 7, 28, 0,
				7, 28, 0, 7, 156, 0, 3, 184, 0, 3, 184, 0, 3, 184, 0, 1, 240, 0,
				1, 240, 0, 0, 224, 0, 0, 224, 0, 29, 25, 100, 31, 1, 0, 240, 7,
				0, 120, 240, 7, 0, 120, 240, 15, 128, 120, 112, 15, 128, 112,
				112, 15, 128, 112, 120, 29, 192, 240, 120, 29, 192, 240, 56, 29,
				192, 224, 56, 29, 192, 224, 56, 56, 224, 224, 60, 56, 225, 224,
				28, 56, 225, 192, 28, 48, 225, 192, 28, 112, 113, 192, 28, 112,
				113, 192, 14, 112, 115, 128, 14, 224, 59, 128, 14, 224, 59, 128,
				14, 224, 59, 128, 7, 224, 63, 128, 7, 192, 31, 0, 7, 192, 31, 0,
				7, 192, 31, 0, 3, 128, 14, 0, 3, 128, 14, 0, 20, 25, 75, 22, 1,
				0, 248, 0, 240, 120, 1, 224, 60, 3, 192, 28, 3, 192, 30, 7, 128,
				15, 7, 0, 15, 15, 0, 7, 158, 0, 3, 156, 0, 3, 252, 0, 1, 248, 0,
				0, 240, 0, 0, 240, 0, 1, 248, 0, 1, 248, 0, 3, 156, 0, 7, 158,
				0, 7, 14, 0, 15, 15, 0, 30, 7, 128, 30, 7, 128, 60, 3, 192, 120,
				1, 224, 120, 1, 224, 240, 0, 240, 21, 25, 75, 22, 0, 0, 240, 0,
				120, 120, 0, 240, 120, 0, 224, 60, 1, 224, 28, 1, 192, 30, 3,
				192, 14, 7, 128, 15, 7, 128, 7, 143, 0, 3, 142, 0, 3, 222, 0, 1,
				220, 0, 1, 252, 0, 0, 248, 0, 0, 248, 0, 0, 112, 0, 0, 112, 0,
				0, 112, 0, 0, 112, 0, 0, 112, 0, 0, 112, 0, 0, 112, 0, 0, 112,
				0, 0, 112, 0, 0, 112, 0, 18, 25, 75, 20, 1, 0, 127, 255, 192,
				127, 255, 192, 127, 255, 192, 0, 7, 128, 0, 15, 128, 0, 15, 0,
				0, 30, 0, 0, 60, 0, 0, 60, 0, 0, 120, 0, 0, 240, 0, 1, 224, 0,
				1, 224, 0, 3, 192, 0, 7, 128, 0, 7, 128, 0, 15, 0, 0, 30, 0, 0,
				60, 0, 0, 60, 0, 0, 120, 0, 0, 240, 0, 0, 255, 255, 192, 255,
				255, 192, 255, 255, 192, 6, 32, 32, 9, 2, 249, 252, 252, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				224, 252, 252, 9, 24, 48, 9, 0, 0, 192, 0, 192, 0, 96, 0, 96, 0,
				96, 0, 48, 0, 48, 0, 48, 0, 16, 0, 24, 0, 24, 0, 24, 0, 12, 0,
				12, 0, 12, 0, 6, 0, 6, 0, 6, 0, 2, 0, 3, 0, 3, 0, 3, 0, 1, 128,
				1, 128, 6, 32, 32, 9, 1, 249, 252, 252, 28, 28, 28, 28, 28, 28,
				28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
				28, 28, 28, 28, 28, 28, 252, 252, 12, 13, 26, 16, 1, 11, 6, 0,
				15, 0, 15, 0, 31, 128, 25, 128, 25, 128, 57, 192, 48, 192, 112,
				224, 96, 96, 96, 96, 224, 112, 192, 48, 18, 2, 6, 18, 0, 250,
				255, 255, 192, 255, 255, 192, 6, 5, 5, 11, 1, 20, 224, 240, 112,
				56, 28, 16, 18, 36, 18, 1, 0, 15, 224, 63, 248, 60, 120, 112,
				60, 112, 28, 0, 28, 0, 60, 1, 252, 31, 252, 126, 28, 120, 28,
				240, 28, 224, 28, 224, 60, 224, 124, 121, 254, 127, 223, 63,
				143, 15, 25, 50, 18, 2, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224,
				0, 224, 0, 224, 0, 227, 224, 239, 240, 255, 248, 248, 60, 240,
				28, 240, 30, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 224,
				14, 240, 30, 240, 28, 252, 60, 255, 248, 239, 240, 231, 224, 14,
				18, 36, 16, 1, 0, 7, 192, 31, 240, 63, 248, 56, 60, 112, 28,
				112, 28, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 28, 224,
				28, 112, 28, 120, 56, 63, 248, 31, 240, 7, 192, 15, 25, 50, 18,
				1, 0, 0, 14, 0, 14, 0, 14, 0, 14, 0, 14, 0, 14, 0, 14, 7, 206,
				31, 238, 63, 254, 124, 62, 112, 30, 240, 30, 224, 14, 224, 14,
				224, 14, 224, 14, 224, 14, 224, 14, 240, 30, 240, 30, 120, 62,
				127, 254, 63, 238, 15, 206, 15, 18, 36, 18, 2, 0, 7, 192, 31,
				240, 63, 248, 120, 60, 112, 28, 240, 14, 224, 14, 224, 14, 255,
				254, 255, 254, 224, 0, 224, 0, 240, 14, 112, 30, 120, 60, 63,
				248, 31, 240, 7, 192, 8, 25, 25, 9, 1, 0, 15, 31, 60, 56, 56,
				56, 56, 255, 255, 255, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
				56, 56, 56, 56, 56, 15, 25, 50, 18, 1, 249, 7, 206, 31, 238, 63,
				254, 124, 62, 112, 30, 240, 30, 224, 14, 224, 14, 224, 14, 224,
				14, 224, 14, 224, 14, 240, 30, 112, 62, 120, 62, 63, 254, 31,
				238, 7, 142, 0, 14, 224, 14, 224, 28, 240, 28, 124, 120, 63,
				248, 31, 224, 14, 25, 50, 18, 2, 0, 224, 0, 224, 0, 224, 0, 224,
				0, 224, 0, 224, 0, 224, 0, 227, 224, 239, 240, 255, 248, 248,
				60, 240, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 3, 25, 25, 7, 2, 0, 224, 224, 224, 224, 0, 0, 0, 224, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				224, 224, 224, 6, 32, 32, 7, 255, 249, 28, 28, 28, 28, 0, 0, 0,
				28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
				28, 28, 28, 28, 28, 28, 60, 252, 248, 15, 25, 50, 16, 1, 0, 224,
				0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 120,
				224, 240, 225, 224, 227, 192, 231, 128, 239, 0, 255, 0, 255, 0,
				251, 128, 243, 192, 225, 192, 225, 224, 224, 224, 224, 240, 224,
				120, 224, 56, 224, 60, 224, 30, 3, 25, 25, 7, 2, 0, 224, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 23, 18, 54,
				27, 2, 0, 227, 192, 240, 239, 243, 252, 255, 247, 252, 248, 126,
				30, 240, 60, 14, 224, 56, 14, 224, 56, 14, 224, 56, 14, 224, 56,
				14, 224, 56, 14, 224, 56, 14, 224, 56, 14, 224, 56, 14, 224, 56,
				14, 224, 56, 14, 224, 56, 14, 224, 56, 14, 224, 56, 14, 14, 18,
				36, 18, 2, 0, 227, 224, 239, 248, 255, 248, 248, 60, 240, 28,
				224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28,
				224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 15, 18,
				36, 18, 1, 0, 7, 192, 31, 240, 63, 248, 120, 60, 112, 28, 240,
				30, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 240,
				30, 112, 28, 120, 60, 63, 248, 31, 240, 7, 192, 15, 25, 50, 18,
				2, 249, 3, 192, 239, 240, 255, 248, 248, 60, 240, 28, 240, 30,
				224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 240, 30,
				240, 28, 248, 60, 255, 248, 239, 240, 231, 224, 224, 0, 224, 0,
				224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 15, 25, 50, 18, 1, 249,
				7, 192, 31, 238, 63, 254, 124, 62, 112, 30, 240, 30, 224, 14,
				224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 240, 30, 112, 30,
				120, 62, 63, 254, 31, 238, 15, 206, 0, 14, 0, 14, 0, 14, 0, 14,
				0, 14, 0, 14, 0, 14, 8, 18, 18, 11, 2, 0, 231, 239, 255, 252,
				240, 240, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				224, 13, 18, 36, 16, 2, 0, 15, 128, 63, 224, 127, 224, 112, 240,
				224, 112, 224, 0, 112, 0, 126, 0, 63, 192, 7, 240, 0, 240, 0,
				120, 224, 56, 224, 56, 240, 112, 127, 240, 127, 224, 31, 128, 8,
				22, 22, 9, 1, 0, 56, 56, 56, 56, 255, 255, 255, 56, 56, 56, 56,
				56, 56, 56, 56, 56, 56, 56, 56, 60, 63, 31, 14, 18, 36, 18, 2,
				0, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				60, 240, 124, 127, 252, 127, 220, 31, 28, 15, 18, 36, 16, 0, 0,
				224, 14, 224, 14, 112, 28, 112, 28, 112, 28, 56, 56, 56, 56, 56,
				56, 28, 112, 28, 112, 28, 112, 14, 224, 14, 224, 14, 224, 7,
				192, 7, 192, 3, 128, 3, 128, 23, 18, 54, 23, 0, 0, 224, 56, 14,
				224, 56, 14, 112, 124, 28, 112, 124, 28, 112, 108, 28, 56, 238,
				28, 56, 238, 56, 56, 238, 56, 56, 198, 56, 24, 198, 48, 29, 199,
				112, 29, 199, 112, 29, 199, 112, 13, 131, 96, 15, 131, 224, 15,
				131, 224, 7, 1, 192, 7, 1, 192, 15, 18, 36, 16, 0, 0, 240, 30,
				120, 28, 56, 56, 60, 112, 28, 112, 14, 224, 15, 224, 7, 192, 3,
				128, 7, 192, 7, 192, 15, 224, 30, 224, 28, 112, 56, 120, 56, 56,
				112, 28, 240, 30, 14, 25, 50, 16, 1, 249, 224, 28, 224, 28, 240,
				56, 112, 56, 112, 56, 112, 112, 56, 112, 56, 112, 56, 224, 60,
				224, 28, 224, 29, 192, 29, 192, 15, 192, 15, 128, 15, 128, 7, 0,
				7, 0, 7, 0, 14, 0, 14, 0, 28, 0, 124, 0, 120, 0, 112, 0, 14, 18,
				36, 16, 1, 0, 127, 248, 127, 248, 127, 248, 0, 120, 0, 240, 0,
				224, 1, 192, 3, 192, 7, 128, 7, 0, 14, 0, 28, 0, 60, 0, 120, 0,
				112, 0, 255, 252, 255, 252, 255, 252, 8, 32, 32, 11, 1, 249, 15,
				31, 28, 24, 24, 24, 24, 24, 24, 24, 24, 24, 56, 56, 112, 224,
				224, 112, 56, 56, 24, 24, 24, 24, 24, 24, 24, 24, 24, 28, 31,
				15, 2, 31, 31, 9, 3, 249, 192, 192, 192, 192, 192, 192, 192,
				192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
				192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 8, 32,
				32, 11, 1, 249, 240, 248, 56, 24, 24, 24, 24, 24, 24, 24, 24,
				24, 28, 28, 14, 7, 7, 14, 28, 28, 24, 24, 24, 24, 24, 24, 24,
				24, 24, 56, 248, 240, 14, 6, 12, 19, 2, 9, 24, 0, 124, 12, 127,
				12, 199, 220, 193, 248, 0, 240, 255, 255, 255, 255, 255, 255,
				255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
				255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
				255, 0, 0, 0, 9, 0, 1, 3, 25, 25, 11, 4, 249, 224, 224, 224,
				224, 0, 0, 64, 64, 224, 224, 224, 224, 224, 224, 224, 224, 224,
				224, 224, 224, 224, 224, 224, 224, 224, 14, 25, 50, 19, 2, 252,
				0, 32, 0, 96, 0, 64, 7, 224, 31, 240, 60, 248, 120, 188, 112,
				156, 112, 156, 225, 128, 225, 0, 225, 0, 227, 0, 227, 0, 226,
				12, 226, 28, 118, 28, 124, 60, 60, 120, 31, 240, 15, 224, 8, 0,
				24, 0, 16, 0, 16, 0, 15, 24, 48, 19, 1, 0, 3, 192, 15, 248, 31,
				252, 60, 60, 120, 30, 112, 14, 112, 14, 112, 0, 112, 0, 56, 0,
				56, 0, 255, 192, 255, 192, 12, 0, 14, 0, 14, 0, 12, 0, 28, 0,
				24, 0, 56, 0, 115, 134, 255, 254, 255, 254, 96, 124, 12, 13, 26,
				18, 3, 5, 230, 48, 255, 240, 127, 240, 112, 224, 96, 96, 224,
				112, 224, 112, 224, 112, 96, 96, 112, 224, 127, 240, 255, 240,
				230, 48, 16, 24, 48, 18, 1, 0, 224, 7, 224, 7, 112, 14, 112, 14,
				56, 28, 56, 28, 28, 56, 28, 56, 14, 112, 14, 112, 7, 224, 127,
				254, 127, 254, 127, 254, 1, 192, 1, 192, 127, 254, 127, 254,
				127, 254, 1, 192, 1, 192, 1, 192, 1, 192, 1, 192, 2, 32, 32, 9,
				3, 249, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
				192, 192, 0, 0, 0, 0, 0, 0, 192, 192, 192, 192, 192, 192, 192,
				192, 192, 192, 192, 192, 192, 15, 32, 64, 18, 1, 249, 3, 192,
				15, 240, 31, 248, 28, 120, 56, 60, 56, 28, 56, 28, 60, 0, 30, 0,
				31, 128, 63, 224, 113, 240, 224, 248, 224, 124, 224, 28, 224,
				30, 112, 14, 124, 14, 62, 14, 31, 28, 15, 156, 3, 248, 1, 240,
				0, 240, 0, 120, 112, 56, 112, 56, 120, 56, 56, 112, 63, 240, 31,
				224, 7, 128, 8, 3, 3, 11, 1, 22, 231, 231, 231, 24, 25, 75, 25,
				0, 0, 0, 254, 0, 3, 255, 128, 7, 1, 224, 12, 0, 112, 24, 0, 24,
				48, 126, 12, 96, 255, 134, 97, 193, 198, 195, 128, 195, 195, 0,
				3, 199, 0, 3, 134, 0, 1, 134, 0, 1, 134, 0, 1, 134, 0, 1, 199,
				0, 3, 195, 128, 195, 97, 225, 198, 96, 255, 134, 48, 62, 12, 24,
				0, 24, 28, 0, 56, 7, 1, 224, 3, 255, 128, 0, 254, 0, 10, 15, 30,
				12, 1, 10, 63, 0, 119, 128, 97, 128, 1, 128, 7, 128, 127, 128,
				225, 128, 193, 128, 195, 128, 231, 128, 125, 192, 0, 0, 0, 0,
				255, 192, 255, 192, 12, 9, 18, 18, 3, 5, 28, 112, 56, 224, 113,
				192, 227, 128, 195, 0, 227, 128, 113, 192, 56, 224, 28, 112, 16,
				9, 18, 19, 1, 3, 255, 255, 255, 255, 255, 255, 0, 7, 0, 7, 0, 7,
				0, 7, 0, 7, 0, 7, 8, 2, 2, 11, 1, 8, 255, 255, 24, 25, 75, 25,
				0, 0, 0, 126, 0, 3, 255, 128, 7, 1, 224, 12, 0, 112, 24, 0, 24,
				48, 0, 12, 97, 255, 6, 97, 255, 134, 193, 129, 195, 193, 128,
				195, 193, 128, 195, 129, 129, 129, 129, 255, 1, 129, 252, 1,
				129, 142, 1, 193, 134, 3, 193, 131, 3, 97, 129, 134, 97, 129,
				198, 48, 0, 12, 24, 0, 24, 28, 0, 56, 7, 1, 224, 3, 255, 128, 0,
				126, 0, 9, 2, 4, 11, 1, 22, 255, 128, 255, 128, 9, 9, 18, 13, 2,
				15, 62, 0, 127, 0, 227, 128, 193, 128, 193, 128, 193, 128, 227,
				128, 127, 0, 62, 0, 17, 21, 63, 19, 1, 0, 1, 192, 0, 1, 192, 0,
				1, 192, 0, 1, 192, 0, 1, 192, 0, 1, 192, 0, 1, 192, 0, 255, 255,
				128, 255, 255, 128, 255, 255, 128, 1, 192, 0, 1, 192, 0, 1, 192,
				0, 1, 192, 0, 1, 192, 0, 1, 192, 0, 0, 0, 0, 0, 0, 0, 255, 255,
				128, 255, 255, 128, 255, 255, 128, 9, 15, 30, 11, 1, 9, 30, 0,
				127, 0, 99, 0, 193, 128, 193, 128, 1, 128, 3, 0, 7, 0, 30, 0,
				56, 0, 112, 0, 224, 0, 192, 0, 255, 128, 255, 128, 9, 15, 30,
				11, 1, 9, 62, 0, 127, 0, 227, 128, 193, 128, 193, 128, 3, 128,
				15, 0, 15, 0, 3, 128, 1, 128, 193, 128, 193, 128, 227, 128, 127,
				0, 62, 0, 7, 5, 5, 11, 3, 22, 30, 60, 56, 112, 224, 14, 24, 48,
				19, 2, 250, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 60, 240, 124, 255, 252, 255, 220, 255, 28, 224, 0, 224,
				0, 224, 0, 224, 0, 224, 0, 224, 0, 16, 30, 60, 17, 1, 251, 7,
				255, 31, 255, 63, 140, 63, 140, 127, 140, 127, 140, 255, 140,
				255, 140, 255, 140, 255, 140, 127, 140, 127, 140, 63, 140, 63,
				140, 31, 140, 3, 140, 1, 140, 1, 140, 1, 140, 1, 140, 1, 140, 1,
				140, 1, 140, 1, 140, 1, 140, 1, 140, 1, 140, 1, 140, 1, 140, 1,
				140, 4, 4, 4, 9, 3, 11, 96, 240, 240, 96, 7, 7, 7, 11, 2, 249,
				24, 24, 60, 14, 6, 206, 124, 5, 15, 15, 11, 2, 9, 24, 56, 248,
				248, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 10, 15, 30, 12,
				1, 10, 30, 0, 127, 128, 97, 128, 225, 192, 192, 192, 192, 192,
				192, 192, 192, 192, 225, 192, 97, 128, 127, 128, 30, 0, 0, 0,
				255, 192, 255, 192, 12, 9, 18, 18, 3, 5, 227, 128, 113, 192, 56,
				224, 28, 112, 12, 48, 28, 112, 56, 224, 113, 192, 227, 128, 25,
				25, 100, 28, 1, 0, 0, 0, 48, 0, 24, 0, 112, 0, 56, 0, 96, 0,
				248, 0, 224, 0, 248, 1, 192, 0, 24, 1, 128, 0, 24, 3, 128, 0,
				24, 3, 0, 0, 24, 7, 0, 0, 24, 14, 0, 0, 24, 12, 0, 0, 24, 28, 6,
				0, 24, 24, 14, 0, 24, 56, 30, 0, 24, 112, 62, 0, 24, 96, 118, 0,
				0, 224, 102, 0, 1, 192, 198, 0, 1, 129, 198, 0, 3, 131, 134, 0,
				3, 3, 255, 128, 7, 3, 255, 128, 6, 0, 6, 0, 14, 0, 6, 0, 12, 0,
				6, 0, 25, 25, 100, 28, 1, 0, 0, 0, 96, 0, 24, 0, 224, 0, 56, 0,
				192, 0, 248, 1, 128, 0, 248, 3, 128, 0, 24, 3, 0, 0, 24, 6, 0,
				0, 24, 14, 0, 0, 24, 12, 0, 0, 24, 28, 0, 0, 24, 24, 0, 0, 24,
				56, 60, 0, 24, 48, 255, 0, 24, 112, 195, 128, 24, 97, 129, 128,
				24, 193, 129, 128, 1, 192, 3, 128, 1, 128, 7, 0, 3, 128, 14, 0,
				3, 0, 60, 0, 6, 0, 112, 0, 14, 0, 224, 0, 12, 1, 192, 0, 28, 1,
				255, 128, 24, 1, 255, 128, 25, 24, 96, 28, 1, 0, 62, 0, 14, 0,
				127, 0, 12, 0, 99, 128, 24, 0, 193, 128, 56, 0, 193, 128, 48, 0,
				3, 128, 96, 0, 15, 0, 224, 0, 15, 128, 192, 0, 1, 193, 128, 0,
				0, 195, 128, 0, 192, 195, 6, 0, 192, 199, 14, 0, 97, 206, 30, 0,
				127, 140, 62, 0, 30, 24, 118, 0, 0, 56, 102, 0, 0, 48, 198, 0,
				0, 97, 198, 0, 0, 227, 134, 0, 1, 195, 255, 128, 1, 131, 255,
				128, 3, 0, 6, 0, 7, 0, 6, 0, 6, 0, 6, 0, 14, 25, 50, 19, 3, 249,
				3, 128, 3, 128, 3, 128, 3, 128, 0, 0, 0, 0, 3, 128, 3, 128, 3,
				128, 7, 128, 7, 0, 15, 0, 30, 0, 60, 0, 120, 0, 112, 0, 240, 0,
				224, 28, 224, 28, 224, 28, 240, 60, 120, 120, 127, 240, 63, 224,
				7, 128, 20, 31, 93, 22, 1, 0, 3, 192, 0, 1, 224, 0, 0, 224, 0,
				0, 112, 0, 0, 56, 0, 0, 0, 0, 0, 240, 0, 0, 240, 0, 0, 240, 0,
				1, 248, 0, 1, 248, 0, 3, 252, 0, 3, 156, 0, 3, 156, 0, 7, 158,
				0, 7, 14, 0, 7, 14, 0, 15, 15, 0, 14, 15, 0, 14, 7, 0, 30, 7,
				128, 31, 255, 128, 31, 255, 128, 63, 255, 192, 60, 3, 192, 56,
				1, 192, 120, 1, 224, 120, 1, 224, 112, 0, 224, 240, 0, 240, 240,
				0, 240, 20, 31, 93, 22, 1, 0, 0, 60, 0, 0, 120, 0, 0, 112, 0, 0,
				224, 0, 1, 192, 0, 0, 0, 0, 0, 240, 0, 0, 240, 0, 0, 240, 0, 1,
				248, 0, 1, 248, 0, 3, 252, 0, 3, 156, 0, 3, 156, 0, 7, 158, 0,
				7, 14, 0, 7, 14, 0, 15, 15, 0, 15, 15, 0, 14, 7, 0, 30, 7, 128,
				31, 255, 128, 31, 255, 128, 63, 255, 192, 60, 3, 192, 120, 1,
				192, 120, 1, 224, 120, 1, 224, 112, 0, 224, 240, 0, 240, 240, 0,
				240, 20, 31, 93, 22, 1, 0, 0, 64, 0, 0, 224, 0, 1, 240, 0, 3,
				184, 0, 7, 28, 0, 0, 0, 0, 0, 240, 0, 0, 240, 0, 0, 240, 0, 1,
				248, 0, 1, 248, 0, 3, 252, 0, 3, 156, 0, 3, 156, 0, 7, 158, 0,
				7, 14, 0, 7, 14, 0, 15, 15, 0, 15, 15, 0, 14, 7, 0, 30, 7, 128,
				31, 255, 128, 31, 255, 128, 63, 255, 192, 60, 3, 192, 56, 1,
				192, 120, 1, 224, 120, 1, 224, 112, 0, 224, 240, 0, 240, 240, 0,
				240, 20, 30, 90, 22, 1, 0, 1, 198, 0, 3, 254, 0, 7, 252, 0, 6,
				56, 0, 0, 0, 0, 0, 240, 0, 0, 240, 0, 0, 240, 0, 1, 248, 0, 1,
				248, 0, 3, 252, 0, 3, 156, 0, 3, 156, 0, 7, 158, 0, 7, 14, 0, 7,
				14, 0, 15, 15, 0, 15, 15, 0, 14, 7, 0, 30, 7, 128, 31, 255, 128,
				31, 255, 128, 63, 255, 192, 60, 3, 192, 56, 1, 192, 120, 1, 224,
				120, 1, 224, 112, 0, 224, 240, 0, 240, 240, 0, 240, 20, 30, 90,
				22, 1, 0, 3, 156, 0, 3, 156, 0, 3, 156, 0, 0, 0, 0, 0, 0, 0, 0,
				240, 0, 0, 240, 0, 0, 240, 0, 1, 248, 0, 1, 248, 0, 3, 252, 0,
				3, 156, 0, 3, 156, 0, 7, 158, 0, 7, 14, 0, 7, 14, 0, 15, 15, 0,
				15, 15, 0, 14, 7, 0, 30, 7, 128, 31, 255, 128, 31, 255, 128, 63,
				255, 192, 60, 3, 192, 56, 1, 192, 120, 1, 224, 120, 1, 224, 112,
				0, 224, 240, 0, 240, 240, 0, 240, 20, 31, 93, 22, 1, 0, 0, 240,
				0, 1, 152, 0, 1, 8, 0, 1, 8, 0, 1, 152, 0, 0, 240, 0, 0, 0, 0,
				0, 240, 0, 0, 240, 0, 1, 248, 0, 1, 248, 0, 3, 252, 0, 3, 156,
				0, 3, 156, 0, 7, 158, 0, 7, 14, 0, 7, 14, 0, 15, 15, 0, 14, 15,
				0, 14, 7, 0, 30, 7, 128, 31, 255, 128, 31, 255, 128, 63, 255,
				192, 60, 3, 192, 56, 1, 192, 120, 1, 224, 120, 1, 224, 112, 0,
				224, 240, 0, 240, 240, 0, 240, 29, 25, 100, 32, 1, 0, 0, 127,
				255, 248, 0, 127, 255, 248, 0, 255, 255, 248, 0, 227, 128, 0, 1,
				195, 128, 0, 1, 195, 128, 0, 3, 195, 128, 0, 3, 131, 128, 0, 3,
				131, 128, 0, 7, 131, 128, 0, 7, 3, 128, 0, 7, 3, 255, 240, 15,
				3, 255, 240, 14, 3, 255, 240, 30, 3, 128, 0, 31, 255, 128, 0,
				31, 255, 128, 0, 63, 255, 128, 0, 56, 3, 128, 0, 120, 3, 128, 0,
				120, 3, 128, 0, 112, 3, 128, 0, 240, 3, 255, 248, 224, 3, 255,
				248, 224, 3, 255, 248, 20, 32, 96, 23, 2, 249, 1, 248, 0, 7,
				254, 0, 15, 255, 128, 31, 7, 128, 60, 3, 192, 120, 1, 224, 112,
				0, 224, 112, 0, 224, 240, 0, 0, 240, 0, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 240, 0, 112, 240, 0, 112, 112,
				0, 240, 112, 0, 224, 120, 1, 224, 60, 3, 192, 31, 7, 192, 15,
				255, 128, 7, 254, 0, 1, 248, 0, 0, 96, 0, 0, 96, 0, 0, 240, 0,
				0, 56, 0, 0, 24, 0, 3, 56, 0, 1, 240, 0, 17, 31, 93, 22, 3, 0,
				15, 0, 0, 7, 128, 0, 3, 128, 0, 1, 192, 0, 0, 224, 0, 0, 0, 0,
				255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0,
				0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0,
				0, 255, 255, 128, 255, 255, 128, 255, 255, 128, 17, 31, 93, 22,
				3, 0, 0, 120, 0, 0, 240, 0, 0, 224, 0, 1, 192, 0, 3, 128, 0, 0,
				0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224,
				0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224,
				0, 0, 255, 255, 128, 255, 255, 128, 255, 255, 128, 17, 31, 93,
				22, 3, 0, 0, 128, 0, 1, 192, 0, 3, 224, 0, 7, 112, 0, 14, 56, 0,
				0, 0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224,
				0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 255, 255, 128, 255, 255, 128, 255, 255, 128, 17,
				30, 90, 22, 3, 0, 28, 56, 0, 28, 56, 0, 28, 56, 0, 0, 0, 0, 0,
				0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224,
				0, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224,
				0, 0, 255, 255, 128, 255, 255, 128, 255, 255, 128, 7, 31, 31, 9,
				0, 0, 240, 120, 56, 28, 14, 0, 28, 28, 28, 28, 28, 28, 28, 28,
				28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
				28, 7, 31, 31, 9, 2, 0, 30, 60, 56, 112, 224, 0, 112, 112, 112,
				112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112,
				112, 112, 112, 112, 112, 112, 112, 112, 112, 9, 31, 62, 9, 0, 0,
				8, 0, 28, 0, 62, 0, 119, 0, 227, 128, 0, 0, 28, 0, 28, 0, 28, 0,
				28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0,
				28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0,
				28, 0, 28, 0, 28, 0, 28, 0, 9, 30, 60, 9, 0, 0, 227, 128, 227,
				128, 227, 128, 0, 0, 0, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0,
				28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0,
				28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0,
				28, 0, 28, 0, 21, 25, 75, 23, 0, 0, 31, 254, 0, 31, 255, 128,
				31, 255, 192, 28, 3, 224, 28, 0, 224, 28, 0, 240, 28, 0, 112,
				28, 0, 112, 28, 0, 56, 28, 0, 56, 28, 0, 56, 255, 192, 56, 255,
				192, 56, 28, 0, 56, 28, 0, 56, 28, 0, 56, 28, 0, 120, 28, 0,
				112, 28, 0, 112, 28, 0, 240, 28, 0, 224, 28, 3, 192, 31, 255,
				192, 31, 255, 128, 31, 254, 0, 19, 30, 90, 24, 2, 0, 1, 198, 0,
				3, 254, 0, 7, 252, 0, 6, 56, 0, 0, 0, 0, 240, 0, 224, 248, 0,
				224, 248, 0, 224, 252, 0, 224, 252, 0, 224, 254, 0, 224, 239, 0,
				224, 231, 0, 224, 231, 128, 224, 227, 192, 224, 227, 192, 224,
				225, 224, 224, 224, 224, 224, 224, 240, 224, 224, 120, 224, 224,
				56, 224, 224, 60, 224, 224, 28, 224, 224, 30, 224, 224, 15, 224,
				224, 7, 224, 224, 7, 224, 224, 3, 224, 224, 1, 224, 224, 1, 224,
				23, 31, 93, 25, 1, 0, 0, 240, 0, 0, 120, 0, 0, 56, 0, 0, 28, 0,
				0, 14, 0, 0, 0, 0, 0, 254, 0, 3, 255, 128, 15, 255, 224, 31, 1,
				240, 62, 0, 248, 60, 0, 120, 120, 0, 60, 112, 0, 28, 112, 0, 28,
				240, 0, 30, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224,
				0, 14, 240, 0, 30, 240, 0, 30, 112, 0, 28, 120, 0, 60, 60, 0,
				120, 62, 0, 248, 31, 1, 240, 15, 255, 224, 3, 255, 128, 0, 254,
				0, 23, 31, 93, 25, 1, 0, 0, 15, 0, 0, 30, 0, 0, 28, 0, 0, 56, 0,
				0, 112, 0, 0, 0, 0, 0, 254, 0, 3, 255, 128, 15, 255, 224, 31, 1,
				240, 62, 0, 248, 60, 0, 120, 120, 0, 60, 112, 0, 28, 112, 0, 28,
				240, 0, 30, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224,
				0, 14, 240, 0, 30, 240, 0, 30, 112, 0, 28, 120, 0, 60, 60, 0,
				120, 62, 0, 248, 31, 1, 240, 15, 255, 224, 3, 255, 128, 0, 254,
				0, 23, 31, 93, 25, 1, 0, 0, 16, 0, 0, 56, 0, 0, 124, 0, 0, 238,
				0, 1, 199, 0, 0, 0, 0, 0, 254, 0, 3, 255, 128, 15, 255, 224, 31,
				1, 240, 62, 0, 248, 60, 0, 120, 120, 0, 60, 112, 0, 28, 112, 0,
				28, 240, 0, 30, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14,
				224, 0, 14, 240, 0, 30, 240, 0, 30, 112, 0, 28, 120, 0, 60, 60,
				0, 120, 62, 0, 248, 31, 1, 240, 15, 255, 224, 3, 255, 128, 0,
				254, 0, 23, 30, 90, 25, 1, 0, 0, 113, 128, 0, 255, 128, 1, 255,
				0, 1, 142, 0, 0, 0, 0, 0, 254, 0, 3, 255, 128, 15, 255, 224, 31,
				1, 240, 62, 0, 248, 60, 0, 120, 120, 0, 60, 112, 0, 28, 112, 0,
				28, 240, 0, 30, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14,
				224, 0, 14, 240, 0, 30, 240, 0, 30, 112, 0, 28, 120, 0, 60, 60,
				0, 120, 62, 0, 248, 31, 1, 240, 15, 255, 224, 3, 255, 128, 0,
				254, 0, 23, 29, 87, 25, 1, 0, 1, 195, 128, 1, 195, 128, 1, 195,
				128, 0, 0, 0, 0, 254, 0, 3, 255, 128, 15, 255, 224, 31, 1, 240,
				62, 0, 248, 60, 0, 120, 120, 0, 60, 112, 0, 28, 112, 0, 28, 240,
				0, 30, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0, 14, 224, 0,
				14, 240, 0, 30, 240, 0, 30, 112, 0, 28, 120, 0, 60, 60, 0, 120,
				62, 0, 248, 31, 1, 240, 15, 255, 224, 3, 255, 128, 0, 254, 0,
				15, 15, 30, 19, 2, 1, 64, 4, 224, 14, 240, 30, 120, 60, 60, 120,
				31, 240, 15, 224, 7, 192, 7, 192, 15, 224, 30, 240, 60, 120,
				120, 60, 240, 30, 96, 12, 23, 25, 75, 25, 1, 0, 0, 254, 6, 3,
				255, 140, 15, 255, 248, 31, 1, 240, 62, 0, 248, 60, 0, 248, 120,
				1, 188, 112, 3, 28, 112, 6, 28, 240, 6, 30, 224, 12, 14, 224,
				24, 14, 224, 48, 14, 224, 96, 14, 224, 192, 14, 225, 128, 30,
				243, 0, 30, 118, 0, 28, 124, 0, 60, 60, 0, 120, 62, 0, 248, 63,
				1, 240, 111, 255, 224, 195, 255, 128, 0, 254, 0, 18, 31, 93, 24,
				3, 0, 7, 128, 0, 3, 192, 0, 1, 192, 0, 0, 224, 0, 0, 112, 0, 0,
				0, 0, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224,
				1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224,
				1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224,
				1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 240,
				3, 192, 120, 7, 128, 124, 15, 128, 63, 255, 0, 31, 254, 0, 3,
				240, 0, 18, 31, 93, 24, 3, 0, 0, 120, 0, 0, 240, 0, 0, 224, 0,
				1, 192, 0, 3, 128, 0, 0, 0, 0, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 240, 3, 192, 120, 7, 128, 124, 15, 128, 63,
				255, 0, 31, 254, 0, 3, 240, 0, 18, 31, 93, 24, 3, 0, 0, 64, 0,
				0, 224, 0, 1, 240, 0, 3, 184, 0, 7, 28, 0, 0, 0, 0, 224, 1, 192,
				224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192,
				224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192,
				224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192,
				224, 1, 192, 224, 1, 192, 224, 1, 192, 240, 3, 192, 120, 7, 128,
				124, 15, 128, 63, 255, 0, 31, 254, 0, 3, 240, 0, 18, 30, 90, 24,
				3, 0, 14, 28, 0, 14, 28, 0, 14, 28, 0, 0, 0, 0, 0, 0, 0, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 224, 1,
				192, 224, 1, 192, 224, 1, 192, 224, 1, 192, 240, 3, 192, 120, 7,
				128, 124, 15, 128, 63, 255, 0, 31, 254, 0, 3, 240, 0, 19, 31,
				93, 22, 1, 0, 0, 60, 0, 0, 120, 0, 0, 112, 0, 0, 224, 0, 1, 192,
				0, 0, 0, 0, 224, 0, 224, 240, 1, 224, 112, 1, 192, 120, 3, 192,
				56, 3, 128, 60, 7, 128, 28, 15, 0, 30, 15, 0, 15, 30, 0, 7, 28,
				0, 7, 188, 0, 3, 184, 0, 3, 248, 0, 1, 240, 0, 1, 240, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 17, 25, 75, 22, 3,
				0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 255,
				248, 0, 255, 254, 0, 255, 255, 0, 224, 15, 0, 224, 7, 0, 224, 7,
				128, 224, 3, 128, 224, 3, 128, 224, 7, 128, 224, 7, 0, 224, 15,
				0, 255, 254, 0, 255, 252, 0, 255, 248, 0, 224, 0, 0, 224, 0, 0,
				224, 0, 0, 224, 0, 0, 224, 0, 0, 224, 0, 0, 14, 25, 50, 20, 4,
				0, 15, 128, 63, 224, 127, 240, 120, 240, 240, 120, 224, 56, 224,
				56, 224, 56, 224, 120, 224, 240, 227, 224, 227, 224, 227, 240,
				224, 120, 224, 60, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28,
				224, 56, 224, 120, 231, 240, 231, 224, 231, 128, 16, 25, 50, 18,
				1, 0, 15, 0, 7, 128, 3, 128, 1, 192, 0, 224, 0, 0, 0, 0, 15,
				224, 63, 248, 60, 124, 112, 28, 112, 28, 0, 28, 0, 28, 0, 252,
				31, 252, 127, 156, 120, 28, 240, 28, 224, 28, 224, 60, 224, 124,
				121, 252, 127, 223, 63, 143, 16, 25, 50, 18, 1, 0, 0, 240, 1,
				224, 1, 192, 3, 128, 7, 0, 0, 0, 0, 0, 15, 224, 63, 248, 60,
				124, 112, 28, 112, 28, 0, 28, 0, 28, 0, 252, 31, 252, 127, 156,
				120, 28, 240, 28, 224, 28, 224, 60, 224, 124, 120, 252, 127,
				223, 63, 143, 16, 25, 50, 18, 1, 0, 1, 0, 3, 128, 7, 192, 14,
				224, 28, 112, 0, 0, 0, 0, 15, 224, 63, 248, 60, 124, 112, 28,
				112, 28, 0, 28, 0, 28, 0, 252, 31, 252, 127, 156, 120, 28, 240,
				28, 224, 28, 224, 60, 224, 124, 120, 252, 127, 223, 63, 143, 16,
				24, 48, 18, 1, 0, 7, 24, 15, 248, 31, 240, 24, 224, 0, 0, 0, 0,
				15, 224, 63, 248, 60, 124, 112, 28, 112, 28, 0, 28, 0, 28, 0,
				252, 31, 252, 127, 156, 120, 28, 240, 28, 224, 28, 224, 60, 224,
				124, 120, 252, 127, 223, 63, 143, 16, 23, 46, 18, 1, 0, 14, 112,
				14, 112, 14, 112, 0, 0, 0, 0, 15, 224, 63, 248, 60, 252, 112,
				28, 112, 28, 0, 28, 0, 28, 0, 252, 31, 252, 127, 156, 120, 28,
				240, 28, 224, 28, 224, 60, 224, 124, 121, 252, 127, 223, 63,
				143, 16, 25, 50, 18, 1, 0, 3, 128, 6, 192, 4, 64, 4, 64, 6, 192,
				3, 128, 0, 0, 15, 224, 63, 248, 60, 124, 112, 28, 112, 28, 0,
				28, 0, 28, 0, 252, 31, 252, 127, 156, 120, 28, 240, 28, 224, 28,
				224, 60, 224, 124, 120, 252, 127, 223, 63, 143, 26, 18, 72, 29,
				1, 0, 7, 192, 248, 0, 31, 241, 254, 0, 60, 127, 143, 0, 112, 62,
				3, 128, 112, 30, 3, 128, 0, 28, 1, 192, 0, 28, 1, 192, 0, 252,
				1, 192, 15, 255, 255, 192, 63, 255, 255, 192, 126, 31, 255, 192,
				240, 28, 0, 0, 224, 28, 1, 192, 224, 30, 1, 192, 224, 126, 3,
				128, 248, 247, 143, 0, 127, 231, 255, 0, 63, 129, 252, 0, 14,
				25, 50, 17, 1, 249, 7, 192, 31, 240, 63, 248, 56, 56, 112, 28,
				112, 28, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 28, 224,
				28, 112, 56, 120, 120, 63, 240, 31, 224, 7, 128, 3, 0, 3, 0, 7,
				128, 1, 192, 0, 192, 25, 192, 15, 128, 15, 25, 50, 18, 1, 0, 30,
				0, 15, 0, 7, 0, 3, 128, 1, 192, 0, 0, 0, 0, 7, 192, 31, 240, 62,
				120, 120, 28, 112, 28, 240, 14, 224, 14, 224, 14, 255, 254, 255,
				254, 224, 0, 224, 0, 224, 14, 112, 14, 120, 28, 60, 124, 31,
				240, 15, 224, 15, 25, 50, 18, 1, 0, 1, 224, 3, 192, 3, 128, 7,
				0, 14, 0, 0, 0, 0, 0, 7, 192, 31, 240, 60, 120, 120, 28, 112,
				28, 240, 14, 224, 14, 224, 14, 255, 254, 255, 254, 224, 0, 224,
				0, 224, 14, 112, 14, 120, 28, 60, 124, 31, 240, 15, 224, 15, 25,
				50, 18, 1, 0, 1, 0, 3, 128, 7, 192, 14, 224, 28, 112, 0, 0, 0,
				0, 7, 192, 31, 240, 60, 120, 120, 28, 112, 28, 240, 14, 224, 14,
				224, 14, 255, 254, 255, 254, 224, 0, 224, 0, 224, 14, 112, 14,
				120, 28, 60, 124, 31, 240, 7, 192, 15, 23, 46, 18, 1, 0, 28,
				112, 28, 112, 28, 112, 0, 0, 0, 0, 7, 192, 31, 240, 60, 120,
				120, 28, 112, 28, 240, 14, 224, 14, 224, 14, 255, 254, 255, 254,
				224, 0, 224, 0, 224, 14, 112, 14, 120, 28, 60, 124, 31, 240, 7,
				192, 7, 25, 25, 9, 0, 0, 240, 120, 56, 28, 14, 0, 0, 28, 28, 28,
				28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 7,
				25, 25, 9, 2, 0, 30, 60, 56, 112, 224, 0, 0, 112, 112, 112, 112,
				112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112,
				112, 9, 25, 50, 9, 0, 0, 8, 0, 28, 0, 62, 0, 119, 0, 227, 128,
				0, 0, 0, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28,
				0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28, 0, 28,
				0, 28, 0, 8, 23, 23, 9, 1, 0, 231, 231, 231, 0, 0, 56, 56, 56,
				56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 15,
				25, 50, 19, 1, 0, 120, 64, 60, 224, 31, 192, 15, 128, 31, 128,
				59, 192, 17, 224, 7, 240, 31, 248, 63, 248, 120, 60, 112, 28,
				112, 28, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14,
				112, 28, 112, 28, 120, 60, 63, 248, 31, 240, 7, 192, 14, 24, 48,
				18, 2, 0, 14, 48, 31, 240, 63, 224, 49, 192, 0, 0, 0, 0, 3, 192,
				239, 240, 255, 248, 248, 60, 240, 28, 240, 28, 224, 28, 224, 28,
				224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28,
				224, 28, 224, 28, 224, 28, 15, 25, 50, 19, 1, 0, 30, 0, 15, 0,
				7, 0, 3, 128, 1, 192, 0, 0, 0, 0, 7, 192, 31, 240, 63, 248, 120,
				60, 112, 28, 112, 28, 224, 14, 224, 14, 224, 14, 224, 14, 224,
				14, 224, 14, 112, 28, 112, 28, 120, 60, 63, 248, 31, 240, 7,
				192, 15, 25, 50, 19, 1, 0, 1, 224, 3, 192, 3, 128, 7, 0, 14, 0,
				0, 0, 0, 0, 7, 192, 31, 240, 63, 248, 120, 60, 112, 28, 112, 28,
				224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 112, 28,
				112, 28, 120, 60, 63, 248, 31, 240, 7, 192, 15, 25, 50, 19, 1,
				0, 1, 0, 3, 128, 7, 192, 14, 224, 28, 112, 0, 0, 0, 0, 7, 192,
				31, 240, 63, 248, 120, 60, 112, 28, 112, 28, 224, 14, 224, 14,
				224, 14, 224, 14, 224, 14, 224, 14, 112, 28, 112, 28, 120, 60,
				63, 248, 31, 240, 7, 192, 15, 24, 48, 19, 1, 0, 14, 48, 31, 240,
				63, 224, 49, 192, 0, 0, 0, 0, 7, 192, 31, 240, 63, 248, 120, 60,
				112, 28, 112, 28, 224, 14, 224, 14, 224, 14, 224, 14, 224, 14,
				224, 14, 112, 28, 112, 28, 120, 60, 63, 248, 31, 240, 7, 192,
				15, 23, 46, 19, 1, 0, 28, 112, 28, 112, 28, 112, 0, 0, 0, 0, 7,
				192, 31, 240, 63, 248, 120, 60, 112, 28, 112, 28, 224, 14, 224,
				14, 224, 14, 224, 14, 224, 14, 224, 14, 112, 28, 112, 28, 120,
				60, 63, 248, 31, 240, 7, 192, 15, 15, 30, 19, 2, 1, 3, 128, 3,
				128, 3, 128, 0, 0, 0, 0, 0, 0, 255, 254, 255, 254, 255, 254, 0,
				0, 0, 0, 0, 0, 3, 128, 3, 128, 3, 128, 16, 18, 36, 19, 2, 0, 7,
				195, 31, 246, 63, 252, 120, 120, 112, 28, 112, 60, 224, 110,
				224, 206, 225, 142, 227, 14, 230, 14, 236, 14, 120, 28, 112, 28,
				56, 60, 127, 248, 223, 240, 135, 192, 14, 25, 50, 19, 2, 0, 30,
				0, 15, 0, 7, 0, 3, 128, 1, 192, 0, 0, 0, 0, 224, 28, 224, 28,
				224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28,
				224, 28, 224, 28, 224, 28, 224, 60, 224, 60, 240, 252, 127, 252,
				63, 220, 15, 0, 14, 25, 50, 19, 2, 0, 1, 224, 3, 192, 3, 128, 7,
				0, 14, 0, 0, 0, 0, 0, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 60, 224, 60, 240, 252, 127, 252, 63, 220, 15, 0, 14,
				25, 50, 19, 2, 0, 1, 0, 3, 128, 7, 192, 14, 224, 28, 112, 0, 0,
				0, 0, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 60, 224,
				60, 240, 252, 127, 252, 63, 220, 15, 0, 14, 23, 46, 19, 2, 0,
				28, 224, 28, 224, 28, 224, 0, 0, 0, 0, 224, 28, 224, 28, 224,
				28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224, 28, 224,
				28, 224, 28, 224, 28, 224, 60, 224, 60, 240, 252, 127, 252, 63,
				220, 15, 0, 14, 32, 64, 17, 1, 249, 0, 240, 1, 224, 1, 192, 3,
				128, 7, 0, 0, 0, 0, 0, 224, 28, 224, 28, 224, 60, 112, 56, 112,
				56, 112, 56, 120, 112, 56, 112, 56, 240, 60, 224, 28, 224, 29,
				192, 29, 192, 15, 192, 15, 128, 15, 128, 7, 0, 7, 0, 7, 0, 14,
				0, 14, 0, 30, 0, 124, 0, 124, 0, 112, 0, 15, 31, 62, 19, 2, 250,
				224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 224, 0, 231,
				224, 239, 240, 255, 248, 248, 60, 240, 28, 240, 30, 224, 14,
				224, 14, 224, 14, 224, 14, 224, 14, 224, 14, 240, 28, 240, 28,
				248, 60, 255, 248, 239, 240, 227, 192, 224, 0, 224, 0, 224, 0,
				224, 0, 224, 0, 224, 0, 14, 30, 60, 17, 1, 249, 28, 112, 28,
				112, 28, 112, 0, 0, 0, 0, 224, 28, 224, 28, 224, 60, 112, 56,
				112, 56, 112, 120, 120, 112, 56, 112, 56, 240, 60, 224, 28, 224,
				29, 192, 29, 192, 15, 192, 15, 128, 15, 128, 7, 0, 7, 0, 7, 0,
				14, 0, 14, 0, 30, 0, 124, 0, 124, 0, 112, 0 };

/*
 Fontname: -Adobe-New Century Schoolbook-Medium-R-Normal--14-100-100-100-P-82-ISO10646-1
 Copyright: Copyright (c) 1984, 1987 Adobe Systems Incorporated. All Rights Reserved. Copyright (c) 1988, 1991 Digital Equipment Corporation. All Rights Reserved.
 Capital A Height: 11, '1' Height: 11
 Calculated Max Values w=17 h=14 x= 4 y= 8 dx=16 dy= 0 ascent=14 len=33
 Font Bounding box     w=18 h=24 x=-2 y=-6
 Calculated Min Values           x=-1 y=-3 dx= 0 dy= 0
 Pure Font   ascent =11 descent=-3
 X Font      ascent =11 descent=-3
 Max Font    ascent =14 descent=-3
 */
#include "u8g.h"
const u8g_fntpgm_uint8_t u8g_font_ncenR10[3813] U8G_FONT_SECTION("u8g_font_ncenR10")
		= { 0, 18, 24, 254, 250, 11, 2, 24, 5, 38, 32, 255, 253, 14, 253, 11,
				253, 0, 0, 0, 4, 0, 1, 1, 11, 11, 3, 1, 0, 128, 128, 128, 128,
				128, 128, 128, 128, 0, 128, 128, 3, 4, 4, 5, 1, 7, 160, 160,
				160, 160, 8, 11, 11, 8, 0, 0, 18, 18, 18, 127, 36, 36, 36, 254,
				72, 72, 72, 6, 14, 14, 8, 1, 254, 32, 120, 164, 172, 160, 224,
				120, 28, 20, 212, 148, 120, 16, 16, 11, 11, 22, 12, 0, 0, 51, 0,
				77, 0, 138, 0, 138, 0, 148, 0, 100, 192, 9, 32, 10, 32, 18, 32,
				18, 64, 33, 128, 11, 11, 22, 13, 1, 0, 28, 0, 50, 0, 34, 0, 52,
				0, 24, 0, 57, 224, 76, 128, 135, 0, 131, 32, 197, 192, 120, 192,
				1, 4, 4, 3, 1, 7, 128, 128, 128, 128, 4, 13, 13, 5, 0, 254, 16,
				32, 64, 64, 128, 128, 128, 128, 128, 64, 64, 32, 16, 4, 13, 13,
				6, 1, 254, 128, 64, 32, 32, 16, 16, 16, 16, 16, 32, 32, 64, 128,
				5, 5, 5, 7, 1, 6, 32, 168, 112, 168, 32, 7, 7, 7, 9, 1, 0, 16,
				16, 16, 254, 16, 16, 16, 2, 4, 4, 4, 0, 254, 192, 64, 64, 128,
				4, 1, 1, 5, 0, 3, 240, 1, 2, 2, 4, 1, 0, 128, 128, 4, 11, 11, 4,
				0, 0, 16, 16, 16, 32, 32, 32, 64, 64, 64, 128, 128, 6, 11, 11,
				8, 1, 0, 120, 204, 132, 132, 132, 132, 132, 132, 132, 204, 120,
				5, 11, 11, 8, 1, 0, 32, 224, 32, 32, 32, 32, 32, 32, 32, 32,
				248, 6, 11, 11, 8, 1, 0, 120, 140, 196, 4, 4, 8, 16, 32, 68,
				132, 252, 6, 11, 11, 8, 1, 0, 120, 140, 196, 4, 8, 56, 12, 4,
				196, 140, 120, 7, 11, 11, 8, 0, 0, 12, 28, 20, 36, 68, 68, 132,
				254, 4, 4, 14, 6, 11, 11, 8, 1, 0, 252, 128, 128, 184, 204, 132,
				4, 4, 196, 140, 120, 6, 11, 11, 8, 1, 0, 56, 68, 140, 128, 184,
				204, 132, 132, 132, 204, 120, 6, 11, 11, 8, 1, 0, 252, 132, 136,
				8, 16, 16, 16, 32, 32, 32, 32, 6, 11, 11, 8, 1, 0, 120, 204,
				132, 196, 104, 120, 140, 132, 132, 204, 120, 6, 11, 11, 8, 1, 0,
				120, 204, 132, 132, 132, 204, 116, 4, 196, 136, 112, 1, 7, 7, 4,
				1, 0, 128, 128, 0, 0, 0, 128, 128, 2, 9, 9, 4, 0, 254, 64, 64,
				0, 0, 0, 192, 64, 64, 128, 8, 7, 7, 10, 1, 0, 3, 12, 48, 192,
				48, 12, 3, 7, 4, 4, 9, 1, 2, 254, 0, 0, 254, 8, 7, 7, 10, 1, 0,
				192, 48, 12, 3, 12, 48, 192, 5, 11, 11, 6, 0, 0, 112, 152, 136,
				8, 16, 32, 32, 32, 0, 32, 32, 12, 11, 22, 13, 0, 0, 31, 224, 32,
				16, 70, 144, 137, 144, 144, 144, 145, 16, 145, 16, 147, 48, 141,
				192, 64, 16, 63, 224, 11, 11, 22, 10, 255, 0, 4, 0, 4, 0, 10, 0,
				10, 0, 10, 0, 17, 0, 17, 0, 63, 128, 32, 128, 32, 128, 251, 224,
				9, 11, 22, 10, 0, 0, 254, 0, 35, 0, 33, 0, 33, 0, 34, 0, 63, 0,
				33, 128, 32, 128, 32, 128, 33, 128, 255, 0, 9, 11, 22, 11, 1, 0,
				30, 128, 97, 128, 64, 128, 192, 128, 128, 0, 128, 0, 128, 0,
				192, 128, 64, 128, 97, 0, 30, 0, 10, 11, 22, 11, 0, 0, 255, 0,
				32, 128, 32, 192, 32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 32,
				192, 32, 128, 255, 0, 9, 11, 22, 10, 0, 0, 255, 128, 32, 128,
				32, 128, 36, 0, 36, 0, 60, 0, 36, 0, 36, 0, 32, 128, 32, 128,
				255, 128, 9, 11, 22, 10, 0, 0, 255, 128, 32, 128, 32, 128, 36,
				0, 36, 0, 60, 0, 36, 0, 36, 0, 32, 0, 32, 0, 248, 0, 10, 11, 22,
				11, 0, 0, 30, 128, 97, 128, 64, 128, 192, 128, 128, 0, 128, 0,
				135, 192, 192, 128, 64, 128, 97, 128, 30, 128, 11, 11, 22, 12,
				0, 0, 251, 224, 32, 128, 32, 128, 32, 128, 32, 128, 63, 128, 32,
				128, 32, 128, 32, 128, 32, 128, 251, 224, 5, 11, 11, 6, 0, 0,
				248, 32, 32, 32, 32, 32, 32, 32, 32, 32, 248, 7, 11, 11, 7, 0,
				0, 62, 8, 8, 8, 8, 8, 8, 200, 136, 136, 112, 11, 11, 22, 11, 0,
				0, 251, 192, 33, 0, 34, 0, 36, 0, 40, 0, 56, 0, 52, 0, 38, 0,
				35, 0, 33, 128, 251, 224, 9, 11, 22, 10, 0, 0, 248, 0, 32, 0,
				32, 0, 32, 0, 32, 0, 32, 0, 32, 0, 32, 0, 32, 128, 32, 128, 255,
				128, 15, 11, 22, 16, 0, 0, 240, 30, 48, 24, 40, 40, 40, 40, 44,
				72, 36, 72, 38, 136, 34, 136, 35, 136, 33, 8, 249, 62, 12, 11,
				22, 13, 0, 0, 225, 240, 48, 64, 56, 64, 40, 64, 44, 64, 38, 64,
				35, 64, 33, 64, 33, 192, 32, 192, 248, 64, 10, 11, 22, 11, 0, 0,
				30, 0, 97, 128, 64, 128, 192, 192, 128, 64, 128, 64, 128, 64,
				192, 192, 64, 128, 97, 128, 30, 0, 9, 11, 22, 10, 0, 0, 255, 0,
				33, 128, 32, 128, 32, 128, 33, 0, 62, 0, 32, 0, 32, 0, 32, 0,
				32, 0, 248, 0, 11, 13, 26, 11, 0, 254, 30, 0, 97, 128, 64, 128,
				192, 192, 128, 64, 128, 64, 128, 64, 220, 192, 98, 128, 99, 128,
				31, 0, 1, 32, 0, 192, 11, 11, 22, 11, 0, 0, 255, 0, 33, 128, 32,
				128, 32, 128, 33, 0, 62, 0, 35, 0, 33, 0, 33, 32, 33, 160, 248,
				192, 7, 11, 11, 8, 0, 0, 122, 198, 130, 130, 224, 56, 14, 130,
				130, 198, 188, 9, 11, 22, 10, 0, 0, 255, 128, 136, 128, 136,
				128, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 62, 0, 12, 11,
				22, 13, 0, 0, 249, 240, 32, 64, 32, 64, 32, 64, 32, 64, 32, 64,
				32, 64, 32, 64, 32, 64, 48, 128, 31, 0, 11, 11, 22, 10, 255, 0,
				251, 224, 32, 128, 48, 128, 17, 0, 17, 0, 25, 0, 10, 0, 10, 0,
				10, 0, 4, 0, 4, 0, 17, 11, 33, 16, 255, 0, 251, 239, 128, 32,
				131, 0, 48, 194, 0, 17, 194, 0, 17, 68, 0, 25, 100, 0, 11, 40,
				0, 10, 40, 0, 14, 56, 0, 6, 16, 0, 4, 16, 0, 12, 11, 22, 13, 0,
				0, 253, 240, 48, 64, 24, 128, 13, 0, 5, 0, 6, 0, 11, 0, 9, 0,
				17, 128, 32, 192, 251, 240, 11, 11, 22, 10, 255, 0, 251, 224,
				96, 128, 49, 0, 17, 0, 26, 0, 10, 0, 4, 0, 4, 0, 4, 0, 4, 0, 31,
				0, 8, 11, 11, 9, 0, 0, 255, 131, 134, 12, 8, 24, 48, 32, 97,
				193, 255, 3, 13, 13, 4, 0, 254, 224, 128, 128, 128, 128, 128,
				128, 128, 128, 128, 128, 128, 224, 6, 11, 11, 8, 1, 0, 128, 128,
				64, 64, 32, 32, 16, 16, 8, 8, 4, 3, 13, 13, 4, 0, 254, 224, 32,
				32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 224, 5, 6, 6, 7, 1, 5,
				32, 32, 80, 80, 136, 136, 7, 1, 1, 7, 0, 254, 254, 3, 3, 3, 5,
				1, 8, 128, 64, 32, 7, 7, 7, 8, 0, 0, 56, 76, 4, 60, 196, 140,
				118, 7, 11, 11, 7, 255, 0, 192, 64, 64, 64, 92, 102, 66, 66, 66,
				102, 92, 6, 7, 7, 7, 0, 0, 120, 204, 128, 128, 128, 196, 120, 7,
				11, 11, 8, 0, 0, 12, 4, 4, 4, 116, 204, 132, 132, 132, 204, 118,
				6, 7, 7, 7, 0, 0, 120, 204, 132, 252, 128, 196, 120, 5, 11, 11,
				5, 0, 0, 56, 72, 64, 64, 240, 64, 64, 64, 64, 64, 224, 7, 10,
				10, 8, 0, 253, 118, 204, 132, 204, 120, 128, 124, 198, 130, 124,
				8, 11, 11, 9, 0, 0, 192, 64, 64, 64, 92, 102, 66, 66, 66, 66,
				231, 3, 10, 10, 4, 0, 0, 64, 64, 0, 192, 64, 64, 64, 64, 64,
				224, 3, 13, 13, 4, 255, 253, 32, 32, 0, 96, 32, 32, 32, 32, 32,
				32, 32, 160, 192, 8, 11, 11, 9, 0, 0, 192, 64, 64, 64, 94, 72,
				80, 120, 76, 70, 239, 3, 11, 11, 4, 0, 0, 192, 64, 64, 64, 64,
				64, 64, 64, 64, 64, 224, 13, 7, 14, 14, 0, 0, 220, 224, 103, 48,
				66, 16, 66, 16, 66, 16, 66, 16, 231, 56, 8, 7, 7, 9, 0, 0, 220,
				102, 66, 66, 66, 66, 231, 6, 7, 7, 7, 0, 0, 120, 204, 132, 132,
				132, 204, 120, 7, 10, 10, 8, 0, 253, 220, 102, 66, 66, 66, 102,
				92, 64, 64, 224, 7, 10, 10, 7, 0, 253, 116, 204, 132, 132, 132,
				204, 116, 4, 4, 14, 6, 7, 7, 7, 0, 0, 220, 100, 64, 64, 64, 64,
				224, 5, 7, 7, 6, 0, 0, 120, 136, 192, 112, 24, 136, 240, 5, 9,
				9, 5, 0, 0, 64, 64, 240, 64, 64, 64, 64, 72, 48, 8, 7, 7, 9, 0,
				0, 231, 66, 66, 66, 66, 102, 59, 7, 7, 7, 8, 0, 0, 238, 68, 68,
				40, 40, 16, 16, 11, 7, 14, 12, 0, 0, 238, 224, 68, 64, 68, 64,
				42, 128, 42, 128, 17, 0, 17, 0, 7, 7, 7, 8, 0, 0, 206, 100, 56,
				16, 56, 76, 230, 7, 10, 10, 8, 0, 253, 238, 68, 68, 40, 40, 16,
				16, 32, 160, 192, 6, 7, 7, 7, 0, 0, 252, 140, 152, 48, 100, 196,
				252, 3, 13, 13, 4, 0, 254, 32, 64, 64, 64, 64, 64, 128, 64, 64,
				64, 64, 64, 32, 1, 11, 11, 9, 4, 0, 128, 128, 128, 128, 128,
				128, 128, 128, 128, 128, 128, 3, 13, 13, 5, 1, 254, 128, 64, 64,
				64, 64, 64, 32, 64, 64, 64, 64, 64, 128, 7, 2, 2, 9, 1, 3, 114,
				140, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
				255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
				255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 4, 0, 1, 1, 11,
				11, 4, 1, 253, 128, 128, 0, 128, 128, 128, 128, 128, 128, 128,
				128, 6, 11, 11, 8, 1, 254, 4, 4, 120, 204, 144, 144, 160, 228,
				120, 128, 128, 7, 11, 11, 8, 0, 0, 60, 98, 70, 64, 32, 252, 16,
				16, 96, 178, 206, 7, 7, 7, 8, 0, 2, 186, 68, 130, 130, 130, 68,
				186, 9, 11, 22, 8, 0, 0, 227, 128, 65, 0, 34, 0, 34, 0, 20, 0,
				20, 0, 62, 0, 8, 0, 62, 0, 8, 0, 28, 0, 1, 11, 11, 9, 4, 0, 128,
				128, 128, 128, 0, 0, 128, 128, 128, 128, 128, 5, 13, 13, 7, 1,
				254, 120, 136, 128, 192, 112, 152, 136, 200, 112, 24, 8, 136,
				240, 4, 2, 2, 6, 1, 8, 144, 144, 12, 11, 22, 14, 1, 0, 15, 0,
				48, 192, 79, 32, 89, 32, 144, 16, 144, 16, 152, 144, 79, 32, 64,
				32, 48, 192, 15, 0, 5, 7, 7, 6, 0, 4, 96, 144, 112, 144, 248, 0,
				248, 6, 5, 5, 7, 0, 1, 36, 72, 144, 72, 36, 7, 4, 4, 9, 0, 1,
				254, 2, 2, 2, 4, 1, 1, 5, 0, 3, 240, 12, 11, 22, 14, 1, 0, 15,
				0, 48, 192, 94, 32, 73, 32, 137, 16, 142, 16, 139, 16, 89, 160,
				64, 32, 48, 192, 15, 0, 5, 1, 1, 5, 0, 8, 248, 4, 4, 4, 6, 1, 7,
				96, 144, 144, 96, 7, 7, 7, 9, 1, 0, 16, 16, 254, 16, 16, 0, 254,
				4, 6, 6, 5, 0, 5, 96, 144, 32, 64, 144, 240, 4, 6, 6, 5, 0, 5,
				96, 144, 32, 16, 144, 96, 3, 3, 3, 5, 1, 8, 32, 64, 128, 8, 10,
				10, 9, 0, 253, 231, 66, 66, 66, 66, 102, 123, 64, 96, 64, 7, 13,
				13, 9, 1, 254, 126, 212, 212, 212, 212, 116, 20, 20, 20, 20, 20,
				20, 62, 2, 2, 2, 4, 1, 3, 192, 192, 3, 4, 4, 5, 0, 253, 64, 64,
				32, 192, 3, 6, 6, 5, 1, 5, 64, 192, 64, 64, 64, 224, 4, 7, 7, 5,
				0, 4, 96, 144, 144, 144, 96, 0, 240, 6, 5, 5, 7, 0, 1, 144, 72,
				36, 72, 144, 10, 11, 22, 12, 0, 0, 65, 0, 193, 0, 66, 0, 66, 0,
				68, 0, 228, 128, 9, 128, 18, 128, 20, 128, 39, 192, 32, 128, 10,
				11, 22, 12, 0, 0, 65, 0, 193, 0, 66, 0, 66, 0, 68, 0, 229, 128,
				10, 64, 16, 128, 17, 0, 34, 64, 35, 192, 10, 11, 22, 12, 0, 0,
				97, 0, 145, 0, 34, 0, 18, 0, 148, 0, 100, 128, 9, 128, 18, 128,
				20, 128, 39, 192, 32, 128, 5, 11, 11, 6, 0, 253, 32, 32, 0, 32,
				32, 32, 64, 128, 136, 200, 112, 11, 14, 28, 10, 255, 0, 8, 0, 4,
				0, 0, 0, 4, 0, 4, 0, 10, 0, 10, 0, 10, 0, 17, 0, 17, 0, 63, 128,
				32, 128, 32, 128, 251, 224, 11, 14, 28, 10, 255, 0, 2, 0, 4, 0,
				0, 0, 4, 0, 4, 0, 10, 0, 10, 0, 10, 0, 17, 0, 17, 0, 63, 128,
				32, 128, 32, 128, 251, 224, 11, 14, 28, 10, 255, 0, 4, 0, 10, 0,
				17, 0, 4, 0, 4, 0, 10, 0, 10, 0, 10, 0, 17, 0, 17, 0, 63, 128,
				32, 128, 32, 128, 251, 224, 11, 14, 28, 10, 255, 0, 12, 128, 19,
				0, 0, 0, 4, 0, 4, 0, 10, 0, 10, 0, 10, 0, 17, 0, 17, 0, 63, 128,
				32, 128, 32, 128, 251, 224, 11, 13, 26, 10, 255, 0, 17, 0, 17,
				0, 4, 0, 4, 0, 10, 0, 10, 0, 10, 0, 17, 0, 17, 0, 63, 128, 32,
				128, 32, 128, 251, 224, 11, 14, 28, 10, 255, 0, 12, 0, 18, 0,
				12, 0, 4, 0, 4, 0, 10, 0, 10, 0, 10, 0, 17, 0, 17, 0, 63, 128,
				32, 128, 32, 128, 251, 224, 14, 11, 22, 15, 0, 0, 15, 252, 5, 4,
				9, 4, 9, 32, 17, 32, 17, 224, 63, 32, 33, 32, 65, 4, 65, 4, 227,
				252, 9, 14, 28, 11, 1, 253, 30, 128, 97, 128, 64, 128, 192, 128,
				128, 0, 128, 0, 128, 0, 192, 128, 64, 128, 97, 0, 30, 0, 8, 0,
				4, 0, 24, 0, 9, 14, 28, 10, 0, 0, 16, 0, 8, 0, 0, 0, 255, 128,
				32, 128, 32, 128, 36, 0, 36, 0, 60, 0, 36, 0, 36, 0, 32, 128,
				32, 128, 255, 128, 9, 14, 28, 10, 0, 0, 4, 0, 8, 0, 0, 0, 255,
				128, 32, 128, 32, 128, 36, 0, 36, 0, 60, 0, 36, 0, 36, 0, 32,
				128, 32, 128, 255, 128, 9, 14, 28, 10, 0, 0, 12, 0, 18, 0, 0, 0,
				255, 128, 32, 128, 32, 128, 36, 0, 36, 0, 60, 0, 36, 0, 36, 0,
				32, 128, 32, 128, 255, 128, 9, 14, 28, 10, 0, 0, 18, 0, 18, 0,
				0, 0, 255, 128, 32, 128, 32, 128, 36, 0, 36, 0, 60, 0, 36, 0,
				36, 0, 32, 128, 32, 128, 255, 128, 5, 14, 14, 6, 0, 0, 64, 32,
				0, 248, 32, 32, 32, 32, 32, 32, 32, 32, 32, 248, 5, 14, 14, 6,
				0, 0, 16, 32, 0, 248, 32, 32, 32, 32, 32, 32, 32, 32, 32, 248,
				5, 14, 14, 6, 0, 0, 48, 72, 0, 248, 32, 32, 32, 32, 32, 32, 32,
				32, 32, 248, 5, 14, 14, 6, 0, 0, 80, 80, 0, 248, 32, 32, 32, 32,
				32, 32, 32, 32, 32, 248, 10, 11, 22, 11, 0, 0, 255, 0, 32, 128,
				32, 192, 32, 64, 32, 64, 248, 64, 32, 64, 32, 64, 32, 192, 32,
				128, 255, 0, 12, 14, 28, 13, 0, 0, 12, 128, 19, 0, 0, 0, 225,
				240, 48, 64, 48, 64, 40, 64, 44, 64, 38, 64, 35, 64, 33, 64, 32,
				192, 32, 64, 248, 64, 10, 14, 28, 11, 0, 0, 8, 0, 4, 0, 0, 0,
				30, 0, 97, 128, 64, 128, 192, 192, 128, 64, 128, 64, 128, 64,
				192, 192, 64, 128, 97, 128, 30, 0, 10, 14, 28, 11, 0, 0, 2, 0,
				4, 0, 0, 0, 30, 0, 97, 128, 64, 128, 192, 192, 128, 64, 128, 64,
				128, 64, 192, 192, 64, 128, 97, 128, 30, 0, 10, 14, 28, 11, 0,
				0, 12, 0, 18, 0, 0, 0, 30, 0, 97, 128, 64, 128, 192, 192, 128,
				64, 128, 64, 128, 64, 192, 192, 64, 128, 97, 128, 30, 0, 10, 14,
				28, 11, 0, 0, 25, 0, 38, 0, 0, 0, 30, 0, 97, 128, 64, 128, 192,
				192, 128, 64, 128, 64, 128, 64, 192, 192, 64, 128, 97, 128, 30,
				0, 10, 14, 28, 11, 0, 0, 18, 0, 18, 0, 0, 0, 30, 0, 97, 128, 64,
				128, 192, 192, 128, 64, 128, 64, 128, 64, 192, 192, 64, 128, 97,
				128, 30, 0, 7, 7, 7, 9, 1, 0, 130, 68, 40, 16, 40, 68, 130, 11,
				11, 22, 11, 255, 0, 15, 32, 48, 192, 32, 192, 97, 96, 66, 32,
				68, 32, 72, 32, 112, 96, 32, 64, 112, 192, 143, 0, 12, 14, 28,
				13, 0, 0, 8, 0, 4, 0, 0, 0, 249, 240, 32, 64, 32, 64, 32, 64,
				32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 48, 128, 31, 0, 12, 14,
				28, 13, 0, 0, 1, 0, 2, 0, 0, 0, 249, 240, 32, 64, 32, 64, 32,
				64, 32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 48, 128, 31, 0, 12,
				14, 28, 13, 0, 0, 6, 0, 9, 0, 0, 0, 249, 240, 32, 64, 32, 64,
				32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 48, 128, 31, 0,
				12, 14, 28, 13, 0, 0, 9, 0, 9, 0, 0, 0, 249, 240, 32, 64, 32,
				64, 32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 48, 128, 31,
				0, 11, 14, 28, 10, 255, 0, 2, 0, 4, 0, 0, 0, 251, 224, 96, 128,
				49, 0, 17, 0, 26, 0, 10, 0, 4, 0, 4, 0, 4, 0, 4, 0, 31, 0, 9,
				11, 22, 10, 0, 0, 248, 0, 32, 0, 63, 0, 33, 128, 32, 128, 32,
				128, 33, 0, 62, 0, 32, 0, 32, 0, 248, 0, 7, 11, 11, 8, 0, 0, 56,
				100, 68, 76, 88, 68, 66, 66, 66, 86, 220, 7, 11, 11, 8, 0, 0,
				32, 16, 8, 0, 56, 76, 4, 60, 196, 140, 118, 7, 11, 11, 8, 0, 0,
				8, 16, 32, 0, 56, 76, 4, 60, 196, 140, 118, 7, 11, 11, 8, 0, 0,
				16, 40, 68, 0, 56, 76, 4, 60, 196, 140, 118, 7, 10, 10, 8, 0, 0,
				50, 76, 0, 56, 76, 4, 60, 196, 140, 118, 7, 10, 10, 8, 0, 0, 72,
				72, 0, 56, 76, 4, 60, 196, 140, 118, 7, 11, 11, 8, 0, 0, 48, 72,
				48, 0, 56, 76, 4, 60, 196, 140, 118, 11, 7, 14, 12, 0, 0, 59,
				192, 78, 96, 4, 32, 63, 224, 196, 0, 142, 32, 115, 192, 6, 10,
				10, 7, 0, 253, 120, 204, 128, 128, 128, 196, 120, 32, 16, 96, 6,
				11, 11, 7, 0, 0, 64, 32, 16, 0, 120, 204, 132, 252, 128, 196,
				120, 6, 11, 11, 7, 0, 0, 8, 16, 32, 0, 120, 204, 132, 252, 128,
				196, 120, 6, 11, 11, 7, 0, 0, 16, 40, 68, 0, 120, 204, 132, 252,
				128, 196, 120, 6, 10, 10, 7, 0, 0, 72, 72, 0, 120, 204, 132,
				252, 128, 196, 120, 3, 11, 11, 4, 0, 0, 128, 64, 32, 0, 192, 64,
				64, 64, 64, 64, 224, 3, 11, 11, 4, 0, 0, 32, 64, 128, 0, 192,
				64, 64, 64, 64, 64, 224, 5, 11, 11, 4, 255, 0, 32, 80, 136, 0,
				96, 32, 32, 32, 32, 32, 112, 4, 10, 10, 4, 255, 0, 144, 144, 0,
				96, 32, 32, 32, 32, 32, 112, 7, 11, 11, 7, 255, 0, 76, 48, 208,
				8, 60, 102, 66, 66, 66, 102, 60, 8, 10, 10, 9, 0, 0, 50, 76, 0,
				220, 102, 66, 66, 66, 66, 231, 6, 11, 11, 7, 0, 0, 64, 32, 16,
				0, 120, 204, 132, 132, 132, 204, 120, 6, 11, 11, 7, 0, 0, 16,
				32, 64, 0, 120, 204, 132, 132, 132, 204, 120, 6, 11, 11, 7, 0,
				0, 32, 80, 136, 0, 120, 204, 132, 132, 132, 204, 120, 6, 10, 10,
				7, 0, 0, 100, 152, 0, 120, 204, 132, 132, 132, 204, 120, 6, 10,
				10, 7, 0, 0, 72, 72, 0, 120, 204, 132, 132, 132, 204, 120, 7, 7,
				7, 9, 1, 0, 16, 16, 0, 254, 0, 16, 16, 6, 9, 9, 7, 0, 255, 8,
				120, 220, 148, 164, 164, 204, 120, 64, 8, 11, 11, 9, 0, 0, 32,
				16, 8, 0, 231, 66, 66, 66, 66, 102, 59, 8, 11, 11, 9, 0, 0, 2,
				4, 8, 0, 231, 66, 66, 66, 66, 102, 59, 8, 11, 11, 9, 0, 0, 8,
				20, 34, 0, 231, 66, 66, 66, 66, 102, 59, 8, 10, 10, 9, 0, 0, 36,
				36, 0, 231, 66, 66, 66, 66, 102, 59, 7, 14, 14, 8, 0, 253, 4, 8,
				16, 0, 238, 68, 68, 40, 40, 16, 16, 32, 160, 192, 7, 14, 14, 8,
				0, 253, 192, 64, 64, 64, 92, 102, 66, 66, 66, 102, 92, 64, 64,
				224, 7, 13, 13, 8, 0, 253, 72, 72, 0, 238, 68, 68, 40, 40, 16,
				16, 32, 160, 192 };

/*
 Fontname: -Misc-Fixed-Bold-R-Normal--13-120-75-75-C-70-ISO10646-1
 Copyright: Public domain font.  Share and enjoy.
 Capital A Height: 9, '1' Height: 9
 Calculated Max Values w= 6 h=11 x= 2 y=11 dx= 7 dy= 0 ascent=11 len=11
 Font Bounding box     w= 7 h=13 x= 0 y=-2
 Calculated Min Values           x= 0 y=-2 dx= 0 dy= 0
 Pure Font   ascent = 9 descent=-2
 X Font      ascent = 9 descent=-2
 Max Font    ascent =11 descent=-2
 */
#include "u8g.h"
const u8g_fntpgm_uint8_t u8g_font_7x13B[2172] U8G_FONT_SECTION("u8g_font_7x13B")
		= { 1, 7, 13, 0, 254, 9, 1, 105, 2, 216, 32, 255, 254, 11, 254, 9, 254,
				13, 0, 112, 34, 41, 121, 192, 192, 192, 192, 192, 192, 0, 192,
				192, 24, 83, 115, 216, 216, 216, 18, 89, 121, 80, 80, 248, 248,
				80, 248, 248, 80, 80, 2, 105, 121, 48, 120, 180, 176, 120, 52,
				180, 120, 48, 2, 105, 121, 228, 172, 232, 24, 48, 96, 92, 212,
				156, 2, 105, 121, 112, 216, 216, 216, 112, 212, 220, 216, 116,
				39, 36, 116, 192, 192, 192, 192, 18, 73, 121, 48, 96, 96, 192,
				192, 192, 96, 96, 48, 18, 73, 121, 192, 96, 96, 48, 48, 48, 96,
				96, 192, 3, 102, 118, 72, 48, 252, 252, 48, 72, 3, 102, 118, 48,
				48, 252, 252, 48, 48, 17, 68, 116, 112, 112, 96, 192, 5, 97,
				113, 252, 17, 67, 115, 96, 240, 96, 2, 105, 121, 12, 12, 24, 24,
				48, 96, 96, 192, 192, 2, 105, 121, 48, 72, 204, 204, 204, 204,
				204, 72, 48, 2, 105, 121, 48, 112, 176, 48, 48, 48, 48, 48, 252,
				2, 105, 121, 120, 204, 204, 12, 56, 96, 192, 192, 252, 2, 105,
				121, 252, 12, 24, 48, 120, 12, 12, 204, 120, 2, 105, 121, 12,
				28, 60, 108, 204, 204, 252, 12, 12, 2, 105, 121, 252, 192, 192,
				248, 204, 12, 12, 204, 120, 2, 105, 121, 120, 204, 192, 192,
				248, 204, 204, 204, 120, 2, 105, 121, 252, 12, 12, 24, 24, 48,
				48, 96, 96, 2, 105, 121, 120, 204, 204, 204, 120, 204, 204, 204,
				120, 2, 105, 121, 120, 204, 204, 204, 124, 12, 12, 204, 120, 17,
				72, 120, 96, 240, 96, 0, 0, 96, 240, 96, 17, 72, 120, 96, 240,
				96, 0, 112, 112, 96, 192, 2, 105, 121, 12, 24, 48, 96, 192, 96,
				48, 24, 12, 4, 100, 116, 252, 0, 0, 252, 2, 105, 121, 192, 96,
				48, 24, 12, 24, 48, 96, 192, 2, 105, 121, 120, 204, 204, 12, 56,
				48, 0, 48, 48, 2, 105, 121, 120, 140, 140, 188, 172, 188, 128,
				140, 120, 2, 105, 121, 120, 204, 204, 204, 252, 204, 204, 204,
				204, 2, 105, 121, 248, 204, 204, 204, 248, 204, 204, 204, 248,
				2, 105, 121, 120, 204, 192, 192, 192, 192, 192, 204, 120, 2,
				105, 121, 248, 204, 204, 204, 204, 204, 204, 204, 248, 2, 105,
				121, 252, 192, 192, 192, 248, 192, 192, 192, 252, 2, 105, 121,
				252, 192, 192, 192, 248, 192, 192, 192, 192, 2, 105, 121, 120,
				204, 192, 192, 220, 204, 204, 204, 124, 2, 105, 121, 204, 204,
				204, 204, 252, 204, 204, 204, 204, 2, 105, 121, 252, 48, 48, 48,
				48, 48, 48, 48, 252, 2, 105, 121, 12, 12, 12, 12, 12, 12, 12,
				204, 120, 2, 105, 121, 196, 204, 216, 240, 224, 240, 216, 204,
				196, 2, 105, 121, 192, 192, 192, 192, 192, 192, 192, 192, 252,
				2, 105, 121, 132, 204, 252, 252, 204, 204, 204, 204, 204, 2,
				105, 121, 204, 204, 236, 236, 252, 220, 220, 204, 204, 2, 105,
				121, 120, 204, 204, 204, 204, 204, 204, 204, 120, 2, 105, 121,
				248, 204, 204, 204, 248, 192, 192, 192, 192, 1, 106, 122, 120,
				204, 204, 204, 204, 204, 236, 220, 120, 12, 2, 105, 121, 248,
				204, 204, 204, 248, 240, 216, 204, 196, 2, 105, 121, 120, 204,
				192, 192, 120, 12, 12, 204, 120, 2, 105, 121, 252, 48, 48, 48,
				48, 48, 48, 48, 48, 2, 105, 121, 204, 204, 204, 204, 204, 204,
				204, 204, 120, 2, 105, 121, 204, 204, 204, 72, 72, 120, 48, 48,
				48, 2, 105, 121, 204, 204, 204, 204, 204, 252, 252, 204, 132, 2,
				105, 121, 132, 204, 72, 120, 48, 120, 72, 204, 132, 2, 105, 121,
				204, 204, 120, 120, 48, 48, 48, 48, 48, 2, 105, 121, 252, 12,
				12, 24, 48, 96, 192, 192, 252, 18, 73, 121, 240, 192, 192, 192,
				192, 192, 192, 192, 240, 2, 105, 121, 192, 192, 96, 96, 48, 24,
				24, 12, 12, 18, 73, 121, 240, 48, 48, 48, 48, 48, 48, 48, 240,
				7, 100, 116, 48, 120, 204, 132, 1, 98, 114, 252, 252, 25, 67,
				115, 192, 96, 48, 2, 102, 118, 120, 12, 124, 204, 204, 124, 2,
				105, 121, 192, 192, 192, 248, 204, 204, 204, 204, 248, 2, 102,
				118, 120, 204, 192, 192, 204, 120, 2, 105, 121, 12, 12, 12, 124,
				204, 204, 204, 204, 124, 2, 102, 118, 120, 204, 252, 192, 204,
				120, 2, 105, 121, 56, 108, 96, 96, 240, 96, 96, 96, 96, 0, 104,
				120, 116, 204, 204, 120, 192, 120, 204, 120, 2, 105, 121, 192,
				192, 192, 248, 204, 204, 204, 204, 204, 2, 105, 121, 48, 48, 0,
				112, 48, 48, 48, 48, 252, 0, 107, 123, 12, 12, 0, 12, 12, 12,
				12, 12, 12, 204, 120, 2, 105, 121, 192, 192, 192, 204, 216, 240,
				240, 216, 204, 2, 105, 121, 112, 48, 48, 48, 48, 48, 48, 48,
				252, 2, 102, 118, 216, 252, 252, 204, 204, 204, 2, 102, 118,
				248, 204, 204, 204, 204, 204, 2, 102, 118, 120, 204, 204, 204,
				204, 120, 0, 104, 120, 248, 204, 204, 204, 248, 192, 192, 192,
				0, 104, 120, 124, 204, 204, 204, 124, 12, 12, 12, 2, 102, 118,
				248, 204, 192, 192, 192, 192, 2, 102, 118, 120, 204, 96, 24,
				204, 120, 2, 104, 120, 96, 96, 248, 96, 96, 96, 108, 56, 2, 102,
				118, 204, 204, 204, 204, 204, 124, 2, 102, 118, 204, 204, 204,
				120, 120, 48, 2, 102, 118, 204, 204, 204, 252, 252, 72, 2, 102,
				118, 204, 204, 120, 120, 204, 204, 0, 104, 120, 204, 204, 204,
				204, 124, 12, 204, 120, 2, 102, 118, 252, 12, 24, 96, 192, 252,
				18, 73, 121, 112, 192, 192, 96, 192, 96, 192, 192, 112, 34, 41,
				121, 192, 192, 192, 192, 192, 192, 192, 192, 192, 18, 73, 121,
				224, 48, 48, 96, 48, 96, 48, 48, 224, 8, 99, 115, 100, 252, 152,
				255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
				255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
				255, 255, 255, 255, 255, 255, 255, 13, 0, 112, 34, 42, 122, 192,
				192, 0, 192, 192, 192, 192, 192, 192, 192, 3, 104, 120, 16, 124,
				212, 208, 208, 212, 124, 16, 2, 105, 121, 56, 108, 96, 96, 248,
				96, 96, 108, 184, 3, 102, 118, 204, 252, 72, 72, 252, 204, 2,
				105, 121, 204, 204, 120, 120, 252, 48, 252, 48, 48, 34, 42, 122,
				192, 192, 192, 192, 0, 0, 192, 192, 192, 192, 2, 106, 122, 120,
				204, 192, 120, 204, 204, 120, 12, 204, 120, 26, 82, 114, 216,
				216, 2, 106, 122, 120, 204, 132, 180, 228, 228, 180, 132, 204,
				120, 20, 87, 119, 240, 24, 248, 152, 248, 0, 248, 3, 103, 119,
				52, 104, 208, 160, 208, 104, 52, 3, 100, 116, 252, 12, 12, 12,
				21, 65, 113, 240, 2, 106, 122, 120, 204, 132, 188, 172, 188,
				180, 172, 204, 120, 27, 81, 113, 248, 7, 100, 116, 120, 204,
				204, 120, 3, 103, 119, 48, 48, 252, 48, 48, 0, 252, 6, 70, 118,
				224, 176, 48, 96, 192, 240, 6, 70, 118, 224, 176, 96, 48, 176,
				224, 25, 67, 115, 48, 96, 192, 1, 103, 119, 204, 204, 204, 204,
				204, 252, 128, 2, 105, 121, 124, 252, 244, 244, 244, 116, 52,
				52, 52, 38, 34, 114, 192, 192, 16, 50, 114, 96, 192, 6, 70, 118,
				96, 224, 96, 96, 96, 240, 21, 87, 119, 112, 248, 136, 248, 112,
				0, 248, 3, 103, 119, 176, 88, 44, 20, 44, 88, 176, 2, 106, 122,
				96, 224, 96, 96, 100, 252, 28, 52, 60, 12, 2, 106, 122, 96, 224,
				96, 96, 120, 236, 12, 24, 48, 60, 2, 106, 122, 224, 176, 96, 48,
				180, 236, 28, 52, 60, 12, 2, 106, 122, 48, 48, 0, 48, 48, 96,
				192, 204, 204, 120, 2, 106, 122, 96, 48, 0, 48, 120, 204, 204,
				252, 204, 204, 2, 106, 122, 24, 48, 0, 48, 120, 204, 204, 252,
				204, 204, 2, 106, 122, 56, 108, 0, 48, 120, 204, 204, 252, 204,
				204, 2, 106, 122, 52, 88, 0, 48, 120, 204, 204, 252, 204, 204,
				2, 106, 122, 204, 204, 0, 48, 120, 204, 204, 252, 204, 204, 2,
				106, 122, 120, 72, 120, 48, 120, 204, 204, 252, 204, 204, 2,
				105, 121, 124, 248, 216, 216, 220, 248, 216, 216, 220, 0, 107,
				123, 120, 204, 192, 192, 192, 192, 192, 204, 120, 48, 96, 2,
				106, 122, 96, 48, 0, 252, 192, 192, 240, 192, 192, 252, 2, 106,
				122, 24, 48, 0, 252, 192, 192, 240, 192, 192, 252, 2, 106, 122,
				56, 108, 0, 252, 192, 192, 240, 192, 192, 252, 2, 106, 122, 204,
				204, 0, 252, 192, 192, 240, 192, 192, 252, 2, 106, 122, 96, 48,
				0, 252, 48, 48, 48, 48, 48, 252, 2, 106, 122, 24, 48, 0, 252,
				48, 48, 48, 48, 48, 252, 2, 106, 122, 56, 108, 0, 252, 48, 48,
				48, 48, 48, 252, 2, 106, 122, 204, 204, 0, 252, 48, 48, 48, 48,
				48, 252, 2, 105, 121, 248, 108, 108, 108, 236, 108, 108, 108,
				248, 2, 106, 122, 52, 88, 0, 204, 204, 236, 252, 220, 204, 204,
				2, 106, 122, 96, 48, 0, 120, 204, 204, 204, 204, 204, 120, 2,
				106, 122, 24, 48, 0, 120, 204, 204, 204, 204, 204, 120, 2, 106,
				122, 56, 108, 0, 120, 204, 204, 204, 204, 204, 120, 2, 106, 122,
				52, 88, 0, 120, 204, 204, 204, 204, 204, 120, 2, 106, 122, 204,
				204, 0, 120, 204, 204, 204, 204, 204, 120, 3, 101, 117, 204,
				120, 48, 120, 204, 1, 106, 122, 4, 120, 220, 220, 220, 236, 236,
				236, 120, 128, 2, 106, 122, 96, 48, 0, 204, 204, 204, 204, 204,
				204, 120, 2, 106, 122, 24, 48, 0, 204, 204, 204, 204, 204, 204,
				120, 2, 106, 122, 56, 108, 0, 204, 204, 204, 204, 204, 204, 120,
				2, 106, 122, 204, 204, 0, 204, 204, 204, 204, 204, 204, 120, 2,
				106, 122, 24, 48, 0, 204, 72, 120, 48, 48, 48, 48, 2, 105, 121,
				192, 248, 204, 204, 204, 248, 192, 192, 192, 2, 105, 121, 120,
				204, 204, 216, 216, 204, 204, 204, 216, 2, 105, 121, 48, 24, 0,
				120, 12, 124, 204, 220, 124, 2, 105, 121, 24, 48, 0, 120, 12,
				124, 204, 220, 124, 2, 105, 121, 56, 108, 0, 120, 12, 124, 204,
				220, 124, 2, 105, 121, 52, 88, 0, 120, 12, 124, 204, 220, 124,
				2, 105, 121, 108, 108, 0, 120, 12, 124, 204, 220, 124, 2, 106,
				122, 56, 40, 56, 0, 120, 12, 124, 204, 220, 124, 2, 102, 118,
				120, 52, 124, 176, 180, 104, 0, 104, 120, 120, 204, 192, 192,
				204, 120, 48, 96, 2, 105, 121, 48, 24, 0, 120, 204, 252, 192,
				204, 120, 2, 105, 121, 24, 48, 0, 120, 204, 252, 192, 204, 120,
				2, 105, 121, 56, 108, 0, 120, 204, 252, 192, 204, 120, 2, 105,
				121, 108, 108, 0, 120, 204, 252, 192, 204, 120, 18, 73, 121,
				192, 96, 0, 224, 96, 96, 96, 96, 240, 18, 73, 121, 48, 96, 0,
				224, 96, 96, 96, 96, 240, 2, 89, 121, 112, 216, 0, 112, 48, 48,
				48, 48, 120, 18, 89, 121, 216, 216, 0, 224, 96, 96, 96, 96, 240,
				2, 106, 122, 104, 48, 120, 12, 124, 204, 204, 204, 204, 120, 2,
				105, 121, 52, 88, 0, 248, 236, 204, 204, 204, 204, 2, 105, 121,
				96, 48, 0, 120, 204, 204, 204, 204, 120, 2, 105, 121, 24, 48, 0,
				120, 204, 204, 204, 204, 120, 2, 105, 121, 56, 108, 0, 120, 204,
				204, 204, 204, 120, 2, 105, 121, 52, 88, 0, 120, 204, 204, 204,
				204, 120, 2, 105, 121, 108, 108, 0, 120, 204, 204, 204, 204,
				120, 3, 103, 119, 48, 48, 0, 252, 0, 48, 48, 1, 105, 121, 4,
				120, 204, 220, 204, 236, 204, 120, 128, 2, 105, 121, 96, 48, 0,
				204, 204, 204, 204, 220, 124, 2, 105, 121, 24, 48, 0, 204, 204,
				204, 204, 220, 124, 2, 105, 121, 56, 108, 0, 204, 204, 204, 204,
				220, 124, 2, 105, 121, 108, 108, 0, 204, 204, 204, 204, 220,
				124, 0, 107, 123, 24, 48, 0, 204, 204, 204, 220, 124, 12, 204,
				120, 0, 106, 122, 192, 192, 216, 236, 204, 204, 236, 216, 192,
				192, 0, 107, 123, 108, 108, 0, 204, 204, 204, 220, 108, 12, 204,
				120 };
