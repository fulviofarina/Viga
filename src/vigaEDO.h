

#define TIME 1

double (*edoAUsar[equ])(double, double, double, double (*)(double, void *), void *);
void bucleY(struct viga *a);
void bucleX(int printEach, struct viga *a, int t_iter);
int bucleT( struct viga *a);
double diffinitas(void *p);


    //1st and 2nd argumento como en el algoritmo de RK4
double edo1(double x, double w, double t, double (*forced)(double, void *), void *vo);
double edo2(double x, double w, double t, double (*forced)(double, void *), void *vo);
double edo3(double t, double z, double x, double (*forced)(double, void *), void *vo) ;
//sistema de EDOs 1er orden acopladas

    void initEDOs();

void solve(void *vo);
