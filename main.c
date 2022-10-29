#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "files.h"

int main(int argc, char *argv[]) {

    char ***array=NULL;
    int table_words[100];

    if (argc != 3){ 
        exit (0);
    }
    char *InputFilename1 = argv[1], *InputFilename2 = argv[2], *OutputFilename=NULL;

    OutputFilename = Files_Ext(InputFilename1, InputFilename2); /* Check the files extension and creates the outputfile  */

    FILE *InputFile1 = OpenFiles(InputFilename1, "r"); /* Opens the input file .dict in read mode */

    read_dictionary(InputFile1, table_words);

    array = array_3d(table_words);
    table_fill(array, InputFile1, table_words);

    int i = 0;

    for (i = 0; i < 100; i++){
        quicksort(array[i], 0, (table_words[i]-1));
    }
    
    //print_dict(array, table_words);

    FILE *InputFile2 = OpenFiles(InputFilename2, "r");
    
    char init[100], end[100];
    int count = 1, size=0, mut_numb = 0;


    while(fscanf(InputFile2, "%s %s %d", init, end, &mut_numb) == 3){
        size = strlen(init)-1;

        //printf("Dimensao das palavras para o problema #%d e mutaçoes maximas = %d\n", size, mut_numb);
        count+=1;
    }
    fclose(InputFile2);
    
    FILE *OutputFile = OpenFiles(OutputFilename, "a");
   process_problems(InputFile2, OutputFile, table_words, array);

    free_everything(array, table_words, OutputFilename);


  return 0;
}

