#include "graph.h"
#define P (wt[v] + t->cost)
#define INFINITY INT_MAX
#define exch(a, b) { int t = a; a = b; b = t; }

/**
 * Graph *init_Graph()
 * Função:  Inicializa o grafo com o numero de vertices do mesmo e uma lista de adjacencias vazia
*/
Graph *init_Graph(int V)
{
    Graph *grafo = (Graph *)malloc(sizeof(Graph));

    if (grafo == NULL)
    {
        fprintf(stderr, "Não conseguiu alocar memoria para o grafo\n");
        return NULL;
    }
    grafo->V = V;
    grafo->adj = (adjacency **)calloc(V, sizeof(adjacency *));
    if (grafo->adj == NULL)
    {
        fprintf(stderr, "Não conseguiu alocar memoria para o grafo\n");
        return NULL;
    }
    return grafo;
}

/**
 *  int square()
 *  Função: Retorna o valor quadrático do argumento 
 */
int square(int count){
    return count*count;
}

/**
 * adjacency *insertadjacency()
 * Função:  Retorna uma instãncia de adjacencia com os valores de idxA, idxB, cost e head já atribuidos
*/
adjacency *insertadjacency(adjacency *head, int sideB, int cost, int sideA)
{
    adjacency *new = NULL;
    new = (adjacency *)malloc(1 * sizeof(adjacency));

    if (new == NULL)
    {
        fprintf(stderr, "Não conseguiu alocar memoria para o grafo\n");
        return NULL;
    }
    new->idxA = sideA;
    new->idxB = sideB;
    new->cost = cost;
    new->next = head;

    return new;
}

/**
 * adjacency **create_adj_list()
 * Função:  Cria a lista de adjacencias associada ao grafo
*/
adjacency **create_adj_list(char **words_array, Graph *graph, int mut_max, int words_counted)
{
    int sideA = 0, sideB = 0, k = 0, count = 0;

    for(sideA = 0; sideA < words_counted; sideA++){
        for(sideB = sideA+1; sideB < words_counted; sideB++){
            count = 0;
            for(k=0; k <= strlen(words_array[sideA]); k++){
                if(words_array[sideA][k]!=words_array[sideB][k])    count+=1;
            }
            if(count <= mut_max && count > 0){
               graph->adj[sideA] = insertadjacency(graph->adj[sideA], sideB, square(count), sideA);
               graph->adj[sideB] = insertadjacency(graph->adj[sideB], sideA, square(count), sideB); 
            }
        } 
    }
    return graph->adj;
}

/**
 * void freeLinkedList()
 * Função:  Liberta a memoria alocada para a Linked list
*/
void freeLinkedList(adjacency *first)
{
    adjacency *aux, *next;
    for (aux = first; aux != NULL; aux = next)
    {
        next = aux->next;
        free(aux);
    }
}

/**
 * void free_graph()
 * Função: Liberta a memoria alocada para o grafo
*/
void free_graph(Graph *graph)
{
    int i;
    for (i = 0; i < graph->V; i++)
    {
        freeLinkedList(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
}

/**
 * heap *PQinit()
 * Função:  Inicializa a fila de prioridade / acervo
*/
heap *PQinit(int Size)
{
    heap *aux = NULL;
    aux = (heap *)malloc(sizeof(heap));

    aux->queue = (int *)malloc(Size * sizeof(int));
    aux->size = Size;
    aux->free = 0;

    return aux;
}

/**
 * heap *update_queue()
 * Função:  Atualiza a fila de prioridade
*/
heap *update_queue(heap *acervo, int *wt, int w)
{
    int i = 0;
    for (i = 0; i < acervo->free; i++)  /* Percorre os elementos presentes no acervo*/
    {
        if (acervo->queue[i] == w)  /* Caso encontre o elemento reordena o acervo com FixUp*/
        {
            acervo = FixUp(acervo, wt, i);
            return acervo;
        }
    }
    return acervo;
}

/**
 * int PQempty()
 * Função: Verifica se o acervo se encontra vazio, retornando 1 caso seja verdade
*/
int PQempty(heap *acervo)
{
    return ((acervo->free == 0) ? 1 : 0);
}

/**
 * heap *PQinsert()
 * Função:  Insere um novo elemento na fila de prioridade
*/
heap *PQinsert(heap *acervo, int *wt, int w)
{
    if ((acervo->free + 1) < acervo->size)  /* insere novo elemento no fim voltando a ordenar com FixUp */
    {
        acervo->queue[acervo->free] = w;
        acervo = FixUp(acervo, wt, acervo->free);
        acervo->free += 1;
    }
    return acervo;
}

/**
 * int PQdelmin()
 * Função:  É efetuada a instrução de POP do elemento com maior prioridade da queue do acervo
*/
int PQdelmin(heap **acervo, int *wt)
{
    exch((*acervo)->queue[0], (*acervo)->queue[((*acervo)->free) - 1]);     /* o maior elemento da tabela é trocado com o último e é reordenado com FixUp */
    *acervo = FixDown(*acervo, wt, 0, (*acervo)->free -1);
                                                                        
    return (*acervo)->queue[--((*acervo)->free)];   /* nao considera o ultimo elemento na reordenação */
}

/**
 * heap *FixUp()
 * Função:  Vai subindo no acervo e comparando a prioridade dos nós descendentes com os ascendentes
*/
heap *FixUp(heap *acervo, int *wt, int Idx)
{
    while (Idx > 0 && (wt[acervo->queue[(Idx - 1) / 2]] > wt[acervo->queue[Idx]]))
    {
        exch(acervo->queue[Idx], acervo->queue[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
    return acervo;
}

/**
 * heap *FixDown()
 * Função:  Vai descendo no acervo e comparando a prioridade dos nós ascendentes com os descendentes
*/
heap *FixDown(heap *acervo,int *wt, int Idx, int N)
{
    int Child;  /* nó descendente */
    while (2 * Idx < N - 1)
    {
        Child = (2 * Idx) + 1;

        if (Child < (N - 1) && HigherPri(wt[acervo->queue[Child]], wt[acervo->queue[Child + 1]]))   Child++;
        if (!HigherPri(wt[acervo->queue[Idx]], wt[acervo->queue[Child]]))   break;          /* condição acervo satisfeita */

        exch(acervo->queue[Idx], acervo->queue[Child]);                
        Idx = Child;    /* continua a descer a árvore */
    }
    return acervo;
}

/**
 * int HigherPri()
 * Função: Compara qual o maior valor, retornando 1 se for o "a" ou 0 se for o "b"
*/
int HigherPri(int a, int b)
{
    if(a > b)
        return 1;
    else
        return 0;
}

/**
 * void print_path()
 * Função: Funçao recursiva, dando printf do caminho solução e do seu respectivo custo no ficheiro de saida
*/
void print_path(FILE *fp_out, int *st, Graph *graph, int *dist_final, int son, char **words_array)
{
    if (st[son] == -1)
    {
        fprintf(fp_out, "%s %d\n", words_array[son],*dist_final);
        return;
    }
    adjacency *aux = NULL;

    for (aux = graph->adj[st[son]]; aux != NULL; aux = aux->next)
    {
        if (aux->idxB == son)
        {
            (*dist_final) += aux->cost;
            son = st[son];
            print_path(fp_out, st, graph, dist_final, son, words_array);
            fprintf(fp_out, "%s\n", words_array[aux->idxB]);
            break;
        }
    }
}

/**
 * void dijkstra()
 * Função:  Algoritmo de procura de caminho de menor custo
*/
void dijkstra(Graph *G, int *wt, int *st, int start, int end, int mut_max)
{
    int v, w;
    adjacency *t = NULL;
    heap *acervo = NULL;
    acervo = PQinit(G->V);
    for (v = 0; v < G->V; v++)
    {
        st[v] = -1;
        wt[v] = INFINITY;
    }
    wt[start] = 0;
    st[start] = -1;
    acervo = PQinsert(acervo, wt, start);

    while (!PQempty(acervo))
    {
        v = PQdelmin(&acervo, wt);  /* Pop */
        if(v==end){ /* termina o algoritmo assim que encontra o vertice destino */
            free(acervo->queue);
            free(acervo);
            return;
        } 

        for (t = G->adj[v]; t != NULL; t = t->next)
        {
            if(t->cost > square(mut_max))   continue;
                
            w = t->idxB;
            if (wt[w] == INFINITY)  
            {
                wt[w] = P;
                st[w] = v;
                acervo = PQinsert(acervo, wt, w);
            }
            else /* Já se encontra no acervo */
            {
                if (wt[w] > P)
                {
                    wt[w] = P;
                    acervo = update_queue(acervo, wt, w);
                    st[w] = v;
                }
            }
        }
    }
    free(acervo->queue);
    free(acervo);
}

/**
 * void search_for_best_route()
 * Função:  Funçao responsavel pela impressão dos diversos caminhos solução de cada problema num ficheiro de saída
*/
void search_for_best_route(Graph **graph, char **words_array, char *init, char *end, FILE *fp_out, int words_counted, int mut_max, int *num_graphs, int *adj_data)
{
    if(strcmp(init,end)==0){    //caso as palavras sejam a mesma
        fprintf(fp_out,"%s 0\n%s\n\n", init, end);
        return;
    }
    int i = 0 , count = 0, size = strlen(init)-1;

    if(strcmp(init,end)!=0){
        for(i=0;i<=strlen(init);i++){
            if(init[i] != end[i])   count +=1;
        }
        if(count == 1){ //caso em que as palavras diferem em apenas uma letra e nao é preciso criar um grafo
            fprintf(fp_out,"%s 1\n%s\n\n", init, end);
            return;
        }

        if(mut_max == 0){   //caso em que o numero maximo de mutaçoes é nulo
            fprintf(fp_out,"%s -1\n%s\n\n", init, end);
            return;
        } 
    }
    if(mut_max < 0){    //caso em que o numero maximo de mutaçoes é negativo
            fprintf(fp_out,"%s -1\n%s\n\n", init, end);
            return;
        } 


    int init_idx = binary_search(words_array, init, 0, words_counted-1);
    if(init_idx == -1){ //caso em que nao encontra a palavra no dicionario
        fprintf(fp_out,"%s -1\n%s\n\n", init, end);
        return;
    }

    int end_idx = binary_search(words_array, end, 0, words_counted-1);
    if(end_idx == -1){  //caso em que nao encontra a palavra no dicionario
        fprintf(fp_out,"%s -1\n%s\n\n", init, end);
        return;
    }

    if(graph[size] == NULL){
        graph[size] = init_Graph(words_counted);
        graph[size]->adj = create_adj_list(words_array, graph[size], adj_data[size], words_counted);
    }

    int *st = NULL, *wt = NULL;
    st = (int *)malloc(graph[size]->V * sizeof(int));
    if (st == NULL)
        exit(0);

    wt = (int *)malloc(graph[size]->V * sizeof(int));
    if (wt == NULL)
        exit(0);
    dijkstra(graph[size], wt, st, init_idx, end_idx, mut_max); 

    if (st[end_idx] == -1)  //nao existe soluçao
    {
        fprintf(fp_out, "%s -1\n%s\n\n", words_array[init_idx], words_array[end_idx]);
        num_graphs[size]+=-1;
        if(num_graphs[size] == 0)   free_graph(graph[size]);
        free(wt);
        free(st);
        return;
    }
    /* Escrita do output no ficheiro de saída */
    int dist_final = 0;
    print_path(fp_out, st, graph[size], &dist_final, end_idx, words_array);
    fprintf(fp_out,"\n");

    free(wt);
    free(st);

    num_graphs[size]-=1;    /* Atualiza o numero de problemas por resolver com o grafo das palavras com tamanho "size" */
    if(num_graphs[size] == 0)   free_graph(graph[size]);    /* Todos os problemas de dimensao "size" já foram resolvidos sendo o seu respetivo grafo libertado */
}
