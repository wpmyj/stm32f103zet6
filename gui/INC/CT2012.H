#ifndef	__CT2012_H
#define	__CT2012_H

//extern U8 biaozhi[(Logo_byte+10)];   //Ҫ��ʾ��LOGO����
//extern char dis_data[300];   //��NAND�ж�����һ��������ʾ�����ݴ��ڴ�

void hand(U8 k);  //���˵���ʾ��
void clrhand(void);//���˵������

void hand_1(U8 k);//�����������ʾ��
void clrhand_1(void);//��������������

void hand_2(U8 k);//����ѡ�����ʾ��
void clrhand_2(void);//����ѡ��������

void CSK_XY(U8 k);//������ǰҪ��ʾ�������궨λ
void clrCSK(void);//����ѡ�����ʾ���������

void CS_XY(U8 k);//������ǰҪ��ʾ�������궨λ
void clrCS_XY(U8 k);//������ǰ��ʾ�����������


void wsd(void);   //��ʾ"�¶� ʪ��  �����ƶ� ����ʱ��"	
		
void disptime(void);//��ʾ����ʱ������	
void dispwsd(void);//��ʾ��ʪ������
	
void clrtime(void);//������� ʱ����ʾ���� 	
void clrtime_1(void);//����޸�����ʱ����ʾ����(�޸�ʱ��ʱ)	
void clrwsd(void);//�����ʪ����ʾ����


void menu1(void);//CT������
void menu2(void);//���ɲ���
void menu4(void);//���ݹ���
void menu5(void);//ϵͳ����
	
void menu(U8 k);//��ʾһ���Ӳ˵�

void h2001(void); //��ʾ"�����������ֳ�У����"


void wr_dface(void);//дLOGO 
    

void dface(void);	 	//��ʾLOGO	
void screen0(void);		//��ʾ��0����,�����˵�
void screen1(U8 n);	//��ʾ��1����,��CT��������,����Ϊ5A��1A
void screen2(U8 n);	//��ʾ��2����(�����������ʾ����)����Ϊ�����򲻻���	
void screen4(U8 n);	// ����Ų�ѯ����
void screen5(U8 n);	// �������ڲ�ѯ����	
void screen6(U8 n);	// ȫ��ɾ������ 
void screen7(U8 n); 	//��������ʱ�����	
void screen8(U8 n);	//�������ؽ��� 
void screenA(void);		// ��ʼ��ϵͳ����
void screen11(U8 n);	//�޸��������
void screen12(U8 n);      //��Ļ����
void DISP2_DISP3(U8 n);//��ʾ�Ȳ�ͽǲ�����(������������ѯʱ��ʾ,����Ҫ��ʾscreen2,����ʾ�Ȳ�ͽǲ�)(����Ϊ����,����ȷ���Ƿ���1%��)
void DISP2(U8 n);		// ��ʾ�Ȳ�����(DISP2_DISP3�����е�����)
void DISP3(U8 n);		// ��ʾ�ǲ�����(DISP2_DISP3�����е�����)
void dispCSK(U8 n);	//��ʾ�����������
void dispCSXZK(U8 n);	//��ʾ����ѡ��������
void dis_bianbi(U8 n); 	//��ʾ����CT��Ƚ���
void dis_zukang(U8 n); 	//��ʾ�����迹���� 		
void no_data(U8 n);		// ��ʾ������ ����������
void send_pc(void);	//����Ҫ���ص������ϵ�����  		
void disp_xh(U8 n);		// ��ʾ���		
void disp_jdt(U8 n);	// ��ʾ���Խ����� 	  
void VATX_wangge(void);	//VA���Ա����ڵ����� 
void VATX_tab(void);	//VA���Ա��� 	
void disp_VATX(U8 n);	//��ʾVA���Բ��Խ��� 			
void disp_TM_HGF(U8 n);// ��ѯʱ��ʾʱ��  		
void disp_WRONG(U8 n);// ��ʾ�����Ժ����Ϣ 
void screen_Zdata(void);//��ʾ��"1"�Ժ�Ĳ���������                      
void Zdata(void);		//��ʾ��"1"�Ժ������ 
void disp_Zdata(void);	//��ʾ��"1"�Ժ��(�м����) ����
void disp_YQJD(U8 n);	//��ʾ���������Ƚ��� 
void hand_3(U8 k);		//�����������Ƚ�����ʾ��
void clrhand_3(void);	//�����������Ƚ��������
void clr_YQJD(U8 k);	//�����������Ƚ��������ǰ��   
void disp_LWWC(U8 n);	//��ʾ��λ������		
void disp_CSD(U8 n);	//���Ե�����
void USB_DISK(U8 n); 	//�������ݵ�U�̵� 	
void SetColor(void);	//�ı�ǰ��/����ɫ
void TIAOSHI3(U8 n);	// ��ʾ�л��ĵ�ѹ����̵�����(������) 


extern void Run_gray(void);//����ʱ�ĶԱȶ��Զ���������
extern void System_Init(void);//������ʼ������
extern U8 Key_Get(void);	//ȡ����
extern void K_screen0(void);	//screen0�����µĲ���
extern void K_menu1	(void);	//menu1�����µĲ���
extern void K_menu2(void);	//menu2�����µĲ���
extern void K_menu3(void);	//menu3�����µĲ���
extern void K_menu4	(void);	//menu4�����µĲ���
extern void K_menu5(void);	//menu5�����µĲ���
extern void Pingbao(void);//	�����Ӻ���
       


const float bianbi[BB_Nb]=   //�CT�������
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


const float bianbi1[BBtest_Nb]=    //CT��Ȳ���ʱ�ı�ȼ�������
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



const   U8 Zimu_Tab[Zm_NB]=		//��ĸ����
	{
  	'A',   'B',    'C',    'D',  
	'E',    'F',     'G',   'H',  
	'I',      'J',    'K',    'L',  
	'M',   'N',   'O',    'P',  
	'Q',    'R',   'S',     'T', 
 	'U',    'V',   'W',    'X', 
 	'Y',     'Z',   '-',      '/',      
	};







const float PT_bianbi[PT_BB_Nb]=   //�PT�������
	{			
	6,10,   
	};
	

const float PT_erci[PT_EC_Nb]=   //PT���ζ��ѹ����
	{			
 	100,(100/1.73205),(100/3),    
	};

const char *PT_erci_disp[] =	//Ҫ��ʾ�Ķ��ζ��ѹ
	{			
	  "100V",
          "(100��)V",
          "(100/3)V",        
          "   ",
          "   ",  
          "   " 
          };  








const float Pt_bianbi[PTBBtest_Nb]=    //PT��Ȳ���ʱ�ı�ȼ�������
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
const char *biandiss[] ={	//PT��Ȳ���Ҫ��ʾ��100V���
	
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
 const char *biandiss[] ={	//PT��Ȳ���Ҫ��ʾ��100V���
	
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
const char *biandiss_1[] ={	//PT��Ȳ���Ҫ��ʾ��100V/~3���)
	   "(6 ��)kV/(100��)V",
	   "(10 ��)kV/(100��)V",
	   "(15.75��)kV/(100��)V",
          "(20 ��)kV/(100��)V",
          "(27.5 ��)kV/(100��)V",
          "(35 ��)kV/(100��)V",
          "(66 ��)kV/(100��)V",
          "(110 ��)kV/(100��)V",
          "(220 ��)kV/(100��)V",                
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
 const char *biandiss_1[] ={	//PT��Ȳ���Ҫ��ʾ��100V/~3���)
	   "(6 ��)kV",
	   "(10 ��)kV",
	   "(15.75��)kV",
          "(20 ��)kV",
          "(27.5 ��)kV",
          "(35 ��)kV",
          "(66 ��)kV",
          "(110 ��)kV",
          "(220 ��)kV",                
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
const char *jddis[] ={	//�ڲ�����Ҫ��ʾ�ľ���
	
	   "0.2",
          "0.5",
          "1.0",
          "0.2 S",
          "0.5 S",          
          "������",
          "   ",  
          "   " 
          };        
*/          

#endif