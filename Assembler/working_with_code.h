#ifndef WORKING_WITH_CODE
#define WORKING_WITH_CODE

#include "header_asm.h"
#include "commands.h"

const char* const FILE_NAME   = "Programms_asm/program_asm.txt"; 


struct CommandWithArg 
{
    const char Command_name[MAX_COMMAND_SIZE];
    MashineCode command;
    void (*to_do_comm)(FILE* file_asm, Asm_SPU* proc, MashineCode com);
};

const CommandWithArg commands_arr[] = {
                                        {"HLT",  HLT,  fill_code_func_with_no_arg},
                                        {"PUSH", PUSH, stack_command},
                                        {"POP",  POP,  stack_command},
                                        {"ADD",  ADD,  fill_code_func_with_no_arg},
                                        {"SUB",  SUB,  fill_code_func_with_no_arg},
                                        {"MUL",  MUL,  fill_code_func_with_no_arg},
                                        {"OUT",  OUT,  fill_code_func_with_no_arg},
                                        {"JUMP", JUMP, put_jump_commands},
                                        {"JA",   JA,   put_jump_commands},
                                        {"JB",   JB,   put_jump_commands},
                                        {"JE",   JE,   put_jump_commands},
                                        {"JNE",  JNE,  put_jump_commands},
                                        {"IN",   IN,   fill_code_func_with_no_arg},
                                        {"OUTC", OUTC, fill_code_func_with_no_arg},
                                        {"DRAW", DRAW, put_draw_command},
                                        {"CALL", CALL, put_jump_commands},
                                        {"RET",  RET,  fill_code_func_with_no_arg},
                                        {"DIV",  DIV,  fill_code_func_with_no_arg},
                                        {"SQRT", SQRT, fill_code_func_with_no_arg}
                                    };


int  fill_code       (int argc, const char *argv[], Asm_SPU* proc, int run_num);
void print_code      (double code[], size_t size_code);
void code_output_file(Asm_SPU* proc);



#endif
