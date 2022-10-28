#include "Proj.h"

int main(int argc, char *argv[])
{
    char program_mode = (strcmp(argv[1], "-s") == 0) ? '0' : '1';
    char *filename = NULL;

    if (program_mode == '0' && argc != 3)
    {
        help();
        exit(0);
    }
    else if (program_mode == '1' && argc != 2)
    {
        help();
        exit(0);
    }
    filename = get_inputfilename(argv, filename, program_mode);
    Read_input_file(filename, program_mode);
    free(filename);

    return 0;
}

void help(void)
{
    printf("Esta é uma mensagem de Ajuda: O formato de invocação do programa será o mesmo que o definido anteriormente, mas existem algumas diferenças de conteúdo.aed$ ./roap -s maze.in1");
}
