#ifndef HEADER_PROC
#define HEADER_PROC

#include "../header.h"
#include <math.h>


#include "../Stack/stack_commands.h"
#include "../Stack/errors.h"
#include "../Stack/utils.h"


enum Masks
{
    ONLY_COMMAND_NUM_MASK = 31,
    ONLY_ELEM_TYPES_MASK = 224,
};


struct SPU
{
    StackElem_t code[MAX_CODE_SIZE];
    size_t ip;
    Stack stack; 
    StackElem_t registers[5];

    StackElem_t ram[RAM_SIZE];

};


#endif