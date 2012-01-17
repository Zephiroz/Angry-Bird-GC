/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2012. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MODE                            1       /* callback function: ON_EXIT */
#define  MODE_NbreOiseau                 2       /* callback function: ON_NOMBRE */
#define  MODE_Agressivite                3       /* callback function: ON_AGRESSIVE */
#define  MODE_LUMIERE                    4       /* callback function: ON_LIGHT */
#define  MODE_QUITTER                    5       /* callback function: ON_QUITTEROPTION */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK ON_AGRESSIVE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_EXIT(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_LIGHT(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_NOMBRE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_QUITTEROPTION(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
