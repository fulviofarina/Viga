#include "file.h"
#include <math.h>
#include "rk4.h"
#include "mathLib.h"
#include "vigaLib.h"
#include "vigaForzado.h"
#include "vigaEDO.h"

void bucleY(struct viga *a)
{
	a->y = -1 * a->yf;
	//	for (int i = 0; a->y <= a->yf; i++) //loop del algoritmo
	{
		printData(a->fp, a);
		printData(a->mainfp, a);
		//	a->y += a->dy;
	}
}
void bucleX(int printEach, struct viga *a, int t_iter)
{
	int printer = printEach;

	for (a->k_iter = 0; a->k_iter < a->maxCells; a->k_iter++) //loop del algoritmo
	{
		solve(a);
		//error(a);

		if (printer > 0)
		{
			if (printer == printEach)
			{
				char *fileData = getFileName(t_iter, a->FILENAME);
				a->fp = openFile(fileData, "a");
				bucleY(a);
				closeFile(a->fp);
				printer = 0;
			}
		}
		printer++;

		a->x -= a->dx;
	}
}

int bucleT(struct viga *a)
{
	int PRINT_BARX = (r.maxCells) / 30;
	PRINT_BARX--;
	int PRINT_BART = r.maxTimeCells / 40;
	PRINT_BART--;
		int when = 0;

	int whenX = 0;
	//desactiva fuerza
	int forcedIndex = a->forcedIndex;
	a->forcedIndex = 0;
	int t_iter = 0;
	//salva el x0 inicial
	double x0 = a->x;

	int i = 0;
	for (i = 0; i < a->maxTimeCells; i++) //loop del algoritmo
	{

		a->t = i * a->dt;

		//double off = (a->maxTimeCells * 0.60) * a->dt;

		double off = (a->maxTimeCells * 0.3) * a->dt;
		double on = (a->maxTimeCells * 0.15) * a->dt;
		onOff(a, on, off, forcedIndex);

		a->x = x0;

		whenX = -1 * PRINT_BARX;
		if (when == PRINT_BART)
		{
			whenX = PRINT_BARX;
			t_iter++;
			when = 0;
		}
		when++;
		bucleX(whenX, a, t_iter);
	}

	return t_iter - 1; //number of files made
}
double diffinitas(void *p)
{
	struct viga *a = (struct viga *)p;

	double w2 = 6 * a->X[0][a->k_iter];
	//if (h == 1)
	//printf("\nw2 = %.2e\t", w2);
	if (a->k_iter < a->maxCells - 2)
	{
		w2 += a->X[0][a->k_iter + 2];
	}
	//	if (h == 1)
	//printf("w2 = %.2e\t", w2);
	if (a->k_iter < a->maxCells - 1)
	{
		w2 += (-4) * a->X[0][a->k_iter + 1];
	}
	//if (h == 1)
	//printf("w2 = %.2e\t", w2);
	if (a->k_iter >= 2)
	{
		w2 += a->X[0][a->k_iter - 2];
	}
	//	if (h == 1)
	//printf("w2 = %.2e\t", w2);
	if (a->k_iter >= 1)
	{
		w2 += (-4) * a->X[0][a->k_iter - 1];
	}
	//if (h == 1)
	//printf("w2 = %.2e\t", w2);
	return w2;
}
//1st and 2nd argumento como en el algoritmo de RK4
double edo2(double t, double z, double x, double (*forced)(double, void *), void *vo) //sistema de EDOs 1er orden acopladas
{
	struct viga *a = (struct viga *)vo;

	a->Vol = volume(&a->H, &a->W, &a->L);
	a->I = inertia(a);
	double EI = coefficient(a);
	a->m = mass(&a->ro, &a->Vol);

	if (a->norm == 1)
	{
		a->F = EI;
	}

#if defined(TIME)
	a->Fx = forced(t, a);
#else
	a->Fx = forced(x, a);
#endif

	double h = heaviside(&x, &a->L);
	a->Fx *= h;

	double w2 = diffinitas(a);

	double wterm = dx4(a);

	//	if (h == 1)
	//	printf("\ndx4= %.2e\n", wterm);
	wterm /= EI;

	//	if (h == 1)

	double Q = wterm * (a->Fx + a->qL);

	//printf("\nFx= %.2e\n", a->qL);
	//	if (h == 1)
	//		printf("\nwterm*q= %.2e\n", Q);
	Q = Q - w2;
	//	if (h == 1)
	//		printf("\nq-w2= %.2e\n", Q);

#if defined(DEBUG_COEFFICIENT)
	printf("I= %.2e\t", a->I);
	printf("I*E= %.2e\t", EI);
	printf("1:(I*E)= %.2e\n", inv_coeff);
	printf("Fx= %.2e\t", a->Fx);
	printf("wterm= %.2e\t", wterm);
	printf("p= %.2e\n", p);

#endif


//	coeff = sqrt(coeff);


	//double k = (10 / EI);
	//	k *= (a->X[0][a->k_iter]);
	return Q ;
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
			a->X[k][a->k_iter + 1] = a->X[k][a->k_iter] + RK4(a->t, a->X[k][a->k_iter], a->dt , a->x, edoAUsar[k], forzado[a->forcedIndex], a);
		}
	}
}