#include <cvirte.h>		/* Needed if linking in external compiler; harmless otherwise */
#include <userint.h>
#include <math.h>
#include "oiseauencolere.h"
#define WIDTH 800
#define HEIGHT 400
#define NBX 40
#define NBY 20

static int panelHandle;

int posX, posY, pos0X, pos0Y;
float v0, alpha, currentT, deltaT, v0X, v0Y;

int scorebrut,divider,score;

int MAT[NBX][NBY];

void drawbird(int x, int y, int coul);
void drawcase(int i, int j, int coul);
void drawmat(void);
int emptymat(void);

int main (int argc, char *argv[])
{
	int i,j;
	if (InitCVIRTE (0, argv, 0) == 0)	/* Needed if linking in external compiler; harmless otherwise */
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "oiseauencolere.uir", PANEL)) < 0)
		return -1;
	scorebrut=0;
	divider=0;
	score=0;
	// taille canvas
	pos0X=0;
	pos0Y=HEIGHT-1-20;
	posX=pos0X;
	posY=pos0Y;
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, WIDTH);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, HEIGHT);
	//initialisation matrice
	for (j=0;j<NBY;j++)
	{
		for (i=0;i<NBX;i++)
		{
			MAT[i][j]=VAL_WHITE;
		}
	}
	for (j=NBY-1;j>=NBY-10;j--)
	{
		MAT[28][j]=VAL_BLACK;
		MAT[29][j]=VAL_BLUE;
		MAT[30][j]=VAL_BLACK;
	}
	
	MAT[28][NBY-10]=VAL_YELLOW;
	MAT[29][NBY-10]=VAL_MAGENTA;
	MAT[30][NBY-1]=VAL_YELLOW;
	MAT[29][NBY-4]=VAL_RED;
	drawmat();
	// dessin oiseau
	drawbird(pos0X,pos0Y,VAL_RED);
	// initialisation timer
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
	// affichage paneau 
	DisplayPanel (panelHandle);
	RunUserInterface ();
	return 0;
}

int CVICALLBACK On_Panel (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
		}
	return 0;
}

int CVICALLBACK On_Fire (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			currentT=0;
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 1);
			SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 1);
			break;
		}
	return 0;
}

int CVICALLBACK On_Puissance (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_PUISSANCE, &v0);
			deltaT=10/(v0+1);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, 0.05*deltaT);
			break;																																							  
		}
	return 0;
}

int CVICALLBACK On_Quit (int panel, int control, int event,
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

int CVICALLBACK On_Timer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int posi,posj,k,l,i,j,imax,jmax;
	switch (event)
		{
		case EVENT_TIMER_TICK:
			currentT=currentT+deltaT;
			posX=v0*cos(alpha*3.141592/180)*currentT+pos0X;
			posY=-v0*sin(alpha*3.141592/180)*currentT+pos0Y+0.5*9.81*currentT*currentT;
			if((posX<WIDTH)&&(posY<HEIGHT)&&(0<=posX)&&(0<=posY))
			{
				posi=posX/20;
				posj=posY/20;
		
				switch (MAT[posi][posj])
				{
					case VAL_WHITE :
						drawmat();
						drawbird(posX,posY,VAL_RED);
						break;
					case VAL_RED :
						if ((posj<NBY-1)&&(posi<NBX-2))
						{
							imax=posi+2;
							jmax=posj+1;
							for (i=posi-2;i<=imax;i++)
							{
								for (j=posj-1;j<=jmax;j++)
								{
									MAT[i][j]=VAL_YELLOW;
									drawmat();
								}
							}
							for (i=posi-2;i<=imax;i++)
							{
								for (j=posj-1;j<=jmax;j++)
								{
									MAT[i][j]=VAL_WHITE;
									drawmat();
								}
							}
						}
						else
						{
							if(posj==NBY-1)
							{
								imax=posi+1;
								jmax=posj;
								for (j=posj-2;j<=jmax;j++)
								{
									for (i=posi-2;i<=imax;i++)
									{
										MAT[i][j]=VAL_YELLOW;
										drawmat();
									}
								}
								for (j=posj-2;j<=jmax;j++)
								{
									for (i=posi-2;i<=imax;i++)
									{
										MAT[i][j]=VAL_WHITE;
										drawmat();
									}
								}
							}
							else
							{
								imax=posi+1;
								jmax=posj+1;
								
								for (j=posj-2;j<=jmax;j++)
								{
									for (i=posi-2;i<=imax;i++)
									{
										MAT[i][j]=VAL_YELLOW;
										drawmat();
									}
								}
								for (j=posj-2;j<=jmax;j++)
								{
									for (i=posi-2;i<=imax;i++)
									{
										MAT[i][j]=VAL_WHITE;
										drawmat();
									}
								}
							}
						}
						for (l=posi-2;l<=imax;l++)
						{
							for (k=jmax;k>(jmax-posj+2);k--)
							{
								MAT[l][k]=MAT[l][k-(jmax-posj+2)];
							}
						}
						drawmat();
						SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
						SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
						SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
						score=score+2000;
						SetCtrlVal (panelHandle, PANEL_NUMERIC, score);
						break;
					case VAL_BLACK :
						MAT[posi][posj]=VAL_DK_GRAY;
						drawmat();
						SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
						SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
						SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
						break;
					case VAL_DK_GRAY :
						MAT[posi][posj]=VAL_LT_GRAY;
						drawmat();
						SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
						SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
						SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
						break;
					case VAL_LT_GRAY :
						MAT[posi][posj]=VAL_WHITE;
						drawmat();
						SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
						SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
						SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
						for (k=posj;k>0;k--)
						{
							MAT[posi][k]=MAT[posi][k-1];
						}
						drawmat();
						score=score+500;
						SetCtrlVal (panelHandle, PANEL_NUMERIC, score);
						break;
					case VAL_YELLOW :
						for (k=0;k<NBY;k++)
						{
							MAT[posi][k]=VAL_YELLOW;
						}
						drawmat();
						for (k=0;k<NBY;k++)
						{
							MAT[posi][k]=VAL_WHITE;
							drawmat();
						}
						drawmat();
						SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
						SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
						SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
						score=score+1000;
						SetCtrlVal (panelHandle, PANEL_NUMERIC, score);
						break;
					case VAL_MAGENTA :
						for (k=0;k<NBX;k++)
						{
							MAT[k][posj]=VAL_YELLOW;
						}
						drawmat();
						for (k=0;k<NBX;k++)
						{
							MAT[k][posj]=VAL_WHITE;
							drawmat();
						}
						drawmat();
						for (l=0;l<NBX;l++)
						{
							for (k=posj;k>0;k--)
							{
								MAT[l][k]=MAT[l][k-1];
							}
						}
						drawmat();
						SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
						SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
						SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
						score=score+1000;
						SetCtrlVal (panelHandle, PANEL_NUMERIC, score);
						break;
					default:
						MAT[posi][posj]=VAL_WHITE;
						drawmat();
						for (k=posj;k>0;k--)
						{
							MAT[posi][k]=MAT[posi][k-1];
						}
						drawmat();
						SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
						SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
						SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
						score=score+100;
						SetCtrlVal (panelHandle, PANEL_NUMERIC, score);
						break;
				}
			}
			else
			{
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
				SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 0);
				SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 0);
			}
			if (emptymat()==0)
			{
				ReplaceTextBoxLine (panelHandle, PANEL_TEXTBOX, 0, "Vous avez gagné!");
				SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED, 1);
				SetCtrlAttribute (panelHandle, PANEL_ANGLE, ATTR_DIMMED, 1);
			}
			break;
		}
	return 0;
}

int CVICALLBACK On_Canvas (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			break;
		}
	return 0;
}


int CVICALLBACK On_Angle (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_ANGLE, &alpha);
			break;
		}
	return 0;
}

void drawbird(int x, int y, int coul)
{
	// couleur pinceau
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, coul);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul);
	// dessin ovale
	CanvasDrawOval (panelHandle, PANEL_CANVAS, MakeRect(y,x,20,20), VAL_DRAW_FRAME_AND_INTERIOR);
}

void drawcase(int i, int j, int coul)
{
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul);
	// dessin case
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect (j*20, i*20, 20, 20), VAL_DRAW_FRAME_AND_INTERIOR);
}

void drawmat(void)
{
	int i,j;
	for (j=0;j<NBY;j++)
	{
		for (i=0;i<NBX;i++)
		{
			drawcase(i,j,MAT[i][j]);
		}
	}
}

int emptymat(void)
{
	int i,j,counter=0;
	for (j=0;j<NBY;j++)
	{
		for (i=0;i<NBX;i++)
		{
			if (MAT[i][j]!=VAL_WHITE)
			{
				counter++;
			}
		}
	}
	return counter;
}
