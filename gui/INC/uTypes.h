#ifndef	__DATA_TYPE_H
#define	__DATA_TYPE_H

#define	NULL					      0
#define	STATUS_ERR				1
#define	STATUS_OK				0

#define  FALSE                      0
#define  TRUE                       1

typedef int BOOL;
typedef int STATUS;
typedef void (*PFUNC_VOID)(void);
typedef PFUNC_VOID (*PPFUNC_VOID)(void);
	
typedef unsigned char 		U8;
typedef unsigned short 	U16;
typedef unsigned int 		U32;
typedef signed char 		S8;
typedef signed short 		S16;
typedef signed int 		S32;

typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef unsigned int		DWORD;

#define outportb(addr, data)	*((volatile BYTE *)(addr)) = (BYTE)(data)
#define inportb(addr)			*((volatile BYTE *)(addr))
#define outport(addr, data)		*((volatile U16 *)(addr)) = (U16)(data)	
#define inport(addr)			*((volatile U16 *)(addr))

#define Swap16(data)	(((data)>>8)&0xff)|(((data)<<8)&0xff00)

#endif