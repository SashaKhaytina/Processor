#ifndef HEADER_PROC
#define HEADER_PROC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


#include "../Stack/stack_commands.h"
#include "../Stack/errors.h"
#include "../Stack/utils.h"
#include "../header.h"

// Должен переводить файл с маш кодом (файл с цифрами) в массив и выполняться 


// enum ArgType
// {
//     REGISTR = 1 << 7,
//     NUMBER = 1 << 6,
//     RAM = 1 << 5
// };

enum Masks
{
    ONLY_COMMAND_NUM_MASK = 31,
    ONLY_ELEM_TYPES_MASK = 224,
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

// enum MathOperation
// {
//     SUM,           // Сумма
//     DIFFERENCE,    // Разность
//     MULTIPLICATION // Умножение
// };

// const size_t MAX_CODE_SIZE       = 10000;
// const char* const READ_FILE_NAME = "program_code.txt"; 
// const size_t RAM_SIZE            = 10000; 
const double DELTA = 1e-10;


struct SPU
{
    StackElem_t code[MAX_CODE_SIZE];
    size_t ip;
    Stack stack; 
    StackElem_t registers[5];  // это норм тип для них?

    StackElem_t ram[RAM_SIZE];
    //char ram[RAM_SIZE]; // Работа с этим держится только на том, что рассматриваем, что там лежат double
    //                     То есть ACCII там тоже double, потому что POP только StackElem_t кладет
    //                     Это можно как-то исправить?
    //                     Делать "разные" POP (c доп аргументом) для разных типов? Или указывать сколько байт занимает элемент?

    //                     Повтор мыслей:
    //                     Но в стеке все равно один тип... А вся эта дичь неизбежно через него проходит
    //                     Можно вытаскивать из стека, преобразовывая тип, но тогдп надо знать во что преобразовывать.
    //                     То есть доп аргумент нужен для POP 
    // char* ram;
};


#endif