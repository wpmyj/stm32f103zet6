/***********************************************************************
File        : FHZK16.C
Purpose     : ºº×Ö¿â¶¨Òå
Height      : 16
***********************************************************************/



#include "GUI.H"

#ifndef GUI_FLASH
  #define GUI_FLASH
#endif

 #if 1
GUI_FLASH const GUI_FONT_MONO GUI_FHZK16_CH = {
 (void GUI_FLASH *)0x100000,
 (void GUI_FLASH *)0x100000,
 0,
 0xa1a1,                    /* FirstChar */
 0xfefe,                   /* LastChar */
 16,                     /* XSize */
 16,                     /* XDist */
 2                      /* BytesPerLine */
};
  
GUI_FLASH const GUI_FONT GUI_Font_HZK16 = {
  GUI_FONTTYPE_MONO
  ,16                /* height of font  */
  ,16                /* space of font y */
  ,1                /* magnification x */
  ,1                /* magnification y */
  ,(void GUI_FLASH *)&GUI_FHZK16_CH
};
#endif
