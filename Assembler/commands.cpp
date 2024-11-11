#include "commands.h"


static void           check_and_put_in_right_order(Asm_SPU* proc, char arg_1[], char arg_2[]);
static IndexRegisters index_of_register           (char arg[]);



static void check_and_put_in_right_order(Asm_SPU* proc, char arg_1[], char arg_2[])
{
    if (isalpha(arg_1[0]))
    {
        proc->code[(proc->ip)++] = index_of_register(arg_1);
        proc->code[(proc->ip)++] = atof(arg_2);
    }
    else
    {
        proc->code[(proc->ip)++] = index_of_register(arg_2);
        proc->code[(proc->ip)++] = atof(arg_1);
    }
}


static IndexRegisters index_of_register(char arg[])
{
    if      (strcmp(arg, "RAX") == 0) return RAX;
    else if (strcmp(arg, "RBX") == 0) return RBX;
    else if (strcmp(arg, "RCX") == 0) return RCX;
    else if (strcmp(arg, "RDX") == 0) return RDX;
    else if (strcmp(arg, "REX") == 0) return REX;
    return RAX; // unreachable
}


void stack_command(FILE* file_asm, Asm_SPU* proc, MashineCode type_command)
{
    proc->code[proc->ip] = type_command;
    char arg_1[MAX_ARG_COMMAND_SIZE] = {}; 
    char arg_2[MAX_ARG_COMMAND_SIZE] = {};

    int count_args = fscanf(file_asm, "%s + %s", arg_1, arg_2);

    if (count_args == 2)  // Два аргуманта (сумма (в любом порядке))
    {
        if (arg_1[0] == '[' && arg_2[strlen(arg_2) - 1] == ']') // если есть [] (оперативная память)
        {
            proc->code[(proc->ip)++] += REGISTER + NUMBER + RAM;

            strcpy(arg_1, &arg_1[1]);
            arg_2[strlen(arg_2) - 1] = '\0';
        }
        else
        {
            if (type_command == POP)
            {
                printf("Синтаксическая ошибка\n"); // в pop нельзя подавать сумму без квадратныx скобок
            }
            else                                   // PUSH
            {
                proc->code[(proc->ip)++] += REGISTER + NUMBER;
            }
        }

        check_and_put_in_right_order(proc, arg_1, arg_2);
    }

    else if (count_args == 1) // Один аргумент
    {
        if (arg_1[0] == '[' && arg_1[strlen(arg_1) - 1] == ']')   // Опреативная память
        {
            proc->code[proc->ip] += RAM;

            strcpy(arg_1, &arg_1[1]);
            arg_1[strlen(arg_1) - 1] = '\0';
        }


        if (isalpha(arg_1[0]))                                    // Регистр
        {
            proc->code[(proc->ip)++] += REGISTER;
            proc->code[(proc->ip)++] = index_of_register(arg_1);
        }
        else                                                      // Число
        {
            if (type_command == POP && proc->code[proc->ip] == POP) // У pop должен быть еще RAM
            {
                printf("Синтаксическая ошибка\n");
            }
            else
            {
                proc->code[(proc->ip)++] += NUMBER;
                proc->code[(proc->ip)++] = atof(arg_1);
            }
        }
    }

    else
    {
        printf("Синтаксическая ошибка\n"); 
    }
}


void fill_code_func_with_no_arg(FILE* file_asm, Asm_SPU* proc, MashineCode com)
{
    proc->code[proc->ip++] = com;
}


void put_jump_commands(FILE* file_asm, Asm_SPU* proc, MashineCode jump_type)
{
    proc->code[proc->ip++] = jump_type;

    char arg[MAX_NAME_LABEL_SIZE] = "";
    fscanf(file_asm, "%s", arg);

    proc->code[proc->ip++] = find_label_ip(&proc->labels, arg);
}


void put_draw_command (FILE* file_asm, Asm_SPU* proc, MashineCode command)
{
    proc->code[proc->ip++] = DRAW;
    int arg = 0;
    fscanf(file_asm, "%d", &arg);
    proc->code[proc->ip++] = (double) arg;
}


