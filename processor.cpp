#include <stdio.h>
#include <string.h>

#include "Stack/stack_commands.h"
#include "Stack/errors.h"
#include "Stack/utils.h"

// Должен переводить файл с маш кодом (файл с цифрами) в массив и выполняться 

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
    JA = 6
};

const size_t MAX_CODE_SIZE = 10000;


struct SPU
{
    StackElem_t code[MAX_CODE_SIZE];
    size_t ip;
    Stack stack;
    StackElem_t registers[5];  // это норм тип для них?
};


size_t read_file_code(int argc, const char *argv[], SPU* proc);
void doing_code(SPU* proc);
void print_code(StackElem_t code[], size_t size_code);



int main(int argc, const char *argv[])
{
    // StackElem_t code[MAX_CODE_SIZE] = {};
    SPU proc = {};
    size_t size_code = read_file_code(argc, argv, &proc);

    print_code(proc.code, size_code);

    default_stack_ctor(&proc.stack, INITIAL_CAPACITY);
    doing_code(&proc);

}







void doing_code(SPU* proc)
{
    proc->ip = 0;

    bool continue_process = true;
    while (continue_process)
    {
        print_stack_info(&proc->stack, OK);
        int command = (int) proc->code[proc->ip];
        switch (command)
        {
        case PUSH: 
            {StackElem_t arg = proc->code[(++(proc->ip))++];
            stack_push(&proc->stack, arg);
            break;}

        case PUSHR: // Должен класть в стек то, что в регистре
            {int arg = proc->code[(++(proc->ip))++];
            stack_push(&proc->stack, proc->registers[arg]);
            break;}
        
        case POP:  // Кладет в регистр последний элемент стека 
            {int arg = proc->code[(++(proc->ip))++];

            proc->registers[arg] = (&proc->stack)->arr[(&proc->stack)->size-1];
            stack_pop(&proc->stack);
            break;}

        
        case ADD:
            {proc->ip++;
            StackElem_t elem = (&proc->stack)->arr[(&proc->stack)->size-1] + (&proc->stack)->arr[(&proc->stack)->size-2]; // Рассчитываем
            stack_pop(&proc->stack); // Удаляем
            stack_pop(&proc->stack); // Удаляем

            stack_push(&proc->stack, elem); // Добавляем
            break;}
        
        case SUB:
            {proc->ip++;
            StackElem_t elem = (&proc->stack)->arr[(&proc->stack)->size-1] - (&proc->stack)->arr[(&proc->stack)->size-2]; // Рассчитываем
            stack_pop(&proc->stack); // Удаляем
            stack_pop(&proc->stack); // Удаляем

            stack_push(&proc->stack, elem); // Добавляем
            break;}

        case MUL:
            {proc->ip++;
            StackElem_t elem = (&proc->stack)->arr[(&proc->stack)->size-1] * (&proc->stack)->arr[(&proc->stack)->size-2]; // Рассчитываем
            stack_pop(&proc->stack); // Удаляем
            stack_pop(&proc->stack); // Удаляем

            stack_push(&proc->stack, elem); // Добавляем
            break;}

        case OUT: // Он должен вытащить еще 
            {proc->ip++;

            printf("%g - это результат\n", (&proc->stack)->arr[(&proc->stack)->size-1]);
            stack_pop(&proc->stack);
            //printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
            break;}

        case JUMP:
            {proc->ip = (int) proc->code[++(proc->ip)];
            break;}
        
        case JA:
            {if ((&proc->stack)->arr[(&proc->stack)->size-2] > (&proc->stack)->arr[(&proc->stack)->size-1]) proc->ip = proc->code[++(proc->ip)];
            else proc->ip += 2;
            break;}
        
        case HLT:
            {proc->ip++;
            printf("Закончили\n");
            continue_process = false;
            break;}
        
        default:
            break;
        }

    }
}

































size_t read_file_code(int argc, const char *argv[], SPU* proc)
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
        int command = 0;
        fscanf(file_code, "%d", &command);
        printf("%d ", command);

        switch (command)
        {
        case PUSH:
            {proc->code[proc->ip++] = PUSH; 
            StackElem_t arg = 0;
            fscanf(file_code, "%lg", &arg);
            proc->code[proc->ip++] = arg;
            break;}

        case PUSHR: // Должен класть в стек то, что в регистре
            {proc->code[proc->ip++] = PUSHR; 
            StackElem_t arg = 0; // Тут индекс регистра (он должен быть int..). ОН УЖЕ ЧИСЛО!!! (его ассемблер сделал числом)
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;}
        
        case POP:  // Кладет в регистр последний элемент стека 
            {proc->code[proc->ip++] = POP; 
            StackElem_t arg = 0; // Тут индекс регистра. ОН УЖЕ ЧИСЛО!!! (его ассемблер сделал числом)
            fscanf(file_code, "%lg", &arg);
            proc->code[proc->ip++] = arg;
            break;}
        
        case ADD:
            {proc->code[proc->ip++] = ADD;
            break;}
        
        case SUB:
            {proc->code[proc->ip++] = SUB;
            break;}

        case MUL:
            {proc->code[proc->ip++] = MUL;
            break;}

        case OUT:
            {proc->code[proc->ip++] = OUT;
            break;}
        
        case JUMP:
            {proc->code[proc->ip++] = JUMP;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;}
        
        case JA:
            {proc->code[proc->ip++] = JA;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            proc->code[proc->ip++] = arg;
            break;}
        
        case HLT:
            {proc->code[proc->ip++] = HLT;
            continue_process = false;  // Из switch можно как-то остановить внешний цикл? (break занят, получается)
            break;}
        
        default:
            break;
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