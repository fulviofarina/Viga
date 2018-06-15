

#include "file.h"
//#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include "rk4.h"
#include "mathLib.h"
#include "vigaLib.h"
//#include "vigaForzado.h"
#include "vigaEDO.h"
#include "vigaEngine.h"

void bucleY(struct viga *a)
{
  //  a->y = -1 * a->yf;
    //	for (int i = 0; a->y <= a->yf; i++) //loop del algoritmo
    {
        printData(a->fp, a);
        printData(a->mainfp, a);
  //      	a->y += a->dy;
    }
}
void bucleX(int printEach, struct viga *a, int t_iter)
{
    int printer = printEach;

    for (a->k_iter = 0; a->k_iter < a->maxCells; a->k_iter++) //loop del algoritmo
    {
        solve(a);
        //error(a);
        if (a->k_iter == a->maxCells - 1) //para imprimir la última fila
        {
            printer = printEach;
        }
        if (printer > 0)
        {
            if (printer == printEach)
            {
                //	printf("%i\n",printer);
                char *fileData = getFileName(t_iter, a->FILENAME);
                a->fp = openFile(fileData, "a");
                bucleY(a);
                closeFile(a->fp);
                printer = 0;
            }
        }
        printer++;

        a->x -= a->dx;
    }
}

int bucleT(struct viga *a)
{
    int PRINT_BARX = (int)(r.maxCells / 50);
    //	PRINT_BARX--;
    int PRINT_BART = (int)(r.maxTimeCells / 100);
    //	PRINT_BART--;
    int when = 0;

    // printf("%i",PRINT_BARX);
    int whenX = 0;
    //desactiva fuerza
    int forcedIndex = a->forcedIndex;
    //	a->forcedIndex = 0;
    int t_iter = 0;
    //salva el x0 inicial
    double x0 = a->x;

  
    for (int i = 0; i < a->maxTimeCells; i++) //loop del algoritmo
    {

        a->t = i * a->dt;
        a->x = x0;

        whenX = -1 * PRINT_BARX;
        if (when == PRINT_BART)
        {
            whenX = PRINT_BARX;
            t_iter++;
            when = 0;
        }
        when++;
        bucleX(whenX, a, t_iter);
    }

    return t_iter - 1; //number of files made
}

void printInitViga(struct viga *a)
{

    double alph = alpha(a);

    double bet = beta(a);
    double converg = (a->L * a->L);
    converg = coeff(a) / converg;
    converg /= bet;

    printf("\n****** DATOS ******\n");                                                                      //tiempo-vx-vy
    printf("\nModulo de Young (N/m2)\nE= %.2e\nAncho\tW= %.2e (m)\nAlto\tH= %.2e (m)\n", a->E, a->W, a->H); //tiempo-vx-vy
    printf("\nCondiciones iniciales:\n");
    printf("\nx inicial= %.2e (m)\tx final= %.2e (m)\tpaso dx= %.2e (m)\n", a->x, a->xf, a->dx); //tiempo-vx-vy

    printf("w= %.2e (m)\tdwdt= %.2e (m/s)\n", a->X[0][a->k_iter], a->X[1][a->k_iter]); //tiempo-vx-vy
                                                                                       //  printf("\nCondiciones iniciales:\nw= %.2e (m)\ndwdx= %.2e\ndwdx2= %.2e\ndwdx3= %.2e\n", a->X[0][a->k_iter], a->X[1][a->k_iter], a->X[2][a->k_iter], a->X[3][a->k_iter]); //tiempo-vx-vy
    printf("tiempo final= %.0lf (s)\tpaso dt= %.2e (s)\n", a->tf, a->dt);              //tiempo-vx-vy
    printf("max Celdas t= %i \tmax Celdas x= %i (s)\n", a->maxTimeCells, a->maxCells); //tiempo-vx-vy
    printf("\nVolumen= %.2e (m3)\nArea= %.2e (m2)\n", a->Vol, a->Area);                //tiempo-vx-vy
    printf("\nInertia= %.2e (m4)\nE*I= %.2e (N.m2)\n", a->I, coeff(a));
    printf("\nalpha = E*I/dx^4= %.2e (N/m2)\nalpha/mu= %.2e (N/(m.Kg))\n", alph, alph * (a->L / a->m)); //tiempo-vx-vy
    printf("\nk= %.2lf\nConvergence = (E*I)/(L^2*A*G*k) << 1 = %.2e (N/m)\n", kapa, converg);           //tiempo-vx-vy
    printf("\nDensidad= %.2e (kg/m3)\nCarga Distribuida= %.2e (N/m)\n", a->ro, a->qL);                  //tiempo-vx-vy
    printf("\nMasa= %.2e (kg)\ngravedad= %.3lf (m/s2)\n", a->m, gravedad);
    printf("\nFuerza extremo= %.2e (N)\nFreq. Forzada= %.2e (radHz)\n", a->F, a->freq);  //tiempo-vx-vy
                                                                                         //tiempo-vx-vy
    printf("\nDirectorio= %s\nTipo Funcion Forzada= %i\n", a->FILENAME, a->forcedIndex); //tiempo-vx-vy
    printf("\n******** DATOS ********\n");
}

void printData(void *filePointer, struct viga *a)
{
    double coef = 1;

  //  coef = coeff(a);
  //  coef /= dx4(a);
   // coef *= (a->L / a->m);
///////////////////////////////////////////////////
   //   coef/= 1e-12;
      coef *= (a->L / a->m);
    	coef /= a->I;
        coef/=a->ro; 
        coef*= beta(a);
       coef *= 1e-13;
    // printf("\n%.2e\t%.2e", coeff, a->X[0][a->k_iter]);

    char *content = "%.2e\t%.2e\t%.2e\t%.2e\t%.2e\t%.2e\t%.2e\t%.4lf\t%.2e\t%i\n";
    fprintf((FILE *)filePointer, content, a->L - a->x, a->X[0][a->k_iter] * coef, a->error, a->X[2][a->k_iter] * coef, a->y, a->T, a->Fx, a->t, a->I, a->k_iter); //tiempo-vx-vy
}
