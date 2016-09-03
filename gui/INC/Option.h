#ifndef __OPTION_H__
#define __OPTION_H__

// ************* OPTIONS **************
//#define MCLK 64000000
#define MCLK 66000000
#define	EXT_OSC_CLK	10000000


#if   (MCLK==24000000)
	#define PLL_M (16)
	#define PLL_P (3)
	#define PLL_S (1)

#elif (MCLK==32000000)
	#define PLL_M (24)
	#define PLL_P (3)
	#define PLL_S (1)

#elif (MCLK==40000000)
	#define PLL_M (32)
	#define PLL_P (3)
	#define PLL_S (1)

#elif (MCLK==48000000)
	#define PLL_M (40)
	#define PLL_P (3)
	#define PLL_S (1)

#elif (MCLK==56000000)
	#define PLL_M (48)
	#define PLL_P (3)
	#define PLL_S (1)

#elif (MCLK==64000000)
	#define PLL_M (56)
	#define PLL_P (3)
	#define PLL_S (1)

#elif (MCLK==66000000)
	#define PLL_M (58)
	#define PLL_P (3)
	#define PLL_S (1)

#endif

#define WRBUFOPT (0x8)   //write_buf_on

#define SYSCFG_0KB (0x0|WRBUFOPT)
#define SYSCFG_4KB (0x2|WRBUFOPT)
#define SYSCFG_8KB (0x6|WRBUFOPT)

#define DRAM	    1		//In case DRAM is used
#define SDRAM	    2		//In case SDRAM is used
#define BDRAMTYPE   SDRAM	//used in power.c,44blib.c

//BUSWIDTH; 16,32
#define BUSWIDTH    (16)

#define CACHECFG    SYSCFG_8KB

#define _RAM_STARTADDRESS 0xc100000

//#define _ISR_STARTADDRESS 0xc1fff00   //GCS6:16M DRAM
#define _ISR_STARTADDRESS 0xc7fff00     //GCS6:64M DRAM/SDRAM

//this code is in Feng's board

#define Non_Cache_Start	(0x2000000)
#define Non_Cache_End 	(0xc000000)


// NOTE: rom.mak,option.a have to be changed
#endif /*__OPTION_H__*/