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

#define  PANEL                           1       /* callback function: On_Panel */
#define  PANEL_CANVAS                    2       /* callback function: On_Canvas */
#define  PANEL_QUITTER                   3       /* callback function: On_Quit */
#define  PANEL_FIRE                      4       /* callback function: On_Fire */
#define  PANEL_PUISSANCE                 5       /* callback function: On_Puissance */
#define  PANEL_ANGLE                     6       /* callback function: On_Angle */
#define  PANEL_NUMERIC                   7
#define  PANEL_TEXTBOX                   8
#define  PANEL_TIMER                     9       /* callback function: On_Timer */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK On_Angle(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK On_Canvas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK On_Fire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK On_Panel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK On_Puissance(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK On_Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK On_Timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
