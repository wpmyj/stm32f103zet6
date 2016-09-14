#include "GUI.H"
#include "option.h"
#include "def.h"
#include "44b.h"
#include "44blib.h"
#include "math.h"
#include "SED1335.h"

#include "DriverUsart4.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "DriverSPI.h"

unsigned char  biaozi[]={
  0x03,0x0C,0x10,0x20,0x40,0x40,0x81,0x81,0x81,0x80,0x80,0x80,0x81,0x81,0x81,0x81,
  0x80,0x80,0x80,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xF8,0xFF,0x7F,0x7F,0x3F,0x1F,0x0F,0x03,0xFF,0x00,0x00,0x00,0x00,0xFC,0x04,0x04,
  0x04,0xE0,0x18,0x04,0x04,0x04,0x88,0x70,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x03,0xFF,
  0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x42,0x7F,0x00,
  0x00,0x00,0x00,0xFF,0xFE,0xFE,0xFD,0xFD,0xFB,0xF0,0xFE,0xFD,0xFB,0xF8,0xFF,0xFC,
  0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x37,0x18,0x10,0x10,0x10,0x10,0x39,0x00,0x00,0x00,0x00,0xFF,0xEF,0xEB,0xEF,0xDF,
  0x40,0x1B,0x5A,0xC1,0xDB,0xD8,0x83,0x5B,0xC0,0xDF,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8D,0x86,0x84,0x84,0x84,0x84,0xCE,0x00,
  0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFB,0xFC,0xFD,0xFD,0xFC,0xFD,0xFC,0xFD,0xFF,
  0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x04,0x00,0x00,
  0xCC,0x44,0x04,0x04,0x04,0x04,0x0E,0x00,0x00,0x00,0x00,0xFF,0xBF,0xBF,0xBF,0xA1,
  0x1B,0xBB,0x83,0x3B,0xBB,0x07,0xBF,0xBF,0xBF,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x22,0x18,0x44,0x42,0x7C,0x00,
  0x00,0x00,0x00,0xFF,0xFF,0xFD,0xFE,0xFF,0xF7,0xF9,0xFE,0xFD,0xFD,0xFD,0xFB,0x7B,
  0x7B,0x7E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x1E,0x21,0x21,0x3E,0x20,0x21,0x1E,0x00,0x00,0x00,0x00,0xFF,0xFF,0x77,0x07,0x55,
  0x55,0x55,0x55,0x55,0x55,0x35,0xBF,0x4F,0x75,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0x80,0x60,0x10,0x08,0x04,0x04,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0xFE,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,
  0x7E,0x7E,0xFC,0xFC,0xF8,0xF0,0xE0,0x80,
                     };

const unsigned char hz2[][72]={
/*--  文字:  多  0--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x30,0x00,0x00,0x60,0x30,0x00,0xDF,0xF0,
0x03,0x40,0x60,0x04,0x21,0x80,0x18,0x33,0x00,0x00,0x06,0x00,0x00,0x18,0x00,0x00,0xEC,0x00,
0x07,0x18,0x00,0x38,0x30,0x18,0x00,0x6F,0xF8,0x00,0xC0,0x30,0x03,0x20,0x60,0x0C,0x30,0xC0,
0x00,0x11,0x80,0x00,0x26,0x00,0x00,0x18,0x00,0x00,0xE0,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,
/*--  文字:  通  1--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x18,0x3F,0xF0,0x0C,0x0C,0xC0,0x0C,0x07,0x00,
0x00,0x03,0x08,0x00,0x7F,0xF8,0x00,0x42,0x08,0x04,0x42,0x08,0x3C,0x7F,0xF8,0x04,0x42,0x08,
0x04,0x42,0x08,0x04,0x42,0x08,0x04,0x7F,0xF8,0x04,0x42,0x08,0x04,0x42,0x08,0x04,0x42,0x08,
0x0C,0x42,0x38,0x33,0x00,0x10,0x60,0xC0,0x02,0x20,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
/*--  文字:  道  2--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x60,0x0C,0x18,0x40,0x0C,0x08,0x80,0x04,0x10,0x8C,
0x00,0xEF,0x70,0x00,0x02,0x00,0x04,0x24,0x30,0x7E,0x3B,0xF0,0x04,0x20,0x30,0x04,0x20,0x30,
0x04,0x3F,0xF0,0x04,0x20,0x30,0x04,0x20,0x30,0x04,0x3F,0xF0,0x04,0x20,0x30,0x04,0x20,0x30,
0x1A,0x3F,0xF0,0x31,0x40,0x00,0x20,0xC0,0x00,0x00,0x3F,0xFC,0x00,0x00,0x78,0x00,0x00,0x00,

/*--  文字:  耐  3--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x30,0x00,0x08,0x30,0x3F,0xF0,0x30,0x02,0x00,0x30,
0x02,0x00,0x30,0x02,0x00,0x36,0x3F,0xFF,0xF8,0x36,0x98,0x30,0x36,0x98,0x30,0x36,0x9A,0x30,
0x36,0x99,0x30,0x36,0x99,0xB0,0x36,0x99,0xB0,0x36,0x98,0xB0,0x36,0x98,0x30,0x36,0x98,0x30,
0x36,0x98,0x30,0x36,0x98,0x30,0x30,0x18,0x30,0x30,0x30,0xF0,0x20,0x00,0x60,0x00,0x00,0x00,

/*--  文字:  压  4--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x0F,0xFF,0xFC,0x0C,0x00,0x00,0x0C,0x0C,0x00,
0x0C,0x0C,0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00,0x0D,0xFF,0xF0,
0x0C,0x0C,0x00,0x0C,0x0C,0x00,0x08,0x0C,0x80,0x08,0x0C,0x40,0x08,0x0C,0x60,0x08,0x0C,0x30,
0x10,0x0C,0x20,0x10,0x0C,0x00,0x20,0x0C,0x0C,0x27,0xF3,0xF0,0x40,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  测  5--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x0C,0x09,0xFE,0x08,0x0D,0x86,0x08,0x05,0x86,0x48,
0x01,0xA6,0x48,0x41,0xB6,0x48,0x33,0xB6,0x48,0x13,0xB6,0x48,0x15,0xB6,0x48,0x05,0xB6,0x48,
0x05,0xB6,0x48,0x05,0xB6,0x48,0x09,0xA6,0x48,0x09,0xA6,0x48,0x39,0xA4,0x48,0x18,0x20,0x48,
0x18,0x58,0x08,0x18,0x44,0x08,0x18,0x86,0x08,0x19,0x02,0x38,0x06,0x00,0x18,0x00,0x00,0x00,

/*--  文字:  试  6--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xA0,0x10,0x01,0xD8,0x08,0x00,0x88,0x0C,0x00,0x88,
0x04,0x00,0x84,0x00,0xFF,0xFE,0x00,0x00,0x80,0x00,0x00,0x80,0x04,0x00,0x80,0x3C,0x02,0x80,
0x04,0x7D,0xC0,0x04,0x08,0xC0,0x04,0x08,0x40,0x04,0x08,0x40,0x04,0x48,0x60,0x04,0x88,0x22,
0x05,0x0F,0x34,0x07,0x38,0x14,0x06,0xE0,0x1C,0x04,0x00,0x0E,0x00,0x00,0x06,0x00,0x00,0x00,

/*--  文字:  仪  7--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x88,0x00,0x03,0x04,0x00,0x02,0x06,0x00,0x06,0x03,0x00,
0x04,0x02,0x30,0x04,0x00,0x30,0x0C,0x20,0x20,0x0C,0x20,0x60,0x14,0x10,0x40,0x14,0x10,0x40,
0x24,0x08,0x80,0x44,0x08,0x80,0x04,0x05,0x00,0x04,0x07,0x00,0x04,0x03,0x00,0x04,0x07,0x00,
0x04,0x0C,0xC0,0x04,0x18,0xE0,0x04,0x30,0x78,0x04,0x40,0x1E,0x05,0x80,0x08,0x00,0x00,0x00,

/*--  文字:  中  8--*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x10,0x10,0x18,
0x1F,0xFF,0xF8,0x18,0x10,0x18,0x18,0x10,0x18,0x18,0x10,0x18,0x18,0x10,0x18,0x18,0x10,0x18,
0x18,0x10,0x18,0x1F,0xFF,0xF8,0x10,0x10,0x10,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x10,0x00,
0x00,0x10,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  宁 9 --*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,
0x10,0x08,0x0F,0xFF,0xFC,0x10,0x00,0x18,0x30,0x00,0x20,0x00,0x00,0x20,0x00,0x00,
0x18,0x1F,0xFF,0xE0,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,
0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,
0xF0,0x00,0x00,0x30,0x00,0x00,0x00,0x00,

/*--  文字:  波 10 --*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/

0x00,0x00,0x00,0x00,0x02,0x00,0x10,0x03,0x00,0x0C,0x01,0x00,0x04,0x01,0x00,0x04,
0x01,0x08,0x01,0xFF,0xFC,0x41,0x41,0x18,0x21,0x41,0x10,0x32,0x41,0x00,0x12,0x41,
0x00,0x02,0x41,0x10,0x04,0x7E,0xF0,0x04,0x48,0x30,0x04,0x44,0x20,0x08,0x44,0x40,
0x78,0x42,0xC0,0x18,0x81,0x80,0x18,0x81,0x80,0x19,0x02,0xC0,0x19,0x0C,0x70,0x1A,
0x10,0x3C,0x04,0xE0,0x08,0x00,0x00,0x00,/*"波",1*/

/*--  文字:  电 11 --*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x1F,
0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x40,0x0F,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x7F,0xFF,0xFE,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"三",2*/


/*--  文字:  测 12 --*/
/*--  宋体18;  此字体下对应的点阵为：宽x高=24x24   --*/
0x00,0x00,0x00,0x00,0x08,0x00,0x06,0x0D,0x00,0x04,0x08,0xC0,0x0C,0x18,0x40,0x08,
0x18,0x40,0x08,0x90,0x0C,0x11,0xFF,0xF0,0x11,0xB0,0x80,0x21,0x30,0x80,0x3E,0x50,
0x88,0x26,0x9F,0xFC,0x04,0x90,0x80,0x08,0x10,0x80,0x11,0x90,0x88,0x3E,0x10,0x98,
0x30,0x1F,0xE0,0x00,0x10,0x80,0x01,0x90,0x80,0x0E,0x10,0x84,0x38,0x1F,0xFE,0x00,
0x10,0x00,0x00,0x10,0x00,0x00,0x00,0x00




};

unsigned char  num[][16]=
{
/*--0  文字:     --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--0  文字:     --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/							 //32位机需增加一组
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*-- 1 文字:  !  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/						   //
0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x18,0x18,0x00,0x00,

/*-- 2 文字:  "  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x12,0x36,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*-- 3 文字:  #  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x24,0x24,0x24,0xFE,0x48,0x48,0x48,0xFE,0x48,0x48,0x48,0x00,0x00,

/*--4  文字:  $  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x10,0x38,0x54,0x54,0x50,0x30,0x18,0x14,0x14,0x54,0x54,0x38,0x10,0x10,

/*-- 5 文字:  %  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x44,0xA4,0xA8,0xA8,0xA8,0x54,0x1A,0x2A,0x2A,0x2A,0x44,0x00,0x00,

/*--6  文字:  &  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x30,0x48,0x48,0x48,0x50,0x6E,0xA4,0x94,0x88,0x89,0x76,0x00,0x00,

/*-- 7 文字:  '  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x60,0x60,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  8文字:  (  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00,

/*-- 9 文字:  )  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00,

/*-- 10 文字:  *  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x10,0x10,0xD6,0x38,0x38,0xD6,0x10,0x10,0x00,0x00,0x00,0x00,

/*--11  文字:  +  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x00,0x00,0x00,

/*-- 12 文字:  ,  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x20,0xC0,

/*-- 13 文字:  -  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*-- 14 文字:  .  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,

/*--15  文字:  /  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x01,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x00,

/*-- 16 文字:  0  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,

/*--17  文字:  1  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,

/*--18  文字:  2  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x04,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00,

/*--19  文字:  3  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x04,0x18,0x04,0x02,0x02,0x42,0x44,0x38,0x00,0x00,

/*--20  文字:  4  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x04,0x0C,0x14,0x24,0x24,0x44,0x44,0x7E,0x04,0x04,0x1E,0x00,0x00,

/*-- 21 文字:  5  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x58,0x64,0x02,0x02,0x42,0x44,0x38,0x00,0x00,

/*-- 22 文字:  6  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x1C,0x24,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x24,0x18,0x00,0x00,

/*-- 23 文字:  7  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x7E,0x44,0x44,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,

/*-- 24 文字:  8  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00,

/*--25  文字:  9  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x26,0x1A,0x02,0x02,0x24,0x38,0x00,0x00,

/*-- 26 文字:  :  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,

/*-- 27 文字:  ;  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x20,

/*--28  文字:  <  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00,

/*-- 29 文字:  =  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,

/*--30  文字:  >  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00,

/*-- 31 文字:  ?  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x62,0x02,0x04,0x08,0x08,0x00,0x18,0x18,0x00,0x00,

/*-- 32 文字:  @  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x38,0x44,0x5A,0xAA,0xAA,0xAA,0xAA,0xB4,0x42,0x44,0x38,0x00,0x00,

/*-- 33 文字:  A  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00,

/*-- 34 文字:  B  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xF8,0x44,0x44,0x44,0x78,0x44,0x42,0x42,0x42,0x44,0xF8,0x00,0x00,

/*--35  文字:  C  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3E,0x42,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00,

/*-- 36 文字:  D  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00,

/*-- 37 文字:  E  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x42,0x42,0xFC,0x00,0x00,

/*-- 38 文字:  F  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x40,0x40,0xE0,0x00,0x00,

/*-- 39 文字:  G  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3C,0x44,0x44,0x80,0x80,0x80,0x8E,0x84,0x44,0x44,0x38,0x00,0x00,

/*--40  文字:  H  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,

/*-- 41 文字:  I  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,

/*-- 42 文字:  J  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0xF0,

/*-- 43 文字:  K  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xEE,0x44,0x48,0x50,0x70,0x50,0x48,0x48,0x44,0x44,0xEE,0x00,0x00,

/*-- 44 文字:  L  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0xFE,0x00,0x00,

/*--  45文字:  M  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xEE,0x6C,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x54,0x54,0xD6,0x00,0x00,

/*-- 46 文字:  N  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xC7,0x62,0x62,0x52,0x52,0x4A,0x4A,0x4A,0x46,0x46,0xE2,0x00,0x00,

/*-- 47 文字:  O  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,

/*-- 48 文字:  P  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0xE0,0x00,0x00,

/*-- 49 文字:  Q  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0xB2,0xCA,0x4C,0x38,0x06,0x00,

/*-- 50 文字:  R  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x48,0x44,0x44,0x42,0xE3,0x00,0x00,

/*-- 51 文字:  S  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x3E,0x42,0x42,0x40,0x20,0x18,0x04,0x02,0x42,0x42,0x7C,0x00,0x00,

/*-- 52 文字:  T  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xFE,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,

/*-- 53 文字:  U  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,

/*-- 54 文字:  V  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xE7,0x42,0x42,0x44,0x24,0x24,0x28,0x28,0x18,0x10,0x10,0x00,0x00,

/*--55  文字:  W  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xD6,0x92,0x92,0x92,0x92,0xAA,0xAA,0x6C,0x44,0x44,0x44,0x00,0x00,

/*-- 56 文字:  X  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00,

/*-- 57 文字:  Y  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,

/*--58  文字:  Z  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x7E,0x84,0x04,0x08,0x08,0x10,0x20,0x20,0x42,0x42,0xFC,0x00,0x00,

/*--59 文字:  [  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00,

/*--60  文字:  \  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x40,0x40,0x20,0x20,0x10,0x10,0x10,0x08,0x08,0x04,0x04,0x04,0x02,0x02,

/*--61  文字:  ]  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00,

/*-- 62 文字:  ^  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1C,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--63  文字:  _  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,

/*-- 64 文字:  `  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x60,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--65  文字:  a  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x1E,0x22,0x42,0x42,0x3F,0x00,0x00,

/*--66  文字:  b  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x00,0x00,

/*-- 67 文字:  c  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x22,0x1C,0x00,0x00,

/*-- 68 文字:  d  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x06,0x02,0x02,0x02,0x1E,0x22,0x42,0x42,0x42,0x26,0x1B,0x00,0x00,

/*--69  文字:  e  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x40,0x40,0x42,0x3C,0x00,0x00,

/*-- 70 文字:  f  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x0F,0x11,0x10,0x10,0x7E,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,

/*-- 71 文字:  g  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x44,0x44,0x38,0x40,0x3C,0x42,0x42,0x3C,

/*-- 72 文字:  h  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,

/*--73  文字:  i  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,

/*--74  文字:  j  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x1C,0x04,0x04,0x04,0x04,0x04,0x04,0x44,0x78,

/*-- 75 文字:  k  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x4E,0x48,0x50,0x68,0x48,0x44,0xEE,0x00,0x00,

/*-- 76 文字:  l  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,

/*--77  文字:  m  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x49,0x49,0x49,0x49,0x49,0xED,0x00,0x00,

/*--78  文字:  n  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDC,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,

/*--79  文字:  o  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,

/*-- 80 文字:  p  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x64,0x42,0x42,0x42,0x44,0x78,0x40,0xE0,

/*--81  文字:  q  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x22,0x42,0x42,0x42,0x22,0x1E,0x02,0x07,

/*--82  文字:  r  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x32,0x20,0x20,0x20,0x20,0xF8,0x00,0x00,

/*--83  文字:  s  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x40,0x3C,0x02,0x42,0x7C,0x00,0x00,

/*--84  文字:  t  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x0C,0x00,0x00,

/*-- 85 文字:  u  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00,

/*-- 86 文字:  v  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x10,0x10,0x00,0x00,

/*-- 87 文字:  w  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD7,0x92,0x92,0xAA,0xAA,0x44,0x44,0x00,0x00,

/*--88  文字:  x  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6E,0x24,0x18,0x18,0x18,0x24,0x76,0x00,0x00,

/*--89  文字:  y  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x18,0x10,0x10,0xE0,

/*--90  文字:  z  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x44,0x08,0x10,0x10,0x22,0x7E,0x00,0x00,

/*--91  文字:  {  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x04,0x04,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x04,0x04,0x03,0x00,

/*--92  文字:  |  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,

/*--93  文字:  }  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x60,0x10,0x10,0x10,0x10,0x10,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x60,0x00,

/*--94  文字:  ~  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x30,0x4C,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--95  文字:  .  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,

/*--96  文字:     --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,


}  ;



unsigned char hz1[][32]={
//联//
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x88,0xFC,0x48,0x48,0x50,0x48,0x00,0x79,0xFC,0x48,0x20,
0x48,0x20,0x78,0x20,0x4B,0xFE,0x48,0x20,0x4C,0x50,0x78,0x50,
0xC8,0x88,0x08,0x88,0x09,0x04,0x0A,0x02,

//系//
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xF8,0x3F,0x00,0x04,0x00,0x08,0x20,0x10,0x40,0x3F,0x80,
0x01,0x00,0x06,0x10,0x18,0x08,0x7F,0xFC,0x01,0x04,0x09,0x20,
0x11,0x10,0x21,0x08,0x45,0x04,0x02,0x00,

//热//
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x40,0x10,0x40,0x10,0x40,0xFD,0xF8,0x10,0x48,0x10,0x48,
0x1C,0xC8,0x30,0x48,0xD0,0xAA,0x10,0xAA,0x51,0x06,0x22,0x02,
0x00,0x00,0x48,0x88,0x44,0x44,0x84,0x44,

//线//
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x50,0x10,0x48,0x20,0x40,0x24,0x5C,0x45,0xE0,0xF8,0x40,
0x10,0x5E,0x23,0xE0,0x40,0x44,0xFC,0x48,0x40,0x30,0x00,0x22,
0x1C,0x52,0xE0,0x8A,0x43,0x06,0x00,0x02,

//通//
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x47,0xF8,0x20,0x10,0x21,0xA0,0x00,0x40,0x07,0xFC,0xE4,0x44,
0x24,0x44,0x27,0xFC,0x24,0x44,0x24,0x44,0x27,0xFC,0x24,0x44,
0x24,0x54,0x54,0x08,0x8F,0xFE,0x00,0x00,

//道//
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x02,0x08,0x21,0x10,0x10,0x00,0x17,0xFC,0x00,0x80,0x03,0xF8,
0xF2,0x08,0x13,0xF8,0x12,0x08,0x13,0xF8,0x12,0x08,0x13,0xF8,
0x12,0x08,0x28,0x00,0x47,0xFE,0x00,0x00,

};




#define AF320240_WRITE	(1)
#define AF320240_READ	(2)
#define RST_LCD			(1 << 5)
#define	AG320240_A0   (1 << 7)
#define AH320240_TSINT  (1 << 6)

#define AG320240_LCS    (1 << 12) //D
#define AG320240_DATA   (0X0007)
#define AG320240_DATA_1 (0XF000)



#define RA8835P_CS(x)		GPIO_WriteBit(GPIOD,AG320240_LCS,x);
#define RA8835P_RST(x)		GPIO_WriteBit(GPIOC,RST_LCD,x);
	
#define RA8835P_RD (x) 		GPIO_WriteBit(GPIOG,AF320240_READ,x);//		
#define RA8835P_WR(x)   	GPIO_WriteBit(GPIOG,AF320240_WRITE,x);
				
#define RA8835P_RS(x)   	GPIO_WriteBit(GPIOC,AG320240_A0,x);



#define RA8835P_Bus GPIOB->ODR

#define RA8835_OSC_FREQ_M    10
#define FR                   75

#define LcmYSize 240
#define LcmXSize 320

#define SCREEN_1_START_ADDRESS 0X0000
#define SCREEN_2_START_ADDRESS 0X58EF

#define SELECT_SCREEN_1  ScreenStartAddress = SCREEN_1_START_ADDRESS
#define SELECT_SCREEN_2  ScreenStartAddress = SCREEN_2_START_ADDRESS

#define  LcdCommand(x)	   WriteCommandRA8835P(x)
#define	 LcdDataWrite(x)   WriteDataRA8835P(x)
		 
//======================================== 变量定义 =============================================== 
u8 const BitWriteTab[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//用来写一位数据的掩码表

u16 ScreenStartAddress = 0; 

__asm void nop(void)
{
  NOP
  bx lr
}

void SomeNopRA8835P(void)
{
   nop();	   
   nop();
   nop();
   nop();
   nop();
   nop();
   nop();
   nop();
   nop();
   nop();
}


void AG320240_GPIOConfig(void)
{
 	GPIO_InitTypeDef 	GPIO_InitStructure;
	EXTI_InitTypeDef    EXTI_InitStructure;
	NVIC_InitTypeDef    NVIC_InitStructure;
	

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOB ,ENABLE );

	GPIO_InitStructure.GPIO_Pin = AF320240_WRITE | AF320240_READ  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG,AF320240_READ);

	GPIO_InitStructure.GPIO_Pin = RST_LCD | AG320240_A0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AG320240_DATA_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = AH320240_TSINT ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AG320240_LCS ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AG320240_DATA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = AH320240_TSINT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOG, &GPIO_InitStructure)  ;

	ExtLineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource6);

	spi_1_innit();
	

	RA8835P_RST(0);
	delay(60000);
	RA8835P_RST(1);
}							  


extern ST_Value g_stVlue;

void WriteCommandRA8835P(u16 CmdData)
{
	u16 v1= 0;
    RA8835P_RS(1);
    RA8835P_CS(0);
	SomeNopRA8835P();

    GPIOB->BSRR = 0x00070000 | ( CmdData & 0x03);//RA8835P_Bus = (u16)CmdData & 0X0FF;

	v1 = CmdData << 8;

	if(v1 & 0x0800)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_8, 1);
	}
	else
	{
		 GPIO_WriteBit(GPIOA,GPIO_Pin_8, 0);
	}

	if(v1 & 0x8000)
	{
		 GPIO_WriteBit(GPIOE,GPIO_Pin_12,1);
	}
	else
	{
		 GPIO_WriteBit(GPIOE,GPIO_Pin_12,0);
	}

	if(v1 & 0x4000)
	{
		 GPIO_WriteBit(GPIOE,GPIO_Pin_13,1);
	}
	else
	{
		  GPIO_WriteBit(GPIOE,GPIO_Pin_13,0);
	}

	if(v1 & 0x2000)
	{
	   GPIO_WriteBit(GPIOE,GPIO_Pin_14,1);
	}
	else
	{
	   GPIO_WriteBit(GPIOE,GPIO_Pin_14,0);
	}

	if(v1 & 0x1000)
	{
		GPIO_WriteBit(GPIOE,GPIO_Pin_15,1);
	}
	else
	{
		GPIO_WriteBit(GPIOE,GPIO_Pin_15,0);
	}
    SomeNopRA8835P();
    RA8835P_WR(0);
    SomeNopRA8835P();
    RA8835P_WR(1);
    RA8835P_CS(1);
}

void WriteDataRA8835P(u16 Data)
{
	u16 v1= 0;
    RA8835P_RS(0);
    RA8835P_CS(0);
						    
	SomeNopRA8835P();
    GPIOB->BSRR = 0x00070000 | ( Data & 0x03);// RA8835P_Bus = Data & 0X0FF;
	v1 = Data << 8;

	if(v1 & 0x0800)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_8, 1);
	}
	else
	{
		 GPIO_WriteBit(GPIOA,GPIO_Pin_8, 0);
	}

	if(v1 & 0x8000)
	{
		 GPIO_WriteBit(GPIOE,GPIO_Pin_12,1);
	}
	else
	{
		 GPIO_WriteBit(GPIOE,GPIO_Pin_12,0);
	}

	if(v1 & 0x4000)
	{
		 GPIO_WriteBit(GPIOE,GPIO_Pin_13,1);
	}
	else
	{
		  GPIO_WriteBit(GPIOE,GPIO_Pin_13,0);
	}

	if(v1 & 0x2000)
	{
	   GPIO_WriteBit(GPIOE,GPIO_Pin_14,1);
	}
	else
	{
	   GPIO_WriteBit(GPIOE,GPIO_Pin_14,0);
	}

	if(v1 & 0x1000)
	{
		 GPIO_WriteBit(GPIOE,GPIO_Pin_15,1);
	}
	else
	{
		  GPIO_WriteBit(GPIOE,GPIO_Pin_15,0);
	}
	
   
    SomeNopRA8835P();
    RA8835P_WR(0);
    SomeNopRA8835P();
    RA8835P_WR(1);
    RA8835P_CS(1);
}

void ShowScreen1(void)
{
	WriteCommandRA8835P(0x59);  //DISPLAY ON SET 
    WriteDataRA8835P(0x04); //SET P1  ()
}

void ShowScreen2(void)
{
	WriteCommandRA8835P(0x59);  //DISPLAY ON SET 
    WriteDataRA8835P(0x10); //SET P1  ()
}

void Display_Locate(u8 DisplayData, u8 x0, u8 y0)
{    
	 u16 csr;
     csr = ScreenStartAddress + y0*(LcmXSize/8) + x0;
     WriteCommandRA8835P(0x46);	//CURSOR SET
     WriteDataRA8835P(csr%256);	//SET P1  (00H)
     WriteDataRA8835P(csr/256);	//SET P2  (00H)
     WriteCommandRA8835P(0x42);	//READY TO WRITE DATA   
     WriteDataRA8835P(DisplayData);         
}

//============================================================================= 
//函 数 名: ScanScreen() 
//功 能:    扫描屏幕
//入口参数: data1:奇数行的数据  data2:偶数行的数据 
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void ScanScreen(u8 data1,u8 data2)
{	
    u8 i,j;

    WriteCommandRA8835P(0x46);	//CURSOR SET
    WriteDataRA8835P(ScreenStartAddress%256);	//SET P1  (00H)
    WriteDataRA8835P(ScreenStartAddress/256);	//SET P2  (00H)
    WriteCommandRA8835P(0x42);	//READY TO WRITE DATA

	for(i=0;i<LcmYSize/2;i++)
   	{
     	for(j=0;j<LcmXSize/8;j++)
        {
        	WriteDataRA8835P(data1);                  				   
        }
        for(j=0;j<LcmXSize/8;j++)																			 
        {
            WriteDataRA8835P(data2);                  				   
        }
    }
}

//============================================================================= 
//函 数 名: DrawPicture() 
//功 能: 	绘制320*240图片
//入口参数:  *p:指向图片的首地址 
//           注意:为了节省空间，图片采取压缩算法
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void DrawPictureRA8835(u8 *p)
{
	u16 i,j,k;

    WriteCommandRA8835P(0x46);	//CURSOR SET
    WriteDataRA8835P(ScreenStartAddress%256);	//SET P1  (00H)
    WriteDataRA8835P(ScreenStartAddress/256);	//SET P2  (00H)
    WriteCommandRA8835P(0x42);	//READY TO WRITE DATA

	for(i=0;i<9600;)
	{       
      	if((*p==0x00)||(*p==0xff)){
			if(*(p+1)==0x00){
				k=(*(p+3)*256)+*(p+2);	
				for(j=0;j<k;j++)
			 	{
			 		WriteDataRA8835P(*p);
			 	    i++;
			 	   
				}
			 	p+=4;
			} 
			else 
			{				
				k=*(p+1);	
				for(j=0;j<k;j++)
			 	{
			 		 WriteDataRA8835P(*p);
			 		 i++;
			 	}
			 	p+=2;	
			}
			
		} else {
		    WriteDataRA8835P(*p++);
	        i++;	        
		} 
	}



}

void SetCursor(unsigned char CursorHIGH,unsigned char CursorLOW)
{
        delay(100);
        LcdCommand(0x4f);		 //向下
				delay(100);
        LcdCommand(0x46);
				delay(100);
        LcdDataWrite(CursorLOW);
				delay(100);
        LcdDataWrite(CursorHIGH);
        delay(100);
        LcdCommand(0x42);
}

union 
{
	unsigned int word;
	
  struct 
	{
		unsigned char low;
		unsigned char high;
  }byte;
}value; 


void chdisp(unsigned char x,unsigned char y,unsigned char *p,unsigned char z)
{
       unsigned char i,j,uLen,c1,*p1;
       unsigned int k;		 

       switch(z)
       {
		   case 1:
	           value.word=y*40+x+0x0000;//一屏	   1和2 或
	       break;

           case 2:
                value.word=y*40+x+0x2580;//二屏	   1和3	异或
           break;

           case 3:
                value.word=y*40+x+0x4b00;//三屏	   2和3 异或
           break;
       }

        uLen=0;

        while ( (unsigned char)p[uLen] >= 0x10 )
		{
			uLen++;
		}	   

        i=0;

        while(i<uLen)						//把*p指向的内容一个个都写出来
        {
			c1=*(p+i);
            SetCursor(value.byte.high,value.byte.low);
		    if (c1 >= 0x10)	
			{
                 k=c1-0x20;
                 p1=&num[k][16];
			     for(j=0;j<16;j++) 
				 {
				   LcdDataWrite(*p1++);
				   delay(100);
				 }	   
		    }
		    value.word++;						// 列数加1
			i++;
 		}
}

void  clear1(void)
{
  		unsigned int x;
		delay(100);
        LcdCommand(0x4c);
		delay(100);
        LcdCommand(0x46);

        LcdDataWrite(0);
        LcdDataWrite(0);
		delay(100);
        LcdCommand(0x42);

        for(x=0;x<0x2580;x++)
        {
          	LcdDataWrite(0);
        }
}

void clear2(void)
{     
	unsigned int x;
  	delay(100);
    LcdCommand(0x4c);
	delay(100);
    LcdCommand(0x46);

    LcdDataWrite(0x80);
    LcdDataWrite(0x25);
	delay(100);
    LcdCommand(0x42);
    for(x=0;x<0x2580;x++)
    {
        LcdDataWrite(0);
    }
}

void clear3(void)
{
     unsigned int x;
	 delay(100);
     LcdCommand(0x4c);
	 delay(100);
     LcdCommand(0x46);

     LcdDataWrite(0x00);

     LcdDataWrite(0x4b);

     delay(100);

     LcdCommand(0x42);

     for(x=0;x<0x2580;x++)
     {
        LcdDataWrite(0);
     }
}

void frame(void)			//显示大框
{
	unsigned char i,j;
	LcdCommand(0x46);	
	LcdDataWrite(0x80);	 
	LcdDataWrite(0x25);	  //9600

	for(j=0;j<=1;j++)
	{
		if(j)
		{
			LcdCommand(0x46);	
			LcdDataWrite(0xb0);	//19 120
			LcdDataWrite(0x4a);
		}
		LcdCommand(0x4c);//right														     
		LcdCommand(0x42);   
		for(i=0;i<=79;i++)
			LcdDataWrite(0xff);	 
	}
	LcdCommand(0x46);//Set cursor address	
	LcdDataWrite(0xd0);	 //9680
	LcdDataWrite(0x25);
	LcdCommand(0x4f);   //down
	LcdCommand(0x42);	//Write to display memory
	for(i=0;i<=235;i++)
		LcdDataWrite(0xc0);		 
	LcdCommand(0x46);		  
	LcdDataWrite(0xf7);	//9719
	LcdDataWrite(0x25);
	LcdCommand(0x42);		  
	for(i=0;i<=235;i++)
		LcdDataWrite(0x03);		
}

void dis_biao(void)
{
	unsigned char count2,count3;
    unsigned char faucs;
    faucs=0x22;
    for(count3=0;count3<9;count3++)
    {
     LcdCommand(0x4f);	//设置方向下
     LcdCommand(0x46);	   //设置光标
     LcdDataWrite(faucs);  //180*40+2
     LcdDataWrite(0x1c); //240/8=30
     LcdCommand(0x42);   //连续写入
     LcdDataWrite(0);
     LcdDataWrite(0);

     for(count2=0;count2<40;count2++)     
	 {
	 	LcdDataWrite(biaozi[count3*40+count2]);
     }
     faucs++;
    }
 }

void hzdisp1(unsigned char x,unsigned char y,const unsigned char *p,unsigned char z)	 //X<40,y<240
{
        
		unsigned char i;

        switch(z)
        {
		   case 1:
                value.word=y*40+x+0x0000;//一屏
                break;
           case 2:
                value.word=y*40+x+0x2580;//二屏
                break;
           case 3:
                value.word=y*40+x+0x4b00;//三屏
                break;

        }

        SetCursor(value.byte.high,value.byte.low);
        i=0;
        do
        {
                LcdDataWrite(p[i]);
                i=i+3;
        }
        while(i<69);
        value.word++;
        SetCursor(value.byte.high,value.byte.low);
        i=1;
        while(i<70)
        {
                LcdDataWrite(p[i]);
                i=i+3;
        }
        value.word++;
        SetCursor(value.byte.high,value.byte.low);

        i=2;
        while(i<71)
        {
                LcdDataWrite(p[i]);
                i=i+3;
        }

     }

void hzdisp(unsigned char x,unsigned char y,unsigned char *p,unsigned char z) 
{
        unsigned char i;
        switch(z)
        {
		   case 1:
                value.word=y*40+x+0x0000;

                break;
           case 2:
                value.word=y*40+x+0x2580;
                break;
           case 3:
                value.word=y*40+x+0x4b00;

                break;

          }

        SetCursor(value.byte.high,value.byte.low);
        i=0;
        do
        {
                LcdDataWrite(p[i]);
                i=i+2;
        }
        while(i<0x1e);
        value.word++;
        SetCursor(value.byte.high,value.byte.low);
        i=1;
        while(i<0x1f)
        {
                LcdDataWrite(p[i]);
                i=i+2;
        }
}

void dis_frame(void)
{
  	unsigned char i,j,d;
	LcdCommand(0x46);	
	LcdDataWrite(0x80);	 
	LcdDataWrite(0x25);	  //9600
	for(j=0;j<6;j++)
	{
		if(j==1)
		{
			LcdCommand(0x46);	
			LcdDataWrite(0xd0);	//10960
			LcdDataWrite(0x2a);
		}
	    else if(j==2)
		{
			LcdCommand(0x46);	
			LcdDataWrite(0x20);	//12320	   +1360
			LcdDataWrite(0x30);
		}

		else if(j==3)
		{
			LcdCommand(0x46);	
			LcdDataWrite(0x70);	//13680
			LcdDataWrite(0x35);
		}

		else if(j==4)
		{
			LcdCommand(0x46);	
			LcdDataWrite(0xc0);	//15040
			LcdDataWrite(0x3a);
		}

		else if(j==5) 
		{
			LcdCommand(0x46);	
			LcdDataWrite(0xb0);	//19120
			LcdDataWrite(0x4a);
		}
#if 0			   
	    else if(j==5)
		{
			LcdCommand(0x46);	
			LcdDataWrite(0x10);	//16400
			LcdDataWrite(0x40);
		}
		
		else if(j==6)
		{
			LcdCommand(0x46);	
			LcdDataWrite(0x60);	//17760
			LcdDataWrite(0x45);
		}
		else if(j==7) 
		{
			LcdCommand(0x46);	
			LcdDataWrite(0xb0);	//19120
			LcdDataWrite(0x4a);
		}
#endif
		LcdCommand(0x4c);//right	
		LcdCommand(0x42);   

		for(i=0;i<=79;i++)
			LcdDataWrite(0xff);	 
	}

	for(d=0;d<7;d++)
	{
		value.word=9680+1360*d;
		LcdCommand(0x46);		
		LcdDataWrite(value.byte.low);	 
		LcdDataWrite(value.byte.high);
		LcdCommand(0x4f);   
		LcdCommand(0x42);	
		for(i=0;i<32;i++)
		{
			LcdDataWrite(0xc0);
		}
	}

	for(d=0;d<7;d++)
	{
		value.word=9719+1360*d;
		LcdCommand(0x46);		
		LcdDataWrite(value.byte.low);	 
		LcdDataWrite(value.byte.high);
		LcdCommand(0x4f);   
		LcdCommand(0x42);	
		for(i=0;i<32;i++)
			LcdDataWrite(0x03);
	}


	for(d=0;d < 3;d++)
	{
		value.word=11049+1360*d;
		LcdCommand(0x46);		
		LcdDataWrite(value.byte.low);	 
		LcdDataWrite(value.byte.high);
		LcdCommand(0x4f);   
		LcdCommand(0x42);	
		for(i=0;i<32;i++)
			LcdDataWrite(0x03);
	}

	for(d=0;d < 3;d++)
	{
		value.word=11059+1360*d;
		LcdCommand(0x46);		
		LcdDataWrite(value.byte.low);	 
		LcdDataWrite(value.byte.high);
		LcdCommand(0x4f);   
		LcdCommand(0x42);	
		for(i=0;i<32;i++)
			LcdDataWrite(0x03);
	}

	for(d=0;d<3;d++)
	{
		value.word=11069+1360*d;
		LcdCommand(0x46);		
		LcdDataWrite(value.byte.low);	
		LcdDataWrite(value.byte.high);
		LcdCommand(0x4f);   
		LcdCommand(0x42);	
		for(i=0;i<32;i++)
			LcdDataWrite(0x03);
	}
}



void screen1(void )
{
#if 0
    clear1();
    clear2();
    clear3();

	frame();
	dis_biao();
   
    hzdisp1(8, 60,hz2[0],1);
    hzdisp1(11,60,hz2[1],1);
    hzdisp1(14,60,hz2[2],1);
    hzdisp1(17,60,hz2[3],1);
    hzdisp1(20,60,hz2[4],1);
    hzdisp1(23,60,hz2[5],1);
    hzdisp1(26,60,hz2[6],1);
    hzdisp1(29,60,hz2[7],1);												 

    hzdisp(12,190,hz1[0],1);
    hzdisp(14,190,hz1[1],1);
	hzdisp(14,190,hz1[1],1);
	hzdisp(14,190,hz1[1],1);
    hzdisp(16,190,hz1[2],1);
    hzdisp(18,190,hz1[3],1);

    chdisp(20,190,":     0574-87577658",1);
    chdisp(12,205,"Sunrise Instruments CO.,LTD.",1);
#endif
}


#if 1
void screen2(void )
{
    clear1();
    clear2();
    clear3();
	dis_frame();
    chdisp(8,10," ",1);
	hzdisp1(10,5,hz2[9],1);
	hzdisp1(14,5,hz2[10],1);
    hzdisp1(18,5,hz2[11],1);
	hzdisp1(22,5,hz2[12],1);

	hzdisp(1,44,hz1[4],1);
	hzdisp(3,44,hz1[5],1);
	chdisp(5,44,"1 :",1);

	hzdisp(1,78,hz1[4],1);
	hzdisp(3,78,hz1[5],1);
	chdisp(5,78,"2 :",1);

	hzdisp(1,112,hz1[4],1);
	hzdisp(3,112,hz1[5],1);
	chdisp(5,112,"3 :",1);
#if 0
	hzdisp(1,146,hz1[4],1);
	hzdisp(3,146,hz1[5],1);
	chdisp(5,146,"4 :",1);

	hzdisp(1,180,hz1[4],1);
	hzdisp(3,180,hz1[5],1);
	chdisp(5,180,"5 :",1);

	hzdisp(1,214,hz1[4],1);
	hzdisp(3,214,hz1[5],1);
	chdisp(5,214,"6 :",1);
#endif
	hzdisp(21,44,hz1[4],1);
	hzdisp(23,44,hz1[5],1);
	chdisp(25,44,"4 :",1);
	hzdisp(21,78,hz1[4],1);
	hzdisp(23,78,hz1[5],1);
	chdisp(25,78,"5 :",1);
	hzdisp(21,112,hz1[4],1);
	hzdisp(23,112,hz1[5],1);
	chdisp(25,112,"6 :",1);

#if 0
	hzdisp(21,146,hz1[4],1);
	hzdisp(23,146,hz1[5],1);
	chdisp(25,146,"10:",1);
	hzdisp(21,180,hz1[4],1);
	hzdisp(23,180,hz1[5],1);
	chdisp(25,180,"11:",1);
	hzdisp(21,214,hz1[4],1);
	hzdisp(23,214,hz1[5],1);
	chdisp(25,214,"12:",1);
#endif  
  
	chdisp(17,44,"V",1);
	chdisp(12,44,"0000",1);
	chdisp(38,44,"V",1);
	chdisp(18,78,"V",1);
	chdisp(38,78,"V",1);
	chdisp(18,112,"V",1);
	chdisp(38,112,"V",1);

#if 0
	chdisp(18,146,"V",1);
	chdisp(38,146,"V",1);
	chdisp(18,180,"V",1);
	chdisp(38,180,"V",1);
	chdisp(18,214,"V",1);
	chdisp(38,214,"V",1); 
#endif  

}
#endif





void AG320240_Init(void)
{
	u16 i= 0;

	AG320240_GPIOConfig();

	spi_1_innit();
 #if 1
	LcdCommand(0x40);       /* ---------LCD SYSTEM SET系统设置令,8个参数-------- */
    LcdDataWrite(0x30);  //0x30 如果要用内部字符集，必须设成30,而且只能显示在第一屏
    LcdDataWrite(0x87);
    LcdDataWrite(0x07);
    LcdDataWrite(39);       /* 显示域长度为320dot */
    LcdDataWrite(0x5c);     /* 确定液晶工作频率 */
    LcdDataWrite(0xf0);      /* 显示屏高度为240dot */
    LcdDataWrite(40);       /* 显示屏一行所占显示缓冲区字节数(L) */
    LcdDataWrite(0);        /* 显示屏一行所占显示缓冲区字节数(H) */
    delay(100);
    LcdCommand(0x44);       /* ---------LCD SCROLL显示区设置命令,最多10个参数--------- */

    LcdDataWrite(0x00);     /* 显示1区对应的显示RAM起始高8位地址 */
    LcdDataWrite(0x00);     /* 显示1区对应的显示RAM起始低8位地址 */
    LcdDataWrite(0xef);      /* 显示1区占用240个dot行 */
    LcdDataWrite(0x80);     /* 显示2区对应的显示RAM起始低8位地址 */
    LcdDataWrite(0x25);     /* 显示2区对应的显示RAM起始高8位地址 */
    LcdDataWrite(0xef);      /* 显示3区占用240个dot行 */
    LcdDataWrite(0x00);     /* 显示3区对应的显示RAM起始低8位地址 */
    LcdDataWrite(0x4b);     /* 显示3区对应的显示RAM起始高8位地址 */
    LcdDataWrite(0x00);
    LcdDataWrite(0x00);
    delay(100);

    LcdCommand(0x5a);       /* 水平卷动,初始化时必须清零 */
    LcdDataWrite(0x00);
    delay(100);

    LcdCommand(0x5b);       /* 各个显示区的合成方式,1个参数 */
    LcdDataWrite(0x1d);     /* 参数:显示方式为三屏图形叠加,逻辑或 */
    delay(100);

    LcdCommand(0x59);       /* 打开显示,1个参数 */
    LcdDataWrite(0x54);     /* 只显示第一个区并关闪烁 */
    delay(100);

    LcdCommand(0x4c);       /* 光标自动向右增一?*/
    delay(100);

    LcdCommand(0x46);       /* 设定光标位置命令 */
    LcdDataWrite(0);        /* 从0000位置开始 */
    LcdDataWrite(0);
    delay(100);

    LcdCommand(0x42);       /* 允许MPU连续地把显示数据写入显示区内命令 */

    for( i=0;i<32760;i++)
    {
        LcdDataWrite(0);  /* 将32K显缓全部清零，即LCD不显示任何东西 */
    }
#else
	WriteCommandRA8835P(0x40);  //SYSTEM SET
	delay(1000);
    WriteDataRA8835P(0x30); //SET P1 (M0=M1=M2=0,W/S=0,IV=1)
    WriteDataRA8835P(0x87); //SET P2 ()
    WriteDataRA8835P(0x07); //SET P3
    WriteDataRA8835P(LcmXSize/8-1); //SET P4 C/R (40 columns=40*8 dots)
    WriteDataRA8835P(RA8835_OSC_FREQ_M*1000000/9/FR/240);  //SET P5 TC/R (TC/R>=C   /R+4)   48
    WriteDataRA8835P(LcmYSize-1);   //SET P6 L/F (240 COM)
    WriteDataRA8835P(LcmXSize/8); //SET P7 (AP=C/R+1)
    WriteDataRA8835P(0x00); //SET P8 
    WriteCommandRA8835P(0x44);  //SCROLL SET
    WriteDataRA8835P(SCREEN_1_START_ADDRESS%256); //SET P1 (SAD1 L)
    WriteDataRA8835P(SCREEN_1_START_ADDRESS/256); //SET P2 (SAD1 H )
    WriteDataRA8835P(LcmYSize); //SET P3 (240 LINE FOR FIRST BLOCK DISPLAY)
    WriteDataRA8835P(SCREEN_2_START_ADDRESS%256); //SET P4  (SAD2 L)
    WriteDataRA8835P(SCREEN_2_START_ADDRESS/256); //SET P5  (SAD2 H)
    WriteDataRA8835P(LcmYSize); //SET P6  (240 LINE FOR SECOND BLOCK DISPLAY)
    WriteCommandRA8835P(0x5a);  //HDOT SCR SET
    WriteDataRA8835P(0x00); //SET P1  (D0=D1=D2=0)
    WriteCommandRA8835P(0x5b);  //OVLAY SET
    WriteDataRA8835P(0x0d); //SET P1  (OV=0,DM2=DM1=1,MX1=MX0=0)
    WriteCommandRA8835P(0x58);  //DISPLAY ON/OFF SET
    WriteDataRA8835P(0x16); //SET P1  (THIRD SCREEN DISPLAY OFF,
    WriteCommandRA8835P(0x5d);  //CURSOR TYPE (CSRFORM) SET 
    WriteDataRA8835P(0x07); //SET P1  ()
    WriteDataRA8835P(0x81); //SET P2  ()
    WriteCommandRA8835P(0x59);  //DISPLAY ON SET 
    WriteDataRA8835P(0x06); //SET P1  ()
    WriteCommandRA8835P(0x4c);  //CSRDID SET 
	//AG320240_Test();
#endif
}



void AG320240_Test(void)
{
	u8 * p;
	//WriteDataRA8835P(0X55);
 	//WriteDataRA8835P(0XAA);
	//WriteCommandRA8835P(0X55);
	//WriteCommandRA8835P(0XAA);
	SELECT_SCREEN_1;//选择第一屏
	ShowScreen1();  //显示第一屏
	ScanScreen(0xaa,0x55);
	delay(60000)   ;
	delay(60000)   ;
	delay(60000)   ;
	delay(60000)   ;
	delay(60000)   ;
//	Delay_ms(TEST_DELAY_TIME);	    
//	p= (u8 *)BMP2;
	DrawPictureRA8835(p);//交叉线
//	Delay_ms(TEST_DELAY_TIME-100);
//	DrawPictureRA8835(BMP2);//回形
//	Delay_ms(TEST_DELAY_TIME-100);
}


												   

//#include <stdarg.h>
//#include <string.h>
//#include <stdlib.h>					 
//#include <stdio.h>

//extern const GUI_BITMAP bmlogo;
//unsigned char ASCIITable[]="0123456789ABCDEF";
//extern void dface1(void);
//extern void dface2(void);


// int LCD_Adr;

//U8 Empty_mode;//清屏模式

//#define  TRUE    1
//#define  FALSE   0

//#define DFACE_TM 	100000  		//DFACE显示时间间

/*
#define Sleep_in		0x53

#define SystemSet        	0x40
#define Scroll           	0x44
#define DispOn           	0x59
#define DispOff          	0x58
#define Ovlay            	0x5b
#define HdotScr          	0x5a
#define CsrForm          	0x5d
#define CgramAdr         0x5c
#define CsrDirR          	0x4c
#define CsrDirL          	0x4d
#define CsrDirU          	0x4e
#define CsrDirD          	0x4f
#define CsrW             	0x46
#define CsrR             	0x47
#define mWrite           	0x42
#define mRead            	0x43


#define WriteCommand Cmdwrite
#define WriteData           Datawrite




typedef  struct
{
	unsigned	Font : 2;
	unsigned	LCD_DrawMode : 2;
	unsigned	LCD_Layer	: 2;
//	unsigned	Funct:	3;
//	unsigned	SecErd:	2;
//	unsigned	Dengji: 2;
//	unsigned	Dengjis:1;
//	unsigned	Range:  2;
	char			X;
	U16			Y;
}Sys_Mode;

Sys_Mode Currsys;



#define  	 SetFont(font)		Currsys.Font = font
#define	 SetDraw(mode)	Currsys.LCD_DrawMode = mode
#define	 SetLayer(lay)		Currsys.LCD_Layer = lay//; LCD_Layer= lay

#define	LCD_X	(Currsys.X)
#define	LCD_Y	(Currsys.Y)

#define  FONT_16  0   
#define  FONT_24  1
#define  FONT_32  2

*/


/*

void mDelay1_2uS( )  //至少延时1.2uS,根据单片机主频调整 
{
	U32	i;
	for ( i = 20; i != 0; i -- );  // 本例由于模拟I/O较慢故只需少量延时 
}



//--------------写指令代码------------------------------ 
void Cmdwrite(unsigned char cmdcode) 
{ 
mDelay1_2uS( ); mDelay1_2uS( );  // 至少延时1uS
SED1335_CMD=cmdcode;
mDelay1_2uS( ); mDelay1_2uS( );  // 至少延时2uS 
} 

//--------------写数据或参数----------------------------- 
void Datawrite(unsigned char wrdata) 
{ 
SED1335_DAT=wrdata;
mDelay1_2uS( );  // 至少延时1.2uS 
}  

//===============================================
//读参数及显示数据子函数
U8 ReadCommand()
{
U8 ReadReg;
mDelay1_2uS( );  // 至少延时1.2uS 
ReadReg = (U8)SED1335_CMD;
return (ReadReg);
}


//SED1335命令写函数
void sed1335_write(unsigned char commandcode, unsigned char *parameter,unsigned char n)
{
unsigned char i=0;

mDelay1_2uS( ); mDelay1_2uS( );  // 至少延时1uS
SED1335_CMD=commandcode;
mDelay1_2uS( ); mDelay1_2uS( );  // 至少延时1uS 
   
for(i=0;i<n;i++)
	{
 	SED1335_DAT=parameter[i];
 	mDelay1_2uS( );  // 至少延时1.2uS
	}
}

 
//sed1335读函数，可以读取光标，显示数据

void sed1335_read(char commandcode, unsigned char *parameter,unsigned int n)
{
int i=0;
U8 tmp;

mDelay1_2uS( ); mDelay1_2uS( );  // 至少延时1uS 
SED1335_CMD=commandcode;
mDelay1_2uS( ); mDelay1_2uS( );  //至少延时1uS 

for(i=0;i<n;i++)
	{
		mDelay1_2uS( );  //至少延时1.2uS 
		tmp=SED1335_CMD;
		parameter[i]=tmp;		
	}

}  
 */        

  
  /*   
//--------------整屏幕写入数据--------------------------- 
void Fullscreenfill(unsigned char low,unsigned char high, unsigned char  fill_data) 
{ 
unsigned char i,j; 
Cmdwrite(CsrW); 
Datawrite(low); 
Datawrite(high); 
Cmdwrite(mWrite); 
for(i=0;i<240;i++) 
{
   for(j=0;j<40;j++) 
     { Datawrite(fill_data); }
 }
}    
//===============================================                  
void Disp_On(void)			//显示开函数
{
Cmdwrite( DispOn );
}


void Disp_Off(void)			//显示关函数
{
//Cmdwrite( DispOff );
}


//===============================================
//清LCD全屏子函数

void LcdClear(void)
{
    U16 i1=0x8000;

    WriteCommand(CsrDirR);   // 光标移动方向定义：自动右移
    WriteCommand(CsrW);      // 光标SCRW,定位参数   2个参数
    WriteData(0x00);         // 写入参数CSRL设置参数光标指针低8位
    WriteData(0x00);         // 写入参数CSRH设置参数光标指针高8位
    WriteCommand(mWrite);    //0x42  数据写入指令，代码0x42
    while(i1--)    {
        WriteData(0x00);     // 写入32768个数据0x00 ,即清除LCD显示
                    }
     }
     
//===============================================
//清LCD屏第1显示区子函数
void LcdClear_1(void)
{
U16 i1=0X2580;
    WriteCommand(CsrDirR);    // 光标移动方向定义：自动右移
    WriteCommand(CsrW);       // 光标SCRW,定位参数   2个参数
    WriteData(0x00);          // 写入参数CSRL设置参数光标指针低8位
    WriteData(0x00);          // 写入参数CSRH设置参数光标指针高8位
    WriteCommand(mWrite);     // 数据写入指令，代码0x42
    while(i1--)    {
        WriteData(0x00);      //写入9600个数据0x00,即清除LCD显示1区
                    }
     }
//===============================================
//清LCD屏第2显示区子函数
void LcdClear_2(void)
{
U16 i1=0X2580;
    WriteCommand(CsrDirR);   // 光标移动方向定义：自动右移
    WriteCommand(CsrW);      // 光标SCRW,定位参数   2个参数
    WriteData(0x80);         // 写入参数CSRL设置参数光标指针低8位
    WriteData(0x25);         // 写入参数CSRH设置参数光标指针高8位
    WriteCommand(mWrite);    // 数据写入指令，代码0x42
    while(i1--)    {
        WriteData(0x00);     // 写入9600个数据0x00 ,即清除LCD显示2区
                    }
     }
 //LCD屏第2显示区填充全黑子函数
void LcdFill_2(void)
{
U16 i1=0X2580;
    WriteCommand(CsrDirR);   // 光标移动方向定义：自动右移
    WriteCommand(CsrW);      // 光标SCRW,定位参数   2个参数
    WriteData(0x80);         // 写入参数CSRL设置参数光标指针低8位
    WriteData(0x25);         // 写入参数CSRH设置参数光标指针高8位
    WriteCommand(mWrite);    // 数据写入指令，代码0x42
    while(i1--)    {
        WriteData(0xff);     // 写入9600个数据0x00 ,即清除LCD显示2区
                    }
     }    
//===============================================
//清LCD屏第3显示区子函数
void LcdClear_3(void)
{
U16 i1=0X2580;
    WriteCommand(CsrDirR);   // 光标移动方向定义：自动右移
    WriteCommand(CsrW);      // 光标SCRW,定位参数   2个参数
    WriteData(0x00);         // 写入参数CSRL设置参数光标指针低8位
    WriteData(0x4b);         // 写入参数CSRH设置参数光标指针高8位
    WriteCommand(mWrite);    // 数据写入指令，代码0x42
    while(i1--)    {
        WriteData(0x00);     // 写入9600个数据0x00 ,即清除LCD显示3区
                    }
     }
 
     
//===============================================     
//--------------模块初始化------------------------------- 
void LCD_Initial(void) 
{ 
//_RES=0; 
//delay_ms(100); 
//_RES=1; 
//delay_ms(100); 

 Cmdwrite( DispOff );

Cmdwrite(SystemSet); 
Datawrite(0x37); 
Datawrite(0x87); 
Datawrite(0x07); 
Datawrite(0x27); 
Datawrite(0x5c); 
Datawrite(0xf0); 
Datawrite(0x28); 
Datawrite(0x00); 

Cmdwrite(Scroll); 
Datawrite(0x00);        // 第1显示区的起始地址
Datawrite(0x00);        // 第1显示区的起始地址
Datawrite(0xF0);        // 第1显示区所控制的显示屏上的行数：0~(L/F)  40行
Datawrite(0x80);        // 第2显示区的起始地址
Datawrite(0x25);        // 第2显示区的起始地址
Datawrite(0xF0);        // 第2显示区所控制的显示屏上的行数：0~(L/F)  40行
Datawrite(0x00);        // 第3显示区的起始地址
Datawrite(0x4B);        // 第3显示区的起始地址
Datawrite(0x00);        // 第4显示区的起始地址
Datawrite(0x00);        // 第4显示区的起始地址

Cmdwrite(HdotScr); 	//0x5A 设置HdotScr参数       1个参数
Datawrite(0x00); 	// 以点为单位的显示画面的水平位移量

Cmdwrite(Ovlay); 	//0x5B  设置Ovlay参数       1个参数
Datawrite(0x1d); 	// 显示一,三区为图形属性 三重合成显示 合成方式为逻辑异或

LcdClear();             //清显示RAM 
//LcdClear_1();             //清显示RAM 
//LcdClear_2();             //清显示RAM 
//LcdClear_3();             //清显示RAM 

Cmdwrite(DispOn); 	//0x59  设置DispOn参数  开显示    1个参数
Datawrite(0x54); 	// 显示设置:一,二,三,四区开显示,关闪烁  光标不显示
}     
     
//===============================================



//显示图片函数
void PutBMP(unsigned char *puts)
{
unsigned char i,j;
unsigned int Y=0;
WriteCommand(0xC5);
for(i=0;i<240;i++)
{
for(j=0;j<40;j++)
{
WriteData(puts[Y]);
Y++;
}
}
}


//===============================================
//===============================================
//显示单个字符函数
void PutChar(unsigned char x,unsigned char y,unsigned char CharByte)
{
WriteCommand(mWrite);//数据写入指令 change to GB/ASCII mode
WriteData(CharByte);
}
//===============================================
//显示字符串函数
void PutStr(unsigned char x,unsigned char y,unsigned char *ptr)
{
WriteCommand(mWrite);//change to GB/ASCII mode
while(*ptr != '\0')
{
WriteData(*ptr);
++ptr;
}
}
*/
//===============================================

/*
//在某位置显示数字函数
void PutBCD(unsigned char x,unsigned char y,unsigned char var)
{
WriteCommand(mWrite);//写数据指令

WriteData(ASCIITable[var / 10]);
var = var%10;
WriteData(ASCIITable[var]);
}
*/
//===============================================
//汉字显示相关功能演示
 /*
x: 列
y: 行
m: 每个字符的扫描线行数 8*16的字符和16*16的汉字取16
n: 字符高度
*p:  字符地址

*/
/*
volatile void CCTW(unsigned int x,unsigned char y,unsigned char m,unsigned char n,unsigned char *p)
{
unsigned char ap=0x28,i,j,k,tt=0,uu=0,rr=0,ee=0,ff=0,gg=0; //ap 修改 P7, 行字符个数 
unsigned int l;

tt = x%8;
x=x/8;
l = y*ap + x+0x0000;     //      1区为0x0000,二区为0x2580,三区为0x4b00
x = (unsigned char)(l&0x00ff);
y = (unsigned char)((l&0xff00)>>8);


//WC_ADD=0x4c; //设置光标“右”移动方式 
WriteCommand(CsrDirR);

//WC_ADD=0x4f; //设置光标“下”移动方式


for(i=0;i< n;i++)
{
//WC_ADD = 0x46; // 光标指针设置 
WriteCommand(CsrW);

//WD_ADD = x;// 光标地址16位        //低
WriteData(x);
//WD_ADD = y;                          //高
WriteData(y);


if(tt==0)
{
//WC_ADD = 0x42; // 连续写入数据
WriteCommand(mWrite);


for (j=0;j<m/8;j++)
{
//WD_ADD = *p;
WriteData(*p);
p++ ;
}
} // 0 1 2 3 //

                    //以下改为列数x不是8的倍数就不显示
else { // 0---7 8---16 17---24 25---32//

for(j=0;j<m/8;j++)
{

//LcdCmdPort=0x43;// 读数据 //
WriteCommand(mRead);
uu=ReadCommand();
rr=ReadCommand();
//uu=ReadCommand(mRead);
//rr=uu;


//-----------------------------------------------------//
gg=*p; //处理数据//
p++;
k=uu>>(8-tt);
k=k<<(8-tt); // 高位
ee=k;
k=gg>>tt; // 移高位作为低位
ee=ee|k;
//-----------//
k=rr<<tt;
k=k>>tt; // 低位
ff=k;
k=gg<<(8-tt);
ff=ff|k;
//--------------------------------------------------------------//

//WC_ADD=0x4d;//改变光标“左”移动方式
WriteCommand(CsrDirL);

//LcdCmdPort=0x43;
//k=LcdCmdPort;
//k=LcdCmdPort;
WriteCommand(mRead);
k=ReadCommand();
k=ReadCommand();

//k=ReadCommand(mRead);




//WC_ADD=0x4c;//非复光标“右”移动方式
WriteCommand(CsrDirR);


//WC_ADD = 0x42; // 送数据两个
WriteCommand(mWrite);


//WD_ADD =ee;
WriteData(ee);
//WD_ADD =ff;
WriteData(ff);

//本送一个数据，前面送了两个，需要返回一个

//WC_ADD=0x4d; //改变光标“左”移动方式
WriteCommand(CsrDirL);


//LcdCmdPort=0x43;
//k=LcdCmdPort;
//k=LcdCmdPort;
WriteCommand(mRead);
k=ReadCommand();
k=ReadCommand();
//k=ReadCommand(mRead);


//WC_ADD=0x4c;//非复光标“右”移动方式
WriteCommand(CsrDirR);

//RD_ADD=0x43;
//k=RD_ADD;
WriteCommand(mRead);

k=ReadCommand();

}
}


l=(ap+x+(y<<8));
x=(unsigned char)(l&0x00ff);
y=(unsigned char)((l&0xff00)>>8);
}
}
*/

//-----------------------------------------//
//    以下为画点子函数
//    x,y为坐标,c为1画黑点 ,c为0画白点
//
//-----------------------------------------//
/*
void dot (U16 x, U16 y,U8 c)
{

unsigned char ap=0x28,tt=0,uu=0,gg=0,k=0; //ap 修改 P7, 行字符个数 
unsigned int l=0;

tt = x%8;
x = x/8;
//l = y*ap + x+0x0000;        // 1区为0x0000,二区为0x2580,三区为0x4b00
if(Currsys.LCD_Layer==1)
	l = y*ap + x+0x0000;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==2)
	l = y*ap + x+0x2580;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==3)
	l = y*ap + x+0x4b00;        // 1区为0x0000,二区为0x2580,三区为0x4b00

x = (unsigned char)(l&0x00ff);
y = (unsigned char)((l&0xff00)>>8);

//WC_ADD = 0x4c;
WriteCommand(CsrDirR);

//WC_ADD = 0x46; //光标指针设置 
WriteCommand(CsrW);

//WD_ADD = x; //光标地址16位 
WriteData(x);
//WD_ADD = y;
WriteData(y);
//RD_ADD=0x43; // 读数据 
//uu=RD_ADD;
//uu=ReadCommand(mRead);
WriteCommand(mRead);
uu=ReadCommand();


if(c)
{
gg = 1;
gg =gg<<(7-tt);
uu=uu|gg;
}
else {
gg = 1;
gg =gg<<(7-tt);
gg = ~gg;
uu=uu&gg;
}

//WC_ADD=0x4d;
WriteCommand(CsrDirL);

//RD_ADD=0x43;
//k=RD_ADD;
WriteCommand(mRead);
k=ReadCommand();


//WC_ADD = 0x4c; //恢复光标“右”移动方式 
WriteCommand(CsrDirR);

//WC_ADD = 0x42; // 送数据两个 
WriteCommand(mWrite);

//WD_ADD = uu;
WriteData(uu);
}
*/


//----------------------------------------------//
/*
void Set_Add1(char x, char y)			//设置操作坐标地址
{
	U16  csrw;
	SetLayer(1);
	LCD_Y=y;
	LCD_X=x;
	csrw=((U16)y<<6)*5+x-321;
	
	Cmdwrite(CsrW);	
	Datawrite((char)csrw);
	Datawrite((char)(csrw>>8));
}

void Set_Add2(char x, char y)
{
	U16  csrw;
	SetLayer(2);
	LCD_X=x;
	LCD_Y=y;
 	csrw=((U16)y<<6)*5+x-321+9600;	//9600=240*40
 	
 	Cmdwrite(CsrW);	
	Datawrite((char)csrw);
	Datawrite((char)(csrw>>8));
}

void Set_Add3(char x,char y)
{
	U16  csrw;
	SetLayer(3);
	LCD_X=x;
	LCD_Y=y;
	csrw=((U16)y<<6)*5+x-321+0x4b00;	//4b00=9600+9600
 	
 	Cmdwrite(CsrW);	
	Datawrite((char)csrw);
	Datawrite((char)(csrw>>8));
}
*/


/*
////////////////////////////////////////////////////////////////
		//下面为我自己写的显示函数//
///////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//SED1335画线的程序（与硬件无关），没有什么限制，
//如果你不需要清除，可去掉 bool clr 参数，当然画点不要这个参数。 
//////////////////////////////////////////////////////
void line(U16 x1, U16 y1, U16 x2, U16 y2, U8 clr) 
{U16 i, xsub, ysub; 
 U8 dir; 

    if(y1 > y2) 
    { 
        if(x2 > x1) 
        { 
            dir = TRUE; 
        } 
        else 
        { 
            dir = FALSE; 
            i = x2; 
            x2 = x1; 
            x1 = i; 
        } 
        i = y2; 
        y2 = y1; 
        y1 = i; 
    } 
    else 
    { 
        dir = FALSE; 
        if(x1 > x2) 
        { 
            dir = TRUE; 
            i = x2; 
            x2 = x1; 
            x1 = i; 
        } 
    } 

    xsub = x2 - x1 + 1; 
    ysub = y2 - y1 + 1; 
    x2 = x1; 
    if(!dir) 
    { 
        y2 = y1; 
    } 
         
    for(y1 = 1; y1 <= ysub; y1++) 
    { 
        i = (U16)(y1 * xsub) / ysub + x1; 
        do 
        { 
            dot(x2, y2, clr); 
            if(x2 < i) 
            { 
                ++x2; 
            } 
        }while(x2 < i); 

        if(dir) 
        { 
            --y2; 
        } 
        else 
        { 
            ++y2; 
        } 
    } 
} 

///////////////////////////////////////////////////////////////


void draw_circle(int a,int b,int R)  //画圆函数
{
int xdot,ydot;

float tmp,i=0;

        while(i<3.15/2){
                        tmp=R*sin(i); if(tmp-(int)tmp>0.7) ++tmp;
                        ydot=(int)tmp;
                        tmp=R*cos(i); if(tmp-(int)tmp>0.7) ++tmp;
                        xdot=(int)tmp;
                        dot(a+xdot,b+ydot,1);
                        if(b-ydot>0) dot(a+xdot,b-ydot,1);
                        if(a-xdot>0) dot(a-xdot,b+ydot,1);
                        if(a-xdot>0 && b-ydot>0) dot(a-xdot,b-ydot,1);
                        i+=1.57/(1+R*2);
        }
}


///////////////////////////////////////////////////////////////


void Write_16Char(unsigned char str)     //写8*16字符
{
unsigned int i,pPt;

	pPt=(str-0x20)*16; 		
		
	Cmdwrite(CsrDirD);	
	Cmdwrite(mWrite);
	for(i=0;i<16;i++)
	{
	Datawrite(chardot_16[pPt+i]);
	}			        
	
	LCD_X++;
	
	if(LCD_X>40)
		{
		LCD_X=1;
	 	LCD_Y+=2;
	 	
		if(LCD_Y>(240-16))
		 LCD_Y=1;		
		 }

	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
}

///////////////////////////////////////////////////////////////

void Write_32Char(unsigned char str)     //写16*32字符
{
unsigned int i,pPt;

	pPt=(str-0x20)*64; 		
		
	Cmdwrite(CsrDirD);	
	Cmdwrite(mWrite);

    if(LCD_X>39)
    	{
    	LCD_X=39;
    	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
   	 }
	 
	Cmdwrite(CsrDirD); 
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)	{Datawrite(chardot_32[pPt+i*2]);}
	
	LCD_X++;	
	
	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
	
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)	{Datawrite(chardot_32[pPt+i*2+1]);}	
	
	LCD_X++;	
	
	if(LCD_X>40)
		{
		LCD_X=1;
	 	LCD_Y+=4;
	 	
		if(LCD_Y>(240-32))
		 LCD_Y=1;		
		 }

	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
}



void Write_16HZ(unsigned char hz0,unsigned char hz1)  //写16*16汉字
{
long offset;
unsigned int i;

    if(hz0>0xf7) return;
	//if(hz0>=0xb0) hz0-=0xb0;
	if(hz0>=0xa1) hz0-=0xa1;//字库中增加特殊符号
	
    hz1-=0xa1;
	offset=hz0*94+hz1;
	offset=32*offset; 
	       
    if(LCD_X>39)
    	{
    	LCD_X=39;
    	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
   	 }
	 
	Cmdwrite(CsrDirD); 
	Cmdwrite(mWrite);
	for(i=0;i<16;i++)	{Datawrite(hzdot_16[offset+i*2]);}
	
	LCD_X++;	
	
	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
	
	Cmdwrite(mWrite);
	for(i=0;i<16;i++)	{Datawrite(hzdot_16[offset+i*2+1]);}	
	
	LCD_X++;	
	
	if(LCD_X>39)
		{
		LCD_X=1;
	 	LCD_Y+=2;
	 	
		if(LCD_Y>(240-16))
		 LCD_Y=1;		
		 }

	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);

}


void Write_32HZ(unsigned char hz0,unsigned char hz1)  //写16*16汉字
{
long offset;
unsigned int i;

    if(hz0>0xf7) return;
	//if(hz0>=0xb0) hz0-=0xb0;
	if(hz0>=0xa1) hz0-=0xa1;//字库中增加特殊符号
    hz1-=0xa1;
	offset=hz0*94+hz1;
	offset=128*offset; 
	       
    if(LCD_X>37)
    	{
    	LCD_X=37;
    	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
   	 }
	 
	Cmdwrite(CsrDirD); 
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)	{Datawrite(hzdot_32[offset+i*4]);}
	
	LCD_X++;	
	
	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
	
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)	{Datawrite(hzdot_32[offset+i*4+1]);}	
	
		LCD_X++;	
	
	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
	
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)	{Datawrite(hzdot_32[offset+i*4+2]);}
	
	
		LCD_X++;	
	
	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);
	
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)	{Datawrite(hzdot_32[offset+i*4+3]);}
	
	LCD_X++;	
	
	if(LCD_X>37)
		{
		LCD_X=1;
	 	LCD_Y+=4;
	 	
		if(LCD_Y>(240-32))
		 LCD_Y=1;		
		 }

	if(Currsys.LCD_Layer==1)
		Set_Add1(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(LCD_X,LCD_Y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(LCD_X,LCD_Y);

}


void Write_16StringChar(char *str)	//自己的显示字符串
{
	while(1)
	{
	    if(*str=='\0')break;
		Write_16Char(*str++);
	}
}


void Write_32StringChar(char *str)	//自己的显示字符串
{
	while(1)
	{
	    if(*str=='\0')break;
		Write_32Char(*str++);
	}
}


void Write_16String( char *strhz)  //自己的显示汉字及字符串
{
unsigned char hz[2];
    while(1)
    {
        hz[0]=*strhz++;
        if(hz[0]=='\0')break;        
        hz[1]=*strhz;
      //  if(hz[1]=='\0')break;
        if((hz[0]>0xa0)&&(hz[1]>0xa0))
        	{Write_16HZ(hz[0],hz[1]);
        	//x+=2;	
        	strhz++;	}
       else if ((hz[0]>=0x20)&&(hz[0]<=0x7E)) 	
       		{Write_16Char(hz[0]);  }
       		
        	
	}
}


void Write_32String( char *strhz)  //自己的显示汉字及字符串
{
unsigned char hz[2];
    while(1)
    {
        hz[0]=*strhz++;
        if(hz[0]=='\0')break;        
        hz[1]=*strhz;
      //  if(hz[1]=='\0')break;
        if((hz[0]>0xa0)&&(hz[1]>0xa0))
        	{Write_32HZ(hz[0],hz[1]);
        	//x+=2;	
        	strhz++;	}
       else if ((hz[0]>=0x20)&&(hz[0]<=0x7E)) 	
       		{Write_32Char(hz[0]);  }
       		
        	
	}
}


*/

/************************************************************
*															*
*	在定点区域显示字符串											*
*															*
*************************************************************/

/*
void Write_16StringAt(char x, char y,char *c)
{
	if(Currsys.LCD_Layer==1)
		Set_Add1(x,y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(x,y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(x,y);
	
	Write_16String(c);
}
*/

////////////////////////////////////////////////////////////////
/*
void Graph_locate(unsigned int row, unsigned char column)
  // 图形模式下屏幕锁定光标 
  // row-行(以像素为单位)  column-列(以字节为单位)
{
  unsigned int address;
  unsigned char high_bit,low_bit;

  //address = ((row - 1) * 40) + (column - 1);
  
 if(Currsys.LCD_Layer==1)
	address = ((row - 1) * 40) + (column - 1)+0x0000;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==2)
	address = ((row - 1) * 40) + (column - 1)+0x2580;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==3)
	address = ((row - 1) * 40) + (column - 1)+0x4b00;        // 1区为0x0000,二区为0x2580,三区为0x4b00 
  
  
  high_bit = (address >> 8) & 0xff;
  low_bit = address & 0xff;
  
  //Locate_cursor(high_bit, low_bit);  
  Cmdwrite(CsrW);  // CSRW 
 Datawrite(low_bit);
 Datawrite(high_bit);
}
*/

/*
////////////////////////////////////////////////////////////////
void Empty_screen(unsigned char mode)
{
  // 艺术化清显示屏 
  // 1-上向下方式   2-下向上方式  3-左往右方式  4-右往左方式 
  unsigned char i,j,row,column;
  U16 k;
  
  Empty_mode++;		//清屏模式自加
  
  SetLayer(1);  //强制设置为第1区

  //LCD_order(0x4c);
  Cmdwrite(CsrDirR);
  
  if(mode==1)
  {
    row = 1;
    for(i=0;i<240;i++)
    {
      column = 1;
      Graph_locate(row,column);     
      //LCD_order(0x42);
      Cmdwrite(0x42);
      for(j=0;j<40;j++) Datawrite(0x00);
      for(k=0;k<21250;k++);
      row++;
    }
  }else if(mode==2)
  {
    row = 240;
    for(i=240;i>0;i--)
    {
      column = 1;
      Graph_locate(row,column);
      Cmdwrite(0x42);
      for(j=0;j<40;j++) Datawrite(0x00);
      for(k=0;k<21250;k++);
      row--;
    }
  }else if(mode==3)
  {
    for(column=1;column<=40;column++)
    {
      row = 1;
      for(i=0;i<240;i++)
      {
        Graph_locate(row,column);
        Cmdwrite(0x42);
        Datawrite(0x00);
        for(k=0;k<500;k++);
        row++;
      }
    }
  }else if(mode==4)
  {
    for(column=40;column>=1;column--)
    {
      row = 1;
      for(i=0;i<240;i++)
      {
        Graph_locate(row,column);
        Cmdwrite(0x42);
        Datawrite(0x00);
        for(k=0;k<500;k++);
        row++;
      }
    }
  }
}

////////////////////////////////////////////////////////////////
void Move_scroll(unsigned char move_mode)
{
  // 滚屏效果 
  // move_mode： 1-上滚屏 2-下滚屏 3-左滚屏 4-右滚屏 
  unsigned int address;
  unsigned char high_bit,low_bit,i,j;
   U32 k;

 // address = 0x0000;
  
   if(Currsys.LCD_Layer==1)
	address = 0x0000;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==2)
	address = 0x2580;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==3)
	address = 0x4b00;        // 1区为0x0000,二区为0x2580,三区为0x4b00 
  
  
  if((move_mode==1)||(move_mode==2))
  {
    for(i=0;i<240;i++)
    {
      high_bit = (address >> 8) & 0xff;
      low_bit = address & 0xff;
      Cmdwrite(0x44);
      Datawrite(low_bit);
      Datawrite(high_bit);
     // delay0();
       for(k=0;k<25500;k++);
      if(move_mode==1)
      {
        address = address + 40;
      }else
      {
        address = address - 40;
      }
    }
  }else if((move_mode==3)||(move_mode==4))
  {
    if(move_mode==3)
    {
      for(i=0;i<40;i++)
      {
        for(j=0;j<8;j++)
        {
          Cmdwrite(0x5a);
          Datawrite(j);
        }
        high_bit = (address >> 8) & 0xff;
        low_bit = address & 0xff;
        Cmdwrite(0x44);
        Datawrite(low_bit);
        Datawrite(high_bit);
        Cmdwrite(0x5a);
        Datawrite(0x00);
        //delay4();
         for(k=0;k<100000;k++);
        address = address + 1;
      }
    }else
    {
      for(i=0;i<40;i++)
      {
        for(j=7;j>0;j--)
        {
          Cmdwrite(0x5a);
          Datawrite(j);
        }
        high_bit = (address >> 8) & 0xff;
        low_bit = address & 0xff;
        Cmdwrite(0x44);
        Datawrite(low_bit);
        Datawrite(high_bit);
        Cmdwrite(0x5a);
        Datawrite(0x07);
        //delay4();
         for(k=0;k<100000;k++);
        address = address - 1;
      }
    }
  }
  Cmdwrite(0x44);
  Datawrite(0x00);
  Datawrite(0x00);
}
*/

////////////////////////////////////////////////////////////////
/*
static char  *chaxunZM(char ptr)  // 查询字母16*8
{	
	char i=0;
	if(ptr>0x50)
	{
		i = 38;
	}
	for(;i<80;i++)
	{
		if(english[i].value==ptr )
			return((char*)&english[i].dat);		 
  	}
	  	  	return(0);
}
static char  *chaxunHZ(U16 ptr)	   // 查询汉字16*16
{			
	char i=0;
	
	//以下几行为新加的，因ADS编译后汉字的内码高8位和低8位倒置	
	U16 ptr_1=ptr;		
	ptr=(ptr<<8)|(ptr_1>>8);
	//
	
	if(ptr>0xbeb3)
	{
		i=57;
	}
	for(;i<120;i++)
	{
		if(chinese[i].value==ptr )
			return((char*)&chinese[i].dat);		 
  	}
  	  	  	return(0);
}
static char  *chaxunZM32(U8 ptr)	// 查询字母32*16
{
	char i=0;
	for(;i<15;i++)
	{
		if(english1[i].value==ptr )
			return((char*)&english1[i].dat);		 
  	}
  	  	  	return(0);
}
static char  *chaxunHZ32(U16 ptr)	  // 查询汉字32*32
{
	char i=0;
	
	//以下几行为新加的，因ADS编译后汉字的内码高8位和低8位倒置	
	U16 ptr_1=ptr;		
	ptr=(ptr<<8)|(ptr_1>>8);
	//
	
	for(;i<5;i++)
	{
		if(chinese1[i].value==ptr )
			return((char*)&chinese1[i].dat);		 
  	}
  	  	  	return(0);
}



static void	Disp16Font(char  *c)//=====
{
	char *p;
	char i;
	
	Cmdwrite(CsrDirD);
	while(*c != 0)
	{
		if(*c>0x80)
			{
			//(*m)=(*(U16 *)c)<<8;
			//(*(U16 *)c)=((*(U16 *)c)>>8)&(*m);
            		//p = chaxunHZ((*(U16 *)c)<<8);
            p = chaxunHZ(*(U16 *)c);
            
            if (p==0x00) {c+=2; continue;  } //字库中没有的字，不显示
           
            }
        else
		{	p = chaxunZM(*c);
			 if (p==0x00) {c++; continue;  } //字库中没有的字，不显示		
		}
		
		Cmdwrite(mWrite);
		for(i=0;i<16;i++)
		{
			Datawrite(*p++);
		}
		if(*c<0x80)
		{
			c++;
			//Set_Add1(LCD_X+1,LCD_Y);
			if(Currsys.LCD_Layer==1)
				Set_Add1(LCD_X+1,LCD_Y);
			else if(Currsys.LCD_Layer==2)
				Set_Add2(LCD_X+1,LCD_Y);
			else if(Currsys.LCD_Layer==3)
				Set_Add3(LCD_X+1,LCD_Y);
			
			continue;
		}
		//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
		
		
		Cmdwrite(mWrite);
		for(i=0;i<16;i++)
		{
			Datawrite(*p++);
		}
		c += 2;
		//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
	}
}



static void	Disp32Font(char  *c)//=====
{
	char *p;
	char i;
	
	Cmdwrite(CsrDirD);
	while(*c != 0)
	{
		if(*c>0x80)
			p = chaxunHZ32(*(U16 *)c);
			if (p==0x00) {c+=2; continue;  } //字库中没有的字，不显示
		
        	else
			{	
			p = chaxunZM32(*c);
			 if (p==0x00) {c++; continue;  } //字库中没有的字，不显示		
			}
		
		Cmdwrite(mWrite);
		for(i=0;i<32;i++)
		{
			Datawrite(*p++);
		}
		//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
		
		Cmdwrite(mWrite);
		for(i=0;i<32;i++)
		{
			Datawrite(*p++);
		}
		if(*c<0x80)
		{
			c++;
			//Set_Add1(LCD_X+1,LCD_Y);
			if(Currsys.LCD_Layer==1)
				Set_Add1(LCD_X+1,LCD_Y);
			else if(Currsys.LCD_Layer==2)
				Set_Add2(LCD_X+1,LCD_Y);
			else if(Currsys.LCD_Layer==3)
				Set_Add3(LCD_X+1,LCD_Y);
			
			continue;
		}
		//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
		
		Cmdwrite(mWrite);
		for(i=0;i<32;i++)
		{
			Datawrite(*p++);
		}
		//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
		
		Cmdwrite(mWrite);
		for(i=0;i<32;i++)
		{
			Datawrite(*p++);
		}
		c += 2;
		//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
	}
}


void Disp_String( char *c)		//显示字符串
{
	if(Currsys.Font == FONT_16)
		Disp16Font(c);
	//else if(Currsys.Font == FONT_24)
		//Disp24Font(c);
	else if(Currsys.Font == FONT_32)
		Disp32Font(c);
}

*/

/************************************************************
*															*
*	在定点区域显示											*
*															*
*************************************************************/
/*
void DispStringAt(char x, char y,char *c)
{
	//assert(c!=NULL);
	//SetAdd(x,y);
	if(Currsys.LCD_Layer==1)
		Set_Add1(x,y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(x,y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(x,y);
	
	Disp_String(c);
}



void Disp_16Char(char c)			//显示一个8*16字符
{
	char *p;
	char i;	
	Cmdwrite(CsrDirD);
    	p = chaxunZM(c);
    	
    	 if (p==0x00)  return ;   //字库中没有的字，不显示	
    	
	Cmdwrite(mWrite);
	for(i=0;i<16;i++)
	{
		Datawrite(*p++);
	}
	//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
}


void Disp_32Char(char c)			//显示一个16*32字符
{
	char *p;
	char i;	
	Cmdwrite(CsrDirD);
    	p = chaxunZM32(c);
    	
    	 if (p==0x00)  return ;   //字库中没有的字，不显示	
    	
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)
	{
		Datawrite(*p++);
	}
	//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
	
	Cmdwrite(mWrite);
	for(i=0;i<32;i++)
	{
		Datawrite(*p++);
	}
	//Set_Add1(LCD_X+1,LCD_Y);
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
}


///////////////////////////////////////////////////////////////
char *F2A(float d, char  * str)	  //浮点数转换成字符串
{
	char str1[11]={0,'0',0,0,0,0,0,0,0,0,0};
	U8 j=1,k;
	U16 i;
	if(d>=0)
		*str = '+';
	else
		*str = '-';
	i = (U16)fabs(d);  			//浮点数的整数部分
	while(i>0)
	{
		str1[j++] = i%10+'0';
		i/=10;
	}
	if(j==1)	j++;
	for(k=0;k<j;k++)
		str[k+1] = str1[j-k-1];	
	str[j++] = '.';
	d=fabs(d)-(U16)fabs(d);		//小数部分
	for(;j<(Float_NUM+1);j++)
	{
		d *= 10;
		str[j] = (U16)d+'0';
		d -= (U16)d;
	}
	str[j] = '\0';
	return str;
}


void Disp_16Float(float value, char numb)  //显示8*16浮点数
{
	char k;
	char str[Float_NUM];
	F2A(value,str);
	for(k=0;k<=numb;k++)
	{
		switch(str[k])
		{
			case '0': 	Write_16Char('0');		break;
			case '1': 	Write_16Char('1');		break;
			case '2': 	Write_16Char('2');		break;
			case '3': 	Write_16Char('3');		break;
			case '4': 	Write_16Char('4');		break;
			case '5': 	Write_16Char('5');		break;
			case '6': 	Write_16Char('6');		break;
			case '7': 	Write_16Char('7');		break;
			case '8': 	Write_16Char('8');		break;
			case '9':	Write_16Char('9');		break;
			case '.':	Write_16Char('.');		break;
			case '+':	Write_16Char(' ');		break;
			case '-':	Write_16Char('-');		break;
		}
	}
}


void Disp_32Float(float value, char numb)  //显示16*32浮点数
{
	char k;
	char str[Float_NUM];
	F2A(value,str);
	for(k=0;k<=numb;k++)
	{
		switch(str[k])
		{
			case '0': 	Disp_32Char('0');		break;
			case '1': 	Disp_32Char('1');		break;
			case '2': 	Disp_32Char('2');		break;
			case '3': 	Disp_32Char('3');		break;
			case '4': 	Disp_32Char('4');		break;
			case '5': 	Disp_32Char('5');		break;
			case '6': 	Disp_32Char('6');		break;
			case '7': 	Disp_32Char('7');		break;
			case '8': 	Disp_32Char('8');		break;
			case '9':	Disp_32Char('9');		break;
			case '.':	Disp_32Char('.');		break;
			case '+':	Disp_32Char(' ');		break;
			case '-':	Disp_32Char('-');		break;
		}
	}
}

*/
/*
void Clear_Rect(char wide,char high)		//某一区域清0
{
	char i;
	//LCD_write_char1(lcm_cmd,0x4f);
	Cmdwrite(CsrDirD);
	for(;wide>0;wide--)
	{
		//LCD_write_char1(lcm_cmd,0x42);
		Cmdwrite(mWrite);
		for(i=0;i<(high<<3);i++)
		{
			//LCD_write_char1(lcm_data,0);
			Datawrite(0);
		}
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
	}
}


void Fill_Rect(char wide,char high)		//反色显示
{
	char i;
	
	Cmdwrite(CsrDirD);
	for(;wide>0;wide--)
	{		
		Cmdwrite(mWrite);
		for(i=0;i<(high<<3);i++)
		{		
			Datawrite(0xff);
		}
		
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
	}
	LCD_Adr=9600;  //给LCD_Adr送显示区以外的数，下次调用GUI时重新设置X Y坐标
}


void Disp_Image(char *p, char x, char y)			 //显示一幅图片
{
	char i;	
	//COMADR(0x4f);
	Cmdwrite(CsrDirD);
	
	for(;x>0;x--)
	{		
		//COMADR(0x42);
		Cmdwrite(mWrite);
		
		for(i=0;i<y;i++)
		{			
			//DATADR(*p++);
			Datawrite(*p++);
		}
		if(Currsys.LCD_Layer==1)
			Set_Add1(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==2)
			Set_Add2(LCD_X+1,LCD_Y);
		else if(Currsys.LCD_Layer==3)
			Set_Add3(LCD_X+1,LCD_Y);
	}
}


void dpara_llel(char x,char y,char wide)    //横线
{
	if(Currsys.LCD_Layer==1)
		Set_Add1(x,y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(x,y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(x,y);
	//LCD_write_char1(lcm_cmd,0x4c);
	Cmdwrite(CsrDirR);     //右
	//LCD_write_char1(lcm_cmd,0x42);
	Cmdwrite(mWrite);
	while(wide--)
		//LCD_write_char1(lcm_data,0xff);
		Datawrite(0xff);
}



void d_perpend(char x,char y,char wide)	 //竖线
{
	if(Currsys.LCD_Layer==1)
		Set_Add1(x,y);
	else if(Currsys.LCD_Layer==2)
		Set_Add2(x,y);
	else if(Currsys.LCD_Layer==3)
		Set_Add3(x,y);
	//LCD_write_char1(lcm_cmd,0x4f);
	Cmdwrite(CsrDirD);
	//LCD_write_char1(lcm_cmd,0x42);
	Cmdwrite(mWrite);
	//wide=wide<<3;//释放该行，则线长为wide*8
	wide--;
	while(wide--)
		//LCD_write_char1(lcm_data,0x80);
		Datawrite(0x80);
}
*/

/*
void frame(void)								//大方框
{	
GUI_DrawHLine(0,0,319);//横线
GUI_DrawHLine(1,0,319);//横线
GUI_DrawHLine(238,0,319);//横线
GUI_DrawHLine(239,0,319);//横线

GUI_DrawVLine(0,    0,239);//竖线
GUI_DrawVLine(1,    0,239);//竖线
GUI_DrawVLine(318,    0,239);//竖线
GUI_DrawVLine(319,    0,239);//竖线	
}*/

/*
void frame(void)								//大方框
{	
GUI_DrawHLine(1,1,638);//横线
GUI_DrawHLine(2,1,638);//横线
GUI_DrawHLine(477,1,638);//横线
GUI_DrawHLine(478,1,638);//横线

GUI_DrawVLine(1,    1,478);//竖线
GUI_DrawVLine(2,    1,478);//竖线
GUI_DrawVLine(637,    1,478);//竖线
GUI_DrawVLine(638,    1,478);//竖线	
}


void frame_sm(void)								//小方框
{
 GUI_DrawHLine(67,7,632);//横线
 GUI_DrawHLine(400,7,632);//横线
 GUI_DrawVLine(7,67,400);//竖线
 GUI_DrawVLine(632,67,400);//竖线
}


void frame_sm1(void)								//主从机自校以及GPS定位用的小方框
{
 GUI_DrawHLine(37,5,314);//横线
 GUI_DrawHLine(197,5,314);//横线
 GUI_DrawVLine(5,37,197);//竖线
 GUI_DrawVLine(314,37,197);//竖线
}



////////////////////////////////////////////////
// 显示区向上滚动出可视区
void RollUp( void )
 {
U16        address=0;
U8         jj = 240;                                       

//        WriteCommand( DispOn );                        // 写入指令DISP ON/OFF代码，后续参数：
//        WriteData( 0x44 );                                // 00 00 01 00显示1区开显示,其余层关闭

 if(Currsys.LCD_Layer==1)
	address = 0x0000;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==2)
	address = 0x2580;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==3)
	address = 0x4b00;        // 1区为0x0000,二区为0x2580,三区为0x4b00 
  

        while(jj--) {

                address += 40;

                Cmdwrite( Scroll );                // 设定显示区域起始地址
                Datawrite( (U8)(address & 0xff) );                        // 写入参数
                Datawrite( (U8)(address /256) );                        // 写入参数

                Delay(100);                                // 调延时子程序
        }        	
        
      //  Cmdwrite( DispOff );
        Disp_Off(); 
        
        Cmdwrite( Scroll );                // 设定显示区域起始地址
        Datawrite( 0 );                        // 写入参数
        Datawrite( 0 );                        // 写入参数
	Delay(10);
}

////////////////////////////////////////////////
// 显示区向下滚动
void RollDown( void ) {

U8         jj = 240;                                        // 演示32次
U16        address=40*240;

//        WriteCommand( DispOn );                        // 写入指令DISP ON/OFF代码，后续参数：
//        WriteData( 0x44 );                                // 00 00 01 00显示1区开显示,其余层关闭
     //  picture_disp1( 20,15,120,23,0,0) ;//picture_disp1( 0,23) ;
     
     
      if(Currsys.LCD_Layer==1)
	address += 0x0000;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==2)
	address += 0x2580;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==3)
	address += 0x4b00;        // 1区为0x0000,二区为0x2580,三区为0x4b00 

                Cmdwrite( Scroll );                // 设定显示区域起始地址
                Datawrite( (U8)(address & 0xff) );                        // 写入参数
                Datawrite( (U8)(address /256) );                        // 写入参数
                
     Disp_On(); 
           
  
        while(jj--) {
                address -= 40;
                Cmdwrite( Scroll );                // 设定显示区域起始地址
                Datawrite( (U8)(address & 0xff) );                        // 写入参数
                Datawrite( (U8)(address /256) );                        // 写入参数
                 Delay(100);                                         // 调延时子程序
        }
        Cmdwrite( Scroll );                // 设定显示区域起始地址
        Datawrite( 0 );                        // 写入参数
        Datawrite( 0 );                        // 写入参数
        Delay(10); 
}



////////////////////////////////////////////////
// 第一显示区向右滚动
void Rollright( void ) {

        U8 tempI,jj=25;
        U16  address=24;
//        return;
//        WriteCommand( DispOn );                        // 写入指令DISP ON/OFF代码，后续参数：
//        WriteData( 0x44 );                                // 00 00 01 00显示1区开显示,其余层关闭

      if(Currsys.LCD_Layer==1)
	address += 0x0000;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==2)
	address += 0x2580;        // 1区为0x0000,二区为0x2580,三区为0x4b00
else if(Currsys.LCD_Layer==3)
	address += 0x4b00;        // 1区为0x0000,二区为0x2580,三区为0x4b00 
  

        while(jj--) {
                tempI = 8;
                Cmdwrite( Scroll );                                // 显示区域（起点）设置
                Datawrite( (U8)(address & 0xff) );                        // 写入参数
                Datawrite( (U8)(address /256) );                        // 写入参数
                while( tempI-- ) {
                        Cmdwrite( HdotScr );                // 写入HDOT SET 指令
                        Datawrite( tempI );                                // 写入参数
                        Delay(60);                                                // 调延时子程序
                }

                address--;
        }
}
*/

/*	
void dface(void)	 
{
SetLayer(1);
Disp_Off(); 
Cmdwrite( DispOff );
dface1();   	//显示logo1

RollDown();
Delay(DFACE_TM/2);
//RollUp();
Empty_screen(1);  //艺术化清显示屏(1-上向下方式   2-下向上方式  3-左往右方式  4-右往左方式)
GUI_Clear();
LcdClear(); //LCD清
Disp_On(); 

dface2();   	//显示logo2
//screen0();
RollDown();
Delay(DFACE_TM);
//Empty_screen(1);
RollUp();
LcdClear();             //清显示RAM
Disp_On();
}
*/	


/*
////////////////////////////////////////////////
//显示一行“PT2010型电压互感器二次压降无线测试仪”以及画方框
////////////////////////////////////////////////
void h2000(void)
{
SetLayer(1);
frame();
Set_Add1(3,2);
//Write_16String("PT2010型电压互感器二次压降无线测试仪");
GUI_DispString("PT2010型电压互感器二次压降无线测试仪");
Set_Add1(0,0);
}
*/

/*
////////////////////////////////////////////////
//主界面
////////////////////////////////////////////////

void mainface(void)
{

h2001();
frame_sm();

SetLayer(1);
Set_Add2(3,2);
Fill_Rect(36,2);
LcdClear_2(); //LCD清第2显示区

}
*/


