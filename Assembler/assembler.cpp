#include "header_asm.h"
#include "working_with_code.h"


int main(int argc, const char *argv[])
{
    Asm_SPU proc = {};

    proc.size_code = fill_code(argc, argv, &proc, 1);
    // print_code(proc.code, proc.size_code);
    // printf("\n");

    proc.size_code = (size_t) fill_code(argc, argv, &proc, 2);
    // print_code(proc.code, proc.size_code);
    code_output_file(&proc);
    
}
