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

#define  ACCUEIL                          1       /* callback function: ON_QUITTE */
#define  ACCUEIL_NIVEAU                   2       /* control type: numeric, callback function: ON_NIVEAU */
#define  ACCUEIL_QUITTER                  3       /* control type: command, callback function: ON_QUITTER */
#define  ACCUEIL_JOUER                    4       /* control type: command, callback function: ON_JOUER */
#define  ACCUEIL_CREDITS                  5       /* control type: command, callback function: ON_CREDIT */
#define  ACCUEIL_CANVASACCUEIL            6       /* control type: canvas, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ON_CREDIT(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_JOUER(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_NIVEAU(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_QUITTE(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ON_QUITTER(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
