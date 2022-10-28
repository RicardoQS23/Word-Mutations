#include "Proj.h"

struct Stack
{
    int index;
    struct Stack *next;
};

stack *Push(stack *Pilha, int idx)
{
    stack *Top = (stack *)malloc(sizeof(stack));
    if (Top == NULL)
    {
        printf("Error when allocating memory!\n");
        exit(0);
    }
    Top->index = idx;
    Top->next = Pilha;
    Pilha = Top;
    return Pilha;
}

int Pop(stack **Pilha)
{
    stack *Aux = *Pilha;
    int res = Aux->index;
    *Pilha = (*Pilha)->next;
    free(Aux);
    return res;
}

int is_empty(stack *Pilha)
{
    return (Pilha == NULL);
}

int get_y(int idx, int C)
{
    return (idx / C);
}

int get_x(int idx, int C)
{
    return (idx % C);
}
/*
int make_islands(int **labyrinth, WallList *wall_list, int L, int C)
{
    stack *Pilha = NULL;
    WallList *t = NULL;
    int num_v = 0, k, y, x;
    int vetor[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}}; // vector that checks the neighbourhood
    int tag = -2;
    for (t = wall_list; t != NULL; t = t->next)
    {
        for (k = 0; k < 4; k++)
        {
            y = get_y(t->idx, C) + vetor[k][0];
            x = get_x(t->idx, C) + vetor[k][1];
            if (inside_labyrinth(y, x, L, C) && labyrinth[y][x] == 0)
            {
                dfs(Pilha, labyrinth, L, C, get_index(y, x, C), tag); // Explore  and paint all cells in this islands.
                ++num_v;                                              // increment islands 's counter
                --tag;
            }
        }
    }
    return num_v;
}*/
/*
void dfs(stack *Pilha, int **labyrinth, int L, int C, int cur_idx, int tag)
{
    labyrinth[get_y(cur_idx, C)][get_x(cur_idx, C)] = tag;
    Pilha = Push(Pilha, cur_idx);

    int i, x = 0, y = 0, next_node = 0;
    int vetor[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // vector that checks the neighbourhood

    while (!is_empty(Pilha))
    {
        cur_idx = Pop(&Pilha);
        for (i = 0; i < 4; i++)
        {
            y = get_y(cur_idx, C) + vetor[i][0];
            x = get_x(cur_idx, C) + vetor[i][1];
            if (inside_labyrinth(y, x, L, C) && labyrinth[y][x] == 0)
            {
                next_node = get_index(y, x, C);
                labyrinth[y][x] = tag;
                Pilha = Push(Pilha, next_node);
            }
        }
    }
    return;
}*/
void dfs(stack *Pilha, int **labyrinth, int L, int C, int cur_idx, int tag)
{
    labyrinth[get_y(cur_idx, C)][get_x(cur_idx, C)] = tag;
    Pilha = Push(Pilha, cur_idx);

    int i, x = 0, y = 0, next_node = 0;
    int vetor[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // vector that checks the neighbourhood

    while (!is_empty(Pilha))
    {
        cur_idx = Pop(&Pilha);
        for (i = 0; i < 4; i++)
        {
            y = get_y(cur_idx, C) + vetor[i][0];
            x = get_x(cur_idx, C) + vetor[i][1];
            if (inside_labyrinth(y, x, L, C) && labyrinth[y][x] == 0)
            {
                next_node = get_index(y, x, C);
                labyrinth[y][x] = tag;
                Pilha = Push(Pilha, next_node);
            }
        }
    }
    return;
}

int make_islands(int **labyrinth, int L, int C)
{
    stack *Pilha = NULL;
    int num_v = 0, i, j;
    int tag = -2;
    for (i = 0; i < L; ++i)
        for (j = 0; j < C; ++j)
            if (labyrinth[i][j] == 0) // visited only white cells
            {
                dfs(Pilha, labyrinth, L, C, get_index(i, j, C), tag); // Explore  and paint all cells in this islands.
                ++num_v;                                              // increment islands 's counter
                --tag;
            }

    return num_v;
}
int inside_labyrinth(int y, int x, int L, int C)
{
    return (y < L && y >= 0 && x < C && x >= 0);
}

Graph *init_Graph(int V)
{
    Graph *grafo = (Graph *)malloc(sizeof(Graph));

    if (grafo == NULL)
    {
        fprintf(stderr, "Error when allocating memory for Graph\n");
        return NULL;
    }

    grafo->V = V;
    grafo->adj = (adjacency **)calloc(V, sizeof(adjacency *));
    if (grafo->adj == NULL)
    {
        fprintf(stderr, "Error when allocating memory for Graph\n");
        return NULL;
    }
    return grafo;
}

WallList *create_wall_entry(WallList *head, int id)
{
    WallList *aux = NULL;
    if (head == NULL)
    {
        WallList *new = (WallList *)calloc(1, sizeof(WallList));
        new->next = NULL;
        new->idx = id;
        return new;
    }
    else
    {
        for (aux = head; aux->next != NULL; aux = aux->next)
            ;
        WallList *new = (WallList *)calloc(1, sizeof(WallList));
        new->idx = id;
        new->next = NULL;
        aux->next = new;
        return head;
    }
}

void print_wall_list(WallList *head, int C)
{
    WallList *aux = NULL;
    for (aux = head; aux != NULL; aux = aux->next)
        printf("Wall:%d %d\n", get_y(aux->idx, C) + 1, get_x(aux->idx, C) + 1);
}

int island_to_id(int island)
{
    return (-1) * (island + 2);
}

int north_south(int **labyrinth, int L, int C, int idx)
{
    if (inside_labyrinth(get_y(idx, C) - 1, get_x(idx, C), L, C) && inside_labyrinth(get_y(idx, C) + 1, get_x(idx, C), L, C))
    {
        if ((labyrinth[get_y(idx, C) - 1][get_x(idx, C)] != labyrinth[get_y(idx, C) + 1][get_x(idx, C)]) && (labyrinth[get_y(idx, C) - 1][get_x(idx, C)] < -1) && (labyrinth[get_y(idx, C) + 1][get_x(idx, C)]) < -1)
            return 1;
    }
    return 0;
}

int west_east(int **labyrinth, int L, int C, int idx)
{
    if (inside_labyrinth(get_y(idx, C), get_x(idx, C) - 1, L, C) && inside_labyrinth(get_y(idx, C), get_x(idx, C) + 1, L, C))
    {
        if ((labyrinth[get_y(idx, C)][get_x(idx, C) - 1] != labyrinth[get_y(idx, C)][get_x(idx, C) + 1]) && (labyrinth[get_y(idx, C)][get_x(idx, C) - 1] < -1) && (labyrinth[get_y(idx, C)][get_x(idx, C) + 1] < -1))
            return 1;
    }
    return 0;
}

adjacency *cost_is_smaller(int **labyrinth, adjacency *ad, WallList *wall, int C)
{
    if (ad->cost > labyrinth[get_y(wall->idx, C)][get_x(wall->idx, C)])
    {
        ad->cost = labyrinth[get_y(wall->idx, C)][get_x(wall->idx, C)];
        ad->idx = wall->idx;
    }
    return ad;
}

int must_create_node(adjacency **head1, adjacency **head2, WallList *wall, int **labyrinth, int sideA, int sideB, int C)
{
    adjacency *aux = NULL;

    for (aux = *head1; aux != NULL; aux = aux->next)
    {
        if (aux->sideB == sideB)
        {
            aux = cost_is_smaller(labyrinth, aux, wall, C);
            for (aux = *head2; aux != NULL; aux = aux->next)
            {
                if (aux->sideB == sideA)
                {
                    aux = cost_is_smaller(labyrinth, aux, wall, C);
                    return 1;
                }
            }
        }
    }
    return 0;
}

adjacency **create_adj_list(int **labyrinth, WallList *wall_list, Graph *grapho, int L, int C)
{
    WallList *aux = NULL;
    int sideA = 0, sideB = 0;

    for (aux = wall_list; aux != NULL; aux = aux->next)
    {
        if (north_south(labyrinth, L, C, aux->idx))
        {
            sideA = island_to_id(labyrinth[get_y(aux->idx, C) - 1][get_x(aux->idx, C)]);
            sideB = island_to_id(labyrinth[get_y(aux->idx, C) + 1][get_x(aux->idx, C)]);

            if (!must_create_node(&grapho->adj[sideA], &grapho->adj[sideB], aux, labyrinth, sideA, sideB, C))
            {
                grapho->adj[sideA] = insertadjacency(grapho->adj[sideA], sideB, labyrinth, aux->idx, C);
                grapho->adj[sideB] = insertadjacency(grapho->adj[sideB], sideA, labyrinth, aux->idx, C);
            }
        }

        if (west_east(labyrinth, L, C, aux->idx))
        {
            sideA = island_to_id(labyrinth[get_y(aux->idx, C)][get_x(aux->idx, C) - 1]);
            sideB = island_to_id(labyrinth[get_y(aux->idx, C)][get_x(aux->idx, C) + 1]);

            if (!must_create_node(&grapho->adj[sideA], &grapho->adj[sideB], aux, labyrinth, sideA, sideB, C))
            {
                grapho->adj[sideA] = insertadjacency(grapho->adj[sideA], sideB, labyrinth, aux->idx, C);
                grapho->adj[sideB] = insertadjacency(grapho->adj[sideB], sideA, labyrinth, aux->idx, C);
            }
        }
    }
    return grapho->adj;
}

void write_graph(Graph *graph, int C)
{
    int i;
    adjacency *aux = NULL;
    for (i = 0; i < graph->V; i++)
    {
        printf("*%d* ", i);
        for (aux = graph->adj[i]; aux != NULL; aux = aux->next)
        {
            printf("%d:%d_ %d-%d ", aux->sideB, aux->cost, get_y(aux->idx, C) + 1, get_x(aux->idx, C) + 1);
        }
        putchar('\n');
    }
}

adjacency *insertadjacency(adjacency *head, int side, int **labyrinth, int idx, int C)
{
    adjacency *new = NULL;

    new = (adjacency *)malloc(1 * sizeof(adjacency));

    if (new == NULL)
    {
        printf("Error when allocating memory!\n");
        return NULL;
    }

    new->sideB = side;
    new->idx = idx;
    new->cost = labyrinth[get_y(idx, C)][get_x(idx, C)];
    new->next = head;

    return new;
}

void programa_final(int **labyrinth, WallList *wall_list, int L, int C, int a, int b, FILE *fp_out)
{
    int num_vertices = make_islands(labyrinth, L, C); //creates islands
    print_table(labyrinth, L, C);
    //putchar('\n');
    int *st = NULL, *wt = NULL;
    int finish_room = island_to_id(labyrinth[a][b]);
    //return 0 if no walls need to be broken(MODE A6)
    if (labyrinth[a][b] == labyrinth[0][0])
    {
        fprintf(fp_out, "0\n\n");
        free_wall_list(wall_list);
        free_labyrinth(labyrinth, L);
        return;
    }
    if (labyrinth[a][b] != 0 && labyrinth[a][b] > -1) //verifica se o destino é uma parede
    {
        fprintf(fp_out, "-1\n\n");
        free_wall_list(wall_list);
        free_labyrinth(labyrinth, L);
        return;
    }
    Graph *grapho = init_Graph(num_vertices);
    grapho->adj = create_adj_list(labyrinth, wall_list, grapho, L, C);
    free_labyrinth(labyrinth, L);
    free_wall_list(wall_list);

    st = (int *)malloc(grapho->V * sizeof(int));
    if (st == NULL)
        exit(0);
    wt = (int *)malloc(grapho->V * sizeof(int));
    if (wt == NULL)
        exit(0);

    GRAPHpfs(grapho, wt, st, 0, finish_room); //Dijjktra
    //printf("%d\n", finish_room);
    if (st[finish_room] == -1)
    {
        fprintf(fp_out, "-1\n\n");
        free_graph(grapho);
        free(wt);
        free(st);
        return;
    }

    write_output_final(fp_out, finish_room, st, grapho, C);
    free_graph(grapho);
    free(wt);
    free(st);
}

void path_find(FILE *fp_out, int *st, Graph *grapho, int *dist_final, int *count_walls, int son, int C)
{
    if (st[son] == son)
    {
        fprintf(fp_out, "%d\n", *dist_final);
        fprintf(fp_out, "%d\n", *count_walls);
        return;
    }
    adjacency *aux = NULL;

    for (aux = grapho->adj[st[son]]; aux != NULL; aux = aux->next)
    {
        if (aux->sideB == son)
        {
            (*count_walls)++;
            (*dist_final) += aux->cost;
            son = st[son];
            path_find(fp_out, st, grapho, dist_final, count_walls, son, C);
            fprintf(fp_out, "%d %d %d\n", get_y(aux->idx, C) + 1, get_x(aux->idx, C) + 1, aux->cost);

            break;
        }
    }
}
void write_output_final(FILE *fp_out, int final_room, int *st, Graph *grapho, int C)
{
    int count_walls = 0, dist_final = 0;
    path_find(fp_out, st, grapho, &dist_final, &count_walls, final_room, C);
}

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

void free_wall_list(WallList *wall_head)
{
    WallList *aux, *next;
    for (aux = wall_head; aux != NULL; aux = next)
    {
        next = aux->next;
        free(aux);
    }
}

void freeLinkedList(adjacency *first)
{
    adjacency *aux, *next;
    for (aux = first; aux != NULL; aux = next)
    {
        next = aux->next;
        free(aux);
    }
}