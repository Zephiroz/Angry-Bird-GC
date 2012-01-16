#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		/* Needed if linking in external compiler; harmless otherwise */
#include <userint.h>
#include <math.h> 
#include "Angry birds.h"


//----------------------------------------------------------------------------------------------------
//DEFINE 
#define width 400
#define height 300
#define sizeCASE 20

#define pi 3.1415  
#define g 9.8
#define Nbx	width/sizeCASE
#define Nby	height/sizeCASE
#define fond VAL_YELLOW
#define Xt 10 //abscisse de la tour (en matricielle)

//----------------------------------------------------------------------------------------------------
//PROTOTYPAGE 
void DrawBird(int x, int y, int color);
void Construction(int i, int j, int coul);
void Matrice(void); 

//----------------------------------------------------------------------------------------------------
//VARIABLES GLOBALES
int posX, posY, posX0, posY0;
float V0, Vx0, Vy0, alpha, currentTIME, deltaT;
int color; 
float Yt;
int tailleTOUR; 

int Mat[Nbx][Nby];//l'air de jeu

//--Am�lioration
int light=0;
//int posxmouse, posymouse, left, right, key;

//----------------------------------------------------------------------------------------------------
//PROGRAMME 

static int panelHandle;

int main (int argc, char *argv[])
{

	int i, j; 
	
	if (InitCVIRTE (0, argv, 0) == 0)	/* Needed if linking in external compiler; harmless otherwise */
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Angry birds.uir", PANEL)) < 0)
		return -1;
	Cls();
	// Initialisation
	posX0=0;
	posY0=height-1-15; //- taille du cercle (carre);
	posX=posX0;
	posY=posY0;
	color = VAL_RED;
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); 
	
	// Dessin de l'arriere plan

	printf("taille de la tour :\n");
	scanf("%d", &tailleTOUR);

	for (j=0; j<Nby; j++)
	{
		for (i=0; i<Nbx; i++)
		{
			if (light==1) 
			{
				Mat[i][j]=VAL_BLACK;
			}else
				Mat [i][j]=fond;
		}
	}
	// Dessin de la tour
	
	for (i=0; i<tailleTOUR; i+=2)
	{
		if (light==1)
		{
			Mat[Xt][Nby-1-i]=VAL_WHITE;  
		}
		else
			Mat[Xt][Nby-1-i]=VAL_GREEN;  
	}
	for (i=1; i<tailleTOUR; i+=2)
	{
		if (light==1)
		{
			Mat[Xt][Nby-1-i]=VAL_WHITE;  
		}
		else
			Mat[Xt][Nby-1-i]=VAL_BLUE;  
	}

	Matrice ();
	
	// Dimentionner le canvas
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, width);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, height);
	
	// Connaitre la position de la souris sur le Canvas
	// GetRelativeMouseState (panelHandle, PANEL_CANVAS, &posxmouse, &posymouse, &left,&right,&key);
	
	DrawBird(posX, posY, color);   
	
	DisplayPanel (panelHandle);
	
	RunUserInterface ();
	return 0;
}

//----------------------------------------------------------------------------------------------------  
// Nos BOUTONS
//---------------------------------------------------------------------------------------------------- 

int CVICALLBACK ON_FIRE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			//calcule de deltaT
			Vx0=V0*cos(alpha*pi/180);
			Vy0=-V0*sin(alpha*pi/180);
			deltaT=5./(V0+1);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, deltaT);  
			currentTIME=0;
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			SetCtrlAttribute (panelHandle, PANEL_Angle, ATTR_CTRL_MODE,VAL_INDICATOR);
	        SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_CTRL_MODE,VAL_INDICATOR); 
	        SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_CTRL_MODE,VAL_INDICATOR); 

			break;
		}
	return 0;
}

//----------------------------------------------------------------------------------------------------  

int CVICALLBACK ON_QUITTER (int panel, int control, int event,
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

//----------------------------------------------------------------------------------------------------  

int CVICALLBACK ON_ANGLE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_Angle, &alpha);
			break;
		}
	return 0;
}

//----------------------------------------------------------------------------------------------------  

int CVICALLBACK ON_PUISSANCE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_PUISSANCE, &V0);
			//calcule de VoX &VoY

			

			break;
		}
	return 0;
}

//----------------------------------------------------------------------------------------------------  

int CVICALLBACK ON_QUITTE (int panel, int event, void *callbackData,
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

//----------------------------------------------------------------------------------------------------  

int CVICALLBACK ON_LIGHT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			light=1;
			break;
		}
	return 0;
}



//---------------------------------------------------------------------------------------------------- 

int CVICALLBACK ON_TIMER (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i,j,a; 
	switch (event)
		{
		case EVENT_TIMER_TICK:
	        
	        // Equations de mouvement
	        Matrice(); 
	        currentTIME=currentTIME+deltaT; 
	        posX=Vx0*currentTIME+posX0;
	        posY=Vy0*currentTIME+0.5*g*currentTIME*currentTIME+posY0;
	        i=posX/sizeCASE;
	        j=posY/sizeCASE;
	        if ((posX<=width)&&(posY<=height))
	        {
	        	if (Mat[i][j]!=fond)
	        		{
	        			/* Mat[i][j]=fond; */
	        			for (a=j; a>1; a--)
	        			{
	        				Mat[i][j]=Mat[i][j-1];
	        				Mat[i][0]=fond;
	        				j--;
	        			}
	        			
	        			Matrice();
	        			DrawBird(posX, posY, fond);
	        			
	        			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
	        			SetCtrlAttribute (panelHandle, PANEL_Angle, ATTR_CTRL_MODE,VAL_HOT);
	         	    	SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_CTRL_MODE,VAL_HOT); 
	         	    	SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_CTRL_MODE,VAL_HOT); 
	        		}
	        		else DrawBird(posX, posY, color); 
	        		
	        }
	        else
	        SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); 
	        SetCtrlAttribute (panelHandle, PANEL_Angle, ATTR_CTRL_MODE,VAL_HOT);
	        SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_CTRL_MODE,VAL_HOT); 
	        SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_CTRL_MODE,VAL_HOT); 

// Idee de collision -------------------------------------------------------------------------	        	
	        /*if ((posX<width)&&(posY<height))
	        {
	        	/*if (distance())
	        	>collision
	        	else 
	        	>pas collision 
	        	
	        	//if (distance())*/
	        	/*DrawBird(posX, posY, color);
	        	/*if (((Xt+2)*sizeCASE>=posX>=(Xt-1)*sizeCASE)&&(posY>=(Nby-tailleTOUR*sizeCASE)) );
	        	{
	        		DrawBird(posX, posY, VAL_BLACK);
					Construction(posX, posY, fond);
	        	}  */
//--------------------------------------------------------------------------------------------  	        	 
	   
			break;
		}
	return 0;
}

//--------------------------------------------------------------------------------------------   
// Nos FONCTIONS  
//--------------------------------------------------------------------------------------------   


void DrawBird(int x, int y, int coul)
{
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul); 
	CanvasDrawOval (panelHandle, PANEL_CANVAS, MakeRect(y,x,15,15), VAL_DRAW_FRAME_AND_INTERIOR); 
	
}

void Construction(int i, int j, int coul)
{
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, coul);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul); 
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(j*sizeCASE,i*sizeCASE,sizeCASE,sizeCASE), VAL_DRAW_FRAME_AND_INTERIOR); 
}

void Matrice(void)
{
	int i, j;
	for (j=0; j<Nby; j++)
	{
		for (i=0; i<Nbx; i++)
		{
			Construction(i, j, Mat [i][j]);
			
		}
	}
}	 

// Idee de collision -------------------------------------------------------------------------	  
/*int distance()
{   (posX*posX+posY*posY)
} */
//--------------------------------------------------------------------------------------------  
