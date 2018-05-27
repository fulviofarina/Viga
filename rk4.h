


double RK4(double x, double v, double d, double t, double (*f)(double, double, double, double (*)(double, void *), void *), double (*forced)(double, void *), void *arg) //algoritmo runge-kutta 4to orden
{
	double e1, e2, e3, k1, k2, k3, k4;

	k1 = d * f(x, v, t, forced, arg);

	e1 = v + (0.5 * k1);
	x += (d * 0.5);
	k2 = d * f(x, e1, t, forced, arg);

	e2 = v + (0.5 * k2);
	k3 = d * f(x, e2, t, forced, arg);

	e3 = v + k3;
	x += (d * 0.5);
	k4 = d * f(x, e3, t, forced, arg);

	double res = (k1 + (2 * k2) + (2 * k3) + k4);
	res /= 6;
	return res;
}
