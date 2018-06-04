
#include "vigaLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



double volume(struct viga *a)
{
return a->W * a->H * a->L;
}
double area(struct viga *a)
{
    return a->W * a->H ;
}
double inertia(struct viga *a)
{
    return a->W * a->H * a->H * a->H / 12;
}
void initCeldas(struct viga *a)
{

    for (int i = 0; i < equ; i++)
    {
        a->X[i] = malloc(sizeof(double) * a->maxCells);
        }

  

}
void limpiaCeldas(struct viga *a)
{

    for (int i = 0; i < equ; i++)
    {
        for (int k = 0; k < a->maxCells; k++)
        {
            a->X[i][k] = 0;
        }
    }
}

    void onOff(struct viga * a, double condOn, double condOff, int forcedIndex)
    {
        if (a->t > condOn)
        {
            //printf("on");
            a->forcedIndex = forcedIndex;
        }
        if (a->t > condOff)
        {
            //printf("off");
            a->forcedIndex = 0;
        }
    }
    void liberaCeldas(struct viga * a)
    {
        for (int i = 0; i < equ; i++)
        {

            free(r.X[i]);
        }
    }
    void initViga(struct viga * a, char *argv[])
    {
        a->k_iter = 0;
        a->FILENAME = argv[1];

        a->E = atof(argv[2]); //GPa for Iron
      
        a->L = atof(argv[3]);
        a->W = atof(argv[4]);
        a->H = atof(argv[5]);

        a->xf = atof(argv[6]);
        a->x = a->L;

        a->dx = atof(argv[7]);

        a->maxCells = (int)((r.x - r.xf) / r.dx);
      //  a->maxCells++;
       // a->maxCells++;

        //  printf("%i",a->maxCells);

        a->yf = a->W * 0.5;
        a->y = -1 * a->yf;
        a->dy = a->W / 10;

        char *aux = argv[8];
        if (aux[0] == 'n')
        {
            a->F = 0;
            a->norm = 1;
        }
        else
        {
            a->F = atof(argv[8]);
            a->F *= gravedad;
            a->norm = 0;
        }
       // a->F *= -1;



        a->error = 0;

        a->ro = atof(argv[11]);
        a->Vol = volume(a);
        a->Area = area(a);
        a->m = a->ro * a->Vol;

        char *aux2 = argv[12];
        if (aux2[0] == 'n')
        {
            a->qL = a->m;
        }
        else
        {
            a->qL = atof(argv[12]); //toma fuerza
        }

        a->qL *= gravedad;
        a->qL /= a->L; //densidad lineal de carga
    //    a->qL *= -1;

        a->forcedIndex = atoi(argv[13]);

        a->I = inertia(a);
        double raiz = coefficient(a) / (a->L * a->L * a->L * a->L);
        //printf("%.2e",raiz);
        raiz /= a->m;
        raiz = sqrt(raiz);
       // a->freqn = atof(argv[9]) * M_PI * 2;
       // a->freq = atof(argv[10]) * M_PI * 2;
        a->freqn = atof(argv[9]) * raiz*3.52;
        a->freq = atof(argv[10]) * raiz*3.52;
        a->fase = a->freqn - a->freq;

        a->maxTimeCells = 10;
        a->dt = 1;
        if (r.freq != 0)
        {
            a->dt /= r.freq;
        }
        a->dt /= a->maxTimeCells;

        a->maxTimeCells *= 10;
    }

    double CFase(double freq, double t, double fase)
    {
        double g= cos((freq * t) + fase);
         return g;
    }
    double heaviside(double *x, double *a)
    {
        if (*x >= *a)
        {
            //printf ("yoyo");
            return 1;
        }
        else
            return 0;
    }
    double dirac(double *x, double *a)
    {
        if (*x > *a)
            return 0;
        else if (*x < *a)
            return 0;
        else
            return 1;
    }

    double coefficient(struct viga * a)
    {

        double coeff = a->I * a->E;

        return coeff;
    }

    void printInitViga(struct viga * a)
    {
        printf("\n****** DATOS ******\n");                                                                                                                                       //tiempo-vx-vy
        printf("\nx0= %.3lf (m)\txf= %.3lf (m)\tdx= %.3lf (m)\n", a->x, a->xf, a->dx);                                                                                           //tiempo-vx-vy
        printf("\nModulo de Young (N/m2)\nE= %.2e\nAncho\tW= %.2e (m)\nAlto\tH= %.2e (m)\n", a->E, a->W, a->H);                                                                  //tiempo-vx-vy
      //  printf("\nCondiciones iniciales:\nw= %.2e (m)\ndwdx= %.2e\ndwdx2= %.2e\ndwdx3= %.2e\n", a->X[0][a->k_iter], a->X[1][a->k_iter], a->X[2][a->k_iter], a->X[3][a->k_iter]); //tiempo-vx-vy
        printf("\nFuerza extremo= %.2e (N)\nFrecuencia Natural= %.2e (radHz)\nFreq Forzada= %.2e (radHz)\n", a->F, a->freqn, a->freq);                                               //tiempo-vx-vy
        printf("\nDensidad= %.2e (kg/m3)\nCarga Distribuida= %.2e (N/m)\n", a->ro, a->qL);                                                                                       //tiempo-vx-vy
        printf("\nMasa= %.2e (kg)\ngravedad= %.3lf (m/s2)\n", a->m, gravedad);                                                                                                   //tiempo-vx-vy
        printf("\nDirectorio= %s\nIndice Funcion Forzada= %i\n", a->FILENAME, a->forcedIndex);                                                                                   //tiempo-vx-vy
        printf("\n******** DATOS ********\n");
    }

    void printData(void *filePointer, struct viga *a)
    {
       // a->T = CFase(a->freqn, a->t, 0);
        // double T0 = CFase(a->freqn, a->t, 0);
        char *content = "%.3lf\t%.2e\t%.1lf\t%.2e\t%.2e\t%.2lf\t%.2e\t%.4lf\t%.2e\t%i\n";
        fprintf((FILE *)filePointer, content, a->x, a->X[0][a->k_iter] , a->error, a->X[1][a->k_iter], a->y, a->T, a->Fx, a->t, a->I, a->k_iter); //tiempo-vx-vy
    }
