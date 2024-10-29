#ifndef COMMANDS
#define COMMANDS

#include "header_asm.h"
#include "working_with_labels.h"

const size_t MAX_ARG_COMMAND_SIZE = 50; // Максимальная длина АРГУМЕНТА КОМАНДЫ (кол-во символов)


void stack_command             (FILE* file_asm, Asm_SPU* proc, MashineCode type_command);
void put_jump_commands         (FILE* file_asm, Asm_SPU* proc, MashineCode jump_type);
void fill_code_func_with_no_arg(FILE* file_asm, Asm_SPU* proc, MashineCode com);
void put_draw_command          (FILE* file_asm, Asm_SPU* proc, MashineCode command);


#endif