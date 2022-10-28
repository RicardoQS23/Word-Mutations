#ifndef Proj_INCLUDED
#define Proj_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Stack stack;

typedef struct adjacency
{
    int sideB;
    int cost;
    int idx; 
    struct adjacency *next;   
}adjacency;

typedef struct heap
{
    int free;
    int size;
    int *queue;
}heap;

typedef struct WallList
{
    int idx;
    struct WallList *next;
}WallList;

typedef struct Graph
{
    int V;
    struct adjacency **adj;
}Graph;

void dfs(stack *Pilha, int **labyrinth, int L, int C, int cur_idx, int tag);
int Pop(stack **Pilha);
stack *Push(stack *Pilha, int idx);
int Read_intermediate(FILE *fp_in, FILE *fp_out, int L, int C, char *out_name, char *filename);
void Read_final(FILE *fp_in, FILE *fp_out, int L, int C, char *out_name, char *filename);
int inside_labyrinth(int y,int x, int L, int C);
void print_wall_list (WallList * head, int);
WallList *create_wall_entry (WallList *head, int id);
void programa_final(int **labyrinth, WallList *wall_list, int L, int C, int a, int b, FILE *fp_out);
void dfs(stack *Pilha, int **labyrinth, int L, int C, int cur_idx, int tag);
int north_south (int **labyrinth, int L, int C, int idx);
int west_east (int **labyrinth, int L, int C, int idx);
adjacency *insertadjacency(adjacency *head, int side, int **labyrinth, int idx, int C);
void write_graph(Graph *graph, int C);
adjacency **create_adj_list(int **labyrinth, WallList *wall_list, Graph *grapho, int L, int C);
int must_create_node(adjacency **head1, adjacency **head2, WallList *wall, int **labyrinth, int sideA, int sideB, int C);
adjacency *cost_is_smaller(int **labyrinth, adjacency *ad, WallList *wall, int C);
void free_graph(Graph *graph);
void freeLinkedList(adjacency *first);
void free_wall_list(WallList *wall_head);
void GRAPHpfs(Graph *G, int *wt, int *st ,int start, int finish);
heap *PQinit(int Size);
heap *PQinsert(heap *acervo, int *wt, int room);
int PQdelmin(heap **acervo, int *wt);
heap *FixUp(heap *acervo, int *wt, int Idx);
void exch(int *a, int *b);
int PQempty(heap *acervo);
heap *update_queue(heap* acervo, int *wt, int w);
int HigherPri(int a, int b);
heap *FixDown(heap *acervo,int *wt, int Idx, int N);
char *allocate_outputname_final(char *out_name, char *in_name);
void write_output_final(FILE *fp_out, int final_room, int *st, Graph *grapho, int C);
void path_find(FILE *fp_out, int *st, Graph *grapho,int *dist_final, int *count_walls, int son, int C);



/**
 * @brief Processa informaçao lida diretamente do ficheiro
 * 
 * @param filename nome do ficheiro de entrada
 */
void Read_input_file(char *filename, char program_mode);

/**
 * @brief invoca a interface de ajuda ao utilizador
 * 
 */
void help(void);

/**
 * @brief Teste A1
 * 
 * @param a ordenada do ponto
 * @param b abcissa do ponto
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas
 * @param C numero de colunas
 * @return int retorna o valor do teste A1
 */
int mode_A1(int a, int b, int **labyrinth, int L, int C);

/**
 * @brief Teste A2
 * 
 * @param a ordenada do ponto
 * @param b abcissa do ponto
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas
 * @param C numero de colunas
 * @return int retorna o valor do teste A2
 */
int mode_A2(int a, int b, int **labyrinth, int L, int C);

/**
 * @brief Teste A3
 * 
 * @param a ordenada do ponto
 * @param b abcissa do ponto
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas
 * @param C numero de colunas
 * @return int retorna o valor do teste A3
 */
int mode_A3(int a, int b, int **labyrinth, int L, int C);

/**
 * @brief Teste A4
 * 
 * @param a ordenada do ponto
 * @param b abcissa do ponto
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas
 * @param C numero de colunas
 * @return int retorna o valor do teste A4
 */
int mode_A4(int a, int b, int **labyrinth, int L, int C);

/**
 * @brief Teste A5
 * 
 * @param a ordenada do ponto
 * @param b abcissa do ponto
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas
 * @param C numero de colunas
 * @return int retorna o valor do teste A5
 */
int mode_A5(int a, int b, int **labyrinth, int L, int C);

/**
 * @brief 
 * 
 * @param a ordenada do ponto start
 * @param b abcissa do ponto start
 * @param l ordenada do ponto finish
 * @param c abcissa do ponto finish
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas
 * @param C numero de colunas
 * @return int retorna o valor do teste A6
 */
int mode_A6(int a, int b, int l, int c, int **labyrinth, int L, int C);

/**
 * @brief Aloca o vetor para incluir o nome do ficheiro de entrada
 * 
 * @param argv string introduzida na linha de comandos com o nome do ficheiro de entrada
 * @param filename string
 * @param program_mode identifica o tipo de programa a ser corrido
 * @return char* retorna a string já alocada dinamicamente
 */
char *get_inputfilename(char **argv, char *filename, char program_mode);

/**
 * @brief Escolhe o teste a fazer sobre o labirinto analisado
 * 
 * @param test_mode string
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas
 * @param C numero de colunas
 * @param a ordenada do ponto start
 * @param b abcissa do ponto start
 * @param c ordenada do ponto finish
 * @param d abcissa do ponto finish
 * @return int retorna o resultado do teste efetuado
 */
int choose_test(char *test_mode, int **labyrinth, int L, int C, int a, int b, int c, int d);


void print_table(int **labyrinth, int L, int C);

/**
 * @brief liberta a memoria alocada dinamicamente para o labirinto
 * 
 * @param labyrinth tabela com o labirinto
 * @param L numero de linhas do tabuleiro
 */
void free_labyrinth(int **labyrinth, int L);

/**
 * @brief escreve no ficheiro de saída o valor do resultado do teste
 * 
 * @param fp pointer para o ficheiro de saida
 * @param result valor do resultado do teste
 */
void write_output(FILE *fp, int result);

/**
 * @brief cola para a string com o ficheiro de saida o nome do ficheiro de entrada
 * 
 * @param name nome do ficheiro de saida
 * @param filename nome do ficheiro de entrada
 * @param num_chars numero de caracteres a serem colados
 */
void str_paste(char *name, char *filename, int num_chars);

/**
 * @brief encontra o ultimo caracter '.'
 * 
 * @param filename nome do ficheiro de entrada
 * @return int retorna a posicao do caracter '.' na string do nome do ficheiro de entrada 
 */
int find_last_period(char *filename);

/**
 * @brief aloca memoria para a string com o nome do ficheiro de saida
 * 
 * @param out_name string com o nome do ficheiro de saida
 * @param in_name nome do ficheiro de entrada
 * @return char* string com o nome do ficheiro de saida
 */
char *allocate_outputname(char *out_name, char *in_name);

/**
 * @brief aloca memoria dinamicamente para a tabela com o labirinto
 * 
 * @param labyrinth tabela com o labirinto
 * @param C numero de colunas do labirinto
 * @param L numero de linhas do labirinto
 * @return int** retorna um vetor de ponteiros para vetores de ints
 */
int **allocate_table(int **labyrinth, int C, int L);

/**
 * @brief abre o ficheiro de entrada
 * 
 * @param fp_in apontador para o ficheiro de entrada
 * @param filename nome do ficheiro de entrada
 * @return FILE* retorna o apontador para o ficheiro de entrada
 */
FILE *open_inputfile(FILE *fp_in, char *filename);
/**
 * @brief abre o ficheiro de saida
 * 
 * @param fp_out apontador para o ficheiro de entrada
 * @param filename nome do ficheiro de saida
 * @return FILE* retorna o apontador para o ficheiro de saida
 */
FILE *open_outputfile(FILE *fp_out, char *filename);
/**
 * @brief em caso de erro libertar memoria
 * 
 * @param fp_in ponteiro para ficheiro de entrada
 * @param fp_out ponteiro para ficheiro de saida
 * @param filename_out apontador para vetor de chars com o nome do ficheiro de saida
 * @param filename_in apontador para vetor de chars com nome do ficheiro de entrada
 */
void error(FILE *fp_in, FILE *fp_out, char *filename_out, char *filename_in);

/**
 * @brief Get the index object
 * 
 * @param a ordenada do ponto
 * @param b abcissa do ponto
 * @param C numero de colunas do labirinto
 * @return int retorna o indice num vetor do tipo v[i]
 */
int get_index(int a, int b, int C);

/**
 * @brief conecta todos os elementos do labirinto das respetivas salas
 * 
 * @param id vetor com indices/etiquetas
 * @param labyrinth tabela com o labirinto
 * @param sz vetor com os tamanhos de cada grupo de etiquetas
 * @param L numero de linhas
 * @param C numero de colunas
 * @param N numero de elementos no tabuleiro(L*C)
 */
void make_families(int *id, int **labyrinth, int *sz, int L, int C, int N);

/**
 * @brief Algoritmo de uniao de objetos
 * 
 * @param id vetor com indices/etiquetas
 * @param labyrinth tabela com o labirinto
 * @param sz vetor com os tamanhos de cada grupo de etiquetas
 * @param p indice de um ponto vizinho
 * @param q indice de um ponto vizinho
 * @param N numero de elementos no tabuleiro(L*C)
 */
void compressed_weighted_quick_union(int *id, int **labyrinth, int *sz, int p, int q, int N);
int verify_extension(char *filename);
#endif