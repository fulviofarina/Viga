#include "vigaLib.h"
#include "vigaForzado.h"
#include <math.h>

double forcedFunction1(double x, void *vo)
{
    struct viga *a = (struct viga *)vo;
   
    double coseno = cos(a->freq * x);
    double res = a->F * coseno;

#if defined(DEBUG_COEFFICIENT)
    printf("freq= %.2e\t", a->freq);
    printf("F= %.2e\t", a->F);
    printf("t= %.2e\t", x);
    printf("coseno= %.2e\t", coseno);
    printf("res= %.2e\n", res);
   
#endif
    return res;
}
double forcedFunction2(double x, void *vo)
{
    struct viga *a = (struct viga *)vo;
    return a->F * sin(a->freq * x) / x;
}
double forcedFunction3(double x, void *vo)
{
    struct viga *a = (struct viga *)vo;

    return x * x + a->F * x;
}
double forcedFunction4(double x, void *vo)
{
    struct viga *a = (struct viga *)vo;
    return a->F * exp(-1 * a->freq * x);
}

void initForzado()
{
    forzado[0] = forcedFunction1;
    forzado[1] = forcedFunction2;
    forzado[2] = forcedFunction3;
    forzado[3] = forcedFunction4;
}