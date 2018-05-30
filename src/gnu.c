
#include <stdio.h>
#include "file.h"
#include "gnu.h"

void deleteAuxiliarFile()
{
         FILE *fp1 = fopen(gnuscriptFile1, "w");
         fclose(fp1);
         FILE *fp2 = fopen(gnuscriptFile2, "w");
         fclose(fp2);
}

void makeGNUPlot(int nroOfFiles, char* filenameroot, char* D3, char *D4, char *pointType, char *pointSize, int stella)
{

     deleteAuxiliarFile();

    initGNUPlot(D3, D4, pointType, pointSize);

    gnu.surface = 1;
    chooseD();
    makeGNUScript(nroOfFiles, filenameroot,gnuscriptFile2,stella);
    mergeFiles(gnu.baseFile, gnuscriptFile2, gnu.finalFile);
   
    gnu.surface = 0;
    chooseD();
    makeGNUScript(nroOfFiles, filenameroot,gnuscriptFile1,stella);
    mergeFiles(gnu.baseFile, gnuscriptFile1, gnu.finalFile);
 
}
void initGNUPlot(char *treeD, char *fourD, char *pointType, char *pointSize)
{
   
    gnu.treeD = treeD;
    gnu.fourD = fourD;
    gnu.pointType = pointType;
    gnu.pointSize = pointSize;
}

void chooseD()
{
    gnu.toUseD = gnu.treeD;
    gnu.baseFile = gnuPlotBaseFile;
    gnu.finalFile = gnuPlotFinalFile;
    if (gnu.surface == 1)
    {
        gnu.toUseD = gnu.fourD;
        gnu.finalFile = gnuSurfaceFinalFile;
        gnu.baseFile = gnuSurfaceBaseFile;
    }
}

void addPlot(char *fileToPlot, char * gnuscriptFile)
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




//1
void makeGNUScript(int nrOfFiles, char *filenameroot, char *scriptauxiliar, int stella)
{
    char *lastFile = FULL_SIZE;
    char *aux_ext = "m";
    for (int i = 0; i <= nrOfFiles; i++) //loop del algoritmo
    {
        char *fileData = getFileName(i, filenameroot);
       
        char *newString = FULL_SIZE;
        strcpy(newString, fileData);
        if (i > 0)
        {
            if (stella)
            {
               strcat(newString, aux_ext);
               mergeFiles(fileData, lastFile, newString);
            }
            addPlot(newString,scriptauxiliar);
        }
        strcpy(lastFile, newString);
     
       // printf(lastFile);
      //  printf("\t");
       // printf("ok\n");
    }
}
