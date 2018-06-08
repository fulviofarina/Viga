
double area(double *ancho, double *largo) ;
double volume(double *ancho, double *largo, double *prof);
double CFase(double freq, double t, double fase);
double ** initCeldas(int cellsX, int cellsY);
void limpiaCeldas(double **p, int cellsX, int cellsY);
void liberaCeldas(double **p, int cells);
double heaviside(double *x, double *a);
double dirac(double *x, double *a);
double mass(double *densidad, double *vol);
