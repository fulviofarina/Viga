

#define g 9.81

//#define DEBUG_COEFFICIENT 1


struct viga
{
    double F, E, I, L, W, H;
    double m, m_test;
    double w, w0, z, x, error, freq, dx, xf, Fx, t;
    void *fp, *mainfp;
    unsigned int norm, forcedIndex;
    char *FILENAME;
};

struct viga r;


void printData(void *filePointer, struct viga * a);

void initViga(struct viga *a, char *argv[]);



double inertia(double W, double H);
double coefficient(struct viga *a);

void printInitViga(struct viga *a);

void inicialCond(double x0, double t0, double w0, double z0, struct viga *a);