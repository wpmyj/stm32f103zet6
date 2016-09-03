/************************ (C) COPYLEFT 2010 Leafgrass *************************

* File Name		: os_cpu_c.c 
* Author		: Librae
* Date			: 06/10/2010
* Description	: ��COS-II��STM32�ϵ���ֲ����C���Բ��֣�
*				  ���������ջ��ʼ������͹��Ӻ�����

******************************************************************************/

#ifndef	__OS_CPU_H__
#define	__OS_CPU_H__

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif


/******************************************************************************
*                    ������������޹ص���������
******************************************************************************/

#define BOOLEAN unsigned char  
#define INT8U unsigned char  			/* Unsigned  8 bit quantity       */
#define INT8S signed   char 			/* Signed    8 bit quantity       */
#define INT16U unsigned short 		/* Unsigned 16 bit quantity       */
#define INT16S signed   short 		/* Signed   16 bit quantity       */
#define INT32U unsigned int   		/* Unsigned 32 bit quantity       */
#define INT32Ssigned   int   			/* Signed   32 bit quantity       */
#define FP32 float          			/* Single precision floating point*/
#define FP64 double         			/* Double precision floating point*/

//STM32��32λλ���,����OS_STK��OS_CPU_SR��Ӧ��Ϊ32λ��������
#define   OS_STK     int   			/* Each stack entry is 32-bit wide*/
#define   OS_CPU_SR  unsigned int 		/* Define size of CPU status register*/
//STM32��32λλ���,����OS_STK��OS_CPU_SR��Ӧ��Ϊ32λ��������

/* 
*******************************************************************************
*                             Cortex M3
*                     Critical Section Management
*******************************************************************************
*/


/*
*******************************************************************************
*                          ARM Miscellaneous
*******************************************************************************
*/


//����ջ����������.
//CM3��,ջ���ɸߵ�ַ��͵�ַ������,����OS_STK_GROWTH����Ϊ1
#define  OS_STK_GROWTH        1      /* Stack grows from HIGH to LOW memory on ARM    */
//�����л���,�ɻ��ʵ��.
#define  OS_TASK_SW()         OSCtxSw()

/*
*******************************************************************************
*                               PROTOTYPES
*                           (see OS_CPU_A.ASM)
*******************************************************************************
*/
//OS_CRITICAL_METHOD = 1 :ֱ��ʹ�ô������Ŀ����ж�ָ����ʵ�ֺ� 
//OS_CRITICAL_METHOD = 2 :���ö�ջ����ͻָ�CPU��״̬ 
//OS_CRITICAL_METHOD = 3 :���ñ�������չ���ܻ�ó���״̬�֣������ھֲ�����cpu_sr

#define  OS_CRITICAL_METHOD   3	 	//�����ٽ�εķ���

#if OS_CRITICAL_METHOD == 3

#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}

#endif

void       OSCtxSw(void);
void       OSIntCtxSw(void);
void       OSStartHighRdy(void);
void       OSPendSV(void);

#if OS_CRITICAL_METHOD == 3u                      /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#endif
OS_CPU_EXT INT32U OSInterrputSum;

#endif

/************************ (C) COPYLEFT 2010 Leafgrass ************************/
