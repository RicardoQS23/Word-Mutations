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

    int *num_graphs = (int *)calloc(100, sizeof(int));
    if(num_graphs==NULL){
        printf("Couldn't allocate memory!\n");
        exit(0); 
    }

    int *adj_data = (int *)calloc(100, sizeof(int));
    if(adj_data==NULL){
        printf("Couldn't allocate memory!\n");
        exit(0); 
    }
    int size = 0, mut_numb = 0;
    while(fscanf(inputFile2, "%s %s %d", init, end, &mut_numb) == 3){
        size = strlen(init)-1;
        num_graphs[size]+=1;
        if(adj_data[size] < mut_numb)    adj_data[size] = mut_numb;  //atualiza o numero maximo de mutaçoes do grafo
    }
    rewind(inputFile2);  
    FILE *outputFile = OpenFiles(outputFilename, "a");
    
    Graph **graph = NULL;
    graph = (Graph **)calloc(100, sizeof(Graph *));        
    if(graph == NULL)    
    {
    fprintf(stderr, "Error when allocating memory!\n");
    exit(0);
    }
    int opa = 1;
    while(fscanf(inputFile2, "%s %s %d", init, end, &mut_numb) == 3){
        printf("Linha #%d ****\n", opa);
        size = strlen(init)-1;
        char **words_array = dictionary[size];
        search_for_best_route(graph, words_array, init, end, outputFile, words_counted[size], mut_numb, num_graphs, adj_data);
        opa++;
    }
    free(graph);
    free(num_graphs);
    free(adj_data);
    fclose(inputFile2);
    free(init);
    free(end);
    fclose(outputFile);
    free_everything(dictionary, words_counted, outputFilename);

  return 0;
}

