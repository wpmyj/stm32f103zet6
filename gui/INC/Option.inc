;**********OPTIONS*******************************
;_RAM_STARTADDRESS  EQU   0xc000000
_ISR_STARTADDRESS   EQU   0xc7fff00 ;GCS6:64M DRAM/SDRAM
;_ISR_STARTADDRESS  EQU   0xc1fff00 ;GCS6:16M DRAM


;BUSWIDTH; 16,32
                GBLA    BUSWIDTH
BUSWIDTH	SETA    16


;"DRAM","SDRAM"
                GBLS    BDRAMTYPE
BDRAMTYPE	SETS    "SDRAM"


;This value has to be TRUE on ROM program.
;This value has to be FALSE in RAM program.
                GBLL    PLLONSTART
PLLONSTART      SETL    {TRUE}

	GBLA	PLLCLK
PLLCLK		SETA	32000000

	[	PLLCLK = 32000000	
M_DIV	EQU		24	;Fin=10MHz Fout=32MHz
P_DIV	EQU		3
S_DIV	EQU		1		
	]
;************************************************
	END