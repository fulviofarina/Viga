

#include <math.h>
double mass(double *densidad, double *vol)
{
    return (*densidad) *(*vol);
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
