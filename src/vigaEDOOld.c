
#include <math.h>
#include "rk4.h"
#include "mathLib.h"
#include "vigaLib.h"
#include "vigaForzado.h"
#include "vigaEDO.h"

double diffinitas(void *p)
{
	struct viga *a = (struct viga *)p;

	double w0 = 0;
	double w2, w1, w2_, w1_;
	w2 = 0;
	w1 = 0;
	w2_ = 0;
	w1_ = 0;

	double coeff = 1;
	//	coeff = coefficient(a) ;
	//coeff*= (a->L / a->m);
	//	coeff /= dx4(a);

	w0 = 6 * a->X[0][a->k_iter] * coeff;

	if (a->k_iter < a->maxCells - 2)
	{
		w2 = a->X[0][a->k_iter + 2] * coeff;
	}

	if (a->k_iter < a->maxCells - 1)
	{
		w1 = (-4) * a->X[0][a->k_iter + 1] * coeff;
	}

	if (a->k_iter >= 2)
	{
		w2_ += a->X[0][a->k_iter - 2] * coeff;
	}

	if (a->k_iter >= 1)
	{
		w1_ = (-4) * a->X[0][a->k_iter - 1] * coeff;
	}

	double sum = (w0 + w1 + w2 + w1_ + w2_);
#if defined(DEBUG_COEFFICIENT)
	printf("\ncoeff = %.2e\t", coeff);
	printf("w0 = %.2e\t", w0);
	printf("w2 = %.2e\t", w2);
	printf("w1 = %.2e\t", w1);
	printf("w2_ = %.2e\t", w2_);
	printf("w1_ = %.2e\t", w1_);
	printf("k = %i\t", a->k_iter);
	printf("sum = %.2e\t", sum);
#endif

	return sum;
}
//1st and 2nd argumento como en el algoritmo de RK4
double edo2(double t, double z, double x, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;

	a->Vol = volume(&a->H, &a->W, &a->L);
	a->I = inertia(a);
	double EI = a->E*a->I;
	a->m = mass(&a->ro, &a->Vol);

	if (a->norm == 1)
	{
		a->F = EI;
	}

	a->Fx = forced(t, a);

	double h = heaviside(&x, &a->L);
	a->Fx *= h;

	double w2 = diffinitas(a);

	double wterm = 1;
	wterm = dx4(a);
	wterm /= EI;

	double coef = 1;
	//	coeff =coefficient(a) ;
	//	coeff *= (a->L / a->m);
	//	coeff /= dx4(a);

	double Q = (a->Fx + a->qL);

	Q *= coef * wterm;

	//printf("\n%.2e\t%.2e\t%.2e", wterm, Q, w2);
	//printf("\nFx= %.2e\n", a->qL);
	//	if (h == 1)
	//		printf("\nwterm*q= %.2e\n", Q);
	Q = Q - w2;

	//	if (h == 1)
	//		printf("\nq-w2= %.2e\n", Q);

#if defined(DEBUG_COEFFICIENT)
	printf("\ncoeff*wterm=invMassDens= %.2e\tQ= %.2e\tw2= %.2e\n", coeff * wterm, Q, w2);

#endif

	//	coeff = sqrt(coeff);

	//double k = (10 / EI);
	//	k *= (a->X[0][a->k_iter]);
	//printf("\n%.2e\t%.2e", coeff, Q);

	return Q;
}


//1st and 2nd argumento como en el algoritmo de RK4
double edo1(double x, double z, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;
	return a->X[1][a->k_iter];
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
		for (int k = equ - 1; k >= 0; k--)
		{
			a->X[k][a->k_iter + 1] = a->X[k][a->k_iter] + Euler(a->t, a->X[k][a->k_iter], a->dt, a->x, edoAUsar[k], forzado[a->forcedIndex], a);
		}
	}
}
