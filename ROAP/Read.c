#include "Proj.h"

void Read_input_file(char *filename, char program_mode)
{
    int C = 0, L = 0; // C=columns, L=lines, (a,b)=coordinates of the cell we want to analyse, P= number of grey/black cells
    int result = 0;
    char *out_name = NULL; // name of the output file

    FILE *fp_in = NULL, *fp_out = NULL;

    fp_in = open_inputfile(fp_in, filename);

    while ((fscanf(fp_in, "%d %d", &L, &C)) == 2)
    {
        if (program_mode == '0')
        {
            out_name = allocate_outputname(out_name, filename);
            fp_out = open_outputfile(fp_out, out_name);

            result = Read_intermediate(fp_in, fp_out, L, C, out_name, filename);
            write_output(fp_out, result);
        }
        else
        {
            out_name = allocate_outputname_final(out_name, filename);
            fp_out = open_outputfile(fp_out, out_name);

            Read_final(fp_in, fp_out, L, C, out_name, filename);
            free(out_name);
            fclose(fp_out);
        }
    }
    fclose(fp_in);
}

int Read_intermediate(FILE *fp_in, FILE *fp_out, int L, int C, char *out_name, char *filename)
{
    int a = 0, b = 0, c = 1, d = 1, result = 0, trash = 0, P = 0, count = 0; // C=columns, L=lines, (a,b)=coordinates of the cell we want to analyse, P= number of grey/black cells
    char test_mode[3];
    int **labyrinth = NULL, x = 0, y = 0, v = 0;

    if ((fscanf(fp_in, "%d %d %s", &a, &b, test_mode)) != 3)
        error(fp_in, fp_out, out_name, filename);

    if (strcmp(test_mode, "A6") == 0)
        if ((fscanf(fp_in, "%d %d", &c, &d)) != 2)
            error(fp_in, fp_out, out_name, filename);

    if ((fscanf(fp_in, "%d", &P)) != 1)
        error(fp_in, fp_out, out_name, filename);

    a--;
    b--;
    c--;
    d--;

    if (!inside_labyrinth(a, b, L, C))
    {
        while (count < P) // pseudo fseek
        {
            if ((fscanf(fp_in, "%d %d %d", &trash, &trash, &trash) != 3))
                error(fp_in, fp_out, out_name, filename);
            count++;
        }
        return -2;
    }
    else if (strcmp(test_mode, "A6") == 0 && (!inside_labyrinth(c, d, L, C)))
    {
        while (count < P) // pseudo fseek
        {
            if ((fscanf(fp_in, "%d %d %d", &trash, &trash, &trash) != 3))
                error(fp_in, fp_out, out_name, filename);
            count++;
        }
        return -2;
    }
    else
    {
        labyrinth = allocate_table(labyrinth, C, L); // Dynamic allocation of the main labyrinth

        while (count < P)
        {
            if ((fscanf(fp_in, "%d %d %d", &y, &x, &v) != 3))
            {
                free_labyrinth(labyrinth, C);
                error(fp_in, fp_out, out_name, filename);
            }
            y--;
            x--;
            labyrinth[y][x] = v; // remember that the coordinate (0,0) represents the (1,1) cell
            count++;
        }
        result = choose_test(test_mode, labyrinth, L, C, a, b, c, d);
        free_labyrinth(labyrinth, L);
    }
    return result;
}

void Read_final(FILE *fp_in, FILE *fp_out, int L, int C, char *out_name, char *filename)
{
    int a = 0, b = 0, trash = 0, P = 0, count = 0; // C=columns, L=lines, (a,b)=coordinates of the cell we want to analyse, P= number of grey/black cells
    int **labyrinth = NULL, x = 0, y = 0, v = 0;
    WallList *wall_list = NULL;

    if ((fscanf(fp_in, "%d %d", &a, &b)) != 2) //destiny's coordinates
        error(fp_in, fp_out, out_name, filename);

    if ((fscanf(fp_in, "%d", &P)) != 1)
        error(fp_in, fp_out, out_name, filename);
    a--;
    b--;

    if (!inside_labyrinth(a, b, L, C))
    {
        fprintf(fp_out,"-1\n\n");
        while (count < P) // pseudo fseek
        {
            if ((fscanf(fp_in, "%d %d %d", &trash, &trash, &trash) != 3))
                error(fp_in, fp_out, out_name, filename);
            count++;
        }
    }
    else
    {
        labyrinth = allocate_table(labyrinth, C, L); // Dynamic allocation of the main labyrinth

        while (count < P)
        {
            if ((fscanf(fp_in, "%d %d %d", &y, &x, &v) != 3))
            {
                free_labyrinth(labyrinth, C);
                error(fp_in, fp_out, out_name, filename);
            }
            y--;
            x--;
            labyrinth[y][x] = v; // remember that the coordinate (0,0) represents the (1,1) cell
            count++;
            if (labyrinth[y][x] > 0) //only breakable grey cells
                wall_list = create_wall_entry(wall_list, get_index(y, x, C));
        }
        programa_final(labyrinth, wall_list, L, C, a, b, fp_out);
    }
    return;
}

void print_table(int **labyrinth, int L, int C)
{
    int i, j, lin;
    printf("    ");

    for (i = 1; i <= C; i++)
        printf(" %4d", i);
    printf("\n");
    for (i = 0; i < L; i++)
    {
        lin = i + 1;
        if (lin <= 9)
            printf(" %4d", lin);
        else
            printf(" %4d", lin);
        for (j = 0; j < C; j++)
            printf("%4d ", labyrinth[i][j]);
        putchar('\n');
    }
}

int find_last_period(char *filename)
{
    char *buffer = NULL;
    int value = 0, n_chars = 0;
    for (buffer = filename; *buffer != '\0'; buffer++)
    {
        n_chars++;
        if (*buffer == '.')
            value = n_chars;
    }
    return value;
}

void write_output(FILE *fp_out, int result)
{
    fprintf(fp_out, "%d\n\n", result);
}

void free_labyrinth(int **labyrinth, int L)
{
    int i;
    for (i = 0; i < L; i++)
    {
        free(labyrinth[i]);
    }
    free(labyrinth);
    return;
}

char *allocate_outputname(char *out_name, char *in_name)
{
    int num_char = 0;
    num_char = find_last_period(in_name);
    out_name = (char *)calloc((num_char + 5), sizeof(char));
    if (out_name == NULL)
    {
        fprintf(stderr, "Not enough memory available!\n");
        exit(5);
    }
    strncpy(out_name, in_name, num_char);
    strcat(out_name, "sol1");

    return out_name;
}

char *allocate_outputname_final(char *out_name, char *in_name)
{
    int num_char = 0;
    num_char = find_last_period(in_name);
    out_name = (char *)calloc((num_char + 4), sizeof(char));
    if (out_name == NULL)
    {
        fprintf(stderr, "Not enough memory available!\n");
        exit(5);
    }
    strncpy(out_name, in_name, num_char);
    strcat(out_name, "sol");

    return out_name;
}

void error(FILE *fp_in, FILE *fp_out, char *filename_in, char *filename_out)
{
    printf("Error when reading data.\n");
    fclose(fp_in);
    fclose(fp_out);
    free(filename_out);
    free(filename_in);
    exit(0);
}

FILE *open_inputfile(FILE *fp_in, char *filename)
{
    if ((fp_in = fopen(filename, "r")) == NULL)
    {
        printf("Error when reading the input file.\n");
        free(filename);
        exit(1);
    }
    return fp_in;
}

FILE *open_outputfile(FILE *fp_out, char *filename)
{
    if ((fp_out = fopen(filename, "a")) == NULL)
    {
        printf("Error when writing the output file.\n");
        free(filename);
        exit(1);
    }
    return fp_out;
}

char *get_inputfilename(char **argv, char *filename, char program_mode)
{
    if (program_mode == '0') // programa fase intermedia
    {
        if (verify_extension(argv[2]))
        {
            printf("Wrong file's extension!\n");
            exit(0);
        }
        if ((filename = (char *)malloc((strlen(argv[2]) + 1) * sizeof(char))) == NULL)
        {
            printf("Error when trying to get memory to allocate input file name!\n");
            exit(0);
        }
        strcpy(filename, argv[2]);
    }
    else //programa fase final
    {
        if (!verify_extension(argv[1]))
        {
            printf("Wrong file's extension!\n");
            exit(0);
        }
        if ((filename = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char))) == NULL)
        {
            printf("Error when trying to get memory to allocate input file name!\n");
            exit(0);
        }
        strcpy(filename, argv[1]);
    }

    return filename;
}

int verify_extension(char *filename)
{
    int n, i, res = 0;
    n = find_last_period(filename);
    char *buffer = (char *)calloc(strlen(filename) - n + 1, sizeof(char));
    for (i = 0; i < strlen(filename) - n + 1; i++)
    {
        buffer[i] = filename[n + i];
    }
    res = (strcmp(buffer, "in1") == 0) ? 0 : 1;
    free(buffer);
    return res;
}
