#ifndef	__CT2012_H
#define	__CT2012_H

//extern U8 biaozhi[(Logo_byte+10)];   //要显示的LOGO数据
//extern char dis_data[300];   //从NAND中读出的一条即将显示的数据存在此

void hand(U8 k);  //主菜单显示手
void clrhand(void);//主菜单清除手

void hand_1(U8 k);//输参数界面显示手
void clrhand_1(void);//输参数界面清除手

void hand_2(U8 k);//参数选择框显示手
void clrhand_2(void);//参数选择框清除手

void CSK_XY(U8 k);//参数框当前要显示的行坐标定位
void clrCSK(void);//参数选择框显示的内容清除

void CS_XY(U8 k);//参数当前要显示的行坐标定位
void clrCS_XY(U8 k);//参数当前显示的行内容清除


void wsd(void);   //显示"温度 湿度  上下移动 日期时间"	
		
void disptime(void);//显示日期时间内容	
void dispwsd(void);//显示温湿度内容
	
void clrtime(void);//清除日期 时间显示内容 	
void clrtime_1(void);//清除修改日期时间显示内容(修改时间时)	
void clrwsd(void);//清除温湿度显示内容


void menu1(void);//CT误差测试
void menu2(void);//负荷测试
void menu4(void);//数据管理
void menu5(void);//系统设置
	
void menu(U8 k);//显示一级子菜单

void h2001(void); //显示"电流互感器现场校验仪"


void wr_dface(void);//写LOGO 
    

void dface(void);	 	//显示LOGO	
void screen0(void);		//显示第0界面,即主菜单
void screen1(U8 n);	//显示第1界面,输CT参数界面,参数为5A或1A
void screen2(U8 n);	//显示第2界面(测量及误差显示界面)参数为化整或不化整	
void screen4(U8 n);	// 按编号查询界面
void screen5(U8 n);	// 按编日期查询界面	
void screen6(U8 n);	// 全部删除界面 
void screen7(U8 n); 	//设置日期时间界面	
void screen8(U8 n);	//数据下载界面 
void screenA(void);		// 初始化系统界面
void screen11(U8 n);	//修改密码界面
void screen12(U8 n);      //屏幕调整
void DISP2_DISP3(U8 n);//显示比差和角差数据(测量结束及查询时显示,首先要显示screen2,再显示比差和角差)(参数为精度,用来确定是否有1%点)
void DISP2(U8 n);		// 显示比差数据(DISP2_DISP3函数中调用它)
void DISP3(U8 n);		// 显示角差数据(DISP2_DISP3函数中调用它)
void dispCSK(U8 n);	//显示参数框的内容
void dispCSXZK(U8 n);	//显示参数选择框的内容
void dis_bianbi(U8 n); 	//显示测试CT变比界面
void dis_zukang(U8 n); 	//显示测试阻抗界面 		
void no_data(U8 n);		// 显示无数据 或数据已满
void send_pc(void);	//传出要下载到电脑上的数据  		
void disp_xh(U8 n);		// 显示序号		
void disp_jdt(U8 n);	// 显示测试进度条 	  
void VATX_wangge(void);	//VA特性表框内的网格 
void VATX_tab(void);	//VA特性表框 	
void disp_VATX(U8 n);	//显示VA特性测试界面 			
void disp_TM_HGF(U8 n);// 查询时显示时间  		
void disp_WRONG(U8 n);// 显示出错以后的信息 
void screen_Zdata(void);//显示按"1"以后的参数名界面                      
void Zdata(void);		//显示按"1"以后的数据 
void disp_Zdata(void);	//显示按"1"以后的(中间过程) 数据
void disp_YQJD(U8 n);	//显示调仪器精度界面 
void hand_3(U8 k);		//调试仪器精度界面显示手
void clrhand_3(void);	//调试仪器精度界面清除手
void clr_YQJD(U8 k);	//调试仪器精度界面清除当前行   
void disp_LWWC(U8 n);	//显示零位误差相关		
void disp_CSD(U8 n);	//测试点设置
void USB_DISK(U8 n); 	//下载数据到U盘的 	
void SetColor(void);	//改变前景/背景色
void TIAOSHI3(U8 n);	// 显示切换的电压数或继电器数(调试用) 


extern void Run_gray(void);//开机时的对比度自动调整函数
extern void System_Init(void);//仪器初始化函数
extern U8 Key_Get(void);	//取键码
extern void K_screen0(void);	//screen0界面下的操作
extern void K_menu1	(void);	//menu1界面下的操作
extern void K_menu2(void);	//menu2界面下的操作
extern void K_menu3(void);	//menu3界面下的操作
extern void K_menu4	(void);	//menu4界面下的操作
extern void K_menu5(void);	//menu5界面下的操作
extern void Pingbao(void);//	屏保子函数
       


const float bianbi[BB_Nb]=   //额定CT变比序列
	{			
	    5000,4000,3150,3000, //4
	    2500,2000,1800,1600, //4
	    1500,1250,1200,1000, //4
	     800, 750, 630, 600,	//4
	     500, 400, 315, 300,	//4
	     250, 200, 150, 125,	//4
	     120, 100,  80,  75,	//4
	      60,  50,  40,  30,		//4
	      25,  20,  15,  12,		//4
	      10,   8, 7.5,   6,		//4
	       5,        			//1   
	};


const float bianbi1[BBtest_Nb]=    //CT变比测试时的变比检索序列
	{
		25000,20000,15000,10000,	//4
		5000,4000,3150,3000,		//4
		2500,2000,1800,1600,		//4
		1500,1250,1200,1000,		//4
		800, 750, 630, 600,			//4
		500, 400, 315, 300,			//4
		250, 200, 160, 150,			//4
		125,                 				//1
	        120, 100,  80,  75,			//4
	        60,  50,  40,  30,			//4
	        25,  20,  15,  12,			//4
	        10,   8, 7.5,   6,				//4
	        5,          					//1   
	};



const   U8 Zimu_Tab[Zm_NB]=		//字母序列
	{
  	'A',   'B',    'C',    'D',  
	'E',    'F',     'G',   'H',  
	'I',      'J',    'K',    'L',  
	'M',   'N',   'O',    'P',  
	'Q',    'R',   'S',     'T', 
 	'U',    'V',   'W',    'X', 
 	'Y',     'Z',   '-',      '/',      
	};







const float PT_bianbi[PT_BB_Nb]=   //额定PT变比序列
	{			
	6,10,   
	};
	

const float PT_erci[PT_EC_Nb]=   //PT二次额定电压序列
	{			
 	100,(100/1.73205),(100/3),    
	};

const char *PT_erci_disp[] =	//要显示的二次额定电压
	{			
	  "100V",
          "(100ㄌ)V",
          "(100/3)V",        
          "   ",
          "   ",  
          "   " 
          };  








const float Pt_bianbi[PTBBtest_Nb]=    //PT变比测试时的变比检索序列
	{
	60,
	100,
	157.5,
	200,	
	275,
	350,
	660,
	1100,		
	2200
	};
/*
const char *biandiss[] ={	//PT变比测试要显示的100V变比
	
	   "6 kV/100V",
	   "10 kV/100V",
	   "15.75 kV/100V",
          "20 kV/100V",
          "27.5 kV/100V",
          "35 kV/100V",
          "66 kV/100V",
          "110 kV/100V",
          "220 kV/100V",  
          "   "
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          };
 */    
 const char *biandiss[] ={	//PT变比测试要显示的100V变比
	
	   "6 kV",
	   "10 kV",
	   "15.75 kV",
          "20 kV",
          "27.5 kV",
          "35 kV",
          "66 kV",
          "110 kV",
          "220 kV",  
          "   "
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          };     
                   
          
/*	
const char *biandiss_1[] ={	//PT变比测试要显示的100V/~3变比)
	   "(6 ㄌ)kV/(100ㄌ)V",
	   "(10 ㄌ)kV/(100ㄌ)V",
	   "(15.75ㄌ)kV/(100ㄌ)V",
          "(20 ㄌ)kV/(100ㄌ)V",
          "(27.5 ㄌ)kV/(100ㄌ)V",
          "(35 ㄌ)kV/(100ㄌ)V",
          "(66 ㄌ)kV/(100ㄌ)V",
          "(110 ㄌ)kV/(100ㄌ)V",
          "(220 ㄌ)kV/(100ㄌ)V",                
          "   "
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",  
          "   "        
          };
 */   
 const char *biandiss_1[] ={	//PT变比测试要显示的100V/~3变比)
	   "(6 ㄌ)kV",
	   "(10 ㄌ)kV",
	   "(15.75ㄌ)kV",
          "(20 ㄌ)kV",
          "(27.5 ㄌ)kV",
          "(35 ㄌ)kV",
          "(66 ㄌ)kV",
          "(110 ㄌ)kV",
          "(220 ㄌ)kV",                
          "   "
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",
          "   ",  
          "   "        
          };                                      
   
 /*     	
const char *jddis[] ={	//在参数框要显示的精度
	
	   "0.2",
          "0.5",
          "1.0",
          "0.2 S",
          "0.5 S",          
          "不化整",
          "   ",  
          "   " 
          };        
*/          

#endif