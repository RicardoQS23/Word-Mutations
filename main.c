#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

int main(int argc, char *argv[]) {

    char ***dictionary=NULL;
    int words_counted[100];

    if (argc != 3){ 
        exit (0);
    }
    char *inputFilename1 = argv[1], *inputFilename2 = argv[2], *outputFilename=NULL;

    outputFilename = Files_Ext(inputFilename1, inputFilename2); /* Check the files extension and creates the outputfile  */

    FILE *inputFile1 = OpenFiles(inputFilename1, "r"); /* Opens the input file .dict in read mode */
    count_words(inputFile1, words_counted);
    rewind(inputFile1);     /*returns the file pointer to the beginning of the file*/
    dictionary = array_3d(words_counted);
    table_fill(dictionary, inputFile1, words_counted);

    for (int i = 0; i < 100; i++){
        quicksort(dictionary[i], 0, (words_counted[i]-1));
    }

    FILE *inputFile2 = OpenFiles(inputFilename2, "r");
    char *init = (char *)malloc(sizeof(char)*100);
    if(init==NULL){
        printf("Couldn't allocate memory!\n");
        exit(0); 
    }
    char *end = (char *)malloc(sizeof(char)*100);
    if(end==NULL){
        printf("Couldn't allocate memory!\n");
        exit(0); 
    }  
   
    int count = 1, size=0, mut_numb = 0;
    FILE *outputFile = OpenFiles(outputFilename, "a");

    while(fscanf(inputFile2, "%s %s %d", init, end, &mut_numb) ==3){
        size = strlen(init)-1;
        count+=1;
        char **words_array = dictionary[size];
        search_for_best_route(words_array, init, end, outputFile, words_counted[size], mut_numb);
    }

    fclose(inputFile2);
    free(init);
    free(end);
    fclose(outputFile);
    free_everything(dictionary, words_counted, outputFilename);

  return 0;
}

