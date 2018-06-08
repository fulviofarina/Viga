

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mathLib.h"
#include "vigaLib.h"


void error(struct viga *a)
{
    a->error = 1;
    if (a->error != 0.0)
    {
        a->error = (a->X[0][a->k_iter] - a->error) * 100 / a->error;
    }
}

double inertia(struct viga *a)
{
    return a->W * a->H * a->H * a->H / 12;
}



    void onOff(struct viga * a, double condOn, double condOff, int forcedIndex)
    {
        if (a->t > condOn)
        {
            a->forcedIndex = forcedIndex;
        }
        if (a->t > condOff)
        {
            a->forcedIndex = 0;
        }
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
    a->dt = 2e-4;
    a->maxTimeCells = (int)(a->tf/a->dt);
   
}

void initViga(struct viga *a, char *argv[])
{
    a->k_iter = 0;
    a->error = 0;

    a->FILENAME = argv[1];
    a->E = atof(argv[2]); //GPa for Iron
    a->L = atof(argv[3]);
    a->W = atof(argv[4]);
    a->H = atof(argv[5]);

    a->xf = atof(argv[6]);
    a->dx = atof(argv[7]);

    a->x = a->L;
    a->maxCells = (int)(abs(a->x - a->xf) / a->dx);

    a->yf = a->W * 0.5;
    a->y = -1 * a->yf;
    a->dy = a->W / 10;

    a->I = inertia(a);

    initFuerzaExtremo(argv[8], a);

   
  
//en este orden
    a->ro = atof(argv[11]);
    a->Vol = volume(&a->H, &a->W, &a->L);
    a->Area = area(&a->H, &a->W);
    a->m = mass(&a->ro, &a->Vol);

    initTiempo(argv[9], a);
    //en este orden
    initFreqForz(argv[10], a);

    initCargaDistr(argv[12], a);

    a->forcedIndex = atoi(argv[13]);
}


double dx4 (struct viga *a)
{
    return (a->dx * a->dx * a->dx * a->dx);
}
double coefficient(struct viga *a)
{
    double coeff = a->I * a->E;
    return coeff;
}
void printAutor()
{
    printf("\n****** Simulacion de viga en voladizo ******\n");
    printf("\n****** autor: Fulvio Farina ******");
    printf("\n****** carne: 16-90516 ******");
    printf("\n****** email: fulviofarina@usb.ve ******\n\n");
}
    void printInitViga(struct viga * a)
    {
      

        printf("\n****** DATOS ******\n");                                                                      //tiempo-vx-vy
        printf("\nModulo de Young (N/m2)\nE= %.2e\nAncho\tW= %.2e (m)\nAlto\tH= %.2e (m)\n", a->E, a->W, a->H); //tiempo-vx-vy
        printf("\nCondiciones iniciales:\n");
        printf("\nx inicial= %.3lf (m)\tx final= %.3lf (m)\tpaso dx= %.3lf (m)\n", a->x, a->xf, a->dx); //tiempo-vx-vy

        printf("w= %.2e (m)\tdwdt= %.2e (m/s)\n", a->X[0][a->k_iter], a->X[1][a->k_iter]); //tiempo-vx-vy
                                                                                           //  printf("\nCondiciones iniciales:\nw= %.2e (m)\ndwdx= %.2e\ndwdx2= %.2e\ndwdx3= %.2e\n", a->X[0][a->k_iter], a->X[1][a->k_iter], a->X[2][a->k_iter], a->X[3][a->k_iter]); //tiempo-vx-vy
        printf("tiempo final= %.0lf (s)\tpaso dt= %.2e (s)\n", a->tf, a->dt);              //tiempo-vx-vy
        printf("max Celdas t= %i \tmax Celdas x= %i (s)\n", a->maxTimeCells, a->maxCells); //tiempo-vx-vy
        printf("\nVolumen= %.2e (m3)\nArea= %.2e (m2)\n", a->Vol, a->Area);                //tiempo-vx-vy
        printf("\nDensidad= %.2e (kg/m3)\nCarga Distribuida= %.2e (N/m)\n", a->ro, a->qL); //tiempo-vx-vy
        printf("\nMasa= %.2e (kg)\ngravedad= %.3lf (m/s2)\n", a->m, gravedad);
        printf("\nFuerza extremo= %.2e (N)\nFreq. Forzada= %.2e (radHz)\n", a->F, a->freq);  //tiempo-vx-vy
                                                                                             //tiempo-vx-vy
        printf("\nDirectorio= %s\nTipo Funcion Forzada= %i\n", a->FILENAME, a->forcedIndex); //tiempo-vx-vy
        printf("\n******** DATOS ********\n");
    }

    void printData(void *filePointer, struct viga *a)
    {
        double coeff =1;
        	coeff =coefficient(a);
          coeff *= (a->L / a->m);
       	coeff /= dx4(a);
        // printf("\n%.2e\t%.2e", coeff, a->X[0][a->k_iter]);

        char *content = "%.3lf\t%.2e\t%.1lf\t%.2e\t%.2e\t%.2lf\t%.2e\t%.4lf\t%.2e\t%i\n";
        fprintf((FILE *)filePointer, content, a->x, a->X[0][a->k_iter] * coeff, a->error, a->X[1][a->k_iter], a->y, a->T, a->Fx, a->t, a->I, a->k_iter); //tiempo-vx-vy
    }
