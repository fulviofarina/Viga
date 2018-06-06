#include "file.h"
#include "gnu.h"
#include "vigaLib.h"
#include "vigaForzado.h"
#include "vigaEDO.h"

#define D3 "1:2:1"
#define D4 "1:5:2:1"

#include <string.h>
#include <stdio.h>





int main(int ar, char *argv[])
{
	initEDOs();

	initForzado();

	initViga(&r, argv);
	
	initCeldas(&r);
	limpiaCeldas(&r);

	printInitViga(&r); //tiempo-vx-vy

	int PRINT_BAR = (r.maxCells)/100;

	r.mainfp = openFile(r.FILENAME, "w");

	int files = bucleT(PRINT_BAR, &r);

	closeFile(r.mainfp);

	liberaCeldas(&r);

	printf("\n");

	//////////////////////////////////////////////
	makeGNUPlot(files, r.FILENAME, D3, D4, "1", "0.3", 0);

	return 0;
}
