#ifndef HEADER_ASM
#define HEADER_ASM


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../header.h"


#define CHECK_COMMAND(commanda) if (strcmp(command, commanda) == 0)
#define FILL_CODE_FUNC_WITH_NO_ARG(command) {\
                                                code[(*ip)++] = command;\
                                                continue;\
                                             }

// enum ArgType
// {
//     REGISTER = 1 << 7, // Это только для double!!!!??
//     NUMBER = 1 << 6,
//     RAM = 1 << 5
// };

enum IndexRegisters 
{
    RAX,
    RBX,
    RCX, 
    RDX,
    REX,
};

// enum MashineCode
// {
//     HLT = 0,
//     PUSH,
//     POP,
//     ADD,
//     SUB,
//     MUL, 
//     OUT, 
//     JUMP,
//     JA,
//     JB,
//     JE,
//     JNE,
//     IN,
//     OUTC, 
//     DRAW, 
//     CALL, // кладет в стек ip откуда прыгнул (свой ip + 1) и прыгфет по метке
//     RET // прыгает по последнему элементу стека ()
// };

// const size_t MAX_CODE_SIZE        = 10000;             // Максимальная длина массива с кодом
const size_t MAX_NAME_LABEL_SIZE  = 50;                // Максимальная длина ИМЕНИ МЕТКИ
const size_t MAX_LABELS_MASS_SIZE = 10;                // Максимальная длина массива меток
const size_t MAX_COMMAND_SIZE     = 50;                // Максимальная длина ИМЕНИ КОМАНДЫ 
const size_t MAX_ARG_COMMAND_SIZE = 50;                // Максимальная длина АРГУМЕНТА КОМАНДЫ (кол-во символов)
// const size_t RAM_SIZE             = 10000;             // Размер оперативной памяти
const char* const FILE_NAME       = "program_asm.txt"; 
// const char* const READ_FILE_NAME  = "program_code.txt";



struct Label
{
    char name[MAX_NAME_LABEL_SIZE];
    int number_command;
};

struct Labels
{
    Label arr[MAX_LABELS_MASS_SIZE];
    size_t size;
};


struct Asm_SPU
{
    double code[MAX_CODE_SIZE];
    size_t size_code;
    int ip;
    Labels labels;
};


#endif