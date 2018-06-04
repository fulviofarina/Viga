

#define TIME 1

double (*edoAUsar[equ])(double, double, double, double (*)(double, void *), void *);

void debugEDO(double a1, double a2, double a3);

//1st and 2nd argumento como en el algoritmo de RK4
double edo1(double x, double w, double t, double (*forced)(double, void *), void *vo);
double edo2(double x, double w, double t, double (*forced)(double, void *), void *vo);
//double edo3(double x, double w, double t, double (*forced)(double, void *), void *vo);
//double edo4(double x, double w, double t, double (*forced)(double, void *), void *vo);
//sistema de EDOs 1er orden acopladas;

double theory(double x, double t, double (*forced)(double, void *), void *vo);
//sistema de EDOs 1er orden acopladas

void initEDOs();

void solve(void *vo);
