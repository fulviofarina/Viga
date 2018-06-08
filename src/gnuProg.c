
#include <stdio.h>
#include "gnu.h"

int main(int ar, char* arg[])
{

      int  nroOfFiles, stella;
      char* filebase, * pointType,  *pointSize, *D3, *D4;
   
      nroOfFiles = atoi(arg[1]);
      filebase = arg[2];
      D3= arg[3];
      D4= arg[4];
      pointType= arg[5];
      pointSize= arg[6];
      stella = atoi(arg[7]);
      makeGNUPlot(nroOfFiles, filebase, D3, D4, pointType, pointSize, stella, arg[8]);

      return 0;
}
