#ifndef _GRAPH_
#define _GRAPH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "table.h"

typedef struct adjacency
{
    int idxA; 
    int idxB;
    int cost;
    struct adjacency *next;   
}adjacency;

typedef struct Graph
{
    int V;
    struct adjacency **adj;
}Graph;

typedef struct heap
{
    int free;   /* Numero de elementos no acervo */
    int size;
    int *queue;
}heap;

Graph *init_Graph(int V);
adjacency **create_adj_list(char **words_array, Graph *graph, int mut_max, int words_counted);
void search_for_best_route(Graph **graph, char **words_array, char *init, char *end, FILE *fp_out, int words_counted, int mut_max, int *num_graphs, int *adj_data);
adjacency *insertadjacency(adjacency *head, int sideB, int cost, int sideA);
int square(int count);
void freeLinkedList(adjacency *first);
void free_graph(Graph *graph);
void dijkstra(Graph *G, int *wt, int *st, int start, int end, int mut_max);
heap *PQinit(int Size);
heap *update_queue(heap *acervo, int *wt, int w);
int PQempty(heap *acervo);
int PQdelmin(heap **acervo, int *wt);
heap *FixDown(heap *acervo,int *wt, int Idx, int N);
heap *FixUp(heap *acervo, int *wt, int Idx);
int HigherPri(int a, int b);
void print_path(FILE *fp_out, int *st, Graph *graph, int *dist_final, int son, char **words_array);
#endif