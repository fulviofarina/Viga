

#define equForzado 4


double (*forzado[equForzado])(double, void *);


double forcedFunction1(double x, void *vo);
double forcedFunction2(double x, void *vo);
double forcedFunction3(double x, void *vo);
double forcedFunction4(double x, void *vo);

void initForzado();