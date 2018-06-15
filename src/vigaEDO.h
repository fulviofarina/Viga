



double (*edoAUsar[equ])(double, double, double, double (*)(double, void *), void *);

double diffinitas(void *p);
double diffinitas2(void *p);


    //1st and 2nd argumento como en el algoritmo de RK4
    double edo1(double x, double w, double t, double (*forced)(double, void *), void *vo);
double edo2(double x, double w, double t, double (*forced)(double, void *), void *vo);
double edo3(double t, double z, double x, double (*forced)(double, void *), void *vo) ;
double edo4(double t, double z, double x, double (*forced)(double, void *), void *vo);
//sistema de EDOs 1er orden acopladas

    void initEDOs();

void solve(void *vo);
