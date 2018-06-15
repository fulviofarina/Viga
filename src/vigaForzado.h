

#define equForzado 6


double (*forzado[equForzado])(double, void *);


double forcedFunctionNULL(double x, void *vo);
double forcedFunction1(double x, void *vo);
double forcedFunction2(double x, void *vo);
double forcedFunction3(double x, void *vo);
double forcedFunction4(double x, void *vo);

void initForzado();