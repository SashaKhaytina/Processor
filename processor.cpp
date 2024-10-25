// g++ processor.cpp Stack/stack_commands.cpp Stack/errors.cpp Stack/utils.cpp -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8000 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -o processor



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Stack/stack_commands.h"
#include "Stack/errors.h"
#include "Stack/utils.h"

// Должен переводить файл с маш кодом (файл с цифрами) в массив и выполняться 


// Это норм вообще?
#define INIT_ELEM1 StackElem_t elem1 = 0; stack_pop(&proc->stack, &elem1); 
#define INIT_ELEM2 StackElem_t elem2 = 0; stack_pop(&proc->stack, &elem2);

enum ArgType
{
    REGISTR = 1 << 0,
    NUMBER = 1 << 1
};

// enum IndexRegistrs // Это не сюда, это в ассемблер
// {
//     RAX,
//     RBX,
//     RCX, 
//     RDX,
//     REX,
// };

enum MashineCode
{
    HLT = 0,
    PUSH = 51,
    PUSHR = 52,
    POP = 42,
    ADD = 1,
    SUB = 2,
    MUL = 3, 
    OUT = 4, // ыыыы
    JUMP = 5,
    JA = 6,
    JB = 7,
    JE = 8,
    JNE = 9,
    IN = 10
};

const size_t MAX_CODE_SIZE = 10000;
const int STOP_PROGRAMM = -1;
const char* const READ_FILE_NAME = "program_code.txt"; // как тут const расставлять


struct SPU
{
    StackElem_t code[MAX_CODE_SIZE];
    size_t ip;
    Stack stack; 
    StackElem_t registers[5];  // это норм тип для них?
};


size_t read_file_code(SPU* proc);
void   run_code      (SPU* proc);
void   print_code    (StackElem_t code[], size_t size_code);

void to_do_push(SPU* proc);
void to_do_pop (SPU* proc);
void to_do_add (SPU* proc);
void to_do_sub (SPU* proc);
void to_do_mul (SPU* proc);
void to_do_out (SPU* proc);
void to_do_in  (SPU* proc);

StackElem_t get_arg(SPU* proc, int bit_arg);

void put_jump_commands(MashineCode jump_type, FILE* file_code, SPU* proc);
void put_arguments    (FILE* file_code, SPU* proc, int bit_arg);
// void to_do_any_jump(SPU* proc, MashineCode jump_type);




int main() 
{
    SPU proc = {};
    size_t size_code = read_file_code(&proc);

    print_code(proc.code, size_code);

    default_stack_ctor(&proc.stack, INITIAL_CAPACITY);
    run_code(&proc);
    stack_dtor(&proc.stack);

}







void run_code(SPU* proc)
{
    proc->ip = 0;

    bool continue_process = true;
    while (continue_process)
    {
        // print_stack_info(&proc->stack, OK);
        MashineCode command = (MashineCode) proc->code[proc->ip];
        switch (command)
        {
        case PUSH: 
        {
            proc->ip++;
            to_do_push(proc);
            break;
        }
        
        case POP:  // Кладет в регистр последний элемент стека 
        {
            proc->ip++;
            to_do_pop(proc);
            break;
        }
        
        case ADD: 
        {
            proc->ip++;
            to_do_add(proc);
            break;
        }
        
        case SUB:
        {
            proc->ip++;
            to_do_sub(proc);
            break;
        }

        case MUL:
        {
            proc->ip++;
            to_do_mul(proc);
            break;
        }

        case OUT: // Он должен вытащить еще 
        {
            proc->ip++;
            to_do_out(proc);
            break;
        }
        
        case IN: // push в стек то, что вводим с клавиатуры
        {
            proc->ip++;
            to_do_in(proc);
            break;
        }

        case JUMP:
        {
            proc->ip = (size_t) proc->code[++(proc->ip)];
            break;
        }
        
        case JA:
        {
            INIT_ELEM1
            INIT_ELEM2

            if (elem2 > elem1) proc->ip = (size_t) proc->code[++(proc->ip)];
            else proc->ip += 2;
            break;
        }

        case JB:
        {
            INIT_ELEM1
            INIT_ELEM2

            if (elem2 < elem1) proc->ip = (size_t) proc->code[++(proc->ip)];
            else proc->ip += 2;
            break;
        }

        case JE: // тут == !!!!
        {
            INIT_ELEM1
            INIT_ELEM2
            
            if (elem2 == elem1) proc->ip = (size_t) proc->code[++(proc->ip)];
            else proc->ip += 2;
            break;
        }

        case JNE:
        {
            INIT_ELEM1
            INIT_ELEM2

            if (elem2 != elem1) proc->ip = (size_t) proc->code[++(proc->ip)];
            else proc->ip += 2;
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

        //print_stack_info(&proc->stack, OK);

    }
}


size_t read_file_code(SPU* proc)
{
    FILE* file_code = NULL;
    file_code = fopen(READ_FILE_NAME, "r");


    proc->ip = 0;
    int command = 0;

    while (fscanf(file_code, "%d", &command) != EOF)
    {
        //fscanf(file_code, "%d", &command);
        printf("%d ", command);

        switch (command)
        {
        case PUSH:
            {
            proc->code[proc->ip++] = PUSH; // TODO: you do that in every case
            int bit_arg = 0;
            fscanf(file_code, "%d", &bit_arg);
            proc->code[proc->ip++] = bit_arg;

            put_arguments(file_code, proc, bit_arg);

            break;
            }
        
        case POP:  // Кладет в регистр последний элемент стека 
            {
            proc->code[proc->ip++] = POP;

            StackElem_t arg = 0;            // Тут индекс регистра. ОН УЖЕ ЧИСЛО!!! (его ассемблер сделал числом)
            fscanf(file_code, "%lg", &arg);
            proc->code[proc->ip++] = arg;

            break;
            }
        
        case ADD:
            {
            proc->code[proc->ip++] = ADD;
            break;
            }
        
        case SUB:
            {
            proc->code[proc->ip++] = SUB;
            break;
            }

        case MUL:
            {
            proc->code[proc->ip++] = MUL;
            break;
            }

        case OUT:
            {
            proc->code[proc->ip++] = OUT;
            break;
            }
        
        case IN:
            {
            proc->code[proc->ip++] = IN;
            break;
            }
        
        case JUMP:
            {
            put_jump_commands(JUMP, file_code, proc);
            break;
            }
        
        case JA:
            {
            put_jump_commands(JA, file_code, proc);
            break;
            }
        
        case JB:
            {
            put_jump_commands(JB, file_code, proc);
            break;
            }
        
        case JE:
            {
            put_jump_commands(JE, file_code, proc);
            break;
            }
        
        case JNE:
            {
            put_jump_commands(JNE, file_code, proc);
            break;
            }
        
        case HLT:
            {
            proc->code[proc->ip++] = HLT;
            // Из switch можно как-то остановить внешний цикл? (break занят, получается) (но тут это не надо)
            break;
            }
        
        default: // TODO: if you don't want to move proc->code... from switch, you should print here an error
        {
            printf("В машинном коде что-то не то. Программа заканчивает выполнение\n");
            exit(STOP_PROGRAMM); // что тут писать...
            break;
        }
        }

    }
    printf("\n");
    return proc->ip;
}






StackElem_t get_arg(SPU* proc, int bit_arg)
{
    StackElem_t which_push = 0;
    
    if (bit_arg & REGISTR) // регистр
    {
        which_push += proc->registers[(int) proc->code[proc->ip++]];
    }
    if (bit_arg & NUMBER) // число .............
    {
        which_push += proc->code[proc->ip++];
    }

    return which_push;
}


void to_do_push(SPU* proc)
{
    int bit_arg = (int) proc->code[proc->ip++]; 

    // StackElem_t which_push = 0;
    
    // if (bit_arg & REGISTR) // регистр
    // {
    //     which_push += proc->registers[(int) proc->code[proc->ip++]];
    // }
    // if (bit_arg & NUMBER) // число .............
    // {
    //     which_push += proc->code[proc->ip++];
    // }

    stack_push(&proc->stack, get_arg(proc, bit_arg));
}


void to_do_pop(SPU* proc)
{
    int arg = (int) proc->code[proc->ip++];

    //proc->registers[arg] = (&proc->stack)->arr[(&proc->stack)->size-1];
    stack_pop(&proc->stack, &proc->registers[arg]); // Это сработает, если там все из char?
}


// Может сделать 1 функцию, в которую передавать знак. Но это лишние if (if in if)
void to_do_add(SPU* proc)
{
    StackElem_t elem1 = 0;
    StackElem_t elem2 = 0;
    
    stack_pop(&proc->stack, &elem1); // Удаляем
    stack_pop(&proc->stack, &elem2); // Удаляем

    stack_push(&proc->stack, elem1 + elem2);
}

void to_do_sub(SPU* proc)
{
    StackElem_t elem1 = 0;
    StackElem_t elem2 = 0;
    
    stack_pop(&proc->stack, &elem1); // Удаляем
    stack_pop(&proc->stack, &elem2); // Удаляем

    stack_push(&proc->stack, elem1 - elem2);
}

void to_do_mul(SPU* proc)
{
    StackElem_t elem1 = 0;
    StackElem_t elem2 = 0;
    
    stack_pop(&proc->stack, &elem1); // Удаляем
    stack_pop(&proc->stack, &elem2); // Удаляем

    stack_push(&proc->stack, elem1 * elem2);
}

void to_do_out(SPU* proc)
{
    StackElem_t elem = 0;
    stack_pop(&proc->stack, &elem);

    printf("%g - это результат\n", elem);
}

void to_do_in(SPU* proc)
{
    StackElem_t arg = 0;
    printf("Введите число: \n");
    scanf("%lg", &arg);
    
    stack_push(&proc->stack, arg);
}

/*
// void to_do_any_jump(SPU* proc, MashineCode jump_type)
// {
    
//     StackElem_t elem1 = 0;
//     StackElem_t elem2 = 0;
    
//     stack_pop(&proc->stack, &elem1); // Удаляем
//     stack_pop(&proc->stack, &elem2); // Удаляем
// }
*/



void put_jump_commands(MashineCode jump_type, FILE* file_code, SPU* proc)
{
    proc->code[proc->ip++] = jump_type;
    int arg = 0;
    fscanf(file_code, "%d", &arg);
    proc->code[proc->ip++] = arg;
}


void put_arguments(FILE* file_code, SPU* proc, int bit_arg) // кладет в code
{
    if (bit_arg & REGISTR) // регистр
    {
        StackElem_t arg = 0;
        fscanf(file_code, "%lg", &arg); 
        proc->code[proc->ip++] = arg;
    }
    if (bit_arg & NUMBER)
    {
        StackElem_t arg = 0;
        fscanf(file_code, "%lg", &arg); 
        proc->code[proc->ip++] = arg;
    }
}


void print_code(StackElem_t code[], size_t size_code)
{
    for (size_t i = 0; i < size_code; i++)
    {
        printf("%g ", code[i]);
    }
    printf("\n");
}