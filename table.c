#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count[100];


/*******************
** read_dictionary()   
** Função: lê o ficheiro do dicionário, constrói uma tabela em que temos 100 indices
**         e em que guarda em cada indice o número de palavras do tamanho da palavra. 
**         Devolve o número total de palavras.      
********************/
void read_dictionary(FILE *InputFile1, int table_words[]){
  
  char word[100];
  int i = 0;

  for(i = 0; i< 100; i++){
      table_words[i] = 0;
  }

  while(fscanf(InputFile1, "%s", word) != -1){

      table_words[strlen(word)-1]+=1;
   
  }
}


/*******************
** char ***array_3d()   
** Função: Alocamos o espaço necessário para colocarmos o 
**         dicionário na nossa estrutura, a qual vai ser criada nesta função.      
********************/
char ***array_3d(int table_words[]){

    char*** array = NULL;
    int i = 0, j = 0;

    array = (char***)malloc((sizeof (char**))*100);

    if(array == NULL){
        exit (0);
    }

    for(i = 0; i<100; i++){
        array[i] = NULL;
        array[i] = (char**)malloc((sizeof (char*))*table_words[i]); //aloca memoria para o numero de palavras com dimensao i+1
    
        if(array[i] == NULL){
        exit (0);
        }
        for(j=0;j<table_words[i];j++){
            array[i][j] = NULL;
            array[i][j] = (char*)malloc((sizeof (char))*(i+2)); // +1 porque o  índice (i) é o tamanho -1, e +1 por causa do '\0'.

            if(array[i][j] == NULL){
                exit (0);
            }
            array[i][j][0]='\0';
        }

    }

    return array;

}


/*******************
** void table_fill()   
** Função: Lemos novamente o dicionário para retirarmos dele as palavras
**         e guardarmos na nossa estrutura de dados.     
********************/
void table_fill(char ***array, FILE *InputFile1, int table_words[]){

    char word[100];
    int i = 0, size=0;

    for (i = 0; i< 100; i++)
    {
        count[i] = 0;
    }

    while(fscanf(InputFile1, "%s", word) != -1){
        size = strlen(word)-1;
        if (table_words[size]!= 0){
            strcpy(array[size][count[size]], word);
            count[size]+=1;
        }
            
    }
    fclose(InputFile1);
}


/*******************
** int binary_search()   
** Função: Esta função faz, através da procura binária, a procura da posição
            da palavra para o modo 2.     
********************/
int binary_search(char **array, char *word, int l, int r){

    while (r >= l){

        int compare = 0;
        int m = (l+r)/2;
        
        compare = strcmp(word, array[m]);
       
        if (compare == 0){
            return m;        
        }

        if(compare < 0){
            r = m-1;
        }
        else{
            l = m+1;
        }
    }

    return -1;
}


/*******************
** void partition()   
**    
********************/
int partition(char **a, int l, int r){
    int i, j;
    char v[100];
    char aux[100];
    int size = 0;

    strcpy(v, a[r]); i = l-1; j = r;
    for (;;){
        while (strcmp(a[++i], v)<0){} 
        while(strcmp(v, a[--j]) < 0)
        {
            if (j == l) break;
        }
        if (i >= j) break;
        strcpy(aux, a[i]);
        strcpy(a[i], a[j]);
        strcpy(a[j], aux);
    }
    size = strlen(a[i]);
    strcpy(aux, a[r]);
    memmove(a[r], a[i], size);
    //strcpy(a[r], a[i]);
    strcpy(a[i], aux);
    return i;

}


/*******************
** void quick_sort()   
** Função: Algortimo que ordena as tabelas    
********************/
void quicksort(char **a, int l, int r){
    int i = 0;

    if (r <= l) return;
        i = partition(a, l, r);
        quicksort(a, l, i-1);
        quicksort(a, i+1, r);
}


/*******************
** void free_everything()   
** Função: Esta função    
********************/
void free_everything(char ***array, int table_words[], char *OutputFilename){

    int i = 0, j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < table_words[i]; j++){
            free(array[i][j]);
        }

        free(array[i]);
    }

    free(array);
    free(OutputFilename);
}
//////////////////////////////////////77
void print_dict(char ***array, int table_words[]){
    int i,j;
    for(i=0; i<100;i++){
        printf("***Palavras de tamanho %d***\n",i+1);
        for(j=0;j<table_words[i];j++)
            printf("%s\n",array[i][j]);
    }
}
