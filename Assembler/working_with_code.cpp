#include "working_with_code.h"


#define CHECK_COMMAND(commanda) if (strcmp(command, commanda) == 0)
#define FILL_CODE_FUNC(commanda) {put_command(file_asm, proc, commanda); continue;}



int fill_code(int argc, const char *argv[], Asm_SPU* proc, int run_num)
{
    Labels* labels = &proc->labels;
    double* code = proc->code;

    proc->ip = 0;
    int* ip = &proc->ip;

    FILE* file_asm = NULL;
    

    if (argc != 1) file_asm = fopen(argv[1], "r");
    else file_asm = fopen(FILE_NAME, "r");

    char command[MAX_COMMAND_SIZE] = {};
    int len_struct_arr = (int) (sizeof(commands_arr) / sizeof(CommandWithArg));

    while(fscanf(file_asm, "%s", command) != EOF) 
    {
        size_t len_str = strlen(command);

        if (command[len_str - 1] == ':')
        {
            command[len_str - 1] = '\0';
            if (run_num == 1) create_new_label(proc, command);

            continue;
        }


        for (int i = 0; i < len_struct_arr; i++)
        {
            if (strcmp(command, commands_arr[i].сommand_name) == 0)
                commands_arr[i].to_do_comm(file_asm, proc, commands_arr[i].command);
        }
    }
    fclose(file_asm);

    return *ip;
}


void print_code(double code[], size_t size_code)
{
    for (size_t i = 0; i < size_code; i++)
    {
        printf("%g ", code[i]);
    }
    printf("\n");
}


void code_output_file(Asm_SPU* proc)
{
    FILE* file_code = fopen(READ_FILE_NAME, "w");

    for (size_t i = 0; i < proc->size_code; i++)
    {
        fprintf(file_code, "%lg ", proc->code[i]);
    }
    fclose(file_code);
}
