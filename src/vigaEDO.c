
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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

double diffinitas2(void *p)
{
	struct viga *a = (struct viga *)p;

	double w0 = 0;
	double  w1,  w1_;

	w1 = 0;
	
	w1_ = 0;

	double coeff = 1;
	//	coeff = coefficient(a) ;
	//coeff*= (a->L / a->m);
	//	coeff /= dx4(a);

	w0 = -1*2 * a->X[2][a->k_iter] * coeff;

	

	if (a->k_iter < a->maxCells - 1)
	{
		w1 =  a->X[2][a->k_iter + 1] * coeff;
	}



	if (a->k_iter >= 1)
	{
		w1_ =  a->X[2][a->k_iter - 1] * coeff;
	}

	double sum = (w0 + w1 + w1_ );
#if defined(DEBUG_COEFFICIENT)
	printf("\ncoeff = %.2e\t", coeff);
	printf("w0 = %.2e\t", w0);
	
	printf("w1 = %.2e\t", w1);

	printf("w1_ = %.2e\t", w1_);
	printf("k = %i\t", a->k_iter);
	printf("sum = %.2e\t", sum);
#endif

	return sum;
}
//1st and 2nd argumento como en el algoritmo de RK4
double edo4(double t, double z, double x, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;

	a->Vol = volume(&a->H, &a->W, &a->L);
	a->I = inertia(a);
	double EI = a->E*a->I;
	a->m = mass(&a->ro, &a->Vol);
	double bet = beta(a);
	double alph = alpha(a);


		if (a->norm == 1)
	{
		a->F = EI;
	}

	a->Fx = forced(t, a);

	double h = heaviside(&x, &a->L);
	a->Fx *= h;

	


    double mu = (a->m/a->L);
	double aux = diffinitas(a);

	double Q = (a->Fx + a->qL);
	Q -= (aux*alph);
	Q -= (mu*(a->X[2][a->k_iter]));
	
	
	double m2 = (bet/ a->ro);

	double dx2 = (a->dx * a->dx);

	double coef = (bet * a->I);
   	coef += (a->Area * dx2*dx2 * alph);
	coef /= dx2;
	coef/=m2;

	double dif2 = diffinitas2(a);

	coef *= dif2;

	//Q *= m2;

	Q+=coef;
//	Q*=1e-12;
//	Q/= a->I;
//	Q/= mu;


#if defined(DEBUG_COEFFICIENT)
	printf("\ncoeff= %.2e\tQ= %.2e\tdif1= %.2e\tm2= %.2e\tdif2= %.2e\tFx= %.2e\talpha= %.2e\tx= %.2e\n", coef, Q, aux, m2, dif2, a->Fx, alph, a->x);
	//	getchar();

#endif


	return Q;
}


//1st and 2nd argumento como en el algoritmo de RK4
double edo1(double x, double z, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;
	return a->X[1][a->k_iter];
}

//1st and 2nd argumento como en el algoritmo de RK4
double edo2(double x, double z, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;
	return a->X[2][a->k_iter];
}
double edo3(double x, double z, double t, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;
	return a->X[3][a->k_iter];
}
void initEDOs()
{
	edoAUsar[0] = edo1; //edo fuerte
	edoAUsar[1] = edo2; //variables de estado
	edoAUsar[2] = edo3; //edo fuerte
	edoAUsar[3] = edo4; //variables de estado
						//	edoAUsar[2] = edo3; //variables de stado
						//edoAUsar[3] = edo4; //variables de estado
}

void solve(void *vo)
{
	struct viga *a = (struct viga *)vo;

	if (a->k_iter < a->maxCells - 1 )
	{
		for (int k = equ - 1; k >= 0; k--)
		{
			a->X[k][a->k_iter+1 ] = a->X[k][a->k_iter] + RK4(a->t, a->X[k][a->k_iter], a->dt, a->x, edoAUsar[k], forzado[a->forcedIndex], a);
		//	a->X[k][a->k_iter + 1] = a->X[k][a->k_iter];
		}
	}
}
