#ifndef	__CT04_H
#define	__CT04_H

extern char biaozhi[38400];   //要显示的LOGO数据
extern char dis_data[300];   //串口收到的数据暂存在此数组

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
void menu6(void);//系统设置
	
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




         
         
const char *biandis[] ={		//在参数框要显示的一次电流(比5)
	
	   "25000 A",
          "20000 A",
          "15000 A",
          "10000 A",
          "8000 A",
          "7500 A",
          "6000 A",
          "5000 A",
          "4000 A",
          "3150 A",
          "3000 A",
          "2500 A",
          "2000 A",
          "1800 A",
          "1600 A",
          "1500 A",
          "1250 A",
          "1200 A",
          "1000 A",
          "800 A",
          "750 A",
          "630 A",
          "600 A",
          "500 A",
          "400 A",
          "315 A",
          "300 A",
          "250 A",
          "200 A",
          "150 A",
          "125 A",
          "120 A",
          "100 A",
          "80 A",
          "75 A",
          "60 A",
          "50 A",
          "40 A",
          "30 A",
          "25 A",
          "20 A",
          "15 A",
          "12.5A",
          "10 A",
          "8  A",
          "7.5A",
          "6  A",
          "5  A",
          "   ",
          };         
          
          
          
          
          
        
        
const char *bian1a[] ={		//在参数框要显示的一次电流(比1)
	
	   "5000 A",
          "4000 A",
          "3150 A",
          "3000 A",
          "2500 A",
          "2000 A",
          "1800 A",
          "1600 A",
          "1500 A",
          "1250 A",
          "1200 A",
          "1000 A",
          "800 A",
          "750 A",
          "630 A",
          "600 A",
          "500 A",
          "400 A",
          "315 A",
          "300 A",
          "250 A",
          "200 A",
          "150 A",
          "125 A",
          "120 A",
          "100 A",
          "80 A",
          "75 A",
          "60 A",
          "50 A",
          "40 A",
          "30 A",
          "25 A",
          "20 A",
          "15 A",
          "12.5A",
          "10 A",
          "8  A",          
          "6  A",
          "5  A",
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
          
                 
                 
                 
const char *biandiss1[] ={		//在误差结果界面要显示的5A变比
	
	   "25000A/5A",
          "20000A/5A",
          "15000A/5A",
          "10000A/5A",
          "8000A/5A",
          "7500A/5A",
          "6000A/5A",
          "5000A/5A",
          "4000A/5A",
          "3150A/5A",
          "3000A/5A",
          "2500A/5A",
          "2000A/5A",
          "1800A/5A",
          "1600A/5A",
          "1500A/5A",
          "1250A/5A",
          "1200A/5A",
          "1000A/5A",
          "800A/5A",
          "750A/5A",
          "630A/5A",
          "600A/5A",
          "500A/5A",
          "400A/5A",
          "315A/5A",
          "300A/5A",
          "250A/5A",
          "200A/5A",
          "150A/5A",
          "125A/5A",
          "120A/5A",
          "100A/5A",
          "80A/5A",
          "75A/5A",
          "60A/5A",
          "50A/5A",
          "40A/5A",
          "30A/5A",
          "25A/5A",
          "20A/5A",
          "15A/5A",
          "12.5A/5A",
          "10A/5A",
          "8A/5A",
          "7.5A/5A",
          "6A/5A",
          "5A/5A",
          "   ",
          };
          
                   



          
	
const char *biandiss[] ={	//在误差结果界面要显示的1A变比)
	
	      "5000A/1A",
          "4000A/1A",
          "3150A/1A",
          "3000A/1A",
          "2500A/1A",
          "2000A/1A",
          "1800A/1A",
          "1600A/1A",
          "1500A/1A",
          "1250A/1A",
          "1200A/1A",
          "1000A/1A",
          "800A/1A",
          "750A/1A",
          "630A/1A",
          "600A/1A",
          "500A/1A",
          "400A/1A",
          "315A/1A",
          "300A/1A",
          "250A/1A",
          "200A/1A",
          "150A/1A",
          "125A/1A",
          "120A/1A",
          "100A/1A",
          "80A/1A",
          "75A/1A",
          "60A/1A",
          "50A/1A",
          "40A/1A",
          "30A/1A",
          "25A/1A",
          "20A/1A",
          "15A/1A",
          "12.5A/1A",
          "10A/1A",
          "8A/1A",          
          "6A/1A",
          "5A/1A",
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
          
          
          
          
          
          
          
          
          
const char *biandiss2[] ={	//变比测试时,要显示的变比数
	
	   "5000",
          "4000",
          "3150",
          "3000",
          "2500",
          "2000",
          "1800",
          "1600",
          "1500",
          "1250",
          "1200",
          "1000",
          "800",
          "750",
          "630",
          "600",
          "500",
          "400",
          "360",
          "320",
          "315",
          "300",
          "250",
          "240",
          "200",
          "160",
          "150",
          "126",
          "125",
          "120",
          "100",
          "80",
          "75",
          "63",
          "60",
          "50",
          "40",
          "30",
          "25",
          "24",
          "20",
          "16",
          "15",
          "12.5",
          "10",
          "8",          
          "6",
          "5",
          "4",
          "3",
          "2.5",
          "2",
          "1.6",
          "1.5",
          "1.2",
          "1",
          "2",
          "   ",
          "   ",
          "   ",
          "   ",
          "   "         
               
          };          
          
          
          
const char *vadis[] ={	//在参数框要显示的额定负荷
	
	      "5   VA",
	      "10  VA",
	      "15  VA",
	      "20  VA",
	      "25  VA",
	      "30  VA",
	      "40  VA",
	      "50  VA",
	      "60  VA",
	      "80  VA",
	      "100 VA",
	      "     ",
	      "     ",          
          
          	};
          


const char *xvadis[] ={	//在参数框要显示的下限负荷
	
	      "1.0 VA",
	      "1.25VA",
	      "2.5 VA",
	      "3.75VA",
	      "5.0 VA",
	      "6.25VA",
	      "7.5 VA",
	      "10.0VA",
	      "12.5VA",
	      "15.0VA",
	      "20.0VA", 
	      "25.0VA",         
         	 "      ",
         	 "	     ",
         	 "      ",
       		   };

          
          
	
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
          
	
const char *glys[] ={	//在参数框要显示的功率因数
	
	   "1.0",
          "0.9",
          "0.8",
          "0.7",
          "0.6",          
          "0.5",
          "0.4",
          "0.3",
          "0.2", 
          "0.1" 
          
          };
          
          
          
const char *clfs[] ={	//在参数框要显示的测量方式
	
	   "50Hz测量",
	   "异频测量",	               
          "      ",
          "	   ",
          "      ",
          };          
          

#endif