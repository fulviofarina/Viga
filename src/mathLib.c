
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double mass(double *densidad, double *vol)
{
    return (*densidad) * (*vol);
}
double area(double *ancho, double *largo)
{
    return (*ancho) * (*largo);
}
double volume(double *ancho, double *largo, double *prof)
{
    return area(ancho, largo) * (*prof);
}

double CFase(double freq, double t, double fase)
{
    double g = cos((freq * t) + fase);
    return g;
}
double **initCeldas(int cellsX, int cellsY)
{
    double **p = malloc(sizeof(double *) * cellsX);
    if (!p)
    {
        printf("\nMemory Allocation Failure !\n\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nMemory Allocation #1 OK !\n");
    }
    for (int i = 0; i < cellsX; i++)
    {
        p[i] = malloc(sizeof(double) * cellsY);
        if (!p[i])
        {
            printf("\nMemory Allocation Failure !\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("\nMemory Allocation #2.%i OK !\n", i);
        }
    }
    return p;
}
void limpiaCeldas(double **p, int cellsX, int cellsY)
{
    for (int i = 0; i < cellsX; i++)
    {
       // printf("\n");
        for (int k = 0; k < cellsY; k++)
        {
            *(*(p + i) + k) = 0.0;
           // printf("\t%.2e", p[i][k]);
        }
     
    }
}
void liberaCeldas(double **p, int cells)
{
    for (int i = 0; i < cells; i++)
    {
        free(p[i]);
    }
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
