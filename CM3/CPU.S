
	EXPORT	IE_vGeneratePendSV
	EXTERN  g_pstCurTask  
	EXTERN  g_pstHighTask
	EXPORT  PendSV_Handler
	EXPORT  IE_syDisable 
	EXPORT  IE_vSet
	EXPORT	IE_vGenerateFirstPendSV
NVIC_INT_CTRL   EQU     0xE000ED04                              ; Interrupt control state register
NVIC_PENDSVSET  EQU     0x10000000                              ; Value to trigger PendSV exception
NVIC_SYSPRI14   EQU     0xE000ED22
NVIC_PENDSV_PRI EQU		0xff




    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

__g_pstCurTask
        DCD     g_pstCurTask


__g_pstHighTask
        DCD     g_pstHighTask



IE_syDisable
    MRS     R0, PRIMASK 
    CPSID   I
	BX      LR

IE_vSet
	MSR     PRIMASK, R0	  
	BX      LR

IE_vGenerateFirstPendSV

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
	;CLZ 	R4, R0
    MRS     R0, PSP                                             ; PSP is process stack pointer
    CBZ     R0, OSPendSV_nosave                                 ; skip register save the first time
    SUBS    R0, R0, #0x20                                       ; save remaining regs r4-11 on process stack
    STM     R0, {R4-R11}
    LDR     R1, __g_pstCurTask;                                     ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]
	



OSPendSV_nosave
    LDR     R0, __g_pstCurTask                                     ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, __g_pstHighTask
    LDR     R2, [R1]
    STR     R2, [R0]
    LDR     R0, [R2]                                            ; R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
    LDM     R0, {R4-R11}                                        ; restore r4-11 from new process stack
    ADDS    R0, R0, #0x20
    MSR     PSP, R0                                             ; load PSP with new process SP
    ORR     LR, LR, #0x04                                       ; ensure exception return uses process stack
    ;MSR     PRIMASK, R3  ;                                               ; exception return will restore remaining context
     BX      LR

IE_vGeneratePendSV
	LDR  R0,=NVIC_SYSPRI14
	LDR  R1,=NVIC_PENDSV_PRI
	STRB R1, [R0] ;?¥•∑¢PendSV“Ï≥£
    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR

 END