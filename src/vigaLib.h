
#define kapa  0.83333333333333333333333333333333

#define gravedad 9.81
#define M_PI 3.1415
#define equ 4
//#define DEBUG_COEFFICIENT 1

struct viga
{
    int maxCells;
    double T;
    int maxTimeCells;

    double F, E, G, I, L, W, H, Vol, Area, ro;
    double qL;
    double m;
    int k_iter; //iterator
                // double *ci;
    double **X;
    double freq;
    double error, fase, Fx, t, dt, tf;
    double x, y, z;
    double dx, dy, dz, xf, yf, zf;
    void *fp, *mainfp;
    unsigned int norm, forcedIndex;
    char *FILENAME;
};

struct viga r;

void printAutor();

void initTiempo(char *aux, struct viga *a);

void initFreqForz(char *aux, struct viga *a);
void initFuerzaExtremo(char *aux, struct viga *a);
void initCargaDistr(char *aux, struct viga *a);
double beta(struct viga *a);
double alpha(struct viga *a);
double coeff(struct viga *a);

//void onOff(struct viga *a, double condOn, double condOff, int forcedIndex);
void initViga(struct viga *a, char *argv[]);

double dx4(struct viga *a);
double inertia(struct viga *a);


