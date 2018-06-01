#include "file.h"
#include "gnu.h"
#include "vigaLib.h"
#include "vigaForzado.h"
#include "vigaEDO.h"

#define D3 "1:2:7"
#define D4 "1:5:2:7"

#include <string.h>
#include <stdio.h>

void bucleX(double printEach, struct viga *a)
{
	double printer = printEach;

	for (int j = 0; a->x <= a->xf + a->dx; j++) //loop del algoritmo
	{
		if (printer == printEach)
		{
			printData(a->fp, a);
			printData(a->mainfp, a);
			printer = 0;
		}
		printer++;
		solve(a);
	}
}

void bucleT(int nrofSteps, double h, double printEach, struct viga *a)
{
	//save the old initial x0
	double x0 = a->x;
	double w0 = a->w;
	double dwdx0 = a->dwdx;
	double y0 = a->y;

//deactivate force
	int forcedIndex = a->forcedIndex;
	a->forcedIndex = 0;

	for (int i = 0; i <= nrofSteps; i++) //loop del algoritmo
	{
		char *fileData = getFileName(i, a->FILENAME);
		a->fp = openFile(fileData, "w");
		//printf(fileData);
		
		double t0 = i * h;
		a->t = t0;
  
        a->y = y0;

if (i>nrofSteps*0.25)
{
	a->forcedIndex=forcedIndex;
}
else if (i>nrofSteps*0.55)
{
		a->forcedIndex=0;
}

	for (int j = 0; a->y < a->yf + a->dy; j++) //loop del algoritmo
	{
		  a->x = x0;
         a->w = w0;
         a->dwdx = dwdx0;
	   // printf("%.2e\t%.2e\n",a->y,a->dy);
		bucleX(printEach, a);
		a->y+=a->dy;
		
	}

		closeFile(a->fp);

		//printf("\tok\n");
	}
}




int main(int ar, char *argv[])
{

	initEDOs();

	initForzado();

	initViga(&r, argv);
	printInitViga(&r); //tiempo-vx-vy

	float PRINT_BAR = (float)1 / 100;
	PRINT_BAR *= (r.xf - r.x) / r.dx;

	int N = 10;
	double dt = 1;
	if (r.freq != 0)
	{
		dt /= r.freq;
	}
	dt /= N;

	N *= 5;

	r.mainfp = openFile(r.FILENAME, "w");

    bucleT(N,dt,PRINT_BAR,&r);

	closeFile(r.mainfp);

	printf("\n");
	
	/////////////////////////////////////////////////
	//////////////////////////////////////////////
	makeGNUPlot(N, r.FILENAME,D3,D4,"5","0.3", 0);
	//	system("gnuplot gnuFinal.gnu");

	return 0;
}
