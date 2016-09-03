

	EXTERN  g_pstCurTask  
	EXTERN	g_ubCurPriority
	EXTERN  g_pstHighTask  
	EXTERN	g_ubHighPriority

    EXPORT  IE_syDisable                                      ; Functions declared in this file
    EXPORT  IE_vSet
	EXPORT  IE_vGenerateFirstPendSV
	EXPORT	IE_vGeneratePendSV
	EXPORT	PendSV_Handler


NVIC_INT_CTRL   EQU     0xE000ED04                              ; Interrupt control state register
NVIC_PENDSVSET  EQU     0x10000000                              ; Value to trigger PendSV exception








    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

__g_pstCurTask
        DCD     g_pstCurTask


__g_pstHighTask
        DCD     g_pstHighTask

;
;We can use it as follow:
;
;	INTSYS g_syIEFlag;
;	g_syIEFlag=IE_syDisable();

;	Protected code
;	...

;	IE_vSet(g_syIEFlag);


IE_syDisable
    MRS     R0, PRIMASK     ;
    CPSID   I
	BX      LR

IE_vSet
	MSR     PRIMASK, R0	  
	BX      LR

IE_vGenerateFirstPendSV

  	;CPSIE   I 

    MOVS    R0, #0                                              ; Set the PSP to 0 for initial context switch call
    MSR     PSP, R0

    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
		    
	BX      LR

;	Use this code to generate a PendSV interrupt, 
; 	The PendSV interrupt will be pushed forward after any other interrupt arises. 

  
    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR


PendSV_Handler
    ;MRS     R3, PRIMASK  ;             
    ;CPSID   I	  ;

    MRS     R0, PSP                                             ; PSP is process stack pointer
   ; CBZ     R0, OSPendSV_nosave                                 ; skip register save the first time

    SUBS    R0, R0, #0x20                                       ; save remaining regs r4-11 on process stack
    STM     R0, {R4-R11}

    ;LDR     R1, __g_pstCurTask;                                     ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]                                            ; R0 is SP of process being switched out

                                                                ; at this point, entire context of process has been saved
OSPendSV_nosave
    ;PUSH    {R14}                                               ; need to save LR exc_return value
    ;LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    ;BLX     R0
    ;POP     {R14}


  ; LDR     R0, __g_pstCurTask                                     ; OSTCBCur  = OSTCBHighRdy;
   ; LDR     R1, __g_pstHighTask
    LDR     R2, [R1]
    STR     R2, [R0]

    LDR     R0, [R2]                                            ; R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
    LDM     R0, {R4-R11}                                        ; restore r4-11 from new process stack
    ADDS    R0, R0, #0x20
    MSR     PSP, R0                                             ; load PSP with new process SP
    ORR     LR, LR, #0x04                                       ; ensure exception return uses process stack
    ;MSR     PRIMASK, R3  ;                                               ; exception return will restore remaining context
     BX      LR





	ALIGN
	END