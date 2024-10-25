// g++ processor.cpp Stack/stack_commands.cpp Stack/errors.cpp Stack/utils.cpp -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8000 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -o processor



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Stack/stack_commands.h"
#include "Stack/errors.h"
#include "Stack/utils.h"

// Должен переводить файл с маш кодом (файл с цифрами) в массив и выполняться 

enum ArgType
{
    REGISTR = 1 << 0,
    NUMBER = 1 << 1
};

enum IndexRegistrs // Это не сюда, это в ассемблер
{
    RAX,
    RBX,
    RCX, 
    RDX,
    REX,
};

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


struct SPU
{
    StackElem_t code[MAX_CODE_SIZE];
    size_t ip;
    Stack stack; 
    StackElem_t registers[5];  // это норм тип для них?
};


size_t read_file_code(SPU* proc);
void run_code      (SPU* proc);
void print_code      (StackElem_t code[], size_t size_code);



int main() // флаги мешают (или нет...)
{
    // StackElem_t code[MAX_CODE_SIZE] = {};
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
        // case PUSH: 
        // {
        //     StackElem_t arg = proc->code[(++(proc->ip))++]; // TODO: pizdec nahui
        //     stack_push(&proc->stack, arg);
        //     break;
        // }

        // case PUSHR: // Должен класть в стек то, что в регистре
        // {
        //     proc->ip++;
        //     int arg = (int) proc->code[proc->ip++];
        //     stack_push(&proc->stack, proc->registers[arg]);
        //     break;
        // }

        case PUSH: 
        {
            // printf("AAA\n");
            int bit_arg = (int) proc->code[(++(proc->ip))++]; // TODO: pizdec nahui 
                                                        // согласна
            StackElem_t which_push = 0;
            
            if (bit_arg & REGISTR) // регистр
            {
                which_push += proc->registers[(int) proc->code[proc->ip++]];
            }
            if (bit_arg & NUMBER) // число .............
            {
                which_push += proc->code[proc->ip++];
            }

            stack_push(&proc->stack, which_push);
            break;
        }
        
        case POP:  // Кладет в регистр последний элемент стека 
        {
            //printf("POP\n");
            proc->ip++;
            int arg = (int) proc->code[proc->ip++];

            proc->registers[arg] = (&proc->stack)->arr[(&proc->stack)->size-1];
            stack_pop(&proc->stack);
            break;
        }
        
        case ADD: // TODO: delete copypaste
        {
            // TODO: stack pop should return value (pass it by pointer)
            proc->ip++;
            StackElem_t elem = (&proc->stack)->arr[(&proc->stack)->size-1] + (&proc->stack)->arr[(&proc->stack)->size-2]; // TODO: pop will delete this pizdec
            stack_pop(&proc->stack); // Удаляем
            stack_pop(&proc->stack); // Удаляем

            stack_push(&proc->stack, elem); // Добавляем
            break;
        }
        
        case SUB:
        {
            proc->ip++;
            StackElem_t elem = (&proc->stack)->arr[(&proc->stack)->size-1] - (&proc->stack)->arr[(&proc->stack)->size-2]; // Рассчитываем
            stack_pop(&proc->stack); // Удаляем
            stack_pop(&proc->stack); // Удаляем

            stack_push(&proc->stack, elem); // Добавляем
            break;
        }

        case MUL:
        {
            proc->ip++;
            StackElem_t elem = (&proc->stack)->arr[(&proc->stack)->size-1] * (&proc->stack)->arr[(&proc->stack)->size-2]; // Рассчитываем
            stack_pop(&proc->stack); // Удаляем
            stack_pop(&proc->stack); // Удаляем

            stack_push(&proc->stack, elem); // Добавляем
            break;
        }

        case OUT: // Он должен вытащить еще 
        {
            proc->ip++;

            printf("%g - это результат\n", (&proc->stack)->arr[(&proc->stack)->size-1]);
            stack_pop(&proc->stack);
            break;
        }
        
        case IN: // push в стек то, что вводим с клавиатуры
        {
            proc->ip++;

            StackElem_t arg = 0;
            printf("Введите число: \n");
            scanf("%lg", &arg);
            
            stack_push(&proc->stack, arg);
            break;
        }

        case JUMP:
        {
            proc->ip = (size_t) proc->code[++(proc->ip)];
            break;
        }
        
        case JA:
        {
            if ((&proc->stack)->arr[(&proc->stack)->size-2] > (&proc->stack)->arr[(&proc->stack)->size-1]) proc->ip = (size_t) proc->code[++(proc->ip)];
            else proc->ip += 2;
            break;
        }

        case JB:
        {
            if ((&proc->stack)->arr[(&proc->stack)->size-2] < (&proc->stack)->arr[(&proc->stack)->size-1]) proc->ip = (size_t) proc->code[++(proc->ip)];
            else proc->ip += 2;
            break;
        }

        case JE: // тут == !!!!
        {
            if ((&proc->stack)->arr[(&proc->stack)->size-2] == (&proc->stack)->arr[(&proc->stack)->size-1]) proc->ip = (size_t) proc->code[++(proc->ip)];
            else proc->ip += 2;
            break;
        }

        case JNE:
        {
            if ((&proc->stack)->arr[(&proc->stack)->size-2] != (&proc->stack)->arr[(&proc->stack)->size-1]) proc->ip = (size_t) proc->code[++(proc->ip)];
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
            break;
        }

        //print_stack_info(&proc->stack, OK);

    }
}

































size_t read_file_code(SPU* proc)
{
    FILE* file_code = NULL;
    file_code = fopen("program_code.txt", "r");

    // if (argc != 1)
    // {
    //     file_code = fopen(argv[1], "r");
    // }
    // else
    // {
    //     file_code = fopen("program_code.txt", "r");
    // }



    proc->ip = 0;
    bool continue_process = true;
    while (continue_process)
    {
        //printf("234567890987\n");//...........................g
        int command = 0;
        fscanf(file_code, "%d", &command);
        printf("%d ", command);

        switch (command)
        {
        // case PUSH:
        //     {
        //     proc->code[proc->ip++] = PUSH; // TODO: you do that in every case
        //     StackElem_t arg = 0;
        //     fscanf(file_code, "%lg", &arg);
        //     proc->code[proc->ip++] = arg;
        //     break;
        //     }

        // case PUSHR: // Должен класть в стек то, что в регистре
        //     {
        //     proc->code[proc->ip++] = PUSHR; 
        //     StackElem_t arg = 0; // Тут индекс регистра (он должен быть int..). ОН УЖЕ ЧИСЛО!!! (его ассемблер сделал числом)
        //     fscanf(file_code, "%lg", &arg); // TODO: why here %d, and in others %lg
        //     proc->code[proc->ip++] = arg;
        //     break;
        //     }

        case PUSH:
            {
            //    printf("PUSH_______\n"); // че за ........ вапвавоповпьвокпиовкаопворапдовапивоапирвиапдивопивиприваипрвкиапривапвдапив
            proc->code[proc->ip++] = PUSH; // TODO: you do that in every case
            int bit_arg = 0;
            fscanf(file_code, "%d", &bit_arg);
            proc->code[proc->ip++] = bit_arg;
            //printf("%d - bit_arg\n", bit_arg);

            if (bit_arg & REGISTR) // регистр
            {
                //printf("AASASASDASAFSDFSDFSDFS\n");
                StackElem_t arg = 0;
                fscanf(file_code, "%lg", &arg); 
                proc->code[proc->ip++] = arg;
            }
            if (bit_arg & NUMBER) // число .............
            {
                StackElem_t arg = 0;
                fscanf(file_code, "%lg", &arg); 
                proc->code[proc->ip++] = arg;
            }

            // StackElem_t arg = 0;
            // fscanf(file_code, "%lg", &arg);
            // proc->code[proc->ip++] = arg;
            break;
            }
        
        case POP:  // Кладет в регистр последний элемент стека 
            {
                //printf("POP_\n");
            proc->code[proc->ip++] = POP; 
            StackElem_t arg = 0; // Тут индекс регистра. ОН УЖЕ ЧИСЛО!!! (его ассемблер сделал числом)
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
            proc->code[proc->ip++] = JUMP;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;
            }
        
        case JA:
            {
            proc->code[proc->ip++] = JA;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;
            }
        
        case JB:
            {
            proc->code[proc->ip++] = JB;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;
            }
        
        case JE:
            {
            proc->code[proc->ip++] = JE;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;
            }
        
        case JNE:
            {
            proc->code[proc->ip++] = JNE;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;
            }
        
        case HLT:
            {
            proc->code[proc->ip++] = HLT;
            continue_process = false;  // Из switch можно как-то остановить внешний цикл? (break занят, получается)
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

















void print_code(StackElem_t code[], size_t size_code)
{
    for (size_t i = 0; i < size_code; i++)
    {
        printf("%g ", code[i]);
    }
    printf("\n");
}