#ifndef __DEF_H__
#define __DEF_H__

///////////////////////////////////////////////////////////////////////////
//#define RES_TEST		//是否有测直流电阻功能(定义过则测直流电阻)		 金华送变电

#define CT12_YTJ		//是否一体机(定义过则为一体机,否则为分体机)	 广西; 金华送变电;珠海科荟

#define PT_ERR_TEST 0	//是否 有测PT误差功能(为0 则无测PT误差功能)	 广东

#define PT_BB_TEST  0	//是否 有测PT变比功能(为0 则无测PT变比功能)	 金华送变电

//#define XX_120		//是否 有测下限120%点误差测试功能(定义过则测下限120%点)  	金华送变电

//#define TEST_TiaoShi	//是否 有测试函数内部数据显示功能 (定义过则显示测试内部数据)

//#define BLUETOOTH	//是否 有蓝牙无线控制功能 (定义过则有蓝牙无线控制功能 )
///////////////////////////////////////////////////////////////////////////	

#define U32 		unsigned int
#define U16 		unsigned short
#define S32 		int
#define S16 		short int
#define U8  		unsigned char
#define S8  		char
#define TRUE 		1
#define FALSE 	0
#define OK		1
#define FAIL		0
#define STATUS_ERR	1
#define STATUS_OK	0

#define outportb(addr, data)		*((volatile BYTE *)(addr)) = (BYTE)(data)
#define inportb(addr)			*((volatile BYTE *)(addr))
#define outport(addr, data)		*((volatile U16 *)(addr)) = (U16)(data)	
#define inport(addr)			*((volatile U16 *)(addr))

#define Swap16(data)	(((data)>>8)&0xff)|(((data)<<8)&0xff00)

#define Swap32(data)	((((data)>>24)&0x000000ff)|(((data)>>16)&0x0000ff00)|(((data)<<24)&0xff000000)|(((data)<<16)&0x00ff0000))



#define	BAUD_0		9600		//串口0波特率

//#define	BAUD_USB	4800		//下载到U盘模块的波特率

#define	BAUD_0_PC	9600		//串口0波特率(PC)
//#define	BAUD_0_USB	4800		//串口0波特率(南京恒沁U盘模块)
#define	BAUD_0_USB	9600		//串口0波特率(蓝色飞舞U盘模块)

#define	BAUD_0_FZX	2400		//串口0波特率(电子负载箱)

#define	BAUD_1		9600		//串口1波特率


#define 	UART0_PC	0x01		//选择COM0_1(PC)
#define 	UART0_USB	0x02		//选择COM0_2(U盘模块)
#define 	UART0_FZX	0x03		//选择COM0_3(电子负载箱)


//////////////////////////////////////////////////////////////
//总线扩展口地址
////////////////////////////////
/*SED1335 */ 
#define SED1335_DAT     (*(volatile U8 *)0x4000000)
#define SED1335_CMD    (*(volatile U8 *)0x4000010) //用74138译码

/*74273地址 */ 
#define BIANBI_ADr    (*(volatile U8 *)0x4000002) //变比继电器控制口  用74138和7432译码
#define UART0_ADr    (*(volatile U8 *)0x4000004) //UART0选择控制口  用74138和7432译码

/*按键扫描地址 */ 
#define KEY_Adr    (*(volatile U8 *)0x4000006) //用74138和7432译码

/*读取电网频率数据地址 */ 
//#define FRE_Adr    (*(volatile U8 *)0x4000008) //用74138和7432译码

/*AD7545地址 */ 
#define AD7545_Adr    (*(volatile U16 *)0x4000008) //用74138译码  16位
/////////////////////////////////////////////////////////////////

/*AD7606地址 */ 
//#define AD7606_Adr    (*(volatile U16 *)0x4000008) //用74138译码  16位
#define AD7606_Adr    (*(volatile U16 *)0x400000E) //用74138译码  16位
/////////////////////////////////////////////////////////////////

/*VC1_VC8切换地址 */ 
#define VC1_8_Adr    (*(volatile U8 *)0x400000A) //用74138译码  8位
/////////////////////////////////////////////////////////////////

#define TP_5kHz(a)       (rPDATG = ( rPDATG&(~(1<<2)) ) | ((a&1)<<2))
#define ON_5kHz    	TP_5kHz(0)  	//5kHz开
#define OFF_5kHz   	TP_5kHz(1)	//5kHz关

////////////////////////
//RTC结构
///////////////////////
typedef struct tagTIME{
	U16 wYear;
	U8   byMonth;
	U8   byDay;
	U8   byWeekday;
	U8   byHour;
	U8   byMin;
	U8   bySec;
}TIME, *PTIME;




////////////////////
/*
 typedef  struct{		
	
	U32 	FRst:1;//：Filter Reset To Raw GPS Solution 
	U32 	KSDW:1;//快速定位 
	U32 	JM:1;//精密跟踪模式（只限 M12T）
	U32 	BL:2;		//保留
	U32 	GPS_MS:3;  //GPS工作模式  
				
				 // 111=3D  定位 
                                 // 110=2D  定位 
                                //  101=广播模式 
                                //  100=定位保持模式 
                               //   011=搜索卫星 
                               //   010=坏几何因子（DOP 大于 20） 
                               //   001=保留 
                               //   000=保留 
								
	
	U32 	DMWZ:1;	//代码位置
				
				//0=外部 
 				//1=内部 
				
	U32 	TXJG:2;	//天线检测结果
				
				// 00=OK  正常 
				// 01=OC  短路 
				// 10=UC  开路 
				// 00=NV  无效 
				
				
	U32 	WXBG:1;//可视卫星数不够
	U32 	ZDBC:1;//自动进入位置保持状态
	U32 	WZSC:1;//位置锁存
	U32 	CFZT:1;//差分状态
	U32 	LQD:1;//冷启动
	
}GPSZT,*PGPSZT;	   //GPS状态位段
*/


#define	MIMW    		8			//输入的用户密码共8位
#define	BHW    		BIANH_NB	//输入的编号共10位
#define	XHW    		XINGH_NB	//输入的型号共10位
#define	EDW    		RATING_NB	//输入的额定负荷共5位
#define	XXW    		XIAXIAN_NB	//输入的下限负荷共5位
//#define	YCW    		YICI_NB		//输入的一次电流共4位
#define	YCW    		4			//输入的一次电流共4位
#define	ECW    		1			//输入的二次电流共1位
#define	JDW    		3			//输入的精度共3位

#define	GLW    		4			//输入的功率因数共4位

#define	CSDW    		3	//输入的测试点共3位

#define	CSD_MAX  	150	//输入的测试点得的最大值

#define	FUHE_MAX  	60.0	//输入负荷的最大值



////////////////////////
//存储数据库结构
///////////////////////
//#define	Error_NB		4			//误差在数据库中占的字节数
#define	BIANH_NB	10			//编号在数据库中占的字节数
#define	XINGH_NB	10			//型号在数据库中占的字节数
#define	RATING_NB	5			//额定负荷在数据库中占的字节数
#define	XIAXIAN_NB	RATING_NB	//下限负荷在数据库中占的字节数
//#define	YICI_NB		4			//一次电流在数据库中占的字节数




//#define	DAT_NB  		((Error_NB*17)+BIANH_NB+10+1)	//数据库中每一条数据占用DAT_NB个字节
#define	DAT_NB  		sizeof(DATABASE)					//数据库中每一条数据占用DAT_NB个字节
//#define	DAT_NB  		strlen(DATABASE)					//数据库中每一条数据占用DAT_NB个字节

//#define	DAT_NB  		sizeof(State)					//数据库中每一条数据占用DAT_NB个字节

#define	MAX_DB  	500							//数据库中最多存MAX_DB条数据
#define 	DB_BUFLEN	(DAT_NB*(MAX_DB+1)) 		//dis_data数组的长度 


 typedef  struct{
 
	U8 	bianhao[BIANH_NB];
	U8 	xinghao[XINGH_NB];
	U8 	rating[RATING_NB];
	U8 	xiaxian[XIAXIAN_NB];	
	
	U16 nian;
	U8 	yue;
	U8 	ri;
	U8 	xingqi;
	U8 	shi;
	U8 	fen;
	U8 	miao;
	
	U8	jingdu;				//精度	
	
	U8 	Edd_1_state;			//额定点1	
	U8 	Edd_2_state;					
	U8 	Edd_3_state;			
	U8 	Edd_4_state;			
	U8 	Edd_5_state;			
	U8 	Edd_6_state;				

	U8 	Xxd_1_state;			//下限点1	
	U8 	Xxd_2_state;					
	U8 	Xxd_3_state;			
	U8 	Xxd_4_state;	
#ifdef XX_120   // 常规点下限有120%点				
	U8 	Xxd_5_state;
#endif	
		
	U8	csd_state;			//是否自设定点（0:常规点  /  1:自设定点）  这一条的位置必须在上一条之后,否则出错
	
	U8 	waitui_edd;			//额定点的每一点是外推还是实测？(每一bit代表一个点, 0为实测,1为外推.  如 0x30(00110000B):说明额定点的第5个点和第6个点都是外推  )	
	U8 	waitui_xxd;			//下限点的每一点是外推还是实测？(每一bit代表一个点, 0为实测,1为外推.  如 0x00(00000000B):说明下限点的4个点都是实测)	
			
		
	U8 	yicidl;				//一次电流	
	U8	ercidl;				//二次电流	
	
	U8 	hege_edd;			//额定点的每一点是否合格？(每一bit代表一个点, 0为合格,1为不合格.  如 0x05(00000101B):说明额定点的第1个点和第3个点不合格  )	
	U8 	hege_xxd;			//下限点的每一点是否合格？(每一bit代表一个点, 0为合格,1为不合格.  如 0x0F(00001111B):说明下限点的4个点都不合格)	
			

	float 	temp;			//温度					浮点数
	float 	humi;			//湿度					浮点数
	
	float 	Glys;			//功率因数				浮点数	
	
	float 	Z2_Res;			//直流电阻				浮点数
	float 	Z2_X2;			//X2						浮点数
	
	
	float 	BC_Edd_1;		//额定点1	比差 			浮点数
	float 	JC_Edd_1;			//额定点1	角差 			浮点数
	
	float 	BC_Edd_2;		//额定点2	比差 			浮点数
	float 	JC_Edd_2;			//额定点2	角差 			浮点数
	
	float 	BC_Edd_3;		//额定点3	比差 			浮点数
	float 	JC_Edd_3;			//额定点3	角差 			浮点数
	
	float 	BC_Edd_4;		//额定点4比差 				浮点数
	float 	JC_Edd_4;			//额定点4角差 				浮点数
	
	float 	BC_Edd_5;		//额定点5	比差 			浮点数
	float 	JC_Edd_5;			//额定点5角差 				浮点数
	
	float 	BC_Edd_6;		//额定点6	比差 			浮点数
	float 	JC_Edd_6;			//额定点6角差 				浮点数
	
	float 	BC_Xxd_1;		//下限点1	比差 			浮点数
	float 	JC_Xxd_1;			//下限点1	角差 			浮点数
	
	float 	BC_Xxd_2;		//下限点2	比差 			浮点数
	float 	JC_Xxd_2;			//下限点2	角差 			浮点数
	
	float 	BC_Xxd_3;		//下限点3	比差 			浮点数
	float 	JC_Xxd_3;			//下限点3	角差 			浮点数
	
	float 	BC_Xxd_4;		//下限点4比差 				浮点数
	float 	JC_Xxd_4;			//下限点4	角差 			浮点数	

#ifdef XX_120   // 常规点下限有120%点				
	float 	BC_Xxd_5;		//下限点5比差 				浮点数
	float 	JC_Xxd_5;			//下限点5	角差 			浮点数
#endif
	
}DATABASE,*PDATABASE;	   //存储数据库结构体




////////////////////
/*
 typedef  struct{	
	float 	bc_A0;			//A0比差 				浮点数
	float 	jc_A0;			//A0角差 				浮点数		
	float 	bc_B0;			//B0比差 				浮点数
	float 	jc_B0;			//B0角差 				浮点数	
	float 	bc_C0;			//C0比差 				浮点数
	float 	jc_C0;			//C0角差 				浮点数	

	float 	bc_AB;			//AB比差 				浮点数
	float 	jc_AB;			//AB角差 				浮点数		
	float 	bc_CB;			//CB比差 				浮点数
	float 	jc_CB;			//CB角差 				浮点数	
	
}ZIJIAODATA,*PZIJIAODATA;	   //自校数据库结构体
*/



#ifdef XX_120   // 常规点下限有120%点				
		#define  CSD_NUM  11  	//最多11个自设定点
#else
		#define  CSD_NUM  10  	//最多10个自设定点
#endif


 typedef  struct{
	
	U8 	Edd_1;			
	U8 	Edd_2;					
	U8 	Edd_3;			
	U8 	Edd_4;			
	U8 	Edd_5;			
	U8 	Edd_6;				

	U8 	Xxd_1;			
	U8 	Xxd_2;					
	U8 	Xxd_3;			
	U8 	Xxd_4;	

#ifdef XX_120   // 常规点下限有120%点				
	U8 	Xxd_5;	
#endif	
	
	U8 	csd_sys;		//是否自设定点（0:常规点  /  1:自设定点）
			
	
}CESHIDIAN,*PCESHIDIAN;	   //测试点数据库结构体


#define  Float_NUM  9  		//最多显示9位浮点数

#define  Float_SendNUM  6  //向电脑发送6位浮点数

/*
以下为NAND  FLASH相关
*/
#define	SIZE_1K		0x00000400
#define	SIZE_2K		0x00000800
#define	SIZE_4K		0x00001000
#define	SIZE_8K		0x00002000
#define	SIZE_16K		0x00004000
#define	SIZE_32K		0x00008000
#define	SIZE_64K		0x00010000
#define	SIZE_128K	0x00020000
#define	SIZE_256K	0x00040000
#define	SIZE_512K	0x00080000
#define	SIZE_1M		0x00100000
#define	SIZE_2M		0x00200000
#define	SIZE_4M		0x00400000
#define	SIZE_8M		0x00800000
#define	SIZE_16M	0x01000000
#define	SIZE_32M	0x02000000
#define	SIZE_64M	0x04000000
#define	SIZE_128M	0x08000000
#define	SIZE_256M	0x10000000
#define	SIZE_512M	0x20000000
#define	SIZE_1G		0x40000000
#define	SIZE_2G		0x80000000

/////////////
/*

//第一版的管脚配置

#define  X9C103_CS   (1<<4)			//数字电位器管脚
#define  X9C103_INC  (1<<2)
#define  X9C103_UD   (1<<3)

#define	X9C103En()	(rPDATF &= ~(X9C103_CS)) 
#define	X9C103Ds()	(rPDATF |=    (X9C103_CS))

#define	X9C103Dn()	(rPDATF &= ~(X9C103_UD))  
#define	X9C103Up()	(rPDATF |=    (X9C103_UD))

#define	X9C103INC_0()   (rPDATF &= ~(X9C103_INC)) 
#define	X9C103INC_1()   (rPDATF |=    (X9C103_INC))
*/
////////////
/*
//第二版的对比度调节管脚配置

#define  X9C103_CS   (1<<2)			//数字电位器管脚
#define  X9C103_INC  (1<<3)
#define  X9C103_UD   (1<<7)

#define	X9C103En()	(rPDATD &= ~(X9C103_CS)) 
#define	X9C103Ds()	(rPDATD |=    (X9C103_CS))

#define	X9C103Dn()	(rPDATC &= ~(X9C103_UD))  
#define	X9C103Up()	(rPDATC |=    (X9C103_UD))

#define	X9C103INC_0()   (rPDATD &= ~(X9C103_INC)) 
#define	X9C103INC_1()   (rPDATD |=    (X9C103_INC))
*/
//////////////////////////
////////////

//CT2012使用44B0核心板以后的对比度调节管脚配置

#define  X9C103_CS   (1<<3)			//数字电位器管脚
#define  X9C103_INC  (1<<8)
#define  X9C103_UD   (1<<2)

#define	X9C103En()	(rPDATF &= ~(X9C103_CS)) 
#define	X9C103Ds()	(rPDATF |=    (X9C103_CS))

#define	X9C103Dn()	(rPDATF &= ~(X9C103_UD))  
#define	X9C103Up()	(rPDATF |=    (X9C103_UD))

#define	X9C103INC_0()   (rPDATE &= ~(X9C103_INC)) 
#define	X9C103INC_1()   (rPDATE |=    (X9C103_INC))

//////////////////////////

////////////
/*
//电子源输出电压调节数字电位器管脚配置

#define  X9C103_Vol_CS   (1<<2)			//电子源输出电压调节数字电位器管脚
#define  X9C103_Vol_INC  (1<<3)
#define  X9C103_Vol_UD   (1<<7)

#define	X9C103_Vol_En()	(rPDATD &= ~(X9C103_Vol_CS)) 
#define	X9C103_Vol_Ds()	(rPDATD |=    (X9C103_Vol_CS))

#define	X9C103_Vol_Dn()	(rPDATC &= ~(X9C103_Vol_UD))  
#define	X9C103_Vol_Up()	(rPDATC |=    (X9C103_Vol_UD))

#define	X9C103_Vol_INC_0()   (rPDATD &= ~(X9C103_Vol_INC)) 
#define	X9C103_Vol_INC_1()   (rPDATD |=    (X9C103_Vol_INC))
*/
//////////////////////////

#define   HJJ_16	22   		//显示16*16字符的行间距(点为单位）
#define   HJJ_24	30   		//显示24*24字符的行间距(点为单位）

#define   HJJ 		HJJ_24   	//显示 的行间距(点为单位)

#define   HJJ_Zdata	23   	//显示按1后的中间数据的行间距(点为单位)

#define   HJJ_Help		20   	//操作指南的行间距(点为单位)

#define   HJJ_CD		40   	//菜单显示 的行间距(点为单位)


#define   Help_X		48   	//操作指南显示内容的起点X坐标（点为单位）
#define   Help_Y		100 	//操作指南显示内容的起点Y坐标（点为单位）

#define   S0_X  		240   	//主菜单下显示内容的起点X坐标（点为单位）
#define   CD_Y  		55   		//菜单标题Y坐标（点为单位）


#define   	BBJD_X  		208   	//变比检定界面的 X坐标（点为单位）
#define   	BBJD_Y  		210   	//变比检定界面的 Y坐标（点为单位）

#define   	PTBB_X  		160   	//PT误差测试时选择变比的 X坐标（点为单位）
#define   	PTBB_Y  		150   	//PT误差测试时选择变比的 Y坐标（点为单位）

#define   TST_JDT_Y  	420   	//自动测试进度条条Y坐标

#define   DBD_Y  		210   	//对比度条Y坐标

#define   SEND_Y  		240   	//下载数据进度条Y坐标

#define   GPS_X  		20   		//GPS定位界面的 X坐标（点为单位）
#define   GPS_Y  		70   		//GPS定位界面第一行的 Y坐标（点为单位）
#define	GPS_H    		20		//GPS定位界面的行间距

#define	Graph_X    	2				//误差表框第一列的X坐标
#define	Graph_Y    	72				//误差表框第一行的Y坐标
#define	Graph_Xend    (640-Graph_X)	//误差表框最后一列的X坐标

#define	Graph_H    	30				//误差表框的行间距
#define	Graph_Hpy    	((Graph_H-24)/2)	//误差表框的行线到字符的间距（Y方向偏移量）


#define	Graph_P    	(12*5+16)			//误差表框的第一例数据相对于Graph_X的X偏移量
#define	Graph_K    	((Graph_Xend-Graph_X-Graph_P)/6)			//误差表框的每一条数据的显示宽度


#define	Ed1    		1			//要显示误差额定点1
#define	Ed2    		(Ed1+1)		//要显示误差额定点2
#define	Ed3    		(Ed2+1)		//要显示误差额定点3
#define	Ed4    		(Ed3+1)		//要显示误差额定点4
#define	Ed5    		(Ed4+1)		//要显示误差额定点5
#define	Ed6    		(Ed5+1)		//要显示误差额定点6

#define	Xx1    		(Ed6+1)		//要显示误差下限点1
#define	Xx2    		(Xx1+1)		//要显示误差下限点2
#define	Xx3    		(Xx2+1)		//要显示误差下限点3
#define	Xx4    		(Xx3+1)		//要显示误差下限点4
#define	Xx5    		(Xx4+1)		//要显示误差下限点5


#define	Shd_X    	20				//手动测试第一例的X坐标
#define	Shd_Y    	80				//手动测试第一行的Y坐标
#define	CSSD_H    	Testms_H		//测试设定的行间距

//#define	Testms_X    	200				//测试参数设定第一列的X坐标
#define	Testms_X    	160				//测试参数设定第一列的X坐标

#define	Testms_Y    	105				//测试参数设定第一行的Y坐标
#define	Testms_H    	30				//测试参数设定的行间距

#define	Dotset_X    	320				//测试点设置第一列的X坐标
#define	Dotset_Y    	96				//测试点设置第一行的Y坐标
#define	Dotset_H    	30				//测试点设置的行间距
#define	Wzh_Dotset   	CSD_NUM		//测试点设置的共10行

#define	ZKtest_X    	340				//阻抗测试参数设置第一列的X坐标
#define	ZKtest_Y    	96				//阻抗测试参数设置第一行的Y坐标
#define	ZKtest_H    	32				//阻抗测试参数设置的行间距
#define	Wzh_ZKtest   	3				//阻抗测试参数设置的共3行

#define	BBtest_X    	340				//变比测试中间量的X坐标
#define	BBtest_Y    	96				//变比测试中间量的Y坐标
#define	BBtest_H    	32				//变比测试中间量的行间距

#define	FHXjzh_X    	340				//负荷箱校准参数设置第一列的X坐标
#define	FHXjzh_Y    	96				//负荷箱校准参数设置第一行的Y坐标
#define	FHXjzh_H    	32				//负荷箱校准参数设置的行间距
#define	Wzh_FHXjzh   	3				//负荷箱校准参数设置的共3行

#define	Bbxl_X    	520				//变比序列显示第一列的X坐标
#define	Bbxl_Y    	78				//变比序列显示第一行的Y坐标
#define	Bbxl_H    	15				//变比序列显示的行间距
#define	Bbxl_L    	(7*8)			//变比序列显示的列间距


#define	Zmk_X    	415				//字母框内容显示第一列的X坐标
#define	Zmk_Y    	170				//字母框内容显示第一行的Y坐标
#define	Zmk_H    	24				//字母框内容显示的行间距
#define	Zmk_L    	(15*2)			//字母框内容显示的列间距

#define	Zmk_Nb_H    	7				//字母框内容横向显示的字母个数
#define	Zmk_Nb_L    	4				//字母框内容纵向显示的字母个数

#define	Zm_NB    	28				//字母框数组字母个数



#if (PT_ERR_TEST!=0)   // 有测PT误差功能 	
	#define	Wzh_JD   	4				//设备检定4行
#else
	#define	Wzh_JD   	3				//设备检定3行	
#endif

#define	JYYJD_X    		260		//校验仪检定显示数据的X坐标
#define	JYYJD_Y    		160		//校验仪检定显示第一行数据的Y坐标
#define   JYYJD_H			45  		//校验仪检定显示数据的 的行间距(点为单位)

#define	Zijiaoms_X    		42	//主从机自校模式选择界面第一列的X坐标
#define	Zijiaoms_Y    		50	//主从机自校模式选择界面第一行的Y坐标
#define	Zijiaoms_H    		60	//主从机自校模式选择界面的行间距
#define   ZijiaomsH_max  	2   	//测试模式选择子菜单菜单 三相四线测试共4行

#define   Hd_r1_1_max  	9   	//测试参数设置共9行

#define   Screen0_row  	5   //主菜单Screen0共5行
//#define   Screen0_row  	4   //主菜单Screen0共4行

//#define   Menu1_row  	4   //子菜单菜单Menu1共4行


#ifdef BLUETOOTH   //有蓝牙无线控制功能	
#define   Menu1_row  	5   //子菜单菜单Menu1共4行
#else
#define   Menu1_row  	4   //子菜单菜单Menu1共4行	
#endif	

/*
#if (PT_ERR_TEST||PT_BB_TEST)   // 有测PT误差功能 或测PT变比功能	
	#define   Menu2_row  	2   //子菜单菜单Menu2共2行	
#else
	#define   Menu2_row  	1   //子菜单菜单Menu2共1行	
#endif	
*/

//////-/-/-///////-/-/-///////-/-/-///////-/-/-///////-/-/-///////-/-/-/
#if (PT_ERR_TEST||PT_BB_TEST)   // 有测PT误差 或PT变比功能	
	#if (PT_BB_TEST==0)    // 只有测PT误差功能			
		#define   Menu2_row  	2   //子菜单菜单Menu2共2行						
	#else		
		#if (PT_ERR_TEST==0)    // 只有测PT变比功能			
			#define   Menu2_row  	2   //子菜单菜单Menu2共2行			
		#else		//既有PT误差功能又有测PT变比功能			
			#define   Menu2_row  	3   //子菜单菜单Menu2共3行			
		#endif						
	#endif			
#else			//既无PT误差功能又无测PT变比功能	
	#define   Menu2_row  	1   //子菜单菜单Menu2共1行	
#endif
//////-/-/-///////-/-/-///////-/-/-///////-/-/-///////-/-/-///////-/-/-/



#define   Menu3_row  	2   //子菜单菜单Menu3共2行 


#ifdef BLUETOOTH   //有蓝牙无线控制功能	
#define   Menu4_row  	7   //子菜单菜单Menu4共6行
#else
#define   Menu4_row  	6   //子菜单菜单Menu4共6行
#endif	

#define   Menu5_row  	5   //子菜单菜单Menu5共5行

#define   Wzh_ZD  		9   //自动测试参数设置共9行
#define   Wzh_SD  		3   //自动测试参数设置共3行

#define 	FACE_PB  	7		//屏保界面
#define	Batt_ch    	1		//测电池电压的通道
#define	Batt_Vfull    	(8.10-0.3)	//电池充满电时的电压
#define	Batt_Vempty  	(7.10-0.3)	//电池无电时的电压
#define	DL_GE  		20		//电池电量图标总的格数

//#define	Batt_X    		252		//显示电池图标的X坐标
//#define	Batt_Y    		206		//显示电池图标的Y坐标

#define	Batt_NB    	10		//电池电压测Batt_NB次取平均

#define	Year_X    		280				//修改日期时间时的X坐标
#define	Month_X    	(Year_X+72)		//修改日期时间时的X坐标
#define	Day_X    		(Month_X+48)	//修改日期时间时的X坐标
#define	Weekday_X    	Year_X			//修改日期时间时的X坐标
#define	Hour_X    	Year_X			//修改日期时间时的X坐标
#define	Minute_X    	(Hour_X+36)		//修改日期时间时的X坐标
#define	Sec_X    		(Minute_X+36)	//修改日期时间时的X坐标

#define	Year_Y    		170				//修改日期时间时的Y坐标
#define	Month_Y    	Year_Y			//修改日期时间时的Y坐标
#define	Day_Y    		Year_Y			//修改日期时间时的Y坐标
#define	Weekday_Y    	(Year_Y+54)		//修改日期时间时的Y坐标
#define	Hour_Y    	(Weekday_Y+54)	//修改日期时间时的Y坐标
#define	Minute_Y    	Hour_Y			//修改日期时间时的Y坐标
#define	Sec_Y    		Hour_Y			//修改日期时间时的Y坐标

//#define	Bianhao_X    	162				//输入编号的X坐标
//#define	Bianhao_Y    	70				//输入编号的Y坐标

#define	Bianhao_X    	(Testms_X+120)		//输入编号的X坐标
#define	Bianhao_Y    	Testms_Y				//输入编号的Y坐标

#define	Bianhao_X1    	320				//按编号查询时编号的X坐标
#define	Bianhao_Y1    	180				//按编号查询时编号的Y坐标

#define	Mima_X    	350			//删除全部数据时密码的X坐标
#define	Mima_Y    	180			//删除全部数据时密码的Y坐标

#define	Mima1_X    	320			//修改用户密码时的X坐标
#define	Mima1O_Y    	156			//修改用户密码时旧的Y坐标
#define	Mima1N_Y    	216			//修改用户密码时新的Y坐标


#define	Bbcs_X    		330			//变比测试时显示第一列的X坐标
#define	Bbcs_Y    		150			//变比测试时显示第一行的Y坐标
#define	Bbcs_H    	60			//变比测试时显示的行间距



#define	DATEW    	4			//按日期查询时的日期共4字节

//#define	Ch_X    		200			//显示信道号的X坐标
//#define	Ch_Y    		20			//显示信道号的Y坐标

//#define	CH_MIN    	1			//数传模块信道号的最小值
//#define	CH_MAX    	8			//数传模块信道号的最大值

#define 	tem_tim  		30		//30秒测一次温湿度
//#define 	batt_tim  	10		//10秒测一次电池电压

#define 	PBcount_flag  		8000000		//不按按键时，进屏保模式的计数值
//#define 	POWER_OFF_flag  	80000000		//屏保模式下，自动关机计数

#define 	Count_50Hz  		600000		//测电网频率防止死机的计数器最大值
#define 	Time2_fre 		1000		//测电网频率时，定时器2送的初值换算成频率（1000Hz）

#define 	Count_GPS  		3800000		//等待GPS传出的数据时防止死机的计数器最大值

//#define 	Count_CJ  		4000000		//等待从机传回GPS卫星数时防止死机的计数器最大值
//#define 	Count_CJdata 		500000		//等待从机传回测试数据时防止死机的计数器最大值

//要读gps模块(LEA-5T)的数据,
//#define 	GPGGA			0x00	
//#define 	GPGLL			0x01
//#define 	GPGSA			0x02
//#define 	GPGSV			0x03
//#define 	GPRMC			0x04
//#define 	GPVTG			0x05


//下面为在24c02中存储的数据的地址
#define	Gray_addr   		0x02					//对比度数据在24c02中存储的地址
#define	LCD_addr   		(Gray_addr+1)		//白底/黑底状态数据在24c02中存储的地址
#define	Syn__addr   		(LCD_addr+1)			//同步方式数据在24c02中存储的地址
#define	DatnbH__addr  	(Syn__addr+1)			//当前有多少条数据在24c02中存储的地址高8位
#define	DatnbL__addr  	(DatnbH__addr+1)		//当前有多少条数据在24c02中存储的地址低8位
#define	Usermima__addr1  (DatnbL__addr+1)		//8位的系统密码在24c02中的存储地址
#define	Usermima__addr2  (Usermima__addr1+1)	//8位的用户密码在24c02中的存储地址
#define	Usermima__addr3  (Usermima__addr2+1)	//8位的用户密码在24c02中的存储地址
#define	Usermima__addr4  (Usermima__addr3+1)	//8位的用户密码在24c02中的存储地址
#define	Usermima__addr5  (Usermima__addr4+1)	//8位的用户密码在24c02中的存储地址
#define	Usermima__addr6  (Usermima__addr5+1)	//8位的用户密码在24c02中的存储地址
#define	Usermima__addr7  (Usermima__addr6+1)	//8位的用户密码在24c02中的存储地址
#define	Usermima__addr8  (Usermima__addr7+1)	//8位的用户密码在24c02中的存储地址

#define	Csd_1  	(Usermima__addr8+1)	//测试点数据在24c02中的存储地址
#define	Csd_2  	(Csd_1+1)			//测试点数据在24c02中的存储地址
#define	Csd_3  	(Csd_2+1)			//测试点数据在24c02中的存储地址
#define	Csd_4  	(Csd_3+1)			//测试点数据在24c02中的存储地址
#define	Csd_5  	(Csd_4+1)			//测试点数据在24c02中的存储地址
#define	Csd_6  	(Csd_5+1)			//测试点数据在24c02中的存储地址
#define	Csd_7  	(Csd_6+1)			//测试点数据在24c02中的存储地址
#define	Csd_8  	(Csd_7+1)			//测试点数据在24c02中的存储地址
#define	Csd_9  	(Csd_8+1)			//测试点数据在24c02中的存储地址
#define	Csd_10  	(Csd_9+1)			//测试点数据在24c02中的存储地址
#define	Csd_11  	(Csd_10+1)			//测试点数据在24c02中的存储地址

#ifdef XX_120   // 常规点下限有120%点				
	#define	Csd_12  	(Csd_11+1)			//测试点数据在24c02中的存储地址
	#define	JXDZHH__addr  	(Csd_12+1)	//误差测试时送负荷要扣除的接线电阻数据在24c02中存储的地址最高8位的存储地址
#else	
	#define	JXDZHH__addr  	(Csd_11+1)		//误差测试时送负荷要扣除的接线电阻数据在24c02中存储的地址最高8位的存储地址
#endif

#define	JXDZH__addr  		(JXDZHH__addr+1)		//误差测试时送负荷要扣除的接线电阻数据在24c02中存储的地址次高8位的存储地址
#define	JXDZL__addr  		(JXDZH__addr+1)		//误差测试时送负荷要扣除接线电阻数据在24c02中存储的地址次低8位的存储地址
#define	JXDZLL__addr  	(JXDZL__addr+1)		//误差测试时送负荷要扣除接线电阻数据在24c02中存储的地址最低8位的存储地址


#define	FHJDDZHH__addr  	(JXDZLL__addr+1)		//负荷箱检定时的接线电阻数据在24c02中存储的地址最高8位的存储地址
#define	FHJDDZH__addr  	(FHJDDZHH__addr+1)	//负荷箱检定时的接线电阻数据在24c02中存储的地址次高8位的存储地址
#define	FHJDDZL__addr  	(FHJDDZH__addr+1)	//负荷箱检定时的接线电阻数据在24c02中存储的地址次低8位的存储地址
#define	FHJDDZLL__addr  	(FHJDDZL__addr+1)		//负荷箱检定时的接线电阻数据在24c02中存储的地址最低8位的存储地址





#define	Logo_byte   		38400	//LOGO字节数

//下面为在NAND中存储的数据的块地址
//#define	Csd_addr   		9					//测试点数据在NAND中存储的数据的块地址
#define	Logo_addr   		10					//Logo数据NAND中存储的数据的块地址
#define	Logo_addr1   		(Logo_addr+1)		//Logo数据NAND中存储的数据的块地址
#define	Logo_addr2   		(Logo_addr1+1)		//Logo数据NAND中存储的数据的块地址

#define	ZijiaoData_addr  	(Logo_addr2+1)		//自校数据在NAND中存储的块地址

#define	Database_addr1  	(ZijiaoData_addr+1)	//数据库在NAND中存储的起始块地址
#define	Database_addr2  	(Database_addr1+1)	//数据库在NAND中存储的第二块地址
#define	Database_addr3  	(Database_addr2+1)	//数据库在NAND中存储的第三块地址


//#define	GRAY_GE    	50		//对比度进度条总的格数
#define	GRAY_GE    	100		//对比度进度条总的格数
#define	Best_gray    	50		//最佳的对比度数据

#define	TST_JDT_GE    	100		//自动测试进度条总的格数


#define	No_Disp 		0		//Test2Bai()函数中不显示测试过程量
#define	Zd_Disp 		1		//Test2Bai()函数中  自动测误差时显示
#define	Sd_Disp 		2		//Test2Bai()函数中  手动测误差时显示
#define	Bb_Disp 		3		//Test2Bai()函数中  变比测误差时显示
#define	Zkcs_Disp 	4		//Test2Bai()函数中  阻抗测误差时显示


#define	Bfd_YCKL		5		//CT测试时检查一次是否开路需升的百分点

#define	Bfd_YCKL_PT	2		//PT误差测试时检查一次是否开路需升的百分点



#define	BB_CK_DA	40		//PT变比测试时检查接线送的DA码(40对应0.8V左右)


//按键键码

#define KEY_ENTER    	0x0b

#define KEY_UP    		0x0c
#define KEY_DOWN   	0x0d
#define KEY_DEL    	0x0a
#define KEY_R    		0x10

#define KEY_ESC    		0x12
#define KEY_DOT  		0x2e
#define KEY_MENU	0x0f

#define KEY_F1		0x13
#define KEY_F2		0x14


//用GPS时，比差和角差分别扣除的数
/*
#define BC_GPS_A    	0.9990109	//用GPS时A0比差
#define BC_GPS_B    	0.9972507	//用GPS时B0比差
#define BC_GPS_C    	0.9955533	//用GPS时C0比差
 */
 
 /*
 #define BC_GPS_A    	1.0	//用GPS时A0比差
#define BC_GPS_B    	1.0	//用GPS时B0比差
#define BC_GPS_C    	1.0	//用GPS时C0比差
        
#define JC_GPS_A    	(0)	//用GPS时A0角差
#define JC_GPS_B    	(0)	//用GPS时B0角差
#define JC_GPS_C    	(0)	//用GPS时C0角差
*/

  
//用光纤时，比差和角差分别扣除的数
/*
#define BC_GX_A    	0.9985228	//用光纤时A0比差
#define BC_GX_B    	0.9983431	//用光纤时B0比差
#define BC_GX_C    	0.9962054	//用光纤时C0比差
*/
/*
#define BC_GX_A    	1.0	//用光纤时A0比差
#define BC_GX_B    	1.0	//用光纤时B0比差
#define BC_GX_C    	1.0	//用光纤时C0比差

#define JC_GX_A    		(0)		//用光纤时A0角差
#define JC_GX_B    		(0)		//用光纤时B0角差
#define JC_GX_C    		(0)		//用光纤时C0角差    


#define XS_a    		1	// A通道电压系数
//#define XS_b    		1	// B通道电压系数
#define XS_c    		1	// C通道电压系数



//显示主机电压时，乘的系数（隔离线圈变比）
#define GL_A0_Z    		(57.47125/2.5)	//主机A0隔离变比
#define GL_B0_Z    		(57.47125/2.5)	//主机B0隔离变比
#define GL_C0_Z    		(57.47125/2.5)	//主机C0隔离变比
#define GL_AB_Z    	(100.0/2.5)	//主机AB隔离变比
#define GL_CB_Z    		(100.0/2.5)	//主机CB隔离变比
 
 //显示从机电压时，乘的系数（隔离线圈变比）
#define GL_A0_C    	(57.47125/2.5)	//从机A0隔离变比
#define GL_B0_C    		(57.47125/2.5)	//从机B0隔离变比
#define GL_C0_C    		(57.47125/2.5)	//从机C0隔离变比
#define GL_AB_C    	(100.0/2.5)	//从机AB隔离变比
#define GL_CB_C   		(100.0/2.5)	//从机CB隔离变比
*/       
  
//#define ZC_NUM   	9		//主机向从机发送的数据的长度  用电力载波模块
//#define ZC_NUM   	10		//主机向从机发送的数据的长度  不用电力载波模块
//#define ZC_NUM   	9		//主机向HEW99测试板发送的数据的长度  
#define ZC_NUM   		4		//主机向HEW99测试板发送的数据的长度(简化,防止HEW99接收出错)

#define ZB_SEND   	0x00		//载波发送
#define ZB_RECE   		0x01		//载波接收

#define Num_Satel 	1		//最少num_Satel颗卫星才可测误差


//#define Umin			(1.0) 		//程控放大时，判断电压的门限小值
//#define Umax			(2.4) 		//程控放大时，判断电压的门限小值

//#define UzkQie		(5.0) 		//测阻抗时，要不要分压的门限值
//#define UzkQie_1	(4.8) 		//测阻抗时，要不要分压的门限
#define UzkQie		(3.4) 		//测阻抗时，要不要分压的门限值
#define UzkQie_1		(3.2) 		//测阻抗时，要不要分压的门限


//#define TEST_PER		(8) 		   //HEW99测试板发回来的 每个浮点数数据 的字节数

#define COUNT_T		(3) 		   //测试COUNT_T个轮回后结束

#define test_time  		(3)		  //等待测试结果稳定的测试次数


#define BB_Nb		(41) 		   //CT额定变比序列个数
#define BBtest_Nb		(46) 		   //CT变比测试时的变比检索序列个数

#define PT_BB_Nb		(2) 		   //PT额定变比(一次电压)序列个数
#define PT_EC_Nb		(3) 		   //PT额定二次电压序列个数

#define PTBBtest_Nb	(9) 		//PT变比测试时的变比检索序列个数


//#define VERSION_NB	("V1.0.0") 		   //版本号
//#define VERSION_NB	("V1.0.1") 		   //版本号(普通版)
//#define VERSION_NB	("V1.0.2") 		   //版本号(含PT误差测试功能版)
//#define VERSION_NB	("V1.0.3") 		   //版本号(金华带PT变比测试,直流电阻测试功能版)

//#define VERSION_NB	("V1.0.5") 		   //版本号 (将CT12里的校验仪测量的数据以#开头直接传给电子负载箱,#开头的
											//    数据不做档位判断，只修正电子负载箱里的DA码数据   注意:需要负荷箱程序配套修改)

//#define VERSION_NB	("V1.0.6")			//版本号(发送给负荷箱的总的字符串长度比原来+2   注意:需要负荷箱程序配套修改)
//#define VERSION_NB	("V1.0.7")			//版本号(在V1.0.6版基础上,校验仪检定时,显示刷新速度改慢(多次取平均),  按编号查询,按日期查询漏洞修改 )	
//#define VERSION_NB	("V1.0.8")			//版本号(在V1.0.7版基础上,1A退磁负荷  改为30欧姆)

#define VERSION_NB	("V2.0.0")			//版本号(在V1.0.8版基础上,仪器部分改为傅立叶变换方式,不再用HEW99的板子)
//#define VERSION_NB	("V2.1.0")			//版本号(在V2.0.0版基础上,增加蓝牙无线控制功能)
	
/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1210719") 	   //出厂编号(苏州华电)		
#define  	Con_x		(-0.000)		//接线电抗 (1210719)
*/
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1212004") 	   //出厂编号(广西一体机1  后给珠海科荟)	
#define  	Con_x		(-0.000)		//接线电抗 (1212004)
*/
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1212006") 	   //出厂编号	(广东带PT误差测试功能)
#define  	Con_x		(-0.005)		//接线电抗 (1212006)
*/
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1304012") 	   //出厂编号	(广东带PT误差测试功能)
#define  	Con_x		(-0.005)		//接线电抗 (1304012)
*/
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1306015") 	   //出厂编号	(金华,带PT变比测试,直流电阻测试，下限有120%功能)
#define  	Con_x		(-0.009)		//接线电抗 (1306015)
*/
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1310019") 	   //出厂编号	(广西一体机2)
#define  	Con_x		(-0.009)		//接线电抗 (1310019)
*/
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1501020") 	   //出厂编号(珠海科荟一体机2  )	
#define  	Con_x		(-0.000)		//接线电抗 (1501020)
*/
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
/*
#define SERIAL_NB		("1506001") 	   //出厂编号(北京君健宏达一体机(带蓝牙功能) )	
#define  	Con_x		(0.025)		//接线电抗 (1506001)
*/
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////

#define SERIAL_NB		("1603006") 	   //出厂编号(武汉南瑞一体机 )	
#define  	Con_x		(0.025)		//接线电抗 (1506001)

//////////////////////////////////////////////////////////////////

#define X9C_MAX		(100-1)  	//电子源的数字电位器X9C103档位最大值

#define Speed_0		0	//速度0(最慢)
#define Speed_1		1	//速度1
#define Speed_2		2	//速度2
#define Speed_3		3	//速度3(最快)

#define Speed_MAX	Speed_3	//速度最大值


#define DA_Full		0xfff	   	//电子源DA(7545)码的最大值  4095
#define DZY_MAX		120.0	//海盐电子源 升流后能输出的最大电流百分表

#define U_Dzy_MAX	138.0	//海盐电子源 能输出的最大电压


#define Up		1	//电子源升
#define Dn		0	//电子源降



/////////////////////////////////////////////////////
//#define TEST_PER	(12) 		   //连续测12个周期取平均
//#define TEST_PER	(8) 		   //连续测8个周期取平均
#define TEST_PER	(6) 		   //连续测6个周期取平均
//#define TEST_PER	(25) 		   //连续测25个周期取平均

//#define TEST_PER		(8) 		   //HEW99测试板发回来的 每个浮点数数据 的字节数


#define TEST_PER_2	(5) 		   //连续测5个周期取平均

#define TEST_fre		(5000) 	  //采样脉冲频率
#define DW_fre		(50) 	  	  //电网理论频率
#define Dot_P_Cyc		(TEST_fre/DW_fre)  //每个周期测的点数

#define N1  (TEST_PER*Dot_P_Cyc)		//AC正式测试,TEST_PER个周期，每个周期Dot_P_Cyc个点

#define N2  (8)		//DC正式测试, N2个点

#define CH7606_Biao   0	//7606 Biao通道
#define CH7606_Cha    7	//7606 Cha通道
#define CH7606_Res    1	//7606 测Res通道
#define CH7606_Fre     6	//7606 测Fre通道


#define CH409_Biao_CT0   		0	//409 Biao通道 I(CT误差和阻抗用到)
#define CH409_Biao_U_DZY   	1	//409 Biao通道U_DZY() 
#define CH409_Biao_a   		3	//409 Biao通道a(PT误差和导纳用到)

#define CH409_Cha_K   		0	//409 Cha通道i(CT误差和导纳用到)
#define CH409_Cha_PTx   	1	//409 Cha通道PTx(PT误差用到)
#define CH409_Cha_KzU_X   	2	//409 Cha通道阻抗电压(小)
#define CH409_Cha_KzU_D   	3	//409 Cha通道阻抗电压(大)


#define Pi  3.14159265358979 
#define H_J  3437.746771



#define TP_C_T1(a)        rPDATC = ( rPDATC&(~(1<<2)) ) | ((a&1)<<2)    //继电器T1控制
#define TP_C_T2(a)		rPDATC = ( rPDATC&(~(1<<3)) ) | ((a&1)<<3)   //继电器T2控制
#define TP_C_T3(a)		rPDATB = ( rPDATB&(~(1<<10)) ) | ((a&1)<<10) //继电器T3控制


	

#endif /*__DEF_H__*/

