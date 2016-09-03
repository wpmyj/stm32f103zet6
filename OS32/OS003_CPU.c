

#include "OSType.h"

/*Set system interrupt priority.
	For example, if you want to set the PendSV (14), 
	you can you use this code to the lowest priority:

	CPU_vSetSysIEPri(14,0xFF);

*/

void CPU_vSetSysIEPri(INTSYS syNum,INTSYS syPriority)
{
	UINT8 *pubSysIEPri =(UINT8*)0xE000ED18;
	if(syNum>15)
	{
		return;
	}
	pubSysIEPri[syNum] =(UINT8)syPriority;		
}

INTSYS *CPU_psyInitSP (void (*fuTask)(void *pvArg), void* pvArg,INTSYS* psySP)
{
    INTSYS *psyStk;
                   
    psyStk       = psySP;                         /* Load stack pointer                                     */
                                                  /* Registers stacked as if auto-saved on exception        */
    *(psyStk)    = (INTSYS)0x01000000L;           /* xPSR                                                   */
    *(--psyStk)  = (INTSYS)fuTask;                  /* Entry Point                                            */
    *(--psyStk)  = (INTSYS)0xFFFFFFFEL;           /* R14 (LR) (init value will cause fault if ever used)    */
    *(--psyStk)  = (INTSYS)0x12121212L;           /* R12                                                    */
    *(--psyStk)  = (INTSYS)0x03030303L;           /* R3                                                     */
    *(--psyStk)  = (INTSYS)0x02020202L;           /* R2                                                     */
    *(--psyStk)  = (INTSYS)0x01010101L;           /* R1                                                     */
    *(--psyStk)  = (INTSYS)pvArg;                 /* R0 : argument                                          */

                                               /* Remaining registers saved on process stack             */
    *(--psyStk)  = (INTSYS)0x11111111L;           /* R11                                                    */
    *(--psyStk)  = (INTSYS)0x10101010L;           /* R10                                                    */
    *(--psyStk)  = (INTSYS)0x09090909L;           /* R9                                                     */
    *(--psyStk)  = (INTSYS)0x08080808L;           /* R8                                                     */
    *(--psyStk)  = (INTSYS)0x07070707L;           /* R7                                                     */
    *(--psyStk)  = (INTSYS)0x06060606L;           /* R6                                                     */
    *(--psyStk)  = (INTSYS)0x05050505L;           /* R5                                                     */
    *(--psyStk)  = (INTSYS)0x04040404L;           /* R4                                                     */

    return (psyStk);
}



