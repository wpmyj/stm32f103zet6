#ifndef __LCD_H
#define __LCD_H	 
#include "sys.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_fsmc.h"
#include "delay.h"

    #define RA8835P_CS(x)		P3_4 = x			
	#define RA8835P_RST(x)		P3_1 = x
	#define RA8835P_RS(x) 		P3_7 = x		
	#define RA8835P_WR(x)   	P3_6 = x				
	#define RA8835P_RD(x)   	P3_5 = x

/* 声明 float ny[12]；
   main	里面写入delay_init();
   				delay_init();
				NVIC_Configuration();
				FSMC_Init(); 总线初始化
				SED1335_INIT();
	while 里面写入num_disp(); 显示测量数据
				  clear_lcd_touchflag(); 触摸清标志
	测到数据后对ny[12]实时更新，对应相应通道
 */

//output
//#define CS PCout(2)	     //1
//#define DIN PCout(1) 	//0
//#define DCLK PCout(0)	//0
//#define RSTLCD PCout(5)
//#define NGCS2 PCout(6)
////input
//#define int1 PCin(3)
//#define DOUT PCin(4)

#define CS PEout(3)	     //1
#define DIN PEout(2) 	//0
#define DCLK PEout(0)	//0
#define RSTLCD PCout(5)
#define NGCS2 PCout(6)
//input
#define int1 PBin(12)
#define DOUT PBin(9)
extern float ny[13];

void LCD_Init(void);//初始化
void FSMC_Init(void);//初始化
void GPIO_INIT(void);
void delay(unsigned int delx);
void Initialize(void);
void LcdCommand(unsigned char num_1);
void LcdDataWrite(unsigned char num_2);
void screen1(void);
void screen2(void);
void clear1(void);
void clear2(void);
void clear3(void);
void pane(void);
void WriteCommand( unsigned char CommandByte );
void WriteData( unsigned dataW );
void chdisp(unsigned char x,unsigned char y,unsigned char *p,unsigned char z);
void SetCursor(unsigned char CursorHIGH,unsigned char CursorLOW);
void p_h(void);
void p_h_1(void);
void p_s(unsigned char j);
void dis_biao(void);
void frame(void);
void dis_frame(void);
unsigned char WRChar(unsigned char num);
void hzdisp1(unsigned char x,unsigned char y,unsigned char *p,unsigned char z);
void hzdisp(unsigned char x,unsigned char y,unsigned char *p,unsigned char z);
void clear_lcd_touchflag(void);
void SED1335_INIT(void);
void num_disp(void);


		 				    
#endif



