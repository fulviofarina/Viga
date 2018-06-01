

#define gravedad 9.81

//#define DEBUG_COEFFICIENT 1


struct viga
{
    double F, E, I, L, W, H, Vol, ro;
    double m, m_test;
    double w, w0, dwdx, x,y, error, freq, dx, xf,yf,dy, Fx, t;
    void *fp, *mainfp;
    unsigned int norm, forcedIndex;
    char *FILENAME;
};

struct viga r;

double volume(struct viga *a);
void printData(void *filePointer, struct viga * a);

void initViga(struct viga *a, char *argv[]);



double inertia(struct viga *a);
double coefficient(struct viga *a);

void printInitViga(struct viga *a);

