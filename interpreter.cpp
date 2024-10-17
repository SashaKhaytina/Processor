#include <stdio.h>
#include <string.h>

#include "Stack/stack_commands.h"
#include "Stack/errors.h"
#include "Stack/utils.h"

// Должен переводить файл с маш кодом (файл с цифрами) в массив и выполняться 
enum MashineCode
{
    HLT = 0,
    PUSH = 51,
    ADD = 1,
    SUB = 2,
    MUL = 3, 
    OUT = 4, // ыыыы
    JUMP = 5
};

const size_t MAX_CODE_SIZE = 10000;
const size_t INITIAL_CAPACITY = 16;

size_t read_file_code(int argc, const char *argv[], StackElem_t code[]);
void doing_code(Stack* stack, StackElem_t code[], size_t size_code);
void print_code(StackElem_t code[], size_t size_code);





int main(int argc, const char *argv[])
{
    StackElem_t code[MAX_CODE_SIZE] = {};
    size_t size_code = read_file_code(argc, argv, code);

    print_code(code, size_code);

    Stack stack = {};
    default_stack_ctor(&stack, INITIAL_CAPACITY);
    doing_code(&stack, code, size_code);

}







void doing_code(Stack* stack, StackElem_t code[], size_t size_code)
{
    int ip = 0;
    bool continue_process = true;
    while (continue_process)
    {
        int command = (int) code[ip];
        switch (command)
        {
        case PUSH: 
            {StackElem_t arg = code[(++ip)++];
            stack_push(stack, arg);
            break;}
        
        case ADD:
            {ip++;
            StackElem_t elem = stack->arr[stack->size-1] + stack->arr[stack->size-2]; // Рассчитываем
            stack_pop(stack); // Удаляем
            stack_pop(stack); // Удаляем

            stack_push(stack, elem); // Добавляем
            break;}
        
        case SUB:
            {ip++;
            StackElem_t elem = stack->arr[stack->size-1] - stack->arr[stack->size-2]; // Рассчитываем
            stack_pop(stack); // Удаляем
            stack_pop(stack); // Удаляем

            stack_push(stack, elem); // Добавляем
            break;}

        case MUL:
            {ip++;
            StackElem_t elem = stack->arr[stack->size-1] * stack->arr[stack->size-2]; // Рассчитываем
            stack_pop(stack); // Удаляем
            stack_pop(stack); // Удаляем

            stack_push(stack, elem); // Добавляем
            break;}

        case OUT:
            {ip++;

            printf("%g\n", stack->arr[stack->size-1]);
            break;}

        case JUMP:
            {ip = code[++ip];
            break;}
        
        case HLT:
            {ip++;
            printf("Закончили\n");
            continue_process = false;
            break;}
        
        default:
            break;
        }

    }
}

































size_t read_file_code(int argc, const char *argv[], StackElem_t code[])
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



    int ip = 0;
    bool continue_process = true;
    while (continue_process)
    {
        int command = 0;
        fscanf(file_code, "%d", &command);
        printf("%d ", command);

        switch (command)
        {
        case PUSH:
            {code[ip++] = PUSH; 
            StackElem_t arg = 0;
            fscanf(file_code, "%lg", &arg);
            code[ip++] = arg;
            break;}
        
        case ADD:
            {code[ip++] = ADD;
            break;}
        
        case SUB:
            {code[ip++] = SUB;
            break;}

        case MUL:
            {code[ip++] = MUL;
            break;}

        case OUT:
            {code[ip++] = OUT;
            break;}
        
        case JUMP:
            {code[ip++] = JUMP;
            int arg = 0;
            fscanf(file_code, "%d", &arg);
            code[ip++] = arg;
            break;}
        
        case HLT:
            {code[ip++] = HLT;
            continue_process = false;  // Из switch можно как-то остановить внешний цикл? (break занят, получается)
            break;}
        
        default:
            break;
        }

    }
    printf("\n");
    return ip;
}

















void print_code(StackElem_t code[], size_t size_code)
{
    for (size_t i = 0; i < size_code; i++)
    {
        printf("%g ", code[i]);
    }
    printf("\n");
}