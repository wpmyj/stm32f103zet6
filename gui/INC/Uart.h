#ifndef __UART_H__
#define __UART_H__

void Test_Uart0(void);
void Test_Uart0Fifo(void);
void Test_Uart1(void);
void Test_Uart1Fifo(void);
void Test_Uart0Range(void);
void Test_Uart1Max(void);
void Test_Uart1Status(void);
void Test_UartAFC_Rx(void);
void Test_UartAFC_Tx(void);
void Test_BDMA(void);

U8 Rxint_Uart0(void);  //串口0用中断方式接收主机发过来的数据

#endif /*__UART_H__*/

