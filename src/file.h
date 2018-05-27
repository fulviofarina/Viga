
#define FULL_SIZE "probandoFulvio0123456789"

void *openFile(char *file, char *mode);
void closeFile(void *pointer);
void mergeFiles(char *file1, char *file2, char *destiny);
char *getFileName(int index, char *filename);
