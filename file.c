#include "file.h"
#include <stdio.h>


void *openFile(char *file, char *mode)
{
    return (void *)fopen(file, mode);
}

void closeFile(void *pointer)
{
    fclose((FILE *)pointer);
}
void mergeFiles(char *file1, char *file2, char *destiny)
{
    char ch;
    FILE *fs1 = fopen(file1, "r");
    FILE *fs2 = fopen(file2, "r");

    FILE *ft = fopen(destiny, "w");

    if (ft == NULL)
    {
        perror("Error ");
        printf("Press any key to exit...\n");
        exit(1);
    }

    while ((ch = fgetc(fs1)) != EOF)
        fputc(ch, ft);

    while ((ch = fgetc(fs2)) != EOF)
        fputc(ch, ft);
}

char *getFileName(int index, char *filename)
{
    char *dat_ext = ".dat";
    char *originalFile = FULL_SIZE;
    strcpy(originalFile, filename);
    char *ext = FULL_SIZE;
    strcpy(ext, "");
    char *fileData = FULL_SIZE;
    strcpy(fileData, originalFile);
    itoa(index, ext, 10);
    strcat(fileData, ext);
    strcat(fileData, dat_ext);

    return fileData;
}