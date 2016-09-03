/*
**********************************************************************

----------------------------------------------------------------------
File        : LCDConf.h
Purpose     : S3C44B0X的lcd控制器的头文件
Data		: 2003-7-14 13:08
----------------------------------------------------------------------
**********************************************************************
*/

#ifndef LCDCONF_H
#define LCDCONF_H

//lcd颜色数,必须定义,LCDMONO(单色),LCDG4(四级灰度),LCDG16(16级灰度)
#define LCDMONO

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_CONTROLLER    0
//#define LCD_XSIZE         320            /* X-resolution of LCD, Logical coor. */
//#define LCD_YSIZE         240            /* Y-resolution of LCD, Logical coor. */

#ifdef LCDCOLOR
#define LCD_INTERFACEBITS 8              /* select 4 or 8 bit interface */
#else
#define LCD_INTERFACEBITS 4              /* select 4 or 8 bit interface */
#endif

//每点的bit数
#ifdef  LCDMONO
#define LCD_BITSPERPIXEL  1              /* Permitted values here: 1 or 2 */
#endif

#ifdef  LCDG4
#define LCD_BITSPERPIXEL  2              /* Permitted values here: 1 or 2 */
#endif

#ifdef  LCDG16
#define LCD_BITSPERPIXEL  4              /* Permitted values here: 1 or 2 */
#endif

#ifdef  LCDCOLOR
#define LCD_BITSPERPIXEL  8              /* Permitted values here: 1 or 2 */
#define LCD_SWAP_RB		  1
#endif

//#define LCD_TIMERINIT0  1200
//#define LCD_TIMERINIT1  1500

/*
**********************************************************************
*																	 *
*以下是S3C44B0X LCD控制器的配置										 *	
*																	 *
**********************************************************************
*/


#include "..\inc\option.h"

#define SCR_XSIZE 	(640)  
#define SCR_YSIZE 	(480)

#define LCD_XSIZE 	(640)
#define LCD_YSIZE 	(480)

#define M5D(n) ((n) & 0x1fffff)

#define ARRAY_SIZE_MONO 	(SCR_XSIZE/8*SCR_YSIZE)
#define ARRAY_SIZE_G4   	(SCR_XSIZE/4*SCR_YSIZE)
#define ARRAY_SIZE_G16  	(SCR_XSIZE/2*SCR_YSIZE)
#define ARRAY_SIZE_COLOR  	(SCR_XSIZE/1*SCR_YSIZE)

#define HOZVAL			(LCD_XSIZE/4-1)
//#define HOZVAL_COLOR	(LCD_XSIZE*3/8-1)
#define LINEVAL			(LCD_YSIZE/2-1)
#define MVAL			(13)

#define CLKVAL_MONO 	(10)  	//60Mhz, CLKVAL=10 -> 152 Hz
 							  	//			  	30 -> 51.6Hz
								//				50 -> 30  Hz	
#define CLKVAL_G4 		(10)
#define CLKVAL_G16 		(10)
#define CLKVAL_COLOR	(10)
												
#define MVAL_USED 1



#endif /* LCDCONF_H */

 
