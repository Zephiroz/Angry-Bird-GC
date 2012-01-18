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

#define  PANEL                            1
#define  PANEL_Angle                      2       /* control type: scale, callback function: ON_ANGLE */
#define  PANEL_JOUER                      3       /* control type: command, callback function: ON_JOUER */
#define  PANEL_PUISSANCE                  4       /* control type: scale, callback function: ON_PUISSANCE */
#define  PANEL_FIRE                       5       /* control type: command, callback function: ON_FIRE */
#define  PANEL_QUITTER                    6       /* control type: command, callback function: ON_QUITTERJEUX */
#define  PANEL_CANVAS                     7       /* control type: canvas, callback function: (none) */
#define  PANEL_CONTROLE                   8       /* control type: command, callback function: ON_CONTROLE */
#define  PANEL_SCORE                      9       /* control type: numeric, callback function: ON_SCORE */
#define  PANEL_MENU                       10      /* control type: command, callback function: ON_MENU */
#define  PANEL_TIMER                      11      /* control type: timer, callback function: ON_TIMER */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ON_ANGLE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_CONTROLE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_FIRE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_JOUER(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_MENU(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_PUISSANCE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_QUITTERJEUX(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_SCORE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_TIMER(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
