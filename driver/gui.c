#include "gui.h"

//============================================================================= 
//函 数 名: DrawDotsRA8835P() 
//功 能:    RA8835P上指定坐标 绘点函数
//入口参数: x:0--320横向坐标,y:0--256  纵向坐标  color:0-1 点的颜色 0:白，1:黑
//出口参数: 无 
//返 回 值: 无 
//============================================================================= 
extern INT16U ScreenStartAddress ;

#define SELECT_SCREEN_1  ScreenStartAddress = SCREEN_1_START_ADDRESS
#define SELECT_SCREEN_2  ScreenStartAddress = SCREEN_2_START_ADDRESS

#define LcmYSize 240
#define LcmXSize 320	 
extern u8 const BitWriteTab[];
void DrawDots(INT16S x,INT16S y,u8 color)
{ 

	INT16U csr;
	INT8U DataTemp = 0;
		
    csr	= ScreenStartAddress + y*(LcmXSize/8) + x/8;

    //WriteCommandRA8835P(0x46);	//CURSOR SET
    //WriteDataRA8835P(csr%256);	//SET P1  (00H)
    //WriteDataRA8835P(csr/256);	//SET P2  (00H)
   // WriteCommandRA8835P(0x43);	//READY TO READ DATA
#if 1
   // DataTemp = ReadDataRA8835P();
    
   if(color)
   {
//	DataTemp|=(BitWriteTab[7-x%8]);	
   }		
   else 
   {
//	DataTemp&=~(BitWriteTab[7-x%8]) ;
   }				    
  
    WriteCommandRA8835P(0x46);	//CURSOR SET
    WriteDataRA8835P(csr%256);	//SET P1  (00H)
    WriteDataRA8835P(csr/256);	//SET P2  (00H)
    //WriteCommandRA8835P(0x42);	//READY TO WRITE DATA
    //WriteDataRA8835P(0xff);
	DataTemp |=(BitWriteTab[7-x%8]);
	WriteDataRA8835P(DataTemp);
#endif
}

void DrawLine( INT16S x, INT16S y, INT16S x1, INT16S y1, u8 color) 
{ 

   static u8 glow = 0;
   static u8 ghigh = 0;

    INT16S dx,dy,err = 0;

   	WriteCommandRA8835P(0x46);	//CURSOR SET

	SetCursor(glow,glow);
 
    if(y != y1)
	{
		if(y1 < y) //这个判断语句保证了y1>=y这个前提
		{
			dx = y1; dy = x1;
			y1 = y;  x1 = x;
			y = dx;  x = dy;
		}
		dy = y1 - y;
		dx = x1 - x;
		DrawDots(x ,y,color);
		
		if((x1 >= x)&&((y1 - y) <= (x1 - x)))
		{
			for(;x != x1;)
			{
				if(err < 0)
				{
					DrawDots(x + 1,y,color);
					x += 1;
					err += dy;
				}
				else
				{
					DrawDots(x + 1,y + 1,color);
					x += 1;
					y += 1;
					err += (dy - dx);
				}
			}
		}
		else
			if((x1 >= x)&&((y1 - y) > (x1 - x)))
			{
				for(;y != y1;)
				{
					if(err < 0)
					{
						DrawDots(x + 1,y + 1,color);
						x += 1;
						y += 1;
						err += (dy - dx);
					}
					else
					{
						DrawDots(x,y + 1,color);
						y += 1;
						err -= dx;
					}
				}
			}
			else
				if((x1 < x)&&((y1 - y) <= (x - x1)))
				{
					for(;x != x1;)
					{
						if(err < 0)
						{
							DrawDots(x - 1,y,color);
							x -= 1;
							err += dy;
						}
						else
						{
							DrawDots(x - 1,y + 1,color);
							x -= 1;
							y += 1;
							err += (dy + dx);
						}
					}
				}
				else
					if((x1 < x)&&((y1 - y) > (x1 - x)))
					{
						for(;y != y1;)
						{
							if(err < 0)
							{
								DrawDots(x - 1,y + 1,color);
								x -= 1;
								y += 1;
								err += (dy + dx);
							}
							else
							{
								DrawDots(x,y + 1,color);
								y += 1;
								err += dx;
							}
						}
					}
	}	
	else
	{
		dx = x; dy = x1;
		if(x < x1)
		{
			dx = x1;
			dy = x;
		}
		for(;dy < dx;dy++)
			DrawDots(dy,y,color);

			DrawDots(x1 ,y1,color);
	}
}

union  
{
	unsigned int word;
    struct 
	{
		unsigned char low;
		unsigned char high;
    }byte;
}v_test1;

void test_gui(void)
{	
	int ii =0;
	
	v_test1.word = 24 + (150 +(8*3)-8)*40;	 //	竖线

	for( ii = 0; ii <16; ii++)
	{
		LcdCommand(0x46);			
		LcdDataWrite(v_test1.byte.low);	//19 120
		LcdDataWrite(v_test1.byte.high);	
		WriteCommandRA8835P(0x2c);//right
		WriteCommandRA8835P(0x42); 
		WriteDataRA8835P(0x01); 
		v_test1.word += 40; 
	}

	v_test1.word = 24 + (150 +(8*3))*40;

	for( ii = 0; ii <2; ii++)
	{
		LcdCommand(0x46);			
		LcdDataWrite(v_test1.byte.low);	//19 120
		LcdDataWrite(v_test1.byte.high);
		WriteCommandRA8835P(0x2c);//right
		WriteCommandRA8835P(0x42); 
		WriteDataRA8835P(0x0ff); 
		v_test1.word ++; 
	}

    v_test1.word = 20 + 150*40;	 //竖线

    for( ii = 0; ii <48; ii++) //竖线
	{
		LcdCommand(0x46);	
		
		LcdDataWrite(v_test1.byte.low);	//19 120
		LcdDataWrite(v_test1.byte.high);
	
		WriteCommandRA8835P(0x2c);//right
		WriteCommandRA8835P(0x42); 
		WriteDataRA8835P(0x80); 
		v_test1.word += 40; 
	}

	v_test1.word = 28 + 150*40;	//竖线
	for( ii = 0; ii <48; ii++) //竖线
	{
		LcdCommand(0x46);	
		
		LcdDataWrite(v_test1.byte.low);	//19 120
		LcdDataWrite(v_test1.byte.high);
	
		WriteCommandRA8835P(0x2c);//right
		WriteCommandRA8835P(0x42); 
		WriteDataRA8835P(0x01); 
		v_test1.word += 40; 
	}

	v_test1.word = 20 + 150*40;	//横线
	for( ii = 0; ii <9; ii++)
	{
		LcdCommand(0x46);	
		
		LcdDataWrite(v_test1.byte.low);	//19 120
		LcdDataWrite(v_test1.byte.high);
	
		WriteCommandRA8835P(0x2c);//right
		WriteCommandRA8835P(0x42); 
		WriteDataRA8835P(0xff); 
		v_test1.word ++; 
	}
	v_test1.word = 20 + 198*40;	//横线
	for( ii = 0; ii <9; ii++)
	{
		LcdCommand(0x46);	
		
		LcdDataWrite(v_test1.byte.low);	//19 120
		LcdDataWrite(v_test1.byte.high);
	
		WriteCommandRA8835P(0x2c);//right
		WriteCommandRA8835P(0x42); 
		WriteDataRA8835P(0xff); 
		v_test1.word ++; 
	}

	


#if 0	
   DrawDots(30,50,0);
   DrawDots(31,50,0);
   DrawDots(32,50,0);
   DrawDots(33,50,0);
   DrawDots(34,50,0);
   DrawDots(35,50,0);
   DrawDots(36,50,0);
   DrawDots(37,50,0);

   DrawDots(30,50,0);
   DrawDots(31,51,0);
   DrawDots(32,52,0);
   DrawDots(33,53,0);
   DrawDots(34,54,0);
   DrawDots(35,55,0);
   DrawDots(36,56,0);
   DrawDots(37,57,0);
#endif
}



