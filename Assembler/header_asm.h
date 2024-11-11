#ifndef HEADER_ASM
#define HEADER_ASM


#include "../header.h" 


enum IndexRegisters 
{
    RAX,
    RBX,
    RCX, 
    RDX,
    REX,
};

const size_t MAX_LABELS_MASS_SIZE = 10; // Максимальная длина массива меток
const size_t MAX_COMMAND_SIZE     = 50; // Максимальная длина ИМЕНИ КОМАНДЫ 
const size_t MAX_NAME_LABEL_SIZE  = 50; // Максимальная длина ИМЕНИ МЕТКИ



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