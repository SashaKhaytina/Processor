#ifndef WORKING_WITH_CODE_IN_PROC
#define WORKING_WITH_CODE_IN_PROC

#include "header_proc.h"

size_t read_file_code(SPU* proc);
void   run_code      (SPU* proc);
void   print_code    (StackElem_t code[], size_t size_code);


#endif