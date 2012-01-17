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

#define  PANEL                           1       /* callback function: ON_QUITTE */
#define  PANEL_Angle                     2       /* callback function: ON_ANGLE */
#define  PANEL_PUISSANCE                 3       /* callback function: ON_PUISSANCE */
#define  PANEL_FIRE                      4       /* callback function: ON_FIRE */
#define  PANEL_QUITTER                   5       /* callback function: ON_QUITTER */
#define  PANEL_CANVAS                    6
#define  PANEL_CONTROLE                  7       /* callback function: ON_CONTROLE */
#define  PANEL_SCORE                     8       /* callback function: ON_SCORE */
#define  PANEL_MENU                      9       /* callback function: ON_MENU */
#define  PANEL_TIMER                     10      /* callback function: ON_TIMER */


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
