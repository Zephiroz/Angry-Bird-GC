#include <cvirte.h>		
#include <userint.h>
#include "credits.h"

static int credits;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((credits = LoadPanel (0, "credits.uir", CREDITS)) < 0)
		return -1;
	DisplayPanel (credits);
	RunUserInterface ();
	DiscardPanel (credits);
	return 0;
}

int CVICALLBACK ON_QUITTERCREDITS (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
