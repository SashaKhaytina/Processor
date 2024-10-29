#include "working_with_labels.h"


void create_new_label(Asm_SPU* proc, char label_name[])
{
    Label* new_label = &(&proc->labels)->arr[(&proc->labels)->size];
    strcpy(new_label->name, label_name);

    new_label->number_command = proc->ip;
    
    (&proc->labels)->size++;
}

int find_label_ip(Labels* labels, char label_name[]) 
{
    for (size_t i = 0; i < labels->size; i++)
    {
        if (strcmp(label_name, labels->arr[i].name) == 0) return labels->arr[i].number_command;
    }
    return -1;
}
