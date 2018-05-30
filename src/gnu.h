#define gnuscriptFile1 "deleteme1.txt"
#define gnuscriptFile2 "deleteme2.txt"
#define gnuPlotBaseFile "gnuBasePlot.b"
#define gnuSurfaceBaseFile "gnuBaseSurface.b"
#define gnuPlotFinalFile "gnuPlot.gnu"
#define gnuSurfaceFinalFile "gnuSurface.gnu"

struct gnuObject
{
    int surface;
    char *treeD;
    char *fourD;
    char *toUseD;
    char *pointType;
    char *pointSize;
    char *baseFile;
    char *finalFile;
} gnu;
//struct gnuObject gnu;
void deleteAuxiliarFile();
void initGNUPlot(char *treeD, char *fourD, char *pointType, char *pointSize);
void chooseD();
void addPlot(char *fileToPlot, char *auxiliarscriptfile);
//void composeGNUFile();
void makeGNUScript(int nrOfFiles, char *basefileName,char *auxiliarscriptfile, int stella);
void makeGNUPlot( int nroOfFiles, char* filebase, char* D3, char *D4, char *pointType, char *pointSize, int stella);
