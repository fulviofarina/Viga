
#include "vigaEDO.h"
#include "vigaForzado.h"
#include "vigaLib.h"
#include <math.h>
#include "rk4.h"

void debugEDO(double a1, double a2, double a3)
{
	printf("\n");
	printf("cf= %.2e\t", a1);
	printf("F(x)= %.2e\t", a2);
	double a4 = a2 * a1;
	printf("cf*F(x)= %.2e\n", a4);
	printf("dLx= %.3lf\t", a3);
	a4 *= a3;
	printf("d2wdx2= %.2e\n", a4);
	printf("\n");
}

//1st and 2nd argumento como en el algoritmo de RK4
double edo1(double x, double w, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;

	double a1 = coefficient(a);
	double a3 = (a->L - x);
//	double a3 = (a->L*a->L)-(2*a->L*x)+(x*x);
	//a3*=-0.5;
	a3 *=  (-1*a3*0.5);
	double a2 = 0;
#if defined(TIME)
	a2 = forced(t, a);
#else
	a2 = forced(x, a);
#endif

#if defined(DEBUG_COEFFICIENT)
	debugEDO(a1, a2, a3);
#endif

	a->Fx = a2 * a1;

	return a1 * a2 * a3;
}

//1st and 2nd argumento como en el algoritmo de RK4
double edo2(double x, double z, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	//struct viga *a = (struct viga *)vo;
#if defined(TIME)
#else
#endif
	return z;
}

double theory(double x, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;

	double coef = (2 * a->E * a->I);

#if defined(TIME)
	coef = forced(t, a) / coef;
#else
	coef = forced(x, a) / coef;
#endif

	coef *= a->L;

	return coef * ((x * x) - (x * x * x / (3 * a->L)));
}

void initEDOs()
{
	edoAUsar[0] = edo1;
	edoAUsar[1] = edo2;
}

void solve(void *vo)
{
	struct viga *a = (struct viga *)vo;
	a->x += a->dx;
	a->w0 = a->w;

	a->z += RK4(a->x, a->w, a->dx, a->t, edoAUsar[0], forzado[a->forcedIndex], a);
	a->w += RK4(a->x, a->z, a->dx, a->t, edoAUsar[1], forzado[a->forcedIndex], a);

	a->error = theory(a->x, a->t, forzado[a->forcedIndex], a);
	a->error = (a->w - a->error) * 100 / a->error;
}