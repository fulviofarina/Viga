#include <math.h>
#include "mathLib.h"
#include "vigaLib.h"
#include "vigaForzado.h"

double iter = 0;

double forcedFunctionNULL(double x, void *vo)
{
return 0;
}
double forcedFunction1(double x, void *vo)
{
    struct viga *a = (struct viga *)vo;
   
    double coseno = CFase(a->freq ,x,0);
   
    if (coseno<0) coseno = 0;
  // printf("\n%.2lf", coseno);
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
    if (x<0) return 0;
    return a->F * sin(a->freq * x) / x;
}


double forcedFunction4(double x, void *vo)
{
    struct viga *a = (struct viga *)vo;
    double tau = 1/a->freq;
double toReturn = 0;

if (a->t >= tau+ iter  )
{
    toReturn = a->F;
    iter = a->t;
}
//if (toReturn<0) printf("\n%.2lf", toReturn);
return toReturn;
}
double forcedFunction3(double x, void *vo)
{
    struct viga *a = (struct viga *)vo;
    return a->F * exp(-1 * a->freq* a->freq * x*x);
}
double forcedFunction5(double x, void * vo)
{
    struct viga *a = (struct viga *)vo;

    double coseno = CFase(a->freq, x, 0);
    double res = a->F * coseno;
    if (a->t > 0.7*a->maxTimeCells*a->dt) res = 0;
    return res;
}
void initForzado()
{
       
    forzado[0] = forcedFunctionNULL;
    forzado[1] = forcedFunction1;
    forzado[2] = forcedFunction2;
    forzado[3] = forcedFunction3;
    forzado[4] = forcedFunction4;
    forzado[5] = forcedFunction5;
}