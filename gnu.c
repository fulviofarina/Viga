
#include <stdio.h>
#include "file.h"

#include "gnu.h"

void initGNUPlot(int surface, char *treeD, char *fourD, char *pointType, char *pointSize)
{
    gnu.surface = surface;
    gnu.treeD = treeD;
    gnu.fourD = fourD;
    gnu.pointType = pointType;
    gnu.pointSize = pointSize;
}

void chooseD()
{
    gnu.toUseD = gnu.treeD;
    gnu.baseFile = gnuPlotBaseFile;
    if (gnu.surface == 1)
    {
        gnu.toUseD = gnu.fourD;
        gnu.baseFile = gnuSurfaceBaseFile;
    }
}

void addPlot(char *fileToPlot)
{
    FILE *fp = fopen(gnuscriptFile, "a");
    char *strin = "plot '";
    if (gnu.surface == 1)
        strin = "splot '";
    fprintf(fp, strin);
    fprintf(fp, fileToPlot);
    fprintf(fp, "' using ");

    fprintf(fp, gnu.toUseD);
   
    fprintf(fp, " with points palette pointsize ");
    fprintf(fp, gnu.pointSize);
    fprintf(fp, " pointtype ");
    fprintf(fp, gnu.pointType);
    
    fprintf(fp, "\n");
    fclose(fp);
}

//2
void composeGNUFile()
{
    mergeFiles(gnu.baseFile, gnuscriptFile, gnuFinalFile);
    remove(gnuscriptFile);
}

//1
void makeGNUScript(int nrOfFiles, char *basefileName)
{
    char *lastFile = FULL_SIZE;
    char *aux_ext = "m";
    for (int i = 0; i <= nrOfFiles; i++) //loop del algoritmo
    {
        char *fileData = getFileName(i, basefileName);
        char *newString = FULL_SIZE;
        strcpy(newString, fileData);
        if (i > 0)
        {
            strcat(newString, aux_ext);
            mergeFiles(fileData, lastFile, newString);
            addPlot(newString);
        }
        strcpy(lastFile, newString);

        printf(lastFile);
        printf("\t");
        printf("ok\n");
    }

   
}
