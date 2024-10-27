// g++ processor.cpp Stack/stack_commands.cpp Stack/errors.cpp Stack/utils.cpp -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8000 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -o processor



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#include "Stack/stack_commands.h"
#include "Stack/errors.h"
#include "Stack/utils.h"

// Должен переводить файл с маш кодом (файл с цифрами) в массив и выполняться 


enum ArgType
{
    REGISTR = 1 << 7,
    NUMBER = 1 << 6,
    RAM = 1 << 5
};


enum MashineCode
{
    HLT = 0,
    PUSH,
    PUSHR,
    POP,
    ADD,
    SUB,
    MUL, 
    OUT, // ыыыы
    JUMP,
    JA,
    JB,
    JE,
    JNE,
    IN
};

// enum MathOperation
// {
//     SUM,           // Сумма
//     DIFFERENCE,    // Разность
//     MULTIPLICATION // Умножение
// };

const size_t MAX_CODE_SIZE       = 10000;
// const int STOP_PROGRAMM = -1;
const char* const READ_FILE_NAME = "program_code.txt"; 
const size_t RAM_SIZE            = 10000; 



struct SPU
{
    StackElem_t code[MAX_CODE_SIZE];
    size_t ip;
    Stack stack; 
    StackElem_t registers[5];  // это норм тип для них?

    StackElem_t ram[RAM_SIZE];
};


size_t read_file_code(SPU* proc);
void   run_code      (SPU* proc);
void   print_code    (StackElem_t code[], size_t size_code);

void to_do_push(SPU* proc);
void to_do_pop (SPU* proc);

//void to_do_calculate(SPU* proc, MathOperation operation);
void to_do_calculate(SPU* proc, MashineCode operation);


void to_do_add (SPU* proc);
void to_do_sub (SPU* proc);
void to_do_mul (SPU* proc);


void to_do_out (SPU* proc);
void to_do_in  (SPU* proc);

StackElem_t get_arg(SPU* proc, int bit_arg);


void to_do_jump_with_criteria(SPU* proc, MashineCode operation);

void put_jump_commands(MashineCode jump_type, FILE* file_code, SPU* proc);
void put_arguments    (FILE* file_code, SPU* proc, int bit_arg);
// void to_do_any_jump(SPU* proc, MashineCode jump_type);




int main() 
{
    SPU proc = {};
    proc.ram[5] = 500;
    proc.ram[2] = 200;
    proc.ram[3] = 300;
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
        MashineCode command = (MashineCode) ((int)(proc->code[proc->ip]) & 31);
        switch (command)
        {
        case PUSH: 
        {
            // printf("PUSH\n");
            to_do_push(proc);
            break;
        }
        
        case POP:  // Кладет в регистр последний элемент стека 
        {
            // printf("POP\n");
            // proc->ip++;
            to_do_pop(proc);
            break;
        }
        
        case ADD: 
        {
            // printf("ADD\n");
            proc->ip++;
            to_do_calculate(proc, ADD);
            break;
        }
        
        case SUB:
        {
            // printf("SUB\n");
            proc->ip++;
            to_do_calculate(proc, SUB);
            break;
        }

        case MUL:
        {
            // printf("MUL\n");
            proc->ip++;
            to_do_calculate(proc, MUL);
            break;
        }

        case OUT: // Он должен вытащить еще 
        {
            // printf("OUT\n");
            proc->ip++;
            to_do_out(proc);
            break;
        }
        
        case IN: // push в стек то, что вводим с клавиатуры
        {
            // printf("IN\n");
            proc->ip++;
            to_do_in(proc);
            break;
        }

        case JUMP:
        {
            // printf("JUMP\n");
            proc->ip = (size_t) proc->code[++(proc->ip)];
            break;
        }
        
        case JA: case JB: case JE: case JNE:
        {
            // printf("ANOTHER JUMP\n");
            to_do_jump_with_criteria(proc, command);
            break;
        }
        
        case HLT:
        {
            // printf("HLT\n");
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

    int num_in_mashine_code = 0;

    while (fscanf(file_code, "%d", &num_in_mashine_code) != EOF)
    {
        proc->code[proc->ip++] = num_in_mashine_code;
    }

    return proc->ip;
    // char text[MAX_CODE_SIZE * 3];
    // size_t len_text = size_file(file_code);

    // fread(text, sizeof(char), len_text, file_code);

    // for (size_t i = 0; i < len_text; i++)
    // {
    //     if (isdigit(text[i])) proc->code[i] = 
    // }
}



// size_t size_file(FILE* file)
// {
//     size_t size = 0;

//     fseek(file, 0, SEEK_END);
//     size = (size_t) ftell(file);
//     fseek(file, 0, SEEK_SET);

//     return size;
// }





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
    if (bit_arg & RAM) 
    {
        which_push = proc->ram[(int) which_push];
    }

    return which_push;
}


StackElem_t* get_arg_pop(SPU* proc, int bit_arg) // Указатель на регистр или на ячейку памяти!!!
{
    StackElem_t* point_to_put = NULL;

    if (bit_arg & RAM)
    {
        StackElem_t which_push = 0;
        if (bit_arg & REGISTR) // регистр
        {
            //printf("%d - reg\n", (int) proc->code[proc->ip++]);
            which_push += proc->registers[(int) proc->code[proc->ip++]];
        }
        if (bit_arg & NUMBER) // число .............
        {
            which_push += proc->code[proc->ip++];
        }

        return &proc->ram[(int) which_push]; // указатель на ячейку
    }
    else // только регистр
    {
        int arg = (int) proc->code[proc->ip++];
        return &proc->registers[arg];
        //stack_pop(&proc->stack, &proc->registers[arg]);
    }
    
    // if (bit_arg & RAM) 
    // {
    //     which_push = proc->ram[(int) which_push];
    // }

    //return which_push;
}


void to_do_push(SPU* proc)
{
    int bit_arg = (int) proc->code[proc->ip++] & 224; 

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
    int bit_arg = (int) proc->code[proc->ip++] & 224;
    // int arg = (int) proc->code[proc->ip++];
    StackElem_t last_elem = 0;
    stack_pop(&proc->stack, &last_elem);

    StackElem_t* uk = get_arg_pop(proc, bit_arg);

    *uk = last_elem;

    //proc->registers[arg] = (&proc->stack)->arr[(&proc->stack)->size-1];
    // stack_pop(&proc->stack, &proc->registers[arg]); // Это сработает, если там все из char?
}



// void to_do_calculate(SPU* proc, MathOperation operation)
void to_do_calculate(SPU* proc, MashineCode operation)
{
    StackElem_t elem1 = 0;
    StackElem_t elem2 = 0;
    
    stack_pop(&proc->stack, &elem1); // Удаляем
    stack_pop(&proc->stack, &elem2); // Удаляем

    switch (operation)
    {
    case ADD:
        {
        stack_push(&proc->stack, elem1 + elem2);
        break;
        }

    case SUB:
        {
        stack_push(&proc->stack, elem1 - elem2);
        break;
        }

    case MUL:
        {
        stack_push(&proc->stack, elem1 * elem2);
        break;
        }
    default:
        {
        printf("Тут надо вернуть код ошибки...\nКороче у вас ошибка синтаксиса\n");
        break;
        }
    }
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




void to_do_jump_with_criteria(SPU* proc, MashineCode operation)
{
    StackElem_t elem1 = 0;
    StackElem_t elem2 = 0;
    
    stack_pop(&proc->stack, &elem1); // Удаляем
    stack_pop(&proc->stack, &elem2); // Удаляем

    bool correctness_condition = false;

    switch (operation)
    {
    case JA:
        {
        correctness_condition = (elem2 > elem1);
        break;
        }
    case JB:
        {
        correctness_condition = (elem2 < elem1);
        break;
        }
    case JE:
        {
        correctness_condition = (elem2 == elem1);
        break;
        }
    case JNE:
        {
        correctness_condition = (elem2 != elem1);
        break;
        }
    default:
        printf("Какая-то ошибка. Синтаксическая\n");
    }

    if (correctness_condition) proc->ip = (size_t) proc->code[++(proc->ip)];
    else                       proc->ip += 2;
}


// void put_jump_commands(MashineCode jump_type, FILE* file_code, SPU* proc)
// {
//     proc->code[proc->ip++] = jump_type;
//     int arg = 0;
//     fscanf(file_code, "%d", &arg);
//     proc->code[proc->ip++] = arg;
// }


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