;/*********************** (C) COPYRIGHT 2010 Libraworks *************************
;* File Name	: os_cpu_a.asm 
;* Author		: Librae 
;* Version		: V1.0
;* Date			: 06/10/2010
;* Description	: ��COS-II asm port	for STM32
;*******************************************************************************/

		;IMPORT  OSRunning               ; External references
        ;IMPORT  OSPrioCur
        ;IMPORT  OSPrioHighRdy
        ;IMPORT  OSTCBCur
        ;IMPORT  OSTCBHighRdy
        ;IMPORT  OSIntNesting
        ;IMPORT  OSIntExit	 
        ;IMPORT  OSTaskSwHook
           
        ;EXPORT  OSStartHighRdy               
       ; EXPORT  OSCtxSw
       ; EXPORT  OSIntCtxSw		
		EXPORT  OS_CPU_SR_Save                                      ; Functions declared in this file
    	EXPORT  OS_CPU_SR_Restore       
       ; EXPORT  PendSV_Handler
        	
     
NVIC_INT_CTRL   	EQU     0xE000ED04  ; �жϿ��ƼĴ���
NVIC_SYSPRI2    	EQU     0xE000ED20  ; ϵͳ���ȼ��Ĵ���(2)
NVIC_PENDSV_PRI 	EQU     0xFFFF0000  ; PendSV�жϺ�ϵͳ�����ж�
                                        ; (��Ϊ��ͣ�0xff).
NVIC_PENDSVSET  	EQU     0x10000000  ; ��������жϵ�ֵ.


		PRESERVE8 
		
		AREA    |.text|, CODE, READONLY
        THUMB 
    
           

;********************************************************************************************************
;                                   CRITICAL SECTION METHOD 3 FUNCTIONS
;
; Description: Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
;              would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
;              disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
;              disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
;              into the CPU's status register.
;
; Prototypes :     OS_CPU_SR  OS_CPU_SR_Save(void);
;                  void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
;
;
; Note(s)    : 1) These functions are used in general like this:
;
;                 void Task (void *p_arg)
;                 {
;                 #if OS_CRITICAL_METHOD == 3          /* Allocate storage for CPU status register */
;                     OS_CPU_SR  cpu_sr;
;                 #endif
;
;                          :
;                          :
;                     OS_ENTER_CRITICAL();             /* cpu_sr = OS_CPU_SaveSR();                */
;                          :
;                          :
;                     OS_EXIT_CRITICAL();              /* OS_CPU_RestoreSR(cpu_sr);                */
;                          :
;                          :
;                 }
;********************************************************************************************************

OS_CPU_SR_Save
    MRS     R0, PRIMASK  	;��ȡPRIMASK��R0,R0Ϊ����ֵ 
    CPSID   I				;PRIMASK=1,���ж�(NMI��Ӳ��FAULT������Ӧ)
    BX      LR			    ;����

OS_CPU_SR_Restore
    MSR     PRIMASK, R0	   	;��ȡR0��PRIMASK��,R0Ϊ����
    BX      LR				;����



 end  