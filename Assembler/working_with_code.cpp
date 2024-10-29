#include "working_with_code.h"


#define CHECK_COMMAND(commanda) if (strcmp(command, commanda) == 0)
#define FILL_CODE_FUNC(commanda) {put_command(file_asm, proc, commanda); continue;}


static void put_command(FILE* file_asm, Asm_SPU* proc, MashineCode command);


static void put_command(FILE* file_asm, Asm_SPU* proc, MashineCode command)
{
    // commands_arr[command].to_do_comm(file_asm, proc, command);
    int len_struct_arr = (int) (sizeof(commands_arr) / sizeof(CommandWithArg));

    for (int i = 0; i < len_struct_arr; i++)
    {
        if (command == commands_arr[i].command) 
            commands_arr[i].to_do_comm(file_asm, proc, command);
    }
}


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

    while(fscanf(file_asm, "%s", command) != EOF) 
    {
        size_t len_str = strlen(command);

        if (command[len_str - 1] == ':')
        {
            command[len_str - 1] = '\0';
            if (run_num == 1) create_new_label(proc, command);

            continue;
        }

        CHECK_COMMAND("PUSH") FILL_CODE_FUNC(PUSH)

        CHECK_COMMAND("POP")  FILL_CODE_FUNC(POP)
        
        CHECK_COMMAND("ADD")  FILL_CODE_FUNC(ADD)
        
        CHECK_COMMAND("SUB")  FILL_CODE_FUNC(SUB)
        
        CHECK_COMMAND("MUL")  FILL_CODE_FUNC(MUL)
        
        CHECK_COMMAND("OUT")  FILL_CODE_FUNC(OUT)
        
        CHECK_COMMAND("JUMP") FILL_CODE_FUNC(JUMP)
        
        CHECK_COMMAND("JA")   FILL_CODE_FUNC(JA)
        
        CHECK_COMMAND("JB")   FILL_CODE_FUNC(JB) 
        
        CHECK_COMMAND("JE")   FILL_CODE_FUNC(JE)
        
        CHECK_COMMAND("JNE")  FILL_CODE_FUNC(JNE)
        
        CHECK_COMMAND("IN")   FILL_CODE_FUNC(IN)
        
        CHECK_COMMAND("OUTC") FILL_CODE_FUNC(OUTC)
        
        CHECK_COMMAND("DRAW") FILL_CODE_FUNC(DRAW)
        
        CHECK_COMMAND("CALL") FILL_CODE_FUNC(CALL)
        
        CHECK_COMMAND("RET")  FILL_CODE_FUNC(RET)
        
        CHECK_COMMAND("DIV")  FILL_CODE_FUNC(DIV)
        
        CHECK_COMMAND("SQRT") FILL_CODE_FUNC(SQRT)
        
        CHECK_COMMAND("HLT")  FILL_CODE_FUNC(HLT)


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
    printf("\n");
}
