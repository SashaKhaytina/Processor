#ifndef TO_DO_COMMANDS
#define TO_DO_COMMANDS

#include "header_proc.h"

void to_do_push            (SPU* proc);
void to_do_pop             (SPU* proc);
void to_do_calculate       (SPU* proc, MashineCode operation);
void to_do_sqrt            (SPU* proc);
void to_do_out             (SPU* proc);
void to_do_outc            (SPU* proc);
void to_do_draw            (SPU* proc);
void to_do_in              (SPU* proc);
void to_do_call            (SPU* proc);
void to_do_ret             (SPU* proc);
void to_do_conditional_jump(SPU* proc, MashineCode operation);


#endif