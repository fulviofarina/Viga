#include "vigaLib.h"
#include "vigaEDO.h"
#include "vigaForzado.h"

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
/*
//1st and 2nd argumento como en el algoritmo de RK4
double edo2(double t, double z, double x, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;

	a->Vol = volume(a);

	a->I = inertia(a);
	double EI = coefficient(a);

	a->m = (a->Vol * a->ro);

	if (a->norm == 1)
	{
		a->F = EI;
	}
#if defined(TIME)
	a->Fx = forced(t, a);
#else
	a->Fx = forced(x, a);
#endif

	//a->Fx *= heaviside(&x, &a->L);
	double h = 1; //
	h = heaviside(&x, &a->L);
	a->Fx *= h;
	// printf("\nFx= %.2e\t h = %.2e\t t = %.3lf", a->Fx, h, t);
	double w2 = 6 * a->X[0][a->k_iter];
	if (a->k_iter == 1)
		printf("\nw2 = %.2e\t", w2);
	if (a->k_iter < a->maxCells - 2)
	{
		w2 += a->X[0][a->k_iter + 2];
	}
	if (a->k_iter == 1)
		printf("w2 = %.2e\t", w2);
	if (a->k_iter < a->maxCells - 1)
	{
		w2 += (-4) * a->X[0][a->k_iter + 1];
	}
	if (a->k_iter == 1)
		printf("w2 = %.2e\t", w2);
	if (a->k_iter >= 2)
	{
		w2 += a->X[0][a->k_iter - 2];
	}
	if (a->k_iter == 1)
		printf("w2 = %.2e\t", w2);
	if (a->k_iter >= 1)
	{

		w2 += (-4) * a->X[0][a->k_iter - 1];
	}
	if (a->k_iter == 1)
		printf("w2 = %.2e\t", w2);

	double wterm = (a->dx * a->dx * a->dx * a->dx);
	wterm = w2 / wterm;
	if (a->k_iter == 1)
		printf("\nw2/dx4= %.2e\n", wterm);
	wterm *= EI;

	if (a->k_iter == 1)
		printf("\nw2*EI= %.2e\n", wterm);

	double Q = (a->Fx + a->qL) - wterm;
	if (a->k_iter == 1)
		printf("\nQ= %.2e\n", Q);
	Q *= (a->L / a->m);
	if (a->k_iter == 1)
		printf("\nQ/u= %.2e\n", Q);
	if (h > 0)
	{
		//		printf("\nFx= %.2e\t h = %.2e\t T0 = %.3lf\t Q = %.2e\tX[0] = %.2e\t wterm = %.2e\tqL = %.2e", a->Fx, h, a->T, Q, a->X[0], wterm, a->qL);
	}
#if defined(DEBUG_COEFFICIENT)
	printf("I= %.2e\t", a->I);
	printf("I*E= %.2e\t", EI);
	printf("1:(I*E)= %.2e\n", inv_coeff);

	debugEDO(EI, a->Fx, dLx);
	printf("Fx= %.2e\t", a->Fx);
	printf("wterm= %.2e\t", wterm);
	printf("p= %.2e\n", p);
	if (h > 0 || h < 0)
		printf("\nFx= %.2e\t h = %.2e\t t = %.3lf", a->Fx, h, t);
#endif
	//double k = (10 / EI);
	//	k *= (a->X[0][a->k_iter]);
	return Q;
}
*/
//1st and 2nd argumento como en el algoritmo de RK4
double edo2(double t, double z, double x, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;

	a->Vol = volume(a);

	a->I = inertia(a);
	double EI = coefficient(a);

	a->m = (a->Vol * a->ro);


	if (a->norm == 1)
	{
		a->F = EI;
	}
#if defined(TIME)
	a->Fx = forced(t, a);
#else
	a->Fx = forced(x, a);
#endif

	//a->Fx *= heaviside(&x, &a->L);
	double h = 1; //
	h = heaviside(&x, &a->L);
	a->Fx *= h;
	// printf("\nFx= %.2e\t h = %.2e\t t = %.3lf", a->Fx, h, t);
	double w2 = 6 * a->X[0][a->k_iter];
if (a->k_iter==1)	printf("\nw2 = %.2e\t", w2);
	if (a->k_iter < a->maxCells-2)
	{
		w2 +=  a->X[0][a->k_iter + 2];
	}
	if (a->k_iter == 1)
		printf("w2 = %.2e\t", w2);
	if (a->k_iter < a->maxCells - 1)
	{
		w2 += (- 4 )* a->X[0][a->k_iter + 1];
	}
	if (a->k_iter == 1)
		printf("w2 = %.2e\t", w2);
	if (a->k_iter >= 2)
	{
		w2 += a->X[0][a->k_iter - 2];
			
		}
		if (a->k_iter == 1)
			printf("w2 = %.2e\t", w2);
		if (a->k_iter >= 1)
		{
			
			w2 += (- 4) * a->X[0][a->k_iter - 1];
		}
		if (a->k_iter == 1)
			printf("w2 = %.2e\t", w2);

		double wterm = (a->dx * a->dx * a->dx * a->dx);
	//	wterm = w2 / wterm;
		if (a->k_iter == 1)
			printf("\ndx4= %.2e\n", wterm);
		wterm /= EI;
	
		if (a->k_iter == 1)
			printf("\ndx4/EI= %.2e\n", wterm);

		double Q = 	wterm*(a->Fx + a->qL);
		
		if (a->k_iter == 1)
			printf("\nwterm*q= %.2e\n", Q);
		Q = Q - w2;
			if (a->k_iter == 1)
				printf("\nq-w2= %.2e\n", Q);
		if (h > 0)
		{
			//		printf("\nFx= %.2e\t h = %.2e\t T0 = %.3lf\t Q = %.2e\tX[0] = %.2e\t wterm = %.2e\tqL = %.2e", a->Fx, h, a->T, Q, a->X[0], wterm, a->qL);
		}
#if defined(DEBUG_COEFFICIENT)
	printf("I= %.2e\t", a->I);
	printf("I*E= %.2e\t", EI);
	printf("1:(I*E)= %.2e\n", inv_coeff);

	debugEDO(EI, a->Fx, dLx);
	printf("Fx= %.2e\t", a->Fx);
	printf("wterm= %.2e\t", wterm);
	printf("p= %.2e\n", p);
	if (h > 0 || h < 0)
		printf("\nFx= %.2e\t h = %.2e\t t = %.3lf", a->Fx, h, t);
#endif
	//double k = (10 / EI);
//	k *= (a->X[0][a->k_iter]);
	return Q;
}

//1st and 2nd argumento como en el algoritmo de RK4
double edo1(double x, double z, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;
	//return z;
	return a->X[1][a->k_iter];
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
	edoAUsar[0] = edo1; //edo fuerte
	edoAUsar[1] = edo2; //variables de estado
//	edoAUsar[2] = edo3; //variables de stado
	//edoAUsar[3] = edo4; //variables de estado
}

void solve(void *vo)
{
	struct viga *a = (struct viga *)vo;

	if (a->k_iter < a->maxCells - 1)
	{
		for (int k = 1; k >= 0; k--)
		{
			a->X[k][a->k_iter+1] = a->X[k][a->k_iter] + RK4(a->t, a->X[k][a->k_iter], a->dt, a->x, edoAUsar[k], forzado[a->forcedIndex], a);
		} 
	}
}