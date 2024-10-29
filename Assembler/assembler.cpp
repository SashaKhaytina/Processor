// Порядок запуска:
// g++ Assembler/compil.cpp Assembler/working_with_code.cpp Assembler/working_with_labels.cpp Assembler/commands.cpp
// g++ compil.cpp
// ./a.out
// g++ processor.cpp Stack/stack_commands.cpp Stack/errors.cpp Stack/utils.cpp -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8000 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -o processor
// ./processor


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>


#include "header_asm.h"

#include "working_with_code.h"

// TODO: добавить call, ret, structs array, div (деление), sqrt + сделать квадратку и факториал с функциями

// Должен переводить файл слов (асемблер) в файл с маш кодом (файл с цифрами)
// в битовом формате принципиально в каком типе вводишь и читаешь?.....


// #define CHECK_JUMP_COMMAND(commanda) strcmp(command, commanda) == 0
    // if (CHECK_JUMP_COMMAND("JUMP") || 
    //     CHECK_JUMP_COMMAND("JA") || 
    //     CHECK_JUMP_COMMAND("JB") || 
    //     CHECK_JUMP_COMMAND("JE") || 
    //     CHECK_JUMP_COMMAND("JNE"))
    // {
    //     put_jump_commands(commanda, file_asm, proc);
    //     continue;
    // }







// #define CHECK_COMMAND(commanda) if (strcmp(command, commanda) == 0)
// #define FILL_CODE_FUNC_WITH_NO_ARG(command) {\
//                                                 code[(*ip)++] = command;\
//                                                 continue;\
//                                              }

// enum ArgType
// {
//     REGISTER = 1 << 7, // Это только для double!!!!??
//     NUMBER = 1 << 6,
//     RAM = 1 << 5
// };

// enum IndexRegisters 
// {
//     RAX,
//     RBX,
//     RCX, 
//     RDX,
//     REX,
// };

// enum MashineCode
// {
//     HLT = 0,
//     PUSH,
//     POP,
//     ADD,
//     SUB,
//     MUL, 
//     OUT, 
//     JUMP,
//     JA,
//     JB,
//     JE,
//     JNE,
//     IN,
//     OUTC, 
//     DRAW, 
//     CALL, // кладет в стек ip откуда прыгнул (свой ip + 1) и прыгфет по метке
//     RET // прыгает по последнему элементу стека ()
// };

// const size_t MAX_CODE_SIZE        = 10000;             // Максимальная длина массива с кодом
// const size_t MAX_NAME_LABEL_SIZE  = 50;                // Максимальная длина ИМЕНИ МЕТКИ
// const size_t MAX_LABELS_MASS_SIZE = 10;                // Максимальная длина массива меток
// const size_t MAX_COMMAND_SIZE     = 50;                // Максимальная длина ИМЕНИ КОМАНДЫ 
// const size_t MAX_ARG_COMMAND_SIZE = 50;                // Максимальная длина АРГУМЕНТА КОМАНДЫ (кол-во символов)
// const size_t RAM_SIZE             = 10000;             // Размер оперативной памяти
// const char* const FILE_NAME       = "program_asm.txt"; 
// const char* const READ_FILE_NAME  = "program_code.txt";



// struct Label
// {
//     char name[MAX_NAME_LABEL_SIZE];
//     int number_command;
// };

// struct Labels
// {
//     Label arr[MAX_LABELS_MASS_SIZE];
//     size_t size;
// };


// struct Asm_SPU
// {
//     double code[MAX_CODE_SIZE];
//     size_t size_code;
//     int ip;
//     Labels labels;
// };

// Работа с code
// int  code_put        (int argc, const char *argv[], Asm_SPU* proc, int run_num);
// void print_code      (double code[], size_t size_code);
// void code_output_file(Asm_SPU* proc);

// Работа с метками
// void create_new_label (Asm_SPU* proc, char label_name[]);
// int  find_label_ip    (Labels* labels, char label_name[]);

// // команды
// void stack_command    (FILE* file_asm, Asm_SPU* proc, MashineCode type_command);
// void put_jump_commands(MashineCode jump_type, FILE* file_asm, Asm_SPU* proc);
// void put_draw_command (FILE* file_asm, Asm_SPU* proc);

// IndexRegisters index_of_register(char arg[]);
// void check_and_put_in_right_order(Asm_SPU* proc, char arg_1[], char arg_2[]);



int main(int argc, const char *argv[])
{
    Asm_SPU proc = {};

    proc.size_code = code_put(argc, argv, &proc, 1);
    print_code(proc.code, proc.size_code);
    printf("\n");

    proc.size_code = (size_t) code_put(argc, argv, &proc, 2);
    print_code(proc.code, proc.size_code);
    code_output_file(&proc);
    
}



// int code_put(int argc, const char *argv[], Asm_SPU* proc, int run_num)
// {
//     Labels* labels = &proc->labels;
//     double* code = proc->code;

//     proc->ip = 0;
//     int* ip = &proc->ip;

//     FILE* file_asm = NULL;
    

//     if (argc != 1) file_asm = fopen(argv[1], "r");
//     else file_asm = fopen(FILE_NAME, "r");

//     // |mem|reg|imm|

//     char command[MAX_COMMAND_SIZE] = {};

//     while(fscanf(file_asm, "%s", command) != EOF) 
//     {
//         size_t len_str = strlen(command);

//         if (command[len_str - 1] == ':')
//         {
//             command[len_str - 1] = '\0';
//             if (run_num == 1) create_new_label(proc, command);

//             continue;
//         }

//         // struct CommandWithArg {
//         //     const char*;
//         //     enum;
//         //     foo;
//         // }

//         // strcmp(const char*) foo(file_asm, proc, enum)

//         // {{"PUSH", PUSH, stack_command},  {"JA", JA, put_jump_commands}}

//         CHECK_COMMAND("PUSH")
//         {
//             stack_command(file_asm, proc, PUSH);
//             continue;
//         }

//         CHECK_COMMAND("POP")
//         {
//             stack_command(file_asm, proc, POP);
//             continue;
//         }

//         CHECK_COMMAND("ADD") FILL_CODE_FUNC_WITH_NO_ARG(ADD)

//         CHECK_COMMAND("SUB") FILL_CODE_FUNC_WITH_NO_ARG(SUB)

//         CHECK_COMMAND("MUL") FILL_CODE_FUNC_WITH_NO_ARG(MUL)

//         CHECK_COMMAND("OUT") FILL_CODE_FUNC_WITH_NO_ARG(OUT)

//         CHECK_COMMAND("OUTC") FILL_CODE_FUNC_WITH_NO_ARG(OUTC)
    
//         CHECK_COMMAND("IN") FILL_CODE_FUNC_WITH_NO_ARG(IN)

//         CHECK_COMMAND("JUMP")
//         {
//             put_jump_commands(JUMP, file_asm, proc);
//             continue;
//         }

//         CHECK_COMMAND("JA")
//         {
//             put_jump_commands(JA, file_asm, proc);
//             continue;
//         }

//         CHECK_COMMAND("JB")
//         {
//             put_jump_commands(JB, file_asm, proc);
//             continue;
//         }

//         CHECK_COMMAND("JE")
//         {
//             put_jump_commands(JE, file_asm, proc);
//             continue;
//         }

//         CHECK_COMMAND("JNE")
//         {
//             put_jump_commands(JNE, file_asm, proc);
//             continue;
//         }

//         CHECK_COMMAND("DRAW")
//         {
//             put_draw_command(file_asm, proc);
//             continue;
//         }

//         CHECK_COMMAND("CALL")
//         {
//             put_jump_commands(CALL, file_asm, proc);
//             continue;
//         }

//         CHECK_COMMAND("RET") FILL_CODE_FUNC_WITH_NO_ARG(RET)

//         CHECK_COMMAND("HLT") FILL_CODE_FUNC_WITH_NO_ARG(HLT)        
//     }
//     fclose(file_asm);

//     return *ip;
// }


// void print_code(double code[], size_t size_code)
// {
//     for (size_t i = 0; i < size_code; i++)
//     {
//         printf("%g ", code[i]);
//     }
//     printf("\n");
// }


// void code_output_file(Asm_SPU* proc)
// {
//     FILE* file_code = fopen(READ_FILE_NAME, "w");

//     for (size_t i = 0; i < proc->size_code; i++)
//     {
//         fprintf(file_code, "%lg ", proc->code[i]);
//     }
//     printf("\n");
// }


// void create_new_label(Asm_SPU* proc, char label_name[])
// {
//     Label* new_label = &(&proc->labels)->arr[(&proc->labels)->size];
//     strcpy(new_label->name, label_name);

//     new_label->number_command = proc->ip;
    
//     (&proc->labels)->size++;
// }


// void stack_command(FILE* file_asm, Asm_SPU* proc, MashineCode type_command)
// {
//     proc->code[proc->ip] = type_command;
//     char arg_1[MAX_ARG_COMMAND_SIZE] = {}; 
//     char arg_2[MAX_ARG_COMMAND_SIZE] = {};

//     int count_args = fscanf(file_asm, "%s + %s", arg_1, arg_2);

//     if (count_args == 2)  // Два аргуманта (сумма (в любом порядке))
//     {
//         if (arg_1[0] == '[' && arg_2[strlen(arg_2) - 1] == ']') // если есть [] (оперативная память)
//         {
//             proc->code[(proc->ip)++] += REGISTER + NUMBER + RAM;

//             strcpy(arg_1, &arg_1[1]);
//             arg_2[strlen(arg_2) - 1] = '\0';
//         }
//         else
//         {
//             if (type_command == POP)
//             {
//                 printf("Синтаксическая ошибка\n"); // в pop нельзя подавать сумму без квадратныx скобок
//             }
//             else // PUSH
//             {
//                 proc->code[(proc->ip)++] += REGISTER + NUMBER;
//             }
//         }

//         check_and_put_in_right_order(proc, arg_1, arg_2);
//     }

//     else if (count_args == 1) // один аргумент
//     {
//         if (arg_1[0] == '[' && arg_1[strlen(arg_1) - 1] == ']')   // Опреативная память
//         {
//             proc->code[proc->ip] += RAM;

//             strcpy(arg_1, &arg_1[1]);
//             arg_1[strlen(arg_1) - 1] = '\0';
//         }


//         if (isalpha(arg_1[0]))                                    // Регистр
//         {
//             proc->code[(proc->ip)++] += REGISTER;
//             proc->code[(proc->ip)++] = index_of_register(arg_1);
//         }
//         else                                                      // Число
//         {
//             if (type_command == POP && proc->code[proc->ip] == POP) // У pop должен быть еще RAM
//             {
//                 printf("Синтаксическая ошибка\n");
//             }
//             else
//             {
//                 proc->code[(proc->ip)++] += NUMBER;
//                 proc->code[(proc->ip)++] = atof(arg_1);
//             }
//         }
//     }

//     else
//     {
//         printf("Синтаксическая ошибка\n"); 
//     }
// }


// int find_label_ip(Labels* labels, char label_name[]) 
// {
//     for (size_t i = 0; i < labels->size; i++)
//     {
//         if (strcmp(label_name, labels->arr[i].name) == 0) return labels->arr[i].number_command;
//     }
//     return -1;
// }


// void check_and_put_in_right_order(Asm_SPU* proc, char arg_1[], char arg_2[])
// {
//     if (isalpha(arg_1[0]))
//     {
//         proc->code[(proc->ip)++] = index_of_register(arg_1);
//         proc->code[(proc->ip)++] = atof(arg_2);
//     }
//     else
//     {
//         proc->code[(proc->ip)++] = index_of_register(arg_2);
//         proc->code[(proc->ip)++] = atof(arg_1);
//     }
// }


// IndexRegisters index_of_register(char arg[])
// {
//     if      (strcmp(arg, "RAX") == 0) return RAX;
//     else if (strcmp(arg, "RBX") == 0) return RBX;
//     else if (strcmp(arg, "RCX") == 0) return RCX;
//     else if (strcmp(arg, "RDX") == 0) return RDX;
//     else if (strcmp(arg, "REX") == 0) return REX;
//     return RAX; // unreachable
// }


// void put_jump_commands(MashineCode jump_type, FILE* file_asm, Asm_SPU* proc)
// {
//     proc->code[proc->ip++] = jump_type;

//     char arg[MAX_NAME_LABEL_SIZE] = "";
//     fscanf(file_asm, "%s", arg);

//     proc->code[proc->ip++] = find_label_ip(&proc->labels, arg);
// }


// void put_draw_command (FILE* file_asm, Asm_SPU* proc)
// {
//     proc->code[proc->ip++] = DRAW;
//     int arg = 0;
//     fscanf(file_asm, "%d", &arg);
//     proc->code[proc->ip++] = (double) arg;
// }







// Теперь не нужен
// void labels_ctor(Labels* labels)
// {
//     for (size_t i = 0; i < MAX_LABELS_MASS_SIZE; i++)
//     {
//         // Надо ли что-то делать с именем?
//         labels->arr[i].number_command = -1;
//     }
// }

/*
// нафиг. Но это рабочая тема!!!
// void push_command(FILE* file_asm, double code[], int* ip)
// {
//     // Пришла строка. Там может быть число, может быть регистр, а может быть сумма
//     // можем найти +, а потом запустить функцию выше (которая в комментах) (она по сути определяет тип элемента)
//     // Нет. Элементы должны идти в определенном!!! порядке. 
//     // Но мы же можем их просто переставить, если нужно, в той же функции выше.


//     // rfgtw ghjcnj rfgtw////
//     // Депрессия. ОНО НЕ ДОПИСАНО!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//     char which_push[2 * MAX_NAME_LABEL_SIZE + 1] = {}; // стал вообще треш какой-то
//     // fscanf(file_asm, "%s", which_push);

//     bool is_summ = false;
//     int ind_new_slag = 0;

//     char c = fgetc(file_asm); //пропустить пробел
//     c = fgetc(file_asm);

//     //char c = fgetc(file_asm); // пропустить пробел после 2-ого аргумента
//     for (int i = 0; c != '\n'; i++)
//     {   
//         //printf("%c - c\n", c);


//         // !!!!! Если пробел или еще какая-то фигня, можно просто не делать which_push[i] = c !!!!!

//         // if (c == ' ') // Это вообще... что.. это надо? у нас тогда индекс собьется аоаоаоаоаоаоааооаоаоаа (rax +_4) тут конец строка. За чтооооооооооо
//         // {
//         //     continue;
//         // } 

//         // if (c == '[')
//         // {
//         //     which_push[i] = '\0'; // ээээм может быть просто ничего не добавлять?
//         //     is_summ = true;
//         //     ind_new_slag = i + 1;
//         //     c = fgetc(file_asm);
//         //     continue;
//         // }
        
//         if (c == '+')
//         {
//             which_push[i] = '\0';
//             is_summ = true;
//             ind_new_slag = i + 1;
//             c = fgetc(file_asm);
//             continue;
//         }

//         which_push[i] = c;
//         c = fgetc(file_asm);
//     }
    
    
//     // Надо определить что это.
//     // ищем +
//     if (is_summ) // значит + есть...
//     {
//         code[(*ip)++] = REGISTR + NUMBER;
//         // разделить!!! (на 2 слагаемых)
//         // массив вида ["N", "A", "M", "E", "\0", "N"....]
//         //                                         ^ - тут может быть пробел
//         // ПУСТЬ НИКАКИХ ПРОБЕЛОВ. СТРУКТУРА: RAX+num
//         // Рядом с цифрой пробелы допустимы (из-за работы atof), а рядом с названием регистра - нет (будет всегда RAX по дефолту)

//         code[(*ip)++] = index_of_register(which_push);

//         code[(*ip)++] = atof(which_push + ind_new_slag);


//     }
//     else
//     {
//         //printf("%s - which_push\n", which_push);
//         if (isdigit(which_push[0]))
//         {
//             code[(*ip)++] = NUMBER;
//             code[(*ip)++] = atof(which_push);
//         }
//         else
//         {
//             code[(*ip)++] = REGISTR;
//             code[(*ip)++] = index_of_register(which_push);
//         }
//     }




//     // Это плохо. Не сработает, так как в arg лежит только до пробела.
//     // // Надо определить что это.
//     // // ищем +
//     // char* point_on_plus = strchr(arg,'+');
//     // if (point_on_plus != NULL) // значит + есть...
//     // {
//     //     // разделить!!! (на 2 слагаемых)

//     // }
//     // else
//     // {
//     //     if (isdigit(arg[0]))
//     //     {
//     //         code[(*ip)++] = atof(arg);
//     //     }
//     //     else
//     //     {
//     //         code[(*ip)++] = index_of_register(arg);
//     //     }
//     // }

// }
*/


// Это если заполнять сразу в файл, без промежуточного массива
/*
void run_compil(int argc, const char *argv[])
{
    FILE* file_asm = NULL;
    FILE* file_code = fopen("program_code.txt", "w");
    //printf("%p - uk1\n", file_code);
    

    if (argc != 1)
    {
        file_asm = fopen(argv[1], "r");
    }
    else
    {
        //printf("AAAAAAAAAAAAA\n");
        file_asm = fopen("program_asm.txt", "r");
    }

    //int counter_command = 0;
    while (true)
    {
        //printf("BBBBBBBBBBBBBBBBBB\n");
        char command[50] = {};
        printf("%p - uk\n", file_asm);
        fscanf(file_asm, "%s", command); // При чтении меток, этот съест всю строку. Как-то проверить, что последний символ ":"
        //printf("%s - res\n", command);
        //printf("CCCCC\n");

        if (strcmp(command, "PUSH") == 0)
        {
            //printf("asdaslkdnaishfasgyusdyugiuguyzgdfuigyzrgiuzgtyi\n");
            // printf("%d ", PUSH);

            //fprintf(file_code, "%d ", PUSH);

            // double arg = 0;
            // fscanf(file_asm, "%lg", &arg);
            // fprintf(file_code, "%lg \n", arg);

            char arg[10] = {};
            fscanf(file_asm, "%s", arg);
            if (isdigit(arg[0]))
            {

                fprintf(file_code, "%d ", PUSH);
                fprintf(file_code, "%lg \n", (double) atoi(arg));
            }
            else
            {
                fprintf(file_code, "%d ", PUSHR);

                if      (strcmp(arg, "RAX") == 0) fprintf(file_code, "%d \n", RAX); // ТУТ ДОЛЖЕН БЫТЬ if С ПРОВЕРКОЙ, что это за регистр
                else if (strcmp(arg, "RBX") == 0) fprintf(file_code, "%d \n", RBX);
                else if (strcmp(arg, "RCX") == 0) fprintf(file_code, "%d \n", RCX);
                else if (strcmp(arg, "RDX") == 0) fprintf(file_code, "%d \n", RDX);
                else if (strcmp(arg, "REX") == 0) fprintf(file_code, "%d \n", REX);
            }




            // printf("%lg ", arg);

            //counter_command++;

            continue;
        }

        if (strcmp(command, "POP") == 0)
        {
            fprintf(file_code, "%d ", POP);

            char arg[10] = {};
            fscanf(file_asm, "%s", arg);

            //fprintf(file_code, "0 \n"); // ТУТ ДОЛЖЕН БЫТЬ if С ПРОВЕРКОЙ arg, что это за регистр
            if      (strcmp(arg, "RAX") == 0) fprintf(file_code, "%d \n", RAX); // ТУТ ДОЛЖЕН БЫТЬ if С ПРОВЕРКОЙ, что это за регистр
            else if (strcmp(arg, "RBX") == 0) fprintf(file_code, "%d \n", RBX);
            else if (strcmp(arg, "RCX") == 0) fprintf(file_code, "%d \n", RCX);
            else if (strcmp(arg, "RDX") == 0) fprintf(file_code, "%d \n", RDX);
            else if (strcmp(arg, "REX") == 0) fprintf(file_code, "%d \n", REX);

            //counter_command++;

            continue;
        }

        

        if (strcmp(command, "ADD") == 0)
        {
            fprintf(file_code, "%d \n", ADD);

            //counter_command++;

            continue;
        }

        if (strcmp(command, "SUB") == 0)
        {
            fprintf(file_code, "%d \n", SUB);

            //counter_command++;

            continue;
        }

        if (strcmp(command, "MUL") == 0)
        {
            fprintf(file_code, "%d \n", MUL);

            //counter_command++;

            continue;
        }

        if (strcmp(command, "OUT") == 0)
        {
            fprintf(file_code, "%d \n", OUT);

            //counter_command++;

            continue;
        }

        if (strcmp(command, "JUMP") == 0)
        {
            fprintf(file_code, "%d ", JUMP);

            int arg = 0;
            fscanf(file_asm, "%d", &arg);
            fprintf(file_code, "%d \n", arg);

            //counter_command++;

            continue;
        }

        if (strcmp(command, "JA") == 0)
        {
            fprintf(file_code, "%d ", JA);

            int arg = 0;
            fscanf(file_asm, "%d", &arg);
            fprintf(file_code, "%d \n", arg);

            //counter_command++;

            continue;
        }

        if (strcmp(command, "HLT") == 0)
        {
            fprintf(file_code, "%d \n", HLT);

            //counter_command++;

            break;
        }
    }

    //fseek(file_code, 0L, SEEK_SET );
    //fprintf(file_code, "%d \n", counter_command);
}
*/



