#include "file.h"
#include "gnu.h"
#include "vigaLib.h"
#include "vigaForzado.h"
#include "vigaEDO.h"

#define D3 "1:2:1"
#define D4 "1:5:2:1"

#include <string.h>
#include <stdio.h>

void bucleX(int printEach, struct viga *a)
{
	int printer = printEach;

	for (a->k_iter = 0; a->k_iter < a->maxCells; a->k_iter++) //loop del algoritmo
	{

		
		solve(a);

		a->error = theory(a->x, a->t, forzado[a->forcedIndex], a);
		if (a->error != 0.0)
		{
			a->error = (a->X[0][a->k_iter] - a->error) * 100 / a->error;
		}
		
		if (printer == printEach)
		{
		
			a->y = -1 * a->yf;
			for (int i = 0; a->y <= a->yf; i++) //loop del algoritmo
			{
				printData(a->fp, a);
				printData(a->mainfp, a);
				a->y += a->dy;
			}
			printer = 0;
		}
		printer++;

		a->x -= a->dx;

		

	}
}

int bucleT(int nrofSteps, double h, double printEach, struct viga *a)
{
	//save the old initial x0

	//deactivate force
	int forcedIndex = a->forcedIndex;
	a->forcedIndex = 0;

		double x0 = a->x; // = a->L;

		int i = 0;
		for (i = 0; i <= nrofSteps; i++) //loop del algoritmo
		{
			char *fileData = getFileName(i, a->FILENAME);
			a->fp = openFile(fileData, "w");

			a->t = i * h;

			double off = (nrofSteps * 0.06) * h;
			double on = (nrofSteps * 0.05) * h;
			onOff(a,on,off, forcedIndex);
			
		//	for (int i = 0; i < equ; i++)
			{
				//for (int k = 0; k < a->maxCells; k++)
				{
			//a->X[i][k] = 0;
				}
			}
		
			a->x = x0;
			bucleX(printEach, a);

			closeFile(a->fp);
		}

		return i - 1; //number of files made
}

int main(int ar, char *argv[])
{

	

	initEDOs();

	initForzado();

	initViga(&r, argv);
	
	initCeldas(&r);
	limpiaCeldas(&r);

	printInitViga(&r); //tiempo-vx-vy

	int PRINT_BAR;
	
	//printf("%i",pieces);

	PRINT_BAR = (r.maxCells)/100;



	r.mainfp = openFile(r.FILENAME, "w");

	int files = bucleT(r.maxTimeCells, r.dt, PRINT_BAR, &r);

	closeFile(r.mainfp);

	liberaCeldas(&r);

		printf("\n");

	/////////////////////////////////////////////////
	//////////////////////////////////////////////
	makeGNUPlot(files, r.FILENAME, D3, D4, "5", "0.3", 0);
	//	system("gnuplot gnuFinal.gnu");

	return 0;
}
