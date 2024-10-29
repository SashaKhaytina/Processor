#ifndef WORKING_WITH_CODE
#define WORKING_WITH_CODE

#include "header_asm.h"
#include "commands.h"

int  code_put        (int argc, const char *argv[], Asm_SPU* proc, int run_num);
void print_code      (double code[], size_t size_code);
void code_output_file(Asm_SPU* proc);


#endif
