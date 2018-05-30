#include "file.h"
#include "gnu.h"
#include "vigaLib.h"
#include "vigaForzado.h"
#include "vigaEDO.h"

#define D3 "1:2:7"
#define D4 "1:8:2:7"

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
	double z0 = a->z;

	for (int i = 0; i <= nrofSteps; i++) //loop del algoritmo
	{
		char *fileData = getFileName(i, a->FILENAME);
		a->fp = openFile(fileData, "w");
		//printf(fileData);
		
		double t0 = i * h;
		inicialCond(x0, t0, w0, z0, &r);
		bucleX(printEach, a);
	
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
	makeGNUPlot(N, r.FILENAME,D3,D4,"1","1", 0);
	//	system("gnuplot gnuFinal.gnu");

	return 0;
}
