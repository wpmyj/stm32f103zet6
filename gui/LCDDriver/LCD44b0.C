/*
*********************************************************

---------------------------------------------------------
File	: lcd44b0.c
Purpose	: S3C44B0X的lcd控制器的驱动，用于uC/GUI
Data	: 2003-7-9 13:46
---------------------------------------------------------
2003-7-31 13:52------完成4，16级灰度支持
********************************************************* 
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.H"      /* private modul definitions & config */
#include "GUI_Private.H"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

//********************************************************
//
#include <string.h>
#include "..\inc\44b.h"
#include "..\inc\44blib.h"
#include "..\inc\def.h"
//int i,j;
//********************************************************

#if (LCD_CONTROLLER == 0 ) && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

/*
*********************************************************
*                                                       *
*           Compiler specific settings                  *
*                                                       *
*********************************************************

*/

#ifdef WIN32   /* Avoid warnings in MS-compiler */
  	#pragma warning(disable : 4244)  // warning C4244: '=' : conversion from 'long ' to 'unsigned char ', possible loss of data
  	#pragma warning(disable : 4761)  // warning C4761: integral size mismatch in argument; conversion supplied
#endif

/*
*********************************************************
*                                                       *
*           Defaults for configuration                  *
*                                                       *
*********************************************************

*/

#define   COLOR LCD_COLORINDEX

#ifdef LCDMONO
	U32 (*frameBuffer1)[SCR_XSIZE/32];
#endif

#ifdef LCDG4
	U32 (*frameBuffer4)[SCR_XSIZE/16];
#endif

#ifdef LCDG16
	U32 (*frameBuffer16)[SCR_XSIZE/8];
#endif

#ifdef LCDCOLOR
	U32 (*frameBuffer256)[SCR_XSIZE/4];
#endif

		


/*
*********************************************************
*                                                       *
*       Internal set pixel routines                     *
*                                                       *
*********************************************************
*/

static void SetPixel(int x, int y, LCD_PIXELINDEX c) 
{
	
//	c=LCD_NUM_COLORS-1-c;
//黑白	
#ifdef LCDMONO	
    if(x<SCR_XSIZE && y<SCR_YSIZE)
		frameBuffer1[(y)][(x)/32]=( frameBuffer1[(y)][(x)/32] & ~(0x80000000>>((x)%32)*1) )
            | ( (c)<< ((32-1-((x)%32))*1) );
#endif
//4级灰度
#ifdef LCDG4	
    if(x<SCR_XSIZE && y<SCR_YSIZE)
        frameBuffer4[(y)][(x)/16]=( frameBuffer4[(y)][x/16] & ~(0xc0000000>>((x)%16)*2) )
            | ( (c)<<((16-1-((x)%16))*2) );
#endif
//16级灰度
#ifdef LCDG16
	if(x<SCR_XSIZE && y<SCR_YSIZE)
        frameBuffer16[(y)][(x)/8]=( frameBuffer16[(y)][x/8] & ~(0xf0000000>>((x)%8)*4) )
            | ( (c)<<((8-1-((x)%8))*4) );
#endif
//256色
#ifdef LCDCOLOR
	if(x<SCR_XSIZE && y<SCR_YSIZE)
        frameBuffer256[(y)][(x)/4]=( frameBuffer256[(y)][x/4] & ~(0xff000000>>((x)%4)*8) )
            | ( (c)<<((4-1-((x)%4))*8) );
#endif
}

unsigned int GetPixelIndex(int x, int y) {
    LCD_PIXELINDEX col;
//黑白	
#ifdef LCDMONO
  	col=( frameBuffer1[(y)][(x)/32] >> ( 32-1-(x%32)*1 ) ) & 0x1;
  	return col;
#endif
//4级灰度
#ifdef LCDG4
	col=( frameBuffer4[(y)][(x)/16] >> ( 32-2-(x%16)*2 ) ) & 0x3;
  	return col;
#endif
//16级灰度
#ifdef LCDG16
	col=( frameBuffer16[(y)][(x)/8] >> ( 32-4-(x%8)*4 ) ) & 0xf;
  	return col;
#endif
//256色
#ifdef LCDCOLOR
	col=( frameBuffer256[(y)][(x)/4] >> ( 32-8-(x%4)*8 ) ) & 0xff;
  	return col;
#endif
}

static void XorPixel   (int x, int y) {
    LCD_PIXELINDEX Index = GetPixelIndex(x,y);
    SetPixel(x,y,LCD_NUM_COLORS-1-Index);
}





/*******************************************************/
//自己做的画点函数
/*******************************************************/
/*

extern void SetBit(int x, int y, U8 c) {                    //按位写字节画黑点函数
    if(x<SCR_XSIZE/8 && y<SCR_YSIZE)
		frameBuffer1[(y)][(x)/4]=( frameBuffer1[(y)][(x)/4] & ~(0xff000000)>>(((x)%4)*8) )
             | ( c<<(32-1- (((x)%4)*8)) );
}
*/

/*
//unsigned	char	FrameBuffer[SCR_XSIZE/8*SCR_YSIZE];

void Test_WDTimer(int x, int y,U8 c)
{
*(((unsigned char *)(frameBuffer1))+x*LCD_XSIZE/8+y) =c;
}
*/

extern void Setbyte(int x, int y, U8 c)
{	// 按字节画点函数 X,Y都以点为单位

        U16 i;
        
	 for(i=0;i<8;i++){
		if(c&0x80){	
		 //  c<<=1;
		 //	GUI_DrawPixel((x)+i,y);    //GUI  画点 较慢					
		 //	      }
		 //else
		 //c<<=1;	    }		
		
		SetPixel((x+i),y,LCD_COLORINDEX);     //LCD  前景色画点  较快
			      }
		else
		SetPixel((x+i),y,LCD_BKCOLORINDEX);     //LCD  背景色画点  较快
		c<<=1;	   
		             }
		                              
}
		


extern void Setbyte8(int x, int y, U8 c){    // 按字节画点函数 X8个点(一个字节)为单位,Y以点为单位,X起点只能为8的整数倍
         Setbyte(x*8, y, c);
                                        }



extern void Setbyte8_nom(int j,int x, int y, U8 c){    // 按字节画点函数 X8个点(一个字节)为单位,Y以点为单位,X起点为任意位置(j为起点位置X坐标的偏移量)
         Setbyte(x*8+j, y, c);
                                                  }
                                                  
extern void Setbit_nom(int x, int y){    // 按字节画点函数 X8个点(一个字节)为单位,Y以点为单位,X起点为任意位置(j为起点位置X坐标的偏移量)
         						SetPixel(x,y,LCD_COLORINDEX);     //LCD  前景色画点  较快
                                                   }
                                                   
  
extern void Set_Pixel(int x, int y, LCD_PIXELINDEX c)	//调用SetPixel
				{	    
         			SetPixel(x,y,c);     
                                }                                                   


/**************************************************/


/*
*********************************************************
*                                                       *
*       LCD_L0_XorPixel                                 *
*                                                       *
*********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/

void LCD_L0_XorPixel(int x, int y) {
  	XorPixel(x, y);
}

void LCD_L0_SetPixelIndex(int x, int y, int ColorIndex) {
  	SetPixel(x, y, ColorIndex);
}

/*
*********************************************************
*                                                       *
*          LCD_L0_DrawHLine optimized                   *
*                                                       *
*          16 bit bus, Using BITBLT                     *
*                                                       *
*********************************************************
*/

void LCD_L0_DrawHLine  (int x0, int y,  int x1) 
{
  	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) 
  	{
    	while (x0 <= x1) 
    	{
      		XorPixel(x0, y);
      		x0++;
    	}
  	} else 
  	{
    	while (x0 <= x1) 
    	{
      		SetPixel(x0, y, COLOR);
      		x0++;
    	}
  	}
}

/*
*********************************************************
*                                                       *
*          LCD_L0_DrawVLine optimized                   *
*                                                       *
*          16 bit bus, using BITBLT                     *
*                                                       *
*********************************************************
*/

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (y0 <= y1) {
      XorPixel(x, y0);
      y0++;
    }
  } else {
    while (y0 <= y1) {
      SetPixel(x, y0, COLOR);
      y0++;
    }
  }
}

/*
*********************************************************
*                                                       *
*          LCD_FillRect                                 *
*                                                       *
*********************************************************
*/

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
#if !LCD_SWAP_XY
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0,y0, x1);
  }
#else
  for (; x0 <= x1; x0++) {
    LCD_L0_DrawVLine(x0,y0, y1);
  }
#endif
}

/*
**********************************************************
*                                                        *
*		  Draw a line                                    *
*                                                        *
**********************************************************
*/

static void  DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
//  	LCD_PIXELINDEX aColor[2];
  	U16 Pixels = ((*p) << 8) | (*(p + 1));
  	U8 RemPixels;
  	p++;
//  	aColor[0] = *pTrans;
//  	aColor[1] = *(pTrans + 1);
  	x += Diff;
  	RemPixels = 16 - Diff;
  	Pixels <<= Diff;
  
  	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    	do {
      		if (RemPixels==0) {
        		Pixels = ((*(p + 1)) << 8) | (*(p + 2));
        		p += 2;
        		RemPixels = 16;
      		}
      		if (Pixels & 0x8000) {
        		XorPixel(x, y);
      		}
      		RemPixels--;
      		Pixels <<=1;
      		x++;
    	} while (--xsize);
  	} 
  	else {
    	do {
      		if (RemPixels==0) {
        		Pixels = ((*(p + 1)) << 8) | (*(p + 2));
        		p += 2;
        		RemPixels = 16;
      		}
      		if (Pixels & 0x8000) {
        		SetPixel(x, y, *(pTrans+1));
      		}
      		//////////////////////  JIM LEE加  覆盖原先显示的字符
      		//else if ((GUI_Context.DrawMode | LCD_DRAWMODE_NORMAL)==LCD_DRAWMODE_NORMAL) 
      		else if ((GUI_Context.TextMode | LCD_DRAWMODE_NORMAL)==LCD_DRAWMODE_NORMAL)     		
      			{SetPixel(x, y, *(pTrans));}
      		/////////////////////
      		RemPixels--;
      		Pixels <<=1;
      		x++;
    	} while (--xsize);
  	} 
}

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 2 BPP                    *
    *                                           *
    *********************************************
*/
#if (LCD_MAX_LOG_COLORS > 2)
static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
  if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) switch (Diff&3) {
  case 0:
    goto WriteTBit0;
  case 1:
    goto WriteTBit1;
  case 2:
    goto WriteTBit2;
  default:
    goto WriteTBit3;
  } else switch (Diff&3) {
  case 0:
    goto WriteBit0;
  case 1:
    goto WriteBit1;
  case 2:
    goto WriteBit2;
  default:
    goto WriteBit3;
  }
/*
        Write without transparency
*/
WriteBit0:
  SetPixel(x+0, y, *(pTrans+(pixels>>6)));
  if (!--xsize)
    return;
WriteBit1:
  SetPixel(x+1, y, *(pTrans+(3&(pixels>>4))));
  if (!--xsize)
    return;
WriteBit2:
  SetPixel(x+2, y, *(pTrans+(3&(pixels>>2))));
  if (!--xsize)
    return;
WriteBit3:
  SetPixel(x+3, y, *(pTrans+(3&(pixels))));
  if (!--xsize)
    return;
  pixels = *(++p);
  x+=4;
  goto WriteBit0;
/*
        Write with transparency
*/
WriteTBit0:
  if (pixels&(3<<6))
    SetPixel(x+0, y, *(pTrans+(pixels>>6)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixels&(3<<4))
    SetPixel(x+1, y, *(pTrans+(3&(pixels>>4))));
  if (!--xsize)
    return;
WriteTBit2:
  if (pixels&(3<<2))
    SetPixel(x+2, y, *(pTrans+(3&(pixels>>2))));
  if (!--xsize)
    return;
WriteTBit3:
  if (pixels&(3<<0))
    SetPixel(x+3, y, *(pTrans+(3&(pixels))));
  if (!--xsize)
    return;
  pixels = *(++p);
  x+=4;
  goto WriteTBit0;
}
#endif


/*
    *********************************************
    *                                           *
    *      Draw Bitmap 4 BPP                    *
    *                                           *
    *********************************************
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void  DrawBitLine4BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  U8 pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
  if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) {
    if ((Diff&1) ==0)
      goto WriteTBit0;
    goto WriteTBit1;
  } else {
    if ((Diff&1) ==0)
      goto WriteBit0;
    goto WriteBit1;
  }
/*
        Write without transparency
*/
WriteBit0:
  SetPixel(x+0, y, *(pTrans+(pixels>>4)));
  if (!--xsize)
    return;
WriteBit1:
  SetPixel(x+1, y, *(pTrans+(pixels&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixels = *(++p);
  goto WriteBit0;
/*
        Write with transparency
*/
WriteTBit0:
  if (pixels>>4)
    SetPixel(x+0, y, *(pTrans+(pixels>>4)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixels&0xf)
    SetPixel(x+1, y, *(pTrans+(pixels&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixels = *(++p);
  goto WriteTBit0;
}
#endif

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 8 BPP  (256 colors)      *
    *                                           *
    *********************************************
*/
#if (LCD_MAX_LOG_COLORS > 16)
static void  DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
    if (pTrans) {
      for (;xsize > 0; xsize--,x++,p++) {
        pixel = *p;
        SetPixel(x, y, *(pTrans+pixel));
      }
    } else {
      for (;xsize > 0; xsize--,x++,p++) {
        SetPixel(x, y, *p);
      }
    }
  } else {   /* Handle transparent bitmap */
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SetPixel(x+0, y, *(pTrans+pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SetPixel(x+0, y, pixel);
        }
      }
    }
  }
}
#endif

/*
*********************************************************
*                                                       *
*         Universal draw Bitmap routine                 *
*                                                       *
*********************************************************
*/

void LCD_L0_DrawBitmap   (int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans) {
	int i;
  	for (i=0; i<ysize; i++) {
  		    switch (BitsPerPixel) {
                case 1:
                    DrawBitLine1BPP(x0, i+y0, pData, Diff, xsize, pTrans);
                    break;
                #if (LCD_MAX_LOG_COLORS > 2)
                case 2:
                    DrawBitLine2BPP(x0, i+y0, pData, Diff, xsize, pTrans);
                    break;
                #endif
                #if (LCD_MAX_LOG_COLORS > 4)
                case 4:
                    DrawBitLine4BPP(x0, i+y0, pData, Diff, xsize, pTrans);
                    break;
                #endif
                #if (LCD_MAX_LOG_COLORS > 16)
                case 8:
                    DrawBitLine8BPP(x0, i+y0, pData, xsize, pTrans);
                    break;
                #endif
            }
    	pData += BytesPerLine;
  	}
}

/********************************************************
*                                                       *
*       LCD_L0_SetOrg                                   *
*                                                       *
*********************************************************
                                                        
Purpose:        Sets the original position of the virtual display.
                Has no function at this point with the PC-driver.
*/

int OrgX, OrgY;
void LCD_L0_SetOrg(int x, int y) {
  	OrgX = x;
  	OrgY = y;
}

/*
*********************************************************
*                                                       *
*       LCD_On                                          *
*       LCD_Off                                         *
*                                                       *
*********************************************************
*/

void LCD_Off          (void) {
#if MANY_TASK
	Delay(100);
#endif
  //  rPDATC = ( rPDATC | (1<<8) );  //DISP_ON在GPC8上   (有反相器)
      rPDATE = ( rPDATE & (~(1<<3)) );   //DISP_ON在GPE3上(无反相器)
#if MANY_TASK   
    Delay(100);
#endif
}

void LCD_On           (void) {
#if MANY_TASK
	Delay(100);
#else

#endif
   // rPDATC = ( rPDATC & (~(1<<8)) ); //DISP_ON在GPC8上(有反相器)
   rPDATE = ( rPDATE | (1<<3) );     //DISP_ON在GPE3上  (无反相器)
   
#if MANY_TASK   
    Delay(100);
#else

#endif
}


void LCD_Init_Controler() 
{
	
int i,j;
U32 k= 0;

#ifdef LCDMONO
    //320x240 1bit/1pixel LCD

    if((U32)frameBuffer1==0)
	{
  	frameBuffer1=(unsigned int (*)[SCR_XSIZE/32])malloc(ARRAY_SIZE_MONO); 
	}
 for(j=0;j<480;j++)
    for(i=0;i<20;i++)
    	{
	frameBuffer1[j][i]=0x0;
    	}

    rLCDCON1=(0)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_MONO<<12);
    // disable,4B_SNGL_SCAN,WDLY=16clk,WLH=16clk,
    rLCDCON2=(LINEVAL)|(HOZVAL<<10)|(10<<21);  
    // LINEBLANK=10

	rLCDSADDR1= (0x0<<27) | ( ((U32)frameBuffer1>>22)<<21 ) | M5D((U32)frameBuffer1>>1);
    // monochrome, LCDBANK, LCDBASEU
    
	rLCDSADDR2= M5D( (((U32)frameBuffer1+(SCR_XSIZE*LCD_YSIZE/16))>>1) ) | (MVAL<<21);
	// LCDBASSEL, MVAL
	rLCDSADDR3= (LCD_XSIZE/16) | ( ((SCR_XSIZE-LCD_XSIZE)/16)<<9 );
	// PAGEWIDTH, OFFSIZE (the number of halfwords)
	// No virtual screen. 
	
	rLCDCON1=(1)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_MONO<<12);
	// enable,4B_SNGL_SCAN,WDLY=16clk,WLH=16clk,
#endif

//********************************************************************************
#ifdef LCDG4
	if((U32)frameBuffer4==0)
	{
	    frameBuffer4=(unsigned int (*)[SCR_XSIZE/16])malloc(ARRAY_SIZE_G4); 
	}
for(j=0;j<480;j++)
    for(i=0;i<40;i++)
    {
		frameBuffer4[j][i]=0x0;
    }

	rLCDCON1=(0)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_G4<<12);
	    // disable,4B_SNGL_SCAN,WDLY=8clk,WLH=8clk,
	rLCDCON2=(LINEVAL)|(HOZVAL<<10)|(10<<21);  
	    //LINEBLANK=10 (without any calculation) 
	rLCDSADDR1= (0x1<<27) | ( ((U32)frameBuffer4>>22)<<21 ) | M5D((U32)frameBuffer4>>1);
	    // 4-gray, LCDBANK, LCDBASEU
	rLCDSADDR2= M5D((((U32)frameBuffer4+(SCR_XSIZE*LCD_YSIZE/8))>>1)) | (MVAL<<21);
	rLCDSADDR3= (LCD_XSIZE/8) | ( ((SCR_XSIZE-LCD_XSIZE)/8)<<9 );

	//The following value has to be changed for better display.
	// 

	rBLUELUT=0xfa40; 
	rDITHMODE=0x0;
	rDP1_2 =0xa5a5;      
	rDP4_7 =0xba5da65;
	rDP3_5 =0xa5a5f;
	rDP2_3 =0xd6b;
	rDP5_7 =0xeb7b5ed;
	rDP3_4 =0x7dbe;
	rDP4_5 =0x7ebdf;
	rDP6_7 =0x7fdfbfe;

	rLCDCON1=(1)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_G4<<12);
	    // enable,4B_SNGL_SCAN,WDLY=8clk,WLH=8clk,	
#endif
//********************************************************************************
#ifdef LCDG16
	if((U32)frameBuffer16==0)
	{
	#if 0
		k =	  ARRAY_SIZE_G16;
		k = SCR_XSIZE/8	;
		frameBuffer16=malloc(ARRAY_SIZE_G16);
		free(frameBuffer16);
		frameBuffer16[0][0]=0x0;
	#endif
	    frameBuffer16=(unsigned int (*)[SCR_XSIZE/8]  ) malloc(ARRAY_SIZE_G16);// 		  ARRAY_SIZE_G16
	}
	#if 0
for(j=0;j<SCR_XSIZE;j++)//for(j=0;j<480;j++)
    for(i=0;i<80;i++)
    {
		frameBuffer16[j][i]=0x0;
    }
	#else

 		 memset(frameBuffer16,0,10);
	#endif

	//The following value has to be changed for better display.
/*	rDITHMODE=0x1223a; //philips
	rDP1_2 =0x5a5a;      
	rDP4_7 =0x366cd9b;
	rDP3_5 =0xda5a7;
	rDP2_3 =0xad7;
	rDP5_7 =0xfeda5b7;
	rDP3_4 =0xebd7;
	rDP4_5 =0xebfd7;
	rDP6_7 =0x7efdfbf;*/

    rDITHMODE=0x12210; 	
    //rDITHMODE=0x0;
    rDP1_2 =0xa5a5;      
	rDP4_7 =0xba5da65;
	rDP3_5 =0xa5a5f;
	rDP2_3 =0xd6b;
	rDP5_7 =0xeb7b5ed;
	rDP3_4 =0x7dbe;
	rDP4_5 =0x7ebdf;
	rDP6_7 =0x7fdfbfe;



	rLCDCON1=(0)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_G16<<12);
	    // disable,4B_SNGL_SCAN,WDLY=8clk,WLH=8clk,
	rLCDCON2=(LINEVAL)|(HOZVAL<<10)|(10<<21);  
	    //LINEBLANK=10 (without any calculation) 
	rLCDSADDR1= (0x2<<27) | ( ((U32)frameBuffer16>>22)<<21 ) | M5D((U32)frameBuffer16>>1);
	    // 16-gray, LCDBANK, LCDBASEU
	rLCDSADDR2= M5D((((U32)frameBuffer16+(SCR_XSIZE*LCD_YSIZE/4))>>1)) | (MVAL<<21);
	rLCDSADDR3= (LCD_XSIZE/4) | ( ((SCR_XSIZE-LCD_XSIZE)/4)<<9 );
	rLCDCON1=(1)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_G16<<12);

	    // enable,4B_SNGL_SCAN,WDLY=8clk,WLH=8clk,
#endif
#ifdef LCDCOLOR
	if((U32)frameBuffer256==0)
	{
	    //The total frame memory should be inside 4MB.
	    //For example, if total memory is 8MB, the frame memory 
	    //should be in 0xc000000~0xc3fffff or c400000~c7fffff.
	    //But, the following code doesn't meet this condition(4MB) 
	    //if the code size & location is changed..
	    frameBuffer256=(unsigned int (*)[SCR_XSIZE/4])malloc(ARRAY_SIZE_COLOR); 
	}
	
for(j=0;j<480;j++)
    for(i=0;i<160;i++)
    	{
	frameBuffer256[j][i]=0x0;
    	}	

	rLCDCON1=(0)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_COLOR<<12);
	    // disable,8B_SNGL_SCAN,WDLY=8clk,WLH=8clk,
	rLCDCON2=(LINEVAL)|(HOZVAL_COLOR<<10)|(10<<21);  
	    //LINEBLANK=10 (without any calculation) 
	rLCDSADDR1= (0x3<<27) | ( ((U32)frameBuffer256>>22)<<21 ) | M5D((U32)frameBuffer256>>1);
	    // 256-color, LCDBANK, LCDBASEU
	rLCDSADDR2= M5D((((U32)frameBuffer256+(SCR_XSIZE*LCD_YSIZE/2))>>1)) | (MVAL<<21);
	rLCDSADDR3= (LCD_XSIZE/2) | ( ((SCR_XSIZE-LCD_XSIZE)/2)<<9 );

	//The following value has to be changed for better display.

	rREDLUT  =0xfdb96420;
	rGREENLUT=0xfdb96420;
	rBLUELUT =0xfb40;

	rDITHMODE=0x0;
	rDP1_2 =0xa5a5;      
	rDP4_7 =0xba5da65;
	rDP3_5 =0xa5a5f;
	rDP2_3 =0xd6b;
	rDP5_7 =0xeb7b5ed;
	rDP3_4 =0x7dbe;
	rDP4_5 =0x7ebdf;
	rDP6_7 =0x7fdfbfe;

	rLCDCON1=(1)|(0<<5)|(MVAL_USED<<7)|(0x3<<8)|(0x3<<10)|(CLKVAL_COLOR<<12);
	    // enable,8B_SNGL_SCAN,WDLY=8clk,WLH=8clk,
#endif
}


unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  	return GetPixelIndex(x,y);
}

/*
*********************************************************
*                                                       *
*                   LCD_L0_SetLUTEntry                  *
*                                                       *
*********************************************************
*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {

}

/*
*********************************************************
*                                                       *
*       LCD_L0_ReInit : Re-Init the display             *
*                                                       *
*********************************************************

ReInit contains all of the code that can be re-executed at any point without
changing or even disturbing what can be seen on the LCD.
Note that it is also used as a subroutine by LCD_Init().

*/

void  LCD_L0_ReInit(void) {
	
  	LCD_Init_Controler();                     /* macro defined in config */

}

/*
*********************************************************
*                                                       *
*       LCD_Init : Init the display                     *
*                                                       *
*********************************************************
*/
int LCD_L0_Init(void) {
    GUI_DEBUG_LOG("\nLCD_Init()");
    /* Init controllers (except lookup table) */
    LCD_L0_ReInit();
    LCD_Off();
    return 0;    /* Init successfull ! */
}
 #if 1
/*
*********************************************************
*                                                       *
*       LCD_L0_CheckInit                                *
*                                                       *
*  Check if display controller(s) is/are still          *
*  properly initialized                                 *
*                                                       *
*********************************************************
Return value:	0 => No error, init is O.K.
*/

int LCD_L0_CheckInit(void) {
    return 0;
}

#else

void LCD13XX(void) { } /* avoid empty object files */

#endif  /* (LCD_CONTROLLER == 0) */

#endif

