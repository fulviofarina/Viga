

#define gravedad 9.81
#define M_PI 3.1415
#define equ 2
//#define DEBUG_COEFFICIENT 1


struct viga
{
    int maxCells;
    double T;
    int maxTimeCells;

    double F, E, I, L, W, H, Vol, Area, ro;
    double  qL;
    double m;
    int k_iter; //iterator
   // double *ci;
    double *X[4], freq, freqn;
    double  error, fase, Fx, t, dt;
    double x, y, z;
    double dx, dy, dz, xf, yf, zf;
    void *fp, *mainfp;
    unsigned int norm, forcedIndex;
    char *FILENAME;
};

struct viga r;
double CFase(double freq, double t, double fase);
double heaviside(double *x, double *a);
double dirac(double *x, double *a);
void liberaCeldas(struct viga *a) ;
double volume(struct viga *a);
double area(struct viga *a);
void printData(void *filePointer, struct viga * a);
void onOff(struct viga *a, double condOn, double condOff, int forcedIndex) ;
void initViga(struct viga *a, char *argv[]);
void initCeldas(struct viga *a);
void limpiaCeldas(struct viga *a);

    double inertia(struct viga *a);
double coefficient(struct viga *a);

void printInitViga(struct viga *a);

