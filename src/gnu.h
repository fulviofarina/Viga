#define gnuscriptFile "gnuScript.gnu"
#define gnuPlotBaseFile "gnuBasePlot.b"
#define gnuSurfaceBaseFile "gnuBaseSurface.b"
#define gnuFinalFile "gnuFinal.gnu"

struct gnuObject
{
    int surface;
    char *treeD;
    char *fourD;
    char *toUseD;
    char *pointType;
    char *pointSize;
    char *baseFile;
} gnu;
//struct gnuObject gnu;

void initGNUPlot(int surface, char *treeD, char *fourD, char *pointType, char *pointSize);
void chooseD();
void addPlot(char *fileToPlot);
void composeGNUFile();
void makeGNUScript(int nrOfFiles, char *basefileName);