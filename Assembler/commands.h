#ifndef COMMANDS
#define COMMANDS

#include "header_asm.h"
#include "working_with_labels.h"

void stack_command    (FILE* file_asm, Asm_SPU* proc, MashineCode type_command);
void put_jump_commands(MashineCode jump_type, FILE* file_asm, Asm_SPU* proc);
void put_draw_command (FILE* file_asm, Asm_SPU* proc);

IndexRegisters index_of_register(char arg[]);
void check_and_put_in_right_order(Asm_SPU* proc, char arg_1[], char arg_2[]);




#endif