//================================================================================================
// 文件名称: RA8835P.C  
// 芯片类型: W78E516B + RA8835P
// 开发软件: MedWin V3, Windows XP2 
// 开发时间: 20010年04月08日                                                               
// 程序功能: RA8835P控制器的模组测试程序
// 编写人员: 崔超                                                                       
// 联系方式: 13686036830  cuichao@xrd-lcd.com   
//================================================================================================ 

//========================================= 头文件 ================================================ 

#include "Includes.h"
#include "bmp.c"


#if 0
#define RA8835P_Bus        		P1


#if TEST_JIG == 0 
 //生产测试架
	#define RA8835P_CS(x)		P3_4 = x			
	#define RA8835P_RST(x)		P3_1 = x
	#define RA8835P_RS(x) 		P3_7 = x		
	#define RA8835P_WR(x)   	P3_6 = x				
	#define RA8835P_RD(x)   	P3_5 = x

#else
	#if TEST_JIG == 1 
//老化测试架
		#define RA8835P_CS(x)		P2_3 = x			
		#define RA8835P_RST(x)		P2_4 = x
		#define RA8835P_RS(x) 		P2_0 = x		
		#define RA8835P_WR(x)   	P2_1 = x				
		#define RA8835P_RD(x)   	P2_2 = x
	#else
	   #error  "no define TEST_JIG"
	#endif
#endif

#define SomeNopRA8835P()     
#define TEST_DELAY_TIME 800

#define SCREEN_1_START_ADDRESS 0X0000
#define SCREEN_2_START_ADDRESS 0X58EF


#define SELECT_SCREEN_1  ScreenStartAddress = SCREEN_1_START_ADDRESS
#define SELECT_SCREEN_2  ScreenStartAddress = SCREEN_2_START_ADDRESS
		 
//======================================== 变量定义 =============================================== 
INT8U _CONST_ BitWriteTab[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//用来写一位数据的掩码表

INT16U ScreenStartAddress = 0; 
		 
//======================================== 函数声明 =============================================== 
//============================================================================= 
//函 数 名:  Delay_ms(INT16U ms) 
//功 能: 	延时
//入口参数:  延时的毫秒数
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void Delay_ms(INT16U ms)   
{
    INT8U a,b,c;
    while(ms--)
    for(c=1;c>0;c--)
        for(b=20;b>0;b--)
            for(a=40;a>0;a--);
}
//============================================================================= 
//函 数 名:  StatusCheckRA8835P() 
//功 能: 	检查RA8835P状态位
//入口参数:  无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void StatusCheckRA8835P()
{
    INT8U status;
    INT8U TimeOut;
    TimeOut=0x10;
    RA8835P_CS(0);
    do{
        RA8835P_Bus=0xff;
        RA8835P_RS(0);
        RA8835P_RD(0);
        SomeNopRA8835P();
        status=RA8835P_Bus;
        RA8835P_RD(1);
        status&=0x40;	
        }while((status!=0x40)&&(TimeOut--));
    RA8835P_CS(1);
}
//============================================================================= 
//函 数 名:  WriteCommandRA8835P() 
//功 能: 	写命令到RA8835P
//入口参数:  CmdData:命令码
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void WriteCommandRA8835P(INT8U CmdData)
{
	//StatusCheckRA8835P();
    RA8835P_RS(1);
    RA8835P_CS(0);
    RA8835P_Bus = CmdData;
    SomeNopRA8835P();
    RA8835P_WR(0);
    SomeNopRA8835P();
    RA8835P_WR(1);
    RA8835P_CS(1);

}
//============================================================================= 
//函 数 名:  WriteDataRA8835P() 
//功 能: 	写数据到RA8835P
//入口参数:  CmdData:写入的数据
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void WriteDataRA8835P(INT8U Data)
{
    //StatusCheckRA8835P();
    RA8835P_RS(0);
    RA8835P_CS(0);
    RA8835P_Bus = Data;
    SomeNopRA8835P();
    RA8835P_WR(0);
    SomeNopRA8835P();
    RA8835P_WR(1);
    RA8835P_CS(1);

}

//============================================================================= 
//函 数 名: ReadDataRA8835P() 
//功 能: 	从RA8835P读数据
//入口参数:  无
//出口参数:  无
//返 回 值:  读出的数据
//============================================================================= 
INT8U ReadDataRA8835P()
{
    INT8U Data;
    RA8835P_RS(1);
    RA8835P_CS(0);
    RA8835P_Bus = 0xff;
    RA8835P_RD(0);
    SomeNopRA8835P();
    Data = RA8835P_Bus; 
    RA8835P_RD(1);
    RA8835P_CS(1);
    return (Data);

}
#define RA8835_OSC_FREQ_M    10
#define FR                   75

//============================================================================= 
//函 数 名: InitRA8835P() 
//功 能: 	初始化 RA8835P
//入口参数:  无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void InitRA8835P(void){


	WriteCommandRA8835P(0x40);  //SYSTEM SET
    StatusCheckRA8835P();
    WriteDataRA8835P(0x30); //SET P1 (M0=M1=M2=0,W/S=0,IV=1)
    WriteDataRA8835P(0x87); //SET P2 ()
    WriteDataRA8835P(0x07); //SET P3
    WriteDataRA8835P(LcmXSize/8-1); //SET P4 C/R (40 columns=40*8 dots)


 //  	WriteDataRA8835P(70);  //SET P5 TC/R (TC/R>=C/R+4)   48

    WriteDataRA8835P(RA8835_OSC_FREQ_M*1000000/9/FR/240);  //SET P5 TC/R (TC/R>=C/R+4)   48
    

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
                            //         SECOND SCREEN DISPLAY DISPLAY ON BUT FLASHING
                            //         FIRST SCREEN DISPLAY DISPLAY ON BUT FLASHING )

    WriteCommandRA8835P(0x5d);  //CURSOR TYPE (CSRFORM) SET 
    WriteDataRA8835P(0x07); //SET P1  ()
    WriteDataRA8835P(0x81); //SET P2  ()

    WriteCommandRA8835P(0x59);  //DISPLAY ON SET 
    WriteDataRA8835P(0x06); //SET P1  ()

    WriteCommandRA8835P(0x4c);  //CSRDID SET 
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

//============================================================================= 
//函 数 名: WriteByteLocateRA8835P() 
//功 能:    RA8835P上指定位置 显示指定数据
//入口参数: DisplayData:写入的数据  x0:0--40横向坐标,y0:0--256  纵向坐标 
//出口参数: 无 
//返 回 值: 无 
//============================================================================= 
void Display_Locate(INT8U DisplayData, INT8U x0, INT8U y0)
{    
	INT16U csr;
	
     csr = ScreenStartAddress + y0*(LcmXSize/8) + x0;
     WriteCommandRA8835P(0x46);	//CURSOR SET
     WriteDataRA8835P(csr%256);	//SET P1  (00H)
     WriteDataRA8835P(csr/256);	//SET P2  (00H)
     WriteCommandRA8835P(0x42);	//READY TO WRITE DATA   
     WriteDataRA8835P(DisplayData);         
}

//============================================================================= 
//函 数 名: DrawDotsRA8835P() 
//功 能:    RA8835P上指定坐标 绘点函数
//入口参数: x:0--320横向坐标,y:0--256  纵向坐标  color:0-1 点的颜色 0:白，1:黑
//出口参数: 无 
//返 回 值: 无 
//============================================================================= 

void DrawDots(INT16S x,INT16S y,bit color)
{ 

	INT16U csr;
	INT8U DataTemp;
		
    csr	= ScreenStartAddress + y*(LcmXSize/8) + x/8;
    WriteCommandRA8835P(0x46);	//CURSOR SET
    WriteDataRA8835P(csr%256);	//SET P1  (00H)
    WriteDataRA8835P(csr/256);	//SET P2  (00H)
    WriteCommandRA8835P(0x43);	//READY TO READ DATA
     DataTemp = ReadDataRA8835P();
    
    if(color)
   {
	DataTemp|=(BitWriteTab[7-x%8]);	
   }		
   else 
   {
	DataTemp&=~(BitWriteTab[7-x%8]) ;
   }				    
  
    WriteCommandRA8835P(0x46);	//CURSOR SET
    WriteDataRA8835P(csr%256);	//SET P1  (00H)
    WriteDataRA8835P(csr/256);	//SET P2  (00H)
    WriteCommandRA8835P(0x42);	//READY TO WRITE DATA
    WriteDataRA8835P(DataTemp);
} 
/*
//============================================================================= 
//函 数 名: DrawLine() 
//功 能:    画线子程序:为了回避复杂的浮点运算,采用了整数数字微分的方法
//			以(x列,y行)为起点,以(x1列,y1行)为终点画一条直线
//入口参数: x,y	起始坐标	x1,y1终点坐标	color:0-1 0:白线 1:黑线
//	 ┏━━━━━━━━┓
//	 ┃ x,y ------->x1 ┃
//	 ┃	|╲			   ┃
//   ┃ |  ╲		   ┃	
//	 ┃	|	 ╲		   ┃
//	 ┃	y1	  x1,y1	   ┃
//	 ┗━━━━━━━━┛
//		   zuo
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void DrawLine( INT16S x, INT16S y, INT16S x1, INT16S y1, bit color) 
{ 


    INT16S dx,dy,err = 0;
   
 
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
//============================================================================= 
//函 数 名: DrawRectangle() 
//功 能:    画矩形子程序:
//			以(x列,y行)为起点,以(x1列,y1行)为终点画一矩形
//入口参数: x,y	起始坐标	x1,y1终点坐标	color:0-1 0:白线 1:黑线
//	 ┏━━━━━━━━┓
//	 ┃ x,y ------->x1 ┃
//	 ┃	|┏━━━━┓  ┃
//   ┃ |│   	   ┃  ┃	
//	 ┃	|┗━━━━┛  ┃
//	 ┃	y1		 x1,y1 ┃
//	 ┗━━━━━━━━┛
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void DrawRectangle(INT16S X1, INT16S Y1, INT16S X2, INT16S Y2, bit color) 
{ 
   DrawLine(X1,Y1,X1,Y2, color); 
   DrawLine(X1,Y2,X2,Y2, color); 
   DrawLine(X2,Y2,X2,Y1, color); 
   DrawLine(X2,Y1,X1,Y1, color); 

}
//============================================================================= 
//函 数 名: DrawRectangleArray() 
//功 能:    画"回"形框子程序:
//			以(0,0)为起点,以(x列,y行)为终点画"回"形框
//入口参数: x,y	终点坐标 GapSize:间隙	color:0-1 0:白线 1:黑线
//     ┏━━━━━━━━┓
//     ┃┏━━━━━━┓┃
//     ┃┃┏━━━━┓┃┃
//     ┃┃┃        ┃┃┃
//     ┃┃┗━━━━┛┃┃
//     ┃┗━━━━━━┛┃
//     ┗━━━━━━━━┛
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void DrawRectangleArray(INT16S X, INT16S Y,INT8U GapSize, bit color) 
{ 
   INT16S y1;
  
   for (y1=0;Y-y1>GapSize;y1+=GapSize)
	{DrawRectangle(y1,y1,X,Y,color);
	 X-=GapSize;
	 Y-=GapSize;
	}

}
//============================================================================= 
//函 数 名: DrawCross() 
//功 能:    画交叉线子程序:
//			以(x列,y行)为起点,以(x1列,y1行)为终点画交叉线和矩形边框
//入口参数: x,y	起始坐标	x1,y1终点坐标	color:0-1 0:白线 1:黑线
//	 ┏━━━━━━━━┓
//	 ┃ x,y ------->x1 ┃
//	 ┃	|	┏━┓ 	   ┃
//   ┃ |	│╳┃ 	   ┃	
//	 ┃	|	┗━┛ 	   ┃
//	 ┃	y1	   x1,y1   ┃
//	 ┗━━━━━━━━┛
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void DrawCross(INT16S X1, INT16S Y1, INT16S X2, INT16S Y2, bit color) 
{ 

  DrawLine(X1,Y1,X1,Y2, color); 
  DrawLine(X1,Y2,X2,Y2, color); 
  DrawLine(X2,Y2,X2,Y1, color); 
  DrawLine(X2,Y1,X1,Y1, color); 
  DrawLine(X2,Y1,X1,Y2, color);
  DrawLine(X1,Y1,X2,Y2, color);
}*/
//============================================================================= 
//函 数 名: ScanScreen() 
//功 能:    扫描屏幕
//入口参数: data1:奇数行的数据  data2:偶数行的数据 
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void ScanScreen(INT8U data1,INT8U data2)
{	
    INT8U i,j;

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
void DrawPictureRA8835(INT8U *p)
{

	INT16U i,j,k;

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
			} else {				
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


//sfr   CHPENR=0xF6;    //定义W78E516B的特殊功能寄存器
//sfr   CHPCON=0xBF;    //用来打开片上的256Byte的RAM    
//============================================================================= 
//函 数 名: main() 
//功 能:    RA8835P控制器类型的模组的测试函数 
//入口参数: 无 
//出口参数: 无 
//返 回 值: 无
//============================================================================= 
void main(void)
{
 
   INT16U count;
 
    EA = 1;
    EX0 = 1;

    

    RA8835P_RST(0);
    Delay_ms(100);
   	RA8835P_RST(1);
	Delay_ms(100);
    	
    TP_Init();
    while(1)
	{
		
	
	InitRA8835P();
	InitRA8835P();

	GUI_Init();

	SELECT_SCREEN_1;//选择第一屏
	ShowScreen1();  //显示第一屏
	ScanScreen(0xaa,0x55);
	Delay_ms(TEST_DELAY_TIME);

	DrawPictureRA8835(BMP3);//交叉线
	Delay_ms(TEST_DELAY_TIME-100);

	DrawPictureRA8835(BMP2);//回形
	Delay_ms(TEST_DELAY_TIME-100);

	Delay_ms(TEST_DELAY_TIME);
	ScanScreen(0xff,0xff);//全黑
	Delay_ms(TEST_DELAY_TIME-100);

	SELECT_SCREEN_2;//选择第二屏
	ScanScreen(0x00,0x00);//清屏
	ShowScreen2();  //显示第二屏
	DrawPictureRA8835(BMP1);//大字母图案
	Delay_ms(TEST_DELAY_TIME);


	ScanScreen(0xff,0x00);//横线1
	Delay_ms(TEST_DELAY_TIME);
	ScanScreen(0x00,0xff);//横线2
	Delay_ms(TEST_DELAY_TIME);
	ScanScreen(0xaa,0xaa);//竖线1
	Delay_ms(TEST_DELAY_TIME);
	ScanScreen(0x55,0x55);//竖线2
	Delay_ms(TEST_DELAY_TIME);

	ScanScreen(0xCC,0x33);//测隔行短路
	Delay_ms(TEST_DELAY_TIME);

	ScanScreen(0x00,0x00);//清屏
//	GUI_DispStringAt("绝对坐标X:",0,0);
//	GUI_DispStringAt("绝对坐标Y:",0,16);
//	GUI_DispStringAt("相对坐标X:",0,32);
//	GUI_DispStringAt("相对坐标Y:",0,48);
	GUI_DispStringAt("触摸屏测试",15,0);
	GUI_SetTextMode(GUI_TEXTMODE_REVERSE);
	GUI_DispStringAt("清屏",36,224);
	GUI_SetTextMode(GUI_TEXTMODE_NORMAL);
		
  	count = 0;
   	while (1)
		{
			
		
		TP_GetLCDXY();
		if(TP_GetLCDXY() == 1)
		{	count = 0;
			 DrawDots(TP_X,TP_Y,1);	
			 DrawDots(TP_X+1,TP_Y,1);
			 DrawDots(TP_X,TP_Y+1,1);
			 DrawDots(TP_X+1,TP_Y+1,1);
			 if(TP_X > 287 && TP_Y > 223)
				{
					ScanScreen(0x00,0x00);//清屏
			//		GUI_DispStringAt("绝对坐标X:",0,0);
			//		GUI_DispStringAt("绝对坐标Y:",0,16);
			//		GUI_DispStringAt("相对坐标X:",0,32);
			//		GUI_DispStringAt("相对坐标Y:",0,48);
			        GUI_DispStringAt("触摸屏测试",15,0);
					GUI_SetTextMode(GUI_TEXTMODE_REVERSE);
					GUI_DispStringAt("清屏",36,224);
					GUI_SetTextMode(GUI_TEXTMODE_NORMAL);	
				}
			}else {
			count ++;
			}
 			if(count > 30000) break;

		}
	}
}

//============================================================================= 
//函 数 名: INT0_ROUTING()
//功	能: 中断服务程序
//入口参数:  无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
#define KEY1 P3_2
#define KEY2 P3_3
void INT0_ROUTING() interrupt 0
{	EA	= 0; // 关掉所有中断 防止出错
	
    while(KEY2 == 1);
    Delay_ms(10);
    while(KEY2 == 1);

	EA	= 1; // 打开所有中断  
}
#endif
//================================================================================================= 
//                                   0ooo
//                          ooo0     (   ) 
//                          (   )     ) /
//                           \ (     (_/
//                            \_) 
//================================================================================================= 