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

    outputFilename = Files_Ext(inputFilename1, inputFilename2);

    FILE *inputFile1 = OpenFiles(inputFilename1, "r");
    count_words(inputFile1, words_counted);
    rewind(inputFile1);     /* Retorna o ponteiro do ficheiro para o inicio do mesmo */
    dictionary = array_3d(words_counted);
    table_fill(dictionary, inputFile1, words_counted);
    /* Ordenação das palavras no dictionary */
    for (int i = 0; i < 100; i++){
        quicksort(dictionary[i], 0, (words_counted[i]-1));
    }
    FILE *inputFile2 = OpenFiles(inputFilename2, "r");
    /* Alocação de memoria de alguns vetores */
    char *init = (char *)malloc(sizeof(char)*100);
    if(init==NULL){
        printf("Não conseguiu alocar memoria!\n");
        exit(0); 
    }
    char *end = (char *)malloc(sizeof(char)*100);
    if(end==NULL){
        printf("Não conseguiu alocar memoria!\n");
        exit(0); 
    }

    int *num_graphs = (int *)calloc(100, sizeof(int));
    if(num_graphs==NULL){
        printf("Não conseguiu alocar memoria!\n");
        exit(0); 
    }

    int *adj_data = (int *)calloc(100, sizeof(int));
    if(adj_data==NULL){
        printf("Não conseguiu alocar memoria!\n");
        exit(0); 
    }
    /* Primeira leitura do ficheiro de entrada .pals */
    int size = 0, mut_numb = 0;
    while(fscanf(inputFile2, "%s %s %d", init, end, &mut_numb) == 3){   /* Lê o ficheiro .pals pela primeira vez, guardando alguns dados importantes como o numero de problemas com palavras de dimensao "size" e o valor maximo de mutações para os diferentes problemas com tamanho "size" */
        size = strlen(init)-1;
        num_graphs[size]+=1;
        if(adj_data[size] < mut_numb)    adj_data[size] = mut_numb;  /* Atualiza o valor maximo de mutações para os diferentes problemas com tamanho "size" */
    }
    rewind(inputFile2);

    FILE *outputFile = OpenFiles(outputFilename, "w");
    /* Alocação de memoria do vetor de grafos */
    Graph **graph = NULL;
    graph = (Graph **)calloc(100, sizeof(Graph *));        
    if(graph == NULL)    
    {
    fprintf(stderr, "Error when allocating memory!\n");
    exit(0);
    }
    /* Segunda leitura do ficheiro de entrada .pals */
    while(fscanf(inputFile2, "%s %s %d", init, end, &mut_numb) == 3){   /* Começa a resolver os diferentes problemas do ficheiro de entrada .pals */

        size = strlen(init)-1;
        char **words_array = dictionary[size];  /* Apontador para o vetor de strings de tamanho do problema a resolver*/
        search_for_best_route(graph, words_array, init, end, outputFile, words_counted[size], mut_numb, num_graphs, adj_data);
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

