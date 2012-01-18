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

#define  PANEL                            1       /* callback function: ON_QUITTE */
#define  PANEL_Angle                      2       /* control type: scale, callback function: ON_ANGLE */
#define  PANEL_PUISSANCE                  3       /* control type: scale, callback function: ON_PUISSANCE */
#define  PANEL_FIRE                       4       /* control type: command, callback function: ON_FIRE */
#define  PANEL_QUITTER                    5       /* control type: command, callback function: ON_QUITTER */
#define  PANEL_CANVAS                     6       /* control type: canvas, callback function: (none) */
#define  PANEL_CONTROLE                   7       /* control type: command, callback function: ON_CONTROLE */
#define  PANEL_SCORE                      8       /* control type: numeric, callback function: ON_SCORE */
#define  PANEL_MENU                       9       /* control type: command, callback function: ON_MENU */
#define  PANEL_TIMER                      10      /* control type: timer, callback function: ON_TIMER */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ON_ANGLE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_CONTROLE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_FIRE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_MENU(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_PUISSANCE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_QUITTE(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_QUITTER(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_SCORE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_TIMER(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
