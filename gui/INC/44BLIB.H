/***********************************************
 * NAME    : 44BLIB.H                          *
 ***********************************************/


#ifndef __44blib_h__
#define __44blib_h__

#ifdef __cplusplus
extern "C" {
#endif

#define DebugOut Uart_Printf

#define min(x1,x2) ((x1<x2)? x1:x2)
#define max(x1,x2) ((x1>x2)? x1:x2)

#define ONESEC0 (62500)	//16us resolution, max 1.04 sec
#define ONESEC1 (31250)	//32us resolution, max 2.09 sec
#define ONESEC2 (15625)	//64us resolution, max 4.19 sec
#define ONESEC3 (7812)	//128us resolution, max 8.38 sec
#define ONESEC4 (MCLK/128/(0xff+1))  //@60Mhz, 128*4us resolution, max 32.53 sec

#define NULL 0

#define EnterPWDN(clkcon) ((void (*)(int))0xe0)(clkcon)


/*44blib.c*/
void Delay(int time); //Watchdog Timer is used.

void *malloc(unsigned nbyte); 
void free(void *pt);

void Port_Init(void);
void Cache_Flush(void);
void Uart_Select(int ch);
void Uart_TxEmpty(int ch);
void Uart_Init(int mclk,int baud_0,int baud_1);
char Uart_Getch(void);
char Uart_GetKey(void);
int  Uart_GetIntNum(void);
void Uart_SendByte(int data);
void Uart_Printf(char *fmt,...);
void Uart_SendString(char *pt);
void Uart_GetString(char *string);
void Uart0_SendString(char *pt);
void Uart1_SendString(char *pt);

///////////
char Uart0_Getch(void);
char Uart0_Getch_1(void);
char Uart1_Getch(void);

void Uart0_SendByte(int data);
void Uart0_SendByte_1(int data);  //不判断回车换行，是什么就发送什么

void Uart1_SendByte(int data);
void Uart1_SendByte_1(int data);  //不判断回车换行，是什么就发送什么

void Uart0_SendString_1(char *pt);//不判断回车换行，是什么就发送什么
void Uart1_SendString_1(char *pt);//不判断回车换行，是什么就发送什么

void Uart0_Printf(char *fmt,...);//最多可发送256个字节
void Uart1_Printf(char *fmt,...);//最多可发送256个字节
void Uart1_Printf_1(char *fmt,...);  //最多可发送600个字节


void Isr_Init(void);
///////////////

void Timer_Start(int divider); //Watchdog Timer is used.
int Timer_Stop(void);          //Watchdog Timer is used.

void Led_Display(int data);

void ChangePllValue(int m,int p,int s);

void ChangeMemCon(unsigned *pMemCfg);
void EnableInterrupt(void);
void DisableInterrupt(void);

#ifdef __cplusplus
}
#endif

#endif /*__44blib_h__*/
