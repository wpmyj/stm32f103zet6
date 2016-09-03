//================================================================================================
// 文件名称: GUI.C 
// 芯片类型: W78E516B                                            
// 开发软件: MedWin V3, Windows XP2 
// 开发时间: 2009年09月08日                                                               
// 程序功能: 液晶控制器GUI 
// 编写人员: 崔超                                                                       
// 联系方式: 13686036830  cuichao@xrd-lcd.com   
//================================================================================================ 
 
//#include "Includes.h"
#include "Chinese.h"
#include "ASCII.h"


#if 0
//------------------------------------------------------------------------------------------

/*
-------------------------------------------------------------------------
GUI相关全局变量
-------------------------------------------------------------------------
*/
INT8U  GUIEnFont = En_8x16;                //英文字体
INT8U  GUITextMode = GUI_TEXTMODE_NORMAL;  //显示模式

INT8U Char_XSIZE;   //英文字体X宽度
INT8U Char_YSIZE;   //英文字体Y宽度




/*
*****************************************************************************
* Display_Chinese - 指定位置显示一个16x16的汉字
* DESCRIPTION: -
*
* @Param x0:X轴坐标0--(192-16)
* @Param y0:Y轴坐标0--(8-2)
* @Param UniCode:汉字内码
* @Return :
* ----
*****************************************************************************
*/
void Display_Chinese(INT16U UniCode, INT8U x0, INT8U y0)
{
  INT16U CodeID;
  INT8U i, *ImgData;
  INT8U HZ_Y = y0;
  // 在字库里搜索汉字
    for(CodeID=0; CodeID < hzNum; CodeID++)
   {
        // 找到 指定汉字的 Index 后, 跳出循环
        if ( (hzIndex[2*CodeID] == UniCode/256) && (hzIndex[2*CodeID+1] == UniCode%256) )
		{
            break;
        }
		
		else if( CodeID == (hzNum-1) )
		{
			//未检索到的汉字,显示个"##"提示吧
            GUI_DispCharAt('#',x0,y0);
            GUI_DispCharAt('#',x0+Char_XSIZE,y0);
            return;
        }
    }
//----------------------------------
    switch (GUITextMode) {
        case GUI_TEXTMODE_NORMAL :
//-------------------------------------------------------------------------
            // 写汉字 (一个汉字 32 个字节,  显示为2行 * 16列)
            	ImgData = hzdot+CodeID*32;
            for(i=0; i<16; i++){

                Display_Locate(*ImgData++, x0, HZ_Y);
                Display_Locate(*ImgData++, x0+1, HZ_Y);
                HZ_Y++;
            }
       
//-------------------------------------------------------------------------
             break;
        case GUI_TEXTMODE_REVERSE :
//-------------------------------------------------------------------------
        //-------------------------------------------------------------------------
            // 写汉字 (一个汉字 32 个字节,  显示为2行 * 16列)
            	ImgData = hzdot+CodeID*32;

            for(i=0; i<16; i++)
	    {

                Display_Locate(*ImgData++^0XFF, x0, HZ_Y);
                Display_Locate(*ImgData++^0XFF, x0+1, HZ_Y);
                HZ_Y++;
            }
//-------------------------------------------------------------------------
             break;

        case GUI_TEXTMODE_UNDERLINE :
//-------------------------------------------------------------------------
 			// 写汉字 (一个汉字 32 个字节,  显示为2行 * 16列)
            	ImgData = hzdot+CodeID*32;
            for(i=0; i<15; i++){

                Display_Locate(*ImgData++, x0, HZ_Y);
                Display_Locate(*ImgData++, x0+1, HZ_Y);
                HZ_Y++;
            }
             //最后一样全部显示              
                Display_Locate(0XFF, x0, HZ_Y);             
                Display_Locate(0XFF, x0+1, HZ_Y);

//-------------------------------------------------------------------------
             break;
        default :
             break;
    }
}


/*
*****************************************************************************
* Display_ASCII - 显示一个ASCII
* DESCRIPTION: -
*
* @Param X:X轴坐标 0--192  (注意边界)
* @Param Y:Y轴坐标 0-- 7   (注意边界)
* @Param Char:ASCII码
* @Return :
* ----
*****************************************************************************
*/
void Display_ASCII(INT8U Char, INT8U X, INT8U Y)
{
    INT8U i, ImgData;
    INT8U HZ_Y = Y;
    if(GUIEnFont == En_5x8){        
        
        for(i = 0; i < En_5x8_YSIZE; i++){
            ImgData = chardot_5x8[i+(Char-0x20)*8];
            Display_Locate(ImgData, X, HZ_Y);
            HZ_Y++;
		}
    } else    {
        for(i=0;i<En_8x16_YSIZE;i++){
            ImgData = chardot_8x16[i+(Char-0x20)*16];
            Display_Locate(ImgData, X, HZ_Y);
            HZ_Y++;
        }
 
      

   }
}




/*
*****************************************************************************
* Display_InvASCII - 反显示ASCII
* DESCRIPTION: -
*
* @Param X:X轴坐标  0--191
* @Param Y:Y轴坐标  0--7
* @Param Char:ASCII码
* @Return :
* ----
*****************************************************************************
*/
void Display_InvASCII(INT8U Char, INT8U X, INT8U Y)
{

    INT8U i, ImgData;
    INT8U HZ_Y = Y;
    if(GUIEnFont == En_5x8){        
        
        for(i = 0; i < En_5x8_YSIZE; i++){
            ImgData = chardot_5x8[i+(Char-0x20)*8]^0xff;
            Display_Locate(ImgData, X, HZ_Y);
            HZ_Y++;
		}
    } else {
        for(i=0;i<En_8x16_YSIZE;i++){
            ImgData = chardot_8x16[i+(Char-0x20)*16]^0xff;
            Display_Locate(ImgData, X, HZ_Y);
            HZ_Y++;
        }
 
      

   }
}

/*
*****************************************************************************
* Display_ASCII_UnderLine - 显示一个带有下划线的ASCII
* DESCRIPTION: -
*
* @Param X:X轴坐标
* @Param Y:Y轴坐标
* @Param Char:ASCII码
* @Return :
* ----
*****************************************************************************
*/
void Display_ASCII_UnderLine(INT8U Char, INT8U X, INT8U Y)
{
    INT8U i, ImgData;
    INT8U HZ_Y = Y;
    if(GUIEnFont == En_5x8){        
        
        for(i = 0; i < En_5x8_YSIZE-1; i++){
            ImgData = chardot_5x8[i+(Char-0x20)*8];
            Display_Locate(ImgData, X, HZ_Y);
            HZ_Y++;
		}
		Display_Locate(0xff, X, HZ_Y);
    } else {
        for(i=0;i<En_8x16_YSIZE-1;i++){
            ImgData = chardot_8x16[i+(Char-0x20)*16];
            Display_Locate(ImgData, X, HZ_Y);
            HZ_Y++;
        }
 		Display_Locate(0xff, X, HZ_Y);
   }
}



/*
*****************************************************************************
* GUI_SetTextMode - 设置文字显示模式
* DESCRIPTION: -
*
* @Param TextMode:模式代码
* @Return :模式代码
* ----
*****************************************************************************
*/

INT8U GUI_SetTextMode(INT8U TextMode)
{
    GUITextMode = TextMode;
    return GUITextMode;
}

/*
*****************************************************************************
* GUI_SetEnFont - 设置显示的英文字体
* DESCRIPTION: -
* 目前支持两种字体8x16 5x8
* @Param EnFont:字体代码
* @Return :
* ----
*****************************************************************************
*/
void GUI_SetEnFont(INT8U EnFont)
{
  if (EnFont == En_5x8){
    GUIEnFont = En_5x8;
    Char_XSIZE = En_5x8_XSIZE;
    Char_YSIZE = En_5x8_YSIZE;
  } else {
    GUIEnFont = En_8x16;
    Char_XSIZE = En_8x16_XSIZE;
    Char_YSIZE = En_8x16_YSIZE;

  }

}
/*
----------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------
*/
void GUI_Delay(INT16U Period)
{
    INT8U j;
    for (;  Period>0 ; Period--) 
    {
        for (j = 0; j < 200; j++) ;
    }
}
/*
*****************************************************************************
* GUI_DispCharAt - 指定位置显示一个ASCII码
* DESCRIPTION: - 字体使用是系统设定的字体
*
* @Param x:X轴坐标
* @Param y:Y轴坐标
* @Param c:ASCII码
* @Return :
* ----
*****************************************************************************
*/
void GUI_DispCharAt(INT8U c, INT8U x, INT8U y)
{
    switch (GUITextMode) {
        case GUI_TEXTMODE_NORMAL :
             Display_ASCII(c, x, y);
             break;
        case GUI_TEXTMODE_REVERSE :
             Display_InvASCII(c, x, y);
             break;
        case GUI_TEXTMODE_UNDERLINE :
             Display_ASCII_UnderLine(c, x, y);
             break;
        default :
             break;
    }
}

/*
*****************************************************************************
* GUI_Init - 初始化GUI显示
* DESCRIPTION: -
*
* @Param void:
* @Return :
* ----
*****************************************************************************
*/
void GUI_Init(void)
{

    GUIEnFont = En_8x16;
    GUITextMode = GUI_TEXTMODE_NORMAL;
    Char_XSIZE = En_8x16_XSIZE;
    Char_YSIZE = En_8x16_YSIZE;


}
void GUI_Clear(void)
{
	ScanScreen(0x00,0x00);
}

/*
*****************************************************************************
* GUI_DispStringAt - 指定位置显示一个字符串
* DESCRIPTION: -
* 支持中英混合 当中英混合时英文字体强制为8x16 如果单单英文 按照设定字体
* @Param x0:X轴坐标
* @Param y0:Y轴坐标
* @Param s:字符串
* @Return :
* ----
*****************************************************************************
*/

void GUI_DispStringAt(INT8U _CONST_ *s,INT8U x0,INT8U y0)
{
    INT8U i;

    i = 0;
    while(s[i]!='\0'){
        if (s[i] < 0x80) {//是ASCII
             if(s[i] == '\n'){
                    x0 = 0;
                    y0 += Char_YSIZE;
             } else {
                if (x0 > (LCD_XSIZE-1)) {//换行
                    x0 = 0;
                    y0 += Char_YSIZE;
                }
                switch (GUITextMode) {
                    case GUI_TEXTMODE_NORMAL :
                         Display_ASCII(s[i], x0, y0);
                         break;
                    case GUI_TEXTMODE_REVERSE :
                         Display_InvASCII(s[i], x0, y0);
                         break;
                    case GUI_TEXTMODE_UNDERLINE :
                         Display_ASCII_UnderLine(s[i], x0, y0);
                         break;
                    default :
                         break;
                }
                x0 += Char_XSIZE;
             }
        } else {//是中文
            if (x0 > LCD_XSIZE-2){
                x0 = 0;
                y0 += Chinese_YSIZE;
            }
            Display_Chinese(s[i]*256+s[i+1],x0,y0);//中文
            i++;
            x0 += Chinese_XSIZE;
       }
       s++;
    }

}






/*
*****************************************************************************
* GUI_DispDecAt - 显示十进制数值
* DESCRIPTION: -
* 处理长度最多5个数字(因为INT16U--->65536)
* @Param v:显示的数据
* @Param x:X轴坐标
* @Param y:Y轴坐标  XY 均是起点位置坐标 也就是数值最高位的坐标
* @Param Len:指定的显示长度1--5内
* @Return :
*
*****************************************************************************
*/
void GUI_DispDecAt(INT16U v, INT16U x, INT16U y, INT8U Len)
{
    INT8U i;
    INT8U CharBuf[5];
    INT8U HighByte;

    HighByte = 0;
    for(i = 0; i < 5; i++){
        CharBuf[i] = (INT8U)(v%10);
        v = v/10;
        if(CharBuf[i]){
            HighByte = i;
        }
    }
    //第0位无论如何也显示
    i = 0;
    GUI_DispCharAt(CharBuf[i]+'0',x+((Len-1)-i)*Char_XSIZE,y);
    for(i = 1; i < Len; i++){
        if(CharBuf[i]){
            GUI_DispCharAt(CharBuf[i]+'0',x+((Len-1)-i)*Char_XSIZE,y);
        }else if(i > HighByte){
            GUI_DispCharAt(' ',x+((Len-1)-i)*Char_XSIZE,y);
        }
    }

}

/*
*****************************************************************************
* GUI_DispHexAt - 显示一个数据的十六进制值
* DESCRIPTION: -
* 最大长度4个
* @Param v:数据
* @Param x:X轴坐标
* @Param y:Y轴坐标  XY均是起点坐标 也就是数据最高字节坐标
* @Param Len:长度1--4
* @Return :
*
*****************************************************************************
*/
void GUI_DispHexAt(INT32U v, INT8U x, INT8U y, INT8U Len)
{
    INT8U i;
    INT8U HexData;
    if(Len > 8){//限制范围
        Len = 8;
    }
    for(i = 0; i < Len; i++){
        HexData = v&0x0F;
        v = v >>4;
        if(HexData < 0x0A){
            GUI_DispCharAt(HexData+'0',x+Char_XSIZE*(Len-1-i),y);
        }else{
            GUI_DispCharAt(HexData-0x0A+'A',x+Char_XSIZE*(Len-1-i),y);
        }
    }
}
#endif



//================================================================================================= 
//                                   0ooo
//                          ooo0     (   ) 
//                          (   )     ) /
//                           \ (     (_/
//                            \_) 
//================================================================================================= 
