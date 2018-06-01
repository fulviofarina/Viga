
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "vigaLib.h"


double volume(struct viga *a)
{
return a->W * a->H * a->L;
}
double inertia(struct viga *a)
{
    return a->W * a->H * a->H * a->H / 12;
}
void initViga(struct viga *a, char *argv[])
{

    a->FILENAME = argv[1];

    a->E = atof(argv[2]); //GPa for Iron
    a->I = 0;
    a->L = atof(argv[3]);
    a->W = atof(argv[4]);
    a->H = atof(argv[5]);
 
    a->Vol = volume(a);

    a->w0 = 0;
    a->dwdx = atof(argv[6]);
    a->w = atof(argv[7]);
    
    a->x = atof(argv[8]);
    a->xf = a->L;
    a->dx = atof(argv[9]);


    a->yf =   a->W*0.5;
    a->y = -1*a->yf;
    a->dy = a->W/10;


    char *aux = argv[10];
    if (aux[0] == 'n')
    {
        a->F = 0;
        a->norm = 1;
    }
    else
    {
        a->F = atof(argv[10]);
        a->F *=gravedad;
        a->norm = 0;
    }
    a->freq = atof(argv[11]);

    a->error = 0;
      a->ro = atof(argv[12]);
    a->forcedIndex = atoi(argv[13]);

  
}



double coefficient(struct viga *a)
{

   

    double coeff = a->I * a->E;
 
  

    return coeff;
}

void printInitViga(struct viga *a)
{
    printf("\nINITIAL CONDITIONS ********\n");                                                          //tiempo-vx-vy
    printf("\nx0= %.3lf\txf= %.3lf\tdx= %.3lf\n", a->x, a->xf, a->dx);                                     //tiempo-vx-vy
    printf("\nE= %.2e\tW= %.3lf\tH= %.3lf\n", a->E, a->W, a->H);                                           //tiempo-vx-vy
    printf("\nw= %.2e\tz= %.2e\tx= %.3lf\n", a->w, a->dwdx, a->x);                                            //tiempo-vx-vy
    printf("\nF= %.2e\tfreq= %.3lf\n\nfile= %s\tforced= %i\n", a->F, a->freq, a->FILENAME, a->forcedIndex); //tiempo-vx-vy
    printf("\n******** END ********\n");
}

void printData(void *filePointer, struct viga *a)
{
    char *content = "%.3lf\t%.2e\t%.1lf\t%.2e\t%.2e\t%.2e\t%.2e\t%.4lf\n";
    fprintf((FILE *)filePointer, content, a->x, a->w, a->error, a->dwdx, a->y, a->I, a->Fx, a->t); //tiempo-vx-vy
}

