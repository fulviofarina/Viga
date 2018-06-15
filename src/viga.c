#include <string.h>
#include <stdio.h>
#include <math.h>
#include "file.h"
#include "mathLib.h"
#include "vigaLib.h"
#include "vigaForzado.h"
#include "vigaEDO.h"
#include "vigaEngine.h"


int main(int ar, char *argv[])
{
	initEDOs();
	initForzado();
	initViga(&r, argv);
	
	r.X = initCeldas(equ,r.maxCells);
	limpiaCeldas(r.X,equ,r.maxCells);

	printAutor();
	printInitViga(&r); //tiempo-vx-vy

	

	r.mainfp = openFile(r.FILENAME, "w");

	int files = bucleT( &r);

	closeFile(r.mainfp);

	liberaCeldas(r.X,equ);

	printf("\n");

	//////////////////////////////////////////////
	//makeGNUPlot(files, r.FILENAME, D3, D4, "1", "0.3", 0);

	return 0;
}
