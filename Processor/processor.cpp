#include "header_proc.h"
#include "working_with_code_in_proc.h"


int main() 
{
    SPU proc = {};
    proc.ram[5] = 5;
    proc.ram[2] = 2;
    proc.ram[3] = 3;

    size_t size_code = read_file_code(&proc);

    print_code(proc.code, size_code);

    default_stack_ctor(&proc.stack, INITIAL_CAPACITY);
    run_code(&proc);
    stack_dtor(&proc.stack);

}



