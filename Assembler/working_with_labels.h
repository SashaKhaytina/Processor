#ifndef WORKING_WITH_LABELS
#define WORKING_WITH_LABELS

#include "header_asm.h"

void create_new_label (Asm_SPU* proc, char label_name[]);
int  find_label_ip    (Labels* labels, char label_name[]);


#endif