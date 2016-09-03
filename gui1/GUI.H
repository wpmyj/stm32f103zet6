#ifndef _GUI_H
#define _GUI_H



#define LCD_XSIZE  40
#define LCD_YSIZE  240



//显示模式
#define GUI_TEXTMODE_NORMAL      (0)
#define GUI_TEXTMODE_REVERSE     (1<<0)
#define GUI_TEXTMODE_UNDERLINE   (1<<1)
#define GUI_TEXTMODE_XOR         (1<<2)
//对齐方式
#define GUI_TA_LEFT              (0<<4)
#define GUI_TA_HCENTER           (1<<4)
#define GUI_TA_RIGHT             (2<<4)
#define GUI_JUST_TEXT            (1<<7)

//英文的两种字体
#define En_8x16      (0)
#define En_5x8       (1)

//字体宽度定义
#define En_8x16_XSIZE  1
#define En_8x16_YSIZE  16
#define En_5x8_XSIZE   2
#define En_5x8_YSIZE   8
//英文字体宽度定义

extern INT8U Char_XSIZE;
extern INT8U Char_YSIZE;


//中文字体宽度定义
#define Chinese_XSIZE  2
#define Chinese_YSIZE  16

extern void Display_Locate(INT8U DisplayData, INT8U x0, INT8U y0);

extern INT8U GUI_SetTextMode(INT8U TextMode);
extern void GUI_SetEnFont(INT8U EnFont);
extern void GUI_DispCharAt(INT8U c, INT8U x, INT8U y);
extern void GUI_Init(void);
extern void GUI_Clear(void);

extern void GUI_DispStringAt(INT8U _CONST_ *s,INT8U X,INT8U Y);
extern void GUI_DispDecAt(INT16U v, INT16U x, INT16U y, INT8U Len);
extern void GUI_DispHexAt(INT32U v, INT8U x, INT8U y, INT8U Len);
extern void GUI_Delay(INT16U Period);



#endif
