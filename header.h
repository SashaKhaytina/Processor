#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum ArgType
{
    REGISTER = 1 << 7,
    NUMBER = 1 << 6,
    RAM = 1 << 5
};

enum MashineCode
{
    HLT = 0,
    PUSH,
    POP,
    ADD,
    SUB,
    MUL, 
    OUT, 
    JUMP,
    JA,
    JB,
    JE,
    JNE,
    IN,
    OUTC, 
    DRAW, 
    CALL, // кладет в стек ip откуда прыгнул (свой ip + 1) и прыгфет по метке
    RET, // прыгает по последнему элементу стека ()
    DIV, // деление
    SQRT
};


const size_t MAX_CODE_SIZE        = 10000;             // Максимальная длина массива с кодом
const size_t RAM_SIZE             = 10000;             // Размер оперативной памяти
const char* const READ_FILE_NAME  = "program_code.txt";




#endif