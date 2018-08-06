

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mathLib.h"
#include "vigaLib.h"


double inertia(struct viga *a)
{
    return a->W * a->H * a->H * a->H / 12;
}



  

    void initFuerzaExtremo(char *aux, struct viga *a)
    {
        if (aux[0] == 'n')
        {
            a->F = 0;
            a->norm = 1;
        }
        else
        {
            a->F = atof(aux);
            a->F *= gravedad;
            a->norm = 0;
        }
        a->F *= -1;
    }
    void initCargaDistr(char *aux, struct viga *a)
    {
        if (aux[0] == 'n')
        {
            a->qL = a->m;
        }
        else
        {
            a->qL = atof(aux); //toma fuerza
        }

        a->qL *= gravedad;
        a->qL /= a->L; //densidad lineal de carga
        a->qL *= -1;
}
void initFreqForz(char *aux, struct viga *a)
{
    
  //  double raiz = coefficient(a) / (a->L * a->L * a->L * a->L);
  //  raiz /= a->m;
  //  raiz = sqrt(raiz);
    a->freq = atof(aux)*2*M_PI ;
  //  a->freq *= raiz * 3.52;
    a->fase = 0;
}
void initTiempo(char *aux, struct viga *a)
{
    a->tf = atof(aux);
    a->dt = 1e-3;
    a->maxTimeCells = (int)(a->tf/a->dt);
   
}

void initViga(struct viga *a, char *argv[])
{
    a->k_iter = 0;
    a->error = 0;

    a->FILENAME = argv[1];
    a->E = atof(argv[12]); //GPa for Iron
    a->L = atof(argv[3]);
    a->W = atof(argv[4]);
    a->H = atof(argv[5]);
    a->G = atof(argv[13]);

    a->xf = atof(argv[6]);
    a->maxCells = atoi(argv[7]);
   

    a->x = a->L;
    a->dx = ((a->xf - a->x) / a->maxCells);
    
    a->maxCells++;

    a->yf = a->W * 0.5;
    a->y = -1 * a->yf;
    a->dy = a->W / 10;

    a->I = inertia(a);

    initFuerzaExtremo(argv[8], a);

   
  
//en este orden
    a->ro = atof(argv[14]);
    a->Vol = volume(&a->H, &a->W, &a->L);
    a->Area = area(&a->H, &a->W);
    a->m = mass(&a->ro, &a->Vol);

    initTiempo(argv[2], a);
    //en este orden
    initFreqForz(argv[9], a);

    initCargaDistr(argv[10], a);

    a->forcedIndex = atoi(argv[11]);
}


double dx4 (struct viga *a)
{
    return (a->dx * a->dx * a->dx * a->dx);
}

void printAutor()
{
    printf("\n****** Simulacion de viga en voladizo ******\n");
    printf("\n****** autor: Fulvio Farina ******");
    printf("\n****** carne: 16-90516 ******");
    printf("\n****** email: fulviofarina@usb.ve ******\n\n");
}

double beta(struct viga *a)
{
    return a->Area * a->G * kapa;
}
double coeff(struct viga *a)
{
    return a->E * inertia(a);
}
    double alpha(struct viga * a)
    {

        double alph = dx4(a);
        alph = coeff(a) / alph;

       // printf("\nalpha= %.2e\n", alph);

        return alph;
    }
   