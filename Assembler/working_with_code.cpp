#include "working_with_code.h"

int code_put(int argc, const char *argv[], Asm_SPU* proc, int run_num)
{
    Labels* labels = &proc->labels;
    double* code = proc->code;

    proc->ip = 0;
    int* ip = &proc->ip;

    FILE* file_asm = NULL;
    

    if (argc != 1) file_asm = fopen(argv[1], "r");
    else file_asm = fopen(FILE_NAME, "r");

    // |mem|reg|imm|

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

        // struct CommandWithArg {
        //     const char*;
        //     enum;
        //     foo;
        // }

        // strcmp(const char*) foo(file_asm, proc, enum)

        // {{"PUSH", PUSH, stack_command},  {"JA", JA, put_jump_commands}}

        CHECK_COMMAND("PUSH")
        {
            stack_command(file_asm, proc, PUSH);
            continue;
        }

        CHECK_COMMAND("POP")
        {
            stack_command(file_asm, proc, POP);
            continue;
        }

        CHECK_COMMAND("ADD") FILL_CODE_FUNC_WITH_NO_ARG(ADD)

        CHECK_COMMAND("SUB") FILL_CODE_FUNC_WITH_NO_ARG(SUB)

        CHECK_COMMAND("MUL") FILL_CODE_FUNC_WITH_NO_ARG(MUL)

        CHECK_COMMAND("DIV") FILL_CODE_FUNC_WITH_NO_ARG(DIV)

        CHECK_COMMAND("SQRT") FILL_CODE_FUNC_WITH_NO_ARG(SQRT)

        CHECK_COMMAND("OUT") FILL_CODE_FUNC_WITH_NO_ARG(OUT)

        CHECK_COMMAND("OUTC") FILL_CODE_FUNC_WITH_NO_ARG(OUTC)
    
        CHECK_COMMAND("IN") FILL_CODE_FUNC_WITH_NO_ARG(IN)

        CHECK_COMMAND("JUMP")
        {
            put_jump_commands(JUMP, file_asm, proc);
            continue;
        }

        CHECK_COMMAND("JA")
        {
            put_jump_commands(JA, file_asm, proc);
            continue;
        }

        CHECK_COMMAND("JB")
        {
            put_jump_commands(JB, file_asm, proc);
            continue;
        }

        CHECK_COMMAND("JE")
        {
            put_jump_commands(JE, file_asm, proc);
            continue;
        }

        CHECK_COMMAND("JNE")
        {
            put_jump_commands(JNE, file_asm, proc);
            continue;
        }

        CHECK_COMMAND("DRAW")
        {
            put_draw_command(file_asm, proc);
            continue;
        }

        CHECK_COMMAND("CALL")
        {
            put_jump_commands(CALL, file_asm, proc);
            continue;
        }

        CHECK_COMMAND("RET") FILL_CODE_FUNC_WITH_NO_ARG(RET)

        CHECK_COMMAND("HLT") FILL_CODE_FUNC_WITH_NO_ARG(HLT)        
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
