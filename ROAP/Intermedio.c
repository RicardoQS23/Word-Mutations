#include "Proj.h"

int get_index(int a, int b, int C)
{
    return ((a * C) + b);
}

int **allocate_table(int **labyrinth, int C, int L)
{
    int i;
    labyrinth = (int **)malloc(L * sizeof(int *)); // allocates lines
    for (i = 0; i < L; i++)
        labyrinth[i] = (int *)calloc(C, sizeof(int)); // allocates columns
    return labyrinth;
}

int mode_A1(int a, int b, int **labyrinth, int L, int C) // type of cell
{
    return labyrinth[a][b];
}

int mode_A2(int a, int b, int **labyrinth, int L, int C) // any white cell
{
    int i, x, y;
    int vetor[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // vector that check the neighbourhood

    for (i = 0; i < 4; i++)
    {
        y = a + vetor[i][0];
        x = b + vetor[i][1];
        if (y < L && y >= 0 && x < C && x >= 0)
            if (labyrinth[y][x] == 0)
                return 1;
    }
    return 0;
}

int mode_A3(int a, int b, int **labyrinth, int L, int C) // any grey cell
{
    int i, x, y;
    int vetor[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // vector that check the neighbourhood

    for (i = 0; i < 4; i++)
    {
        y = a + vetor[i][0];
        x = b + vetor[i][1];
        if (y < L && y >= 0 && x < C && x >= 0)
            if (labyrinth[y][x] > 0)
                return 1;
    }
    return 0;
}

int mode_A4(int a, int b, int **labyrinth, int L, int C) // any black cell
{
    int i, x = 1, y = 1;
    int vetor[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // vector that check the neighbourhood

    for (i = 0; i < 4; i++) // for (i = 0; i < sizeof(vetor[5][2] / (2 * sizeof(short))); i++)
    {
        y = a + vetor[i][0];
        x = b + vetor[i][1];
        if (y < L && y >= 0 && x < C && x >= 0)
            if (labyrinth[y][x] == -1)
                return 1;
    }
    return 0;
}

int mode_A5(int a, int b, int **labyrinth, int L, int C)
{
    if (labyrinth[a][b] <= 0)
        return -1;
    if (((0 < a) && (a < L - 1)) && ((0 < b) && (b < C - 1)))
    {
        if ((labyrinth[a - 1][b] == 0 && labyrinth[a + 1][b] == 0) || (labyrinth[a][b - 1] == 0 && labyrinth[a][b + 1] == 0))
            return 1;
    }
    if ((a == 0 && b == 0) || (a == L - 1 && b == C - 1) || (a == L - 1 && b == 0) || (a == 0 && b == C - 1))
        return 0;

    if ((a == 0) || (a == L - 1))
    {
        if ((labyrinth[a][b - 1] == 0 && labyrinth[a][b + 1] == 0))
            return 1;
    }

    if ((b == 0) || (b == C - 1))
    {
        if ((labyrinth[a - 1][b] == 0 && labyrinth[a + 1][b] == 0))
            return 1;
    }

    return 0;
}

int mode_A6(int a, int b, int l, int c, int **labyrinth, int L, int C)
{
    int result = 0;
    int N = L * C; // number of elements in the labyrinth
    int i;
    int j;
    int wall_cnt_up = 0, wall_cnt_left = 0, wall_cnt_right = 0, wall_cnt_down = 0;
    for (j = 0; j < C; j++)
    {
        if (labyrinth[0][j] != 0)
            wall_cnt_up++;
    }
    for (j = 0; j < C; j++)
    {
        if (labyrinth[L - 1][j] != 0)
            wall_cnt_down++;
    }
    for (j = 0; j < L; j++)
    {
        if (labyrinth[j][0] != 0)
            wall_cnt_left++;
    }
    for (j = 0; j < L; j++)
    {
        if (labyrinth[j][C - 1] != 0)
            wall_cnt_right++;
    }
    if (wall_cnt_up == 1 && wall_cnt_right == 0 && wall_cnt_down == 0 && wall_cnt_left == 0)
        return 1;
    if (wall_cnt_right == 1 && wall_cnt_down == 0 && wall_cnt_up == 0 && wall_cnt_left == 0)
        return 1;
    if (wall_cnt_right == 0 && wall_cnt_down == 0 && wall_cnt_up == 0 && wall_cnt_left == 1)
        return 1;

    // allocate memory
    int *id = (int *)malloc(N * sizeof(int));
    if (id == NULL)
    {
        printf("Error when allocating memory!\n");
        exit(0);
    }
    int *sz = (int *)malloc(N * sizeof(int)); // allocates memory for size list
    if (sz == NULL)
    {
        printf("Error when allocating memory!\n");
        exit(0);
    }
    /*initialize; all disconnected*/
    for (i = 0; i < N; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
    make_families(id, labyrinth, sz, L, C, N);

    int start = get_index(a, b, C);
    int finish = get_index(l, c, C);
    if (id[start] == id[finish])
        result = 1;
    free(sz);
    free(id);
    return result;
}

void make_families(int *id, int **labyrinth, int *sz, int L, int C, int N)
{
    int i, j;

    for (i = 0; i < L; i++)
    {
        for (j = 0; j < C; j++)
        {
            if (j != C - 1)
            {
                if ((labyrinth[i][j] == 0) && (labyrinth[i][j + 1] == 0))
                    compressed_weighted_quick_union(id, labyrinth, sz, get_index(i, j, C), get_index(i, j + 1, C), N);
            }
            if (i != L - 1)
            {
                if ((labyrinth[i][j] == 0) && (labyrinth[i + 1][j] == 0))
                    compressed_weighted_quick_union(id, labyrinth, sz, get_index(i, j, C), get_index(i + 1, j, C), N);
            }
        }
    }
    return;
}

void compressed_weighted_quick_union(int *id, int **labyrinth, int *sz, int p, int q, int N)
{
    int i = 0, j = 0, t = 0, x = 0;

    /* do search first */
    for (i = p; i != id[i]; i = id[i])
        ;
    for (j = q; j != id[j]; j = id[j])
        ;
    /* already in the same set; discard */
    if (i == j)
        return;

    /* pair has new info; must perform union; pick right direction */
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
        t = j;
    }
    else
    {
        if (sz[i] == sz[j])
        {
            id[j] = i;
            sz[i] += 1;
            t = i;
        }
        if (sz[i] > sz[j])
        {
            id[j] = i;
            sz[i] += sz[j];
            t = i;
        }

        /* retrace the path and compress to the top */
        for (i = p; i != id[i]; i = x)
        {
            x = id[i];
            id[i] = t;
        }
        for (j = q; j != id[j]; j = x)
        {
            x = id[j];
            id[j] = t;
        }
    }
    return;
}

int choose_test(char *test_mode, int **labyrinth, int L, int C, int a, int b, int c, int d)
{
    if (strcmp(test_mode, "A1") == 0)
        return mode_A1(a, b, labyrinth, L, C);
    if (strcmp(test_mode, "A2") == 0)
        return mode_A2(a, b, labyrinth, L, C);
    if (strcmp(test_mode, "A3") == 0)
        return mode_A3(a, b, labyrinth, L, C);
    if (strcmp(test_mode, "A4") == 0)
        return mode_A4(a, b, labyrinth, L, C);
    if (strcmp(test_mode, "A5") == 0)
        return mode_A5(a, b, labyrinth, L, C);
    if (strcmp(test_mode, "A6") == 0)
        return mode_A6(a, b, c, d, labyrinth, L, C);

    return 0;
}
