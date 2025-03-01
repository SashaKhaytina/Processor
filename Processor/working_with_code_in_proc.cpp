#include "working_with_code_in_proc.h"
#include "to_do_commands.h"

void run_code(SPU* proc)
{
    proc->ip = 0;

    bool continue_process = true;
    while (continue_process)
    {
        MashineCode command = (MashineCode) ((int)(proc->code[proc->ip]) & ONLY_COMMAND_NUM_MASK);
        switch (command)
        {
        case PUSH: 
        {
            to_do_push(proc);
            break;
        }
        
        case POP:
        {
            to_do_pop(proc);
            break;
        }
        
        case ADD: case SUB: case MUL: case DIV: 
        {
            proc->ip++;
            to_do_calculate(proc, command);
            break;
        }

        case SQRT:
        {
            proc->ip++;
            to_do_sqrt(proc);
            break;
        }

        case OUT: 
        {
            proc->ip++;
            to_do_out(proc);
            break;
        }

        case OUTC: 
        {
            proc->ip++;
            to_do_outc(proc);
            break;
        }
        
        case IN: 
        {
            proc->ip++;
            to_do_in(proc);
            break;
        }

        case JUMP:
        {
            proc->ip++;
            proc->ip = (size_t) proc->code[proc->ip];
            break;
        }
        
        case JA: case JB: case JNG: case JNL: case JE: case JNE:
        {
            to_do_conditional_jump(proc, command);
            break;
        }

        case DRAW: 
        {
            proc->ip++;
            to_do_draw(proc);
            break;
        }

        case CALL:
        {
            proc->ip++;
            to_do_call(proc);
            break;
        }

        case RET:
        {
            proc->ip++;
            to_do_ret(proc);
            break;
        }
        
        case HLT:
        {
            proc->ip++;
            printf("Закончили\n");
            continue_process = false;
            break;
        }
        
        default:
        {
            printf("Cинтаксическая ошибка\n");
            break;
        }
        }


    }
}


size_t read_file_code(SPU* proc)
{
    FILE* file_code = NULL;
    file_code = fopen(READ_FILE_NAME, "r");

    
    proc->ip = 0;

    double num_in_mashine_code = 0;

    while (fscanf(file_code, "%lg", &num_in_mashine_code) != EOF)
    {
        proc->code[proc->ip++] = num_in_mashine_code;
    }

    return proc->ip;
}


void print_code(StackElem_t code[], size_t size_code)
{
    for (size_t i = 0; i < size_code; i++)
    {
        printf("%g ", code[i]);
    }
    printf("\n");
}
