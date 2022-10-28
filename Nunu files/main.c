#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "table.h"


/*******************
** int verify_problem()   
** Função: Esta função verifica se o problema dado é válido. 
** Nota: esta função não verifica se as palavras pertencem ao dicionário     
********************/
int verify_problem(char *word1, char *word2, int mode){

    int i = 2;

    if(mode!=1 && mode!=2){
        return 0;
    }

    if (strlen(word1) != strlen(word2)){
        return 0;
    }

      return i;  
}


/*******************
** void process_problems()   
** Função: Esta função processa o ficheiro dos problemas. Lê problema a problema, ou seja, resolve 
            um problema de cada vez, verificando se é válido e escrevendo a resposta no Output    
********************/
void process_problems(FILE *InputFile2, FILE *OutputFile, int table_words[], char ***array){

    char word1[100], word2[100];
    int mode = 0, validator = 0, size = 0;
    int position1 = 0, position2 = 0;

    while (fscanf(InputFile2, "%s %s %d", word1, word2, &mode) == 3){

        size = strlen(word1) -1;

        validator = verify_problem(word1, word2, mode);

        if(validator == 0){
            fprintf(OutputFile, "%s %s %d\n\n", word1, word2, mode);
            mode = 5;
        }

        if (mode ==1){

            position1 = binary_search(array[size], word1, 0, table_words[size]-1);
            position2 = binary_search(array[size], word2, 0, table_words[size]-1);



            if(position1 == -1 || position2 ==-1){  /*Modo inválido pois as palavras não pertencem ao dicionário*/
                
                fprintf(OutputFile, "%s %s %d\n\n", word1, word2, mode);
            }
            else{
                fprintf(OutputFile, "%s %d\n\n", word1, table_words[size]);
            }

        }

        if(mode == 2){

            position1 = binary_search(array[size], word1, 0, table_words[size]-1);
            position2 = binary_search(array[size], word2, 0, table_words[size]-1);


            if(position1 == -1 || position2 ==-1){  /*Modo inválido pois as palavras não pertencem ao dicionário*/
            fprintf(OutputFile, "%s %s %d\n\n", word1, word2, mode);
            }
            else{
            fprintf(OutputFile, "%s %d\n", word1, position1);
            fprintf(OutputFile, "%s %d\n\n", word2, position2);
            }
        }
        
    }

    fclose(InputFile2);
    fclose(OutputFile);
    
}


int main(int argc, char *argv[]) {

    char ***array=NULL;
    int table_words[100];



    if (argc != 3){ 
        exit (0);
    }

    char *InputFilename1 = argv[1], *InputFilename2 = argv[2], *OutputFilename=NULL;


    OutputFilename = Files_Ext(InputFilename1, InputFilename2); /* Check the files extension and creates the outputfile  */

    FILE *InputFile1 = OpenFiles(InputFilename1, "r"); /* Opens the input file .dict in read mode */

    FILE *InputFile2 = OpenFiles(InputFilename2, "r");
    
    FILE *OutputFile = OpenFiles(OutputFilename, "w");


    read_dictionary(InputFile1, table_words);

    InputFile1 = OpenFiles(InputFilename1, "r"); /* Opens the input file .dict in read mode */
    
    array = array_3d(table_words);

    table_fill(array, InputFile1, table_words);

    int i = 0;

    for (i = 0; i < 100; i++){
        quicksort(array[i], 0, (table_words[i]-1));
    }
    

    process_problems(InputFile2, OutputFile, table_words, array);

    free_everything(array, table_words, OutputFilename);


  return 0;
}

