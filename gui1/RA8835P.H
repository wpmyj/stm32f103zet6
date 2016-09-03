#ifndef _RA8835P_H
#define _RA8835P_H 


#define LcmYSize 240
#define LcmXSize 320	 	


extern void Delay_ms(INT16U ms);
extern void DrawDots(INT16S x,INT16S y,bit color);
extern void ScanScreen(INT8U data1,INT8U data2);
#endif
