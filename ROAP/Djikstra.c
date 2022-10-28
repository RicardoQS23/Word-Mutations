#include "Proj.h"
#define P (wt[v] + t->cost)
#define INFINITY INT_MAX
#define exch(a, b) { int t = a; a = b; b = t; }

void GRAPHpfs(Graph *G, int *wt, int *st, int start, int finish)
{
    int v, w;
    adjacency *t = NULL;
    heap *acervo = NULL;

    acervo = PQinit(G->V);
    for (v = 0; v < G->V; v++)
    {
        st[v] = -1;
        wt[v] = INFINITY; //distancias
    }
    wt[start] = 0;
    st[start] = 0;
    acervo = PQinsert(acervo, wt, start);

    while (!PQempty(acervo))
    {
        v = PQdelmin(&acervo, wt); //POP
        for (t = G->adj[v]; t != NULL; t = t->next)
        {
            w = t->sideB;
            if (wt[w] == INFINITY)
            {
                wt[w] = P;
                st[w] = v;
                acervo = PQinsert(acervo, wt, w);
            }
            else //esta no acervo
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

heap *PQinit(int Size)
{
    heap *aux = NULL;
    aux = (heap *)malloc(sizeof(heap));

    aux->queue = (int *)malloc(Size * sizeof(int));
    aux->size = Size;
    aux->free = 0;

    return aux;
}

heap *update_queue(heap *acervo, int *wt, int w)
{
    int i = 0;
    for (i = 0; i < acervo->free; i++)
    {
        if (acervo->queue[i] == w)
        {
            acervo = FixUp(acervo, wt, i);
            return acervo;
        }
    }
    return acervo;
}

int PQempty(heap *acervo)
{
    return ((acervo->free == 0) ? 1 : 0);
}

heap *PQinsert(heap *acervo, int *wt, int room)
{
    /* insere novo elemento no fim e restabelece ordenação com FixUp */
    if ((acervo->free + 1) < acervo->size)
    {
        acervo->queue[acervo->free] = room;
        acervo = FixUp(acervo, wt, acervo->free);
        acervo->free += 1;
    }
    return acervo;
}

int PQdelmin(heap **acervo, int *wt)
{
    /* troca maior elemento com último da tabela e reordena com FixUp */
    exch((*acervo)->queue[0], (*acervo)->queue[((*acervo)->free) - 1]);
    *acervo = FixDown(*acervo, wt, 0, (*acervo)->free -1);
    /* ultimo elemento não considerado na reordenação */
    return (*acervo)->queue[--((*acervo)->free)];
}

heap *FixUp(heap *acervo, int *wt, int Idx)
{
    while (Idx > 0 && (wt[acervo->queue[(Idx - 1) / 2]] > wt[acervo->queue[Idx]]))
    {
        exch(acervo->queue[Idx], acervo->queue[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
    return acervo;
}

heap *FixDown(heap *acervo,int *wt, int Idx, int N)
{
    int Child; /* índice de um nó descendente */
    while (2 * Idx < N - 1)
    {
        Child = (2 * Idx) + 1;

        if (Child < (N - 1) && HigherPri(wt[acervo->queue[Child]], wt[acervo->queue[Child + 1]]))
            Child++;
        if (!HigherPri(wt[acervo->queue[Idx]], wt[acervo->queue[Child]]))
            break; /* condição acervo */
        /* satisfeita */
        exch(acervo->queue[Idx], acervo->queue[Child]);
        /* continua a descer a árvore */
        Idx = Child;
    }
    return acervo;
}

int HigherPri(int a, int b)
{
    if(a > b)
        return 1;
    else
        return 0;
}