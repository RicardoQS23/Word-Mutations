#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"


char *Files_Ext(char *InputFilename1, char *InputFilename2){

  const char dot = '.', InputExtension1[] = ".dict", InputExtension2[] = ".pals", OutputExtension[] = ".stats";
  char *validation1 = strrchr(InputFilename1, dot), *validation2 = strrchr(InputFilename2, dot), *OutputFilename = NULL;

   if ((strcmp(InputExtension1, validation1) != 0)){   /* Checks the extension of dictionary file */
        exit(0);
  }


  if ((strcmp(InputExtension2, validation2) != 0)){   /* Checks the extension of problems file */
        exit(0);
  }
  else {
    OutputFilename = (char *) malloc((strlen(InputFilename2) + 2) * sizeof(char));  /* Puts the correct Output File Extension */
    strcpy(OutputFilename, InputFilename2);
    OutputFilename[strlen(OutputFilename) - strlen(InputExtension2)] = '\0';
    strcat(OutputFilename, OutputExtension);
  }

  return OutputFilename;
}


FILE *OpenFiles(char *filename, char *mode){

   FILE *fp;

   fp = fopen(filename, mode);

   if (fp == NULL){
     exit(0);
   }

   return fp;
}
