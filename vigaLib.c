
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "vigaLib.h"



void initViga(struct viga *a, char *argv[])
{

    a->FILENAME = argv[1];

    a->E = atof(argv[2]); //GPa for Iron
    a->I = 0;
    a->L = atof(argv[3]);

    a->xf = a->L;

    a->W = atof(argv[4]);
    a->H = atof(argv[5]);
    a->w0 = 0;
    a->z = atof(argv[6]);
    a->w = atof(argv[7]);
    a->x = atof(argv[8]);
    a->dx = atof(argv[9]);

    char *aux = argv[10];
    if (aux[0] == 'n')
    {
        a->F = 0;
        a->norm = 1;
    }
    else
    {
        a->F = atof(argv[10]);
        a->norm = 0;
    }
    a->freq = atof(argv[11]);

    a->error = 0;

    a->forcedIndex = atoi(argv[12]) - 1;
}

void inicialCond(double x0, double t0, double w0, double z0, struct viga *a)
{
    a->t = t0;
    a->x = x0;
    a->w = w0;
    a->z = z0;
}
double inertia(double W, double H)
{
    return W * H * H * H / 12;
}
double coefficient(struct viga *a)
{

    a->I = inertia(a->W, a->H);

    double coeff = a->I * a->E;
    double inv_coeff = 1.0 / coeff;

#if defined(DEBUG_COEFFICIENT)
    printf("I= %.2e\t", a->I);
    printf("I*E= %.2e\t", coeff);
    printf("1:(I*E)= %.2e\n", inv_coeff);
#endif
    // si no hay fuerza usar el coeficiente para normalizar

    if (a->norm == 1)
    {
        a->F = coeff;

        // printf("FAmpli= %.2e\n", a->F);
        //  printf("norm\n");
    }

    return inv_coeff;
}

void printInitViga(struct viga *a)
{
    printf("\nINITIAL CONDITIONS ********\n");                                                          //tiempo-vx-vy
    printf("\nx0= %.3lf\txf= %.3lf\tdx= %.3lf\n", a->x, a->xf, a->dx);                                     //tiempo-vx-vy
    printf("\nE= %.2e\tW= %.3lf\tH= %.3lf\n", a->E, a->W, a->H);                                           //tiempo-vx-vy
    printf("\nw= %.2e\tz= %.2e\tx= %.3lf\n", a->w, a->z, a->x);                                            //tiempo-vx-vy
    printf("\nF= %.2e\tfreq= %.3lf\n\nfile= %s\tforced= %i\n", a->F, a->freq, a->FILENAME, a->forcedIndex); //tiempo-vx-vy
    printf("\n******** END ********\n");
}

void printData(void *filePointer, struct viga *a)
{
    char *content = "%.3lf\t%.2e\t%.1lf\t%.2e\t%.3lf\t%.2e\t%.2e\t%.4lf\n";
    fprintf((FILE *)filePointer, content, a->x, a->w, a->error, a->z, a->L, a->I, a->Fx, a->t); //tiempo-vx-vy
}

