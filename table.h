#ifndef _TABLE_H
#define _TABLE_H

#include "files.h"

void read_dictionary(FILE *InputFile1, int table_words[]);

char ***array_3d(int *table_words);

void table_fill(char ***array, FILE *InputFile1, int table_words[]);

int binary_search(char **arr, char *word, int first, int last);

void quicksort(char **a, int l, int r);

int partition(char **a, int l, int r);

void free_everything(char ***array, int table_words[], char *OutputFilename);
////////////////////
void print_dict(char ***array, int table_words[]);
#endif






