#include "Menu.h"
#include "Option.h"
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		/* Needed if linking in external compiler; harmless otherwise */
#include <userint.h>
#include <math.h> 
#include "Angry birds.h"
#include <stdlib.h>
#include <time.h>
#include "Acceuil.h"
#include "credits.h"
// ---------------- DEFINE -------------------------------------------------------------------------------

// Valeurs variables : ------------------------------------------------

#define Xt 10 // Abscisse de la tour (en matricielle)
#define width 700
#define height 500
#define sizeCASE 20

// Valeurs invariantes : ------------------------------------------------

#define Nbx	width/sizeCASE
#define Nby	height/sizeCASE

#define pi 3.1415  
#define g 9.8

// Type de la tour : 
#define colorBETON colorB/*colorG*/
#define colorBOIS colorV/*colorM*/

// Score :
#define VALoisN 3
#define VALoisA 5
#define VALoisE 20
#define VALbois 5
#define VALbet 10
#define VALcochon 50
// Materiau
#define MATfond 0
#define MATcoch 1
#define MATbois 2
#define MATbeton 3
// Mes fonctions aleatoires
#define Hauteur rand()%Nby
#define Largeur rand()%(Nbx-debutX)
#define PileOuFace rand()%2   
//
#define min(x,y) (x)<(y)?(x):(y)

// -------------- PROTOTYPAGE --------------------------------------------------------------------------

void DrawBird(int x, int y, int color);
void Construction(int i, int j, int coul);
void Matrice(void); 
void DrawBirds(int coul);
void DrawBack(void);
void SCOREconstruct(int bt, int bs, int co);
void SCOREoiseau(int i, int j, int k);
int MAT2Col(int mat);

void initialisationVglobales (void);  
void BitMapTypeOiseau(void); 
void DrawArrierePlan (void);
void DrawTour (void);
void DrawCOCH (void);  
void AffichageEcran (void);
void ScoreO(void);
void CalcVinit (void); 
void DesActivation (int i);
void IndicePresenceOiseau (void); 
//void PresenceTrace (void); 
void CoordonneeOiseauEnMat(int k);
int testCOLLISION (int i, int j); 
void testStopOiseau (void); 
int testCANVAS (void);
void collision (int k);

// ----------------------------------------------------------------------------------------------------
// VARIABLES GLOBALES

// Variables recuperees avec Get
int NbrO;
int typeO; 
int Niveau; 
int light; 
int trace;
float V0, alpha;
float vent;

// Variables pour Set
int score; 

// Variables normales
int posX0, posY0, debutX;
int posX[3], posY[3], posoldX[3], posoldY[3]; //pour 3 oiseaux // 
int indice[3]={0,0,0};

float vitX[3],vitY[3];
float alphas[3];
float currentTIME, deltaT;

/*float Vx0, Vy0;
float Vx01, Vy01,alpha1;
float Vx02, Vy02, alpha2;
*/

// Voir define.materiaux pour les valeurs Arbitraires
int color, colorCOCH, colorR, colorN, colorT, colorY, colorV, colorB, fond ,typeTOUR;

int Mat[Nbx][Nby];// L'aire de jeu

float Yt;
int tailleTOUR;

int scoreO;
int scoreS;
int score=0;


// ----------------------------------------------------------------------------------------------------
// PROGRAMME 

static int panelHandle;
static int mode; 
static int menu;
static int accueil;  
static int credits;

int main (int argc, char *argv[])
{
	// Declaration variables locales
	time_t date;
	srand(time(&date));

				if (InitCVIRTE (0, argv, 0) == 0)	/* Needed if linking in external compiler; harmless otherwise */
					return -1;	/* out of memory */
	
				if ((panelHandle = LoadPanel (0, "Angry birds.uir", PANEL)) < 0)
					return -1;
		
				if ((mode = LoadPanel (0, "Option.uir", MODE)) < 0)
					return -1;
	
				if ((menu = LoadPanel (0, "Menu.uir", MENU)) < 0)
					return -1;
			
				if ((accueil = LoadPanel (0, "Acceuil.uir", ACCUEIL)) < 0)
					return -1;
					
				if ((credits = LoadPanel (0, "credits.uir", CREDITS)) < 0)
					return -1;
	
	DisplayPanel (accueil);

	
	RunUserInterface ();
	return 0;
}


// --------------------------------------------------------------------------------------------   
// Nos FONCTIONS  
// --------------------------------------------------------------------------------------------   


void DrawBird(int x, int y, int coul)
{
	//SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, coul);
	//SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul); 
	//CanvasDrawOval (panelHandle, PANEL_CANVAS, MakeRect(y,x,15,15), VAL_DRAW_FRAME_AND_INTERIOR); */
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, coul, VAL_ENTIRE_OBJECT, MakeRect(y,x,sizeCASE,sizeCASE) );
	
	//GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\fond.bmp", &color); 
}

//-------------------------------

void Construction(int i, int j, int coul)
{
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, coul);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul); 
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(j*sizeCASE,i*sizeCASE,sizeCASE,sizeCASE), VAL_DRAW_FRAME_AND_INTERIOR); 
}

void DrawBack(void)
{
	int bmp;
	GetBitmapFromFile("images\\fond.bmp", &bmp);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bmp, VAL_ENTIRE_OBJECT, MakeRect(0, 0, height, width));
}
// -------------------------------

void Matrice(void)
{
	int i, j;
	if (light) DrawBack();
	for (j=0; j<Nby; j++)
	{
		for (i=0; i<Nbx; i++)
		{
			if (Mat[i][j]==MATcoch)/*Does Nothng*/;
				Construction(i, j, MAT2Col(Mat [i][j]));
		}
	}
}	 

// -------------------------------

int MAT2Col(int mat)
{
	switch(mat)
	{
		case MATfond:
			if (light) return colorT;
			else return colorN;
		case MATbeton:
			if (light) return colorBETON;
			else return colorN;
		case MATbois:
			if (light) return colorBOIS;
			else return colorN;
		case MATcoch:
			if (light) return colorCOCH;
			else return colorCOCH;		
		default:
			if (light) return colorT;
			else return colorT;
	}
}

// -------------------------------

void DrawBirds(int coul)
{
	int k;
	for(k=0; k<NbrO; k++)
	{
		if (indice[k]&&(posX[k] <= width) && (posY[k] <= height))
			DrawBird(posX[k], posY[k], coul);
	}
}

//-------------------------------   

void SCOREoiseau(int i, int j, int k) // Nombre de boule normal(3pts), Agressive(5) et explosive(10) // 
{
	scoreO=scoreO-i*VALoisN-j*VALoisA-k*VALoisE;
}

//-------------------------------  

void SCOREconstruct(int bt, int bs, int co)	  //nombre de béton, bois //score brique : beton (10) bois(5)  
{
	scoreS=scoreS+bt*VALbet+bs*VALbois+co*VALcochon;
}

//------------------------------- 

void initialisationVglobales (void)
{
	int k;
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, width);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, height);
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); 
	

	vent = 0;
	light = 1;
	V0 = 50;
	alpha = 45;
	NbrO = 1;
	trace = 0;
	typeO = 0;
	Niveau = 1;
	score=0;
	scoreO=0;
	scoreS=0;	   
	
	posX0=0;
	posY0=height-1-15;// Taille du cercle(carre);
	
	for (k=0; k<NbrO; k++)
	{
		indice[k]=1;
		posX[k]=posX0;
		posY[k]=posY0;
	}
	debutX=5;
		
	// Couleurs 
	colorN = VAL_BLACK;
	colorY = VAL_YELLOW;
	colorR = VAL_RED;
	colorT = VAL_TRANSPARENT;

	colorV = VAL_GREEN;
	colorB = VAL_BLUE;

	// Choix du fond
	fond=colorT;
	
	// Choix du cochon
	colorCOCH = colorR; 
}

//------------------------------- 

void BitMapTypeOiseau(void)
{
	switch(typeO)
	{	
		case 0:
			GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\images\\bebebird.bmp", &color);
			break;
		case 1:
			GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\images\\agressivebird.bmp", &color);
			break;
		case 2:
			GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\images\\poweredbird.bmp", &color);
			break;
	}	
}

//------------------------------- 

void DrawArrierePlan (void)
{
	int i, j;
	for (j=0; j<Nby; j++)
	{
		for (i=0; i<Nbx; i++)
		{
				Mat [i][j]=MATfond;
		}
	}	
}

//------------------------------- 

void DrawTour (void)
{
	int i, j;
	for (i=debutX; i<Nbx; i++)
	{
		if (PileOuFace==1)
		{
			tailleTOUR=Hauteur; 
			if (PileOuFace==1)
			{
				typeTOUR=MATbeton;
			}
			else
				typeTOUR=MATbois;
			for (j=0; j<tailleTOUR; j++)
			{
				Mat[i][Nby-j-1]=typeTOUR;
			}
		}
	}	
}

// -------------------------------

void DrawCOCH (void)

{
	int i, j, NbrC, NbrCp; 
	int PCx, PCy; 
	NbrCp=0;
	
	Cls(); 
	printf("Nombre de cochons :\n");
	scanf("%d", &NbrC);
	
	while(NbrCp<NbrC) 
	{
		PCy=Hauteur;
		PCx=Largeur;
		if (Mat[PCx][PCy]!=MATcoch)
		{
			for (i=PCy; i<Nby; i++)
			{
				PCy=i;
				
				if (i+1>(Nby-1))
				{
					NbrCp++;
					break;
				} 
				else 
				{
					if (Mat[PCx][i+1])
					{
						NbrCp++;
						break;
					}
				}
			}
			Mat[PCx][PCy]=MATcoch;
		}
	}   

}

// ------------------------------- 

void AffichageEcran (void)
{
	SetCtrlVal (panelHandle, PANEL_SCORE, score); 
	//CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bmp, VAL_ENTIRE_OBJECT, MakeRect(0, 0, height, width)); 
	Matrice ();
	DrawBirds(color); 
}

// -------------------------------

void ScoreO(void) // Pas complet : depend que SCOREoiseau
{
	int n, a, e;
	if (typeO==0)
	{
		n=NbrO;
		a=0;
		e=0;
	}
	if (typeO==1)
	{
		n=0;
		a=NbrO;
		e=0;
	}
	if (typeO=2)
	{
		n=0;
		a=0;
		e=NbrO;
	}
	SCOREoiseau(n, a, e);
}

//-------------------------------

void CalcVinit (void)
{
	int i;
	for (i=0; i<NbrO; i++)
	{
		alphas[i]=/*min(*/alpha+i*5;/*,90);*/ // Decalage des Oiseaux
		vitX[i]=V0*cos(alphas[i]*pi/180)-vent;
		vitY[i]=-V0*sin(alphas[i]*pi/180);

	}
}

// -------------------------------
void DesActivation (int i) // Pas complet : il manque des numerique
{	
	// panelHandle
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, i);
	SetCtrlAttribute (panelHandle, PANEL_Angle, ATTR_DIMMED,i);
	SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED,i); 
	SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_DIMMED,i);
	// Option
	SetCtrlAttribute (mode, MODE_NbreOiseau, ATTR_DIMMED,i);
	SetCtrlAttribute (mode, MODE_Agressivite, ATTR_DIMMED,i);
	SetCtrlAttribute (mode, MODE_VENT, ATTR_DIMMED,i);
	SetCtrlAttribute (mode, MODE_Trace, ATTR_DIMMED,i);
}

//-------------------------------  

void CoordonneeOiseauEnMat(int k)
{
	posX[k]=vitX[k]*currentTIME+posX0;
	posY[k]=vitY[k]*currentTIME+0.5*g*currentTIME*currentTIME+posY0;
	
}

//-------------------------------  
				  /*
int testCOLLISION (int i, int j)   //1 il y a collision 
{
	if (Mat[i][j])
		return 1;
	else 
		return 0;
} 				*/

void collision (int k) // gestion de la collision
{			 // début fonction

	int i, j, a;
	i=posX[k]/sizeCASE;
	j=posY[k]/sizeCASE;
	if (	 ((posX[k] > width) || (posY[k] > height)) )	
		{
			indice[k]=0;
		}
	else 	
		{//test collision
			if (Mat[i][j])
			{
				//disparition de la boule
				indice[k]=0;
				//incrementation du score
				if (Mat[i][j]==MATbeton)
					SCOREconstruct(1,0,0);
				if (Mat[i][j]==MATbois)
					SCOREconstruct(0,1,0);
				if (Mat[i][j]==MATcoch)
					SCOREconstruct(0,0,1);
						
				//effondrement strucuture
				for (a=j; a>1; a--)
				{
					Mat[i][j]=Mat[i][j-1];
					Mat[i][0]=MATfond;
					j--;
				}
				//DrawBack();
				Matrice();
			}
			// Deplacement structre (optionnel si tout marche)
		}
}

		
//------------------------------- 

//int testCANVAS (void)
//{
//	if (	((posX[0] <= width) || (posY[0] <= height)) ||
//			((posX[1] <= width) || (posY[1] <= height)) ||
//			((posX[2] <= width) || (posY[2] <= height))	)
//		return 1;
//	else 
//		return 0; 
//}				  

//------------------------------- 
																   /*
void testStopOiseau (void)
{
	int k;
	for (k=0; k<NbrO; k++)
	{
		if (testCOLLISION(posoldX[k]/sizeCASE, posoldY[k]/sizeCASE)=1)
		{
			posX[k]=posold[k];
			posY[k]=posold[k];
		}
		else
			CoordonneeOiseauEnMat();
		if (testCANVAS()==0)
		{	
			posX[k]=posoldX[k];
			posY[k]=posoldY[k];
		}else
		//test sur k ?
			CoordonneeOiseauEnMat();
	}
} 		   */
				
//----------------------------------------------------------------------------------------------------  
// Nos BOUTONS
//---------------------------------------------------------------------------------------------------- 


//----------- FIRE ----------------------------------------------------------------------------- 
int CVICALLBACK ON_FIRE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		
			BitMapTypeOiseau();
			
			ScoreO(); 
		
			CalcVinit ();  // Vitesse & angle initiaux de chaque oiseau
			
			deltaT=5./(V0+1);
			
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, deltaT); 
			currentTIME=0;
			
			DesActivation (1);	// (1 = activeTIMER & desactiveNUMERIC) / (0 = désactiveTIMER & desactiveNUMERIC) 

			break;
		}
	return 0;
}


//-------------- TIMER ------------------------------------------------------------------------- 

int CVICALLBACK ON_TIMER (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
		int i,j;
		int k;
		switch (event)
		{
			case EVENT_TIMER_TICK:

				// temps qui passe
				currentTIME=currentTIME+deltaT; 
					
				for (k=0;k<NbrO;k++)
				{
					
					if (indice[k])
					{
						//sauvegarde des anciennes position
						posoldX[k]=posX[k];
						posoldY[k]=posY[k];
						
						// calcul des nouvelles positions 
						CoordonneeOiseauEnMat(k);  
						
						// Dessin Oiseau
						DrawBird(posX[k], posY[k], color);
						if (trace ==1)
							DrawBird(posoldX[k], posoldY[k], VAL_WHITE);
						collision(k);
					}
				}
				//Calcule et Affichage du score
				score=scoreO+scoreS;
				SetCtrlVal (panelHandle, PANEL_SCORE, score);
			
				//Rechargement du fond
		//		DrawBack();
				
				// Rechargement structure
		//		Matrice();
				
			break;
			
		}  //fin switch actif ou pas
		return 0;
}//fin timer


// ----------- FERMER FENETRE -----------------------------------------------------------------------------   

// Quitter Acceuil (user interface)
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


// Quitter Credits (hide)
int CVICALLBACK ON_QUITTERCREDITS (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (credits);
			DisplayPanel (accueil);
			break;
	}
	return 0;
}


// Quitter panelHandle (hide)
int CVICALLBACK ON_QUITTERJEUX (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (panelHandle);
			DisplayPanel (accueil);
			break;
	}
	return 0;
}


// Quitter option de tir (hide)
int CVICALLBACK ON_QUITTEROPTION (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  HidePanel (mode);
			  DisplayPanel (panelHandle);  
			break;
		}
	return 0;
}

int CVICALLBACK ON_EXIT (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (mode);
			DisplayPanel (panelHandle);
			break;
		}
	return 0;
}


// Quitter Menu (hide)
int CVICALLBACK ON_QUITMENU (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  HidePanel (menu);
			  DisplayPanel (panelHandle);
			break;
		}
	return 0;
}

 int CVICALLBACK ON_QUMENU (int panel, int control, int event,
	void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			HidePanel (menu);
			DisplayPanel (panelHandle); 
			break;
		}
	return 0;
}

// ----------- DISPLAY PANEL -----------------------------------------------------------------------------  
 
 int CVICALLBACK ON_CONTROLE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			HidePanel (panelHandle); 
			DisplayPanel (mode);
		break;
		}
	return 0;
}
 
 int CVICALLBACK ON_MENU (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			HidePanel (panelHandle);
			DisplayPanel (menu);
			break;
		}
	return 0;
}

 int CVICALLBACK ON_JOUER (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int bmp;
	switch (event)
	{
		case EVENT_COMMIT:
			
			// Initialisation globales & Definition taille Canvas & Couleurs & timer
			initialisationVglobales ();
			
			// chargement image.bmp dans le fond du Canvas
			GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\images\\fond.bmp", &bmp); 
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bmp, VAL_ENTIRE_OBJECT, MakeRect(0, 0, height, width));  
			// chargement VAL_TRANSPARENT dans CANVAS_2
			SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, VAL_TRANSPARENT);
			SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_TRANSPARENT); 
			CanvasDrawRect (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT, VAL_DRAW_FRAME_AND_INTERIOR);  
			// Image de l'oiseau en fonction de l'oiseau
			BitMapTypeOiseau();
	
			DrawArrierePlan ();

			DrawTour ();  // Aleatoire
	
			DrawCOCH ();  // Aleatoire
	
			AffichageEcran ();
			//-----------------------------------------------
			
			DesActivation(0);
			HidePanel (accueil);
			DisplayPanel (panelHandle);
			break;
	}
	return 0;
}

 int CVICALLBACK ON_RETIRER (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int k;
	switch (event)
	{
		case EVENT_COMMIT:
			DesActivation(0); 
				for (k=0; k<NbrO; k++)
				{
					indice[k]=1;
					posX[k]=posX0;
					posY[k]=posY0;
				}
				
			break;
	}
	return 0;
}
 
 int CVICALLBACK ON_CREDIT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (accueil);
			DisplayPanel (credits);
			break;
	}
	return 0;
}

 // ----------- Get & Set CtrlVal ----------------------------------------------------------------------------- 

// GetCtrlVal
 int CVICALLBACK ON_NIVEAU (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (accueil, ACCUEIL_NIVEAU, &Niveau);
			break;
	}
	return 0;
}
 
int CVICALLBACK ON_LIGHT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   int i, j;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_LUMIERE, &light);
			DrawBack();
			//CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bmp, VAL_ENTIRE_OBJECT, MakeRect(0, 0, height, width)); // WHAT WHAT WHAT ??
			Matrice();
			break;
		}
	return 0;
}
 
int CVICALLBACK ON_VENT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_VENT, &vent);
			break;
	}
	return 0;
}

int CVICALLBACK ON_TRACE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_Trace, &trace);
			break;
	}
	return 0;
}

int CVICALLBACK ON_NOMBRE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int k;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_NbreOiseau, &NbrO);
			for (k=0; k<NbrO; k++)
			{
				indice[k]=1;
				posX[k]=posX0;
				posY[k]=posY0;
			}
	
			break;
		}
	return 0;
}

int CVICALLBACK ON_AGRESSIVE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		
			GetCtrlVal (mode, MODE_Agressivite, &typeO);
			
			break;
		}
	return 0;
}

int CVICALLBACK ON_PUISSANCE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_PUISSANCE, &V0);

			break;
		}
	return 0;
}

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

// SetCtrlVal

int CVICALLBACK ON_SCORE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SetCtrlVal (mode, PANEL_SCORE, score);
			break;
		}
	return 0;
}

int CVICALLBACK ON_ (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SetCtrlVal (mode, PANEL_SCORE, score);
			break;
		}
	return 0;
}






