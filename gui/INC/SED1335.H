#ifndef __SED1335_H__
#define __SED1335_H__

extern void 	Cmdwrite(unsigned char cmdcode) ;
extern void 	Datawrite(unsigned char wrdata) ;
extern void 	LCD_Initial(void);

extern void 	LcdClear(void);				//清LCD全屏子函数
extern void 	LcdClear_1(void);				//清LCD屏第1显示区子函数
extern void 	LcdClear_2(void);				//清LCD屏第2显示区子函数
extern void 	LcdClear_3(void);				//清LCD屏第3显示区子函数
extern void 	PutBMP(unsigned char *puts);	//显示图片函数
extern void 	dot (U16 x, U16 y,U8 c);			//画点函数
extern void 	draw_circle(int a,int b,int R); 		//画圆函数

extern void 	Set_Add1(char x, char y);			//设置1区操作坐标地址
extern void 	Set_Add2(char x, char y);			//设置2区操作坐标地址
extern void 	Set_Add3(char x, char y);			//设置3区操作坐标地址

extern void 	frame(void);						//方框
extern void 	d_perpend(char x,char y,char wide);	 	//竖线
extern void 	Disp_16Char(char c);					//显示一个8*16字符
extern void 	Disp_32Char(char c);					//显示一个16*32字符
extern void 	Disp_String( char *c);					//显示字符串
extern void 	DispStringAt(char x, char y,char *c);		//在定点区域显示字符串
extern void 	Disp_16Float(float value, char numb);  	//显示8*16浮点数
extern void 	Disp_32Float(float value, char numb);  	//显示16*32浮点数

extern void 	Write_16StringChar(char *str);			//自己的显示字符串
extern void 	Write_16StringHZ( char *strhz);			//自己的显示汉字及字符串


extern void 	Write_16Char(unsigned char str);     				 //我自己的写8*16字符
extern void 	Write_16HZ(unsigned char hz0,unsigned char hz1);  //我自己的写16*16汉字

extern void 	GUI_DispString_GS(char *fmt,...);   //带格式的GUI_DispString显示字符串

extern void dface(void);		//开机界面
extern void mainface(void);	//主界面




//汉字显示相关功能演示
 /*
x: 列
y: 行
m: 每个字符的扫描线行数 8*16的字符和16*16的汉字取16
n: 字符高度
*p:  字符地址

*/

 extern void CCTW(unsigned int x,unsigned char y,unsigned char m,unsigned char n,unsigned char *p);


extern void Printstr(void) ;

extern void sed1335_read(char commandcode, unsigned char *parameter,unsigned int n);

extern void sed1335_write(unsigned char commandcode, unsigned char *parameter,unsigned char n);

extern void mDelay1_2uS(void );  // 至少延时1.2uS,根据单片机主频调整 



  

//void Beep_2(void);

#endif /*__SED1335_H__*/

