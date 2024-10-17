// Порядок запуска:
// g++ compil.cpp
// ./a.out
// g++ processor.cpp Stack/stack_commands.cpp Stack/errors.cpp Stack/utils.cpp -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8000 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -o processor
// ./processor


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Должен переводить файл слов (асемблер) в файл с маш кодом (файл с цифрами)

enum IndexRegistrs 
{
    RAX,
    RBX,
    RCX, 
    RDX,
    REX,
};

enum MashineCode
{
    HLT = 0,
    PUSH = 51,
    PUSHR = 52,
    POP = 42,
    ADD = 1,
    SUB = 2,
    MUL = 3, 
    OUT = 4, // ыыыы
    JUMP = 5,
    JA = 6
};

const size_t MAX_CODE_SIZE = 10000;

// void run_compil(int argc, const char *argv[], double code[]);
int code_put(int argc, const char *argv[], double code[]); // Он заполняет!
void print_code(double code[], size_t size_code);
void code_output_file(int argc, const char *argv[], double code[], size_t size);




int main(int argc, const char *argv[])
{
    double code[MAX_CODE_SIZE]; // В этом файле все StackElem_t заменены на double 
    size_t size = (size_t) code_put(argc, argv, code);
    print_code(code, size);
    code_output_file(argc, argv, code, size);
    
}



void code_output_file(int argc, const char *argv[], double code[], size_t size)
{
    FILE* file_code = fopen("program_code.txt", "w");

    //printf("%p - uk1\n", file_code);
    int ip = 0;



    //int counter_comand = 0;
    while(ip < size) // вроде такой критерий...
    {
        //printf("BBBBBBBBBBBBBBBBBB\n");
        //printf("%s - res\n", command);
        //printf("CCCCC\n");

        int command = code[ip];

        switch (command)
        {
        case PUSH:
            {fprintf(file_code, "%d %lg\n", PUSH, code[++ip]); 
            ip++;
            break;}

        case PUSHR: // Должен класть в стек то, что в регистре
            {fprintf(file_code, "%d %d\n", PUSHR, (int) code[++ip]); 
            ip++;
            break;}
        
        case POP:  // Кладет в регистр последний элемент стека 
            {fprintf(file_code, "%d %d\n", POP, (int) code[++ip]); 
            ip++;
            break;}
        
        case ADD:
            {fprintf(file_code, "%d\n", ADD);
            ip++; 
            break;}
        
        case SUB:
            {fprintf(file_code, "%d\n", SUB);
            ip++; 
            break;}

        case MUL:
            {fprintf(file_code, "%d\n", MUL);
            ip++; 
            break;}

        case OUT:
            {fprintf(file_code, "%d\n", OUT);
            ip++; 
            break;}
        
        case JUMP:
            {fprintf(file_code, "%d %d\n", JUMP, (int) code[++ip]); 
            ip++; 
            break;}
        
        case JA:
            {fprintf(file_code, "%d %d\n", JA, (int) code[++ip]); 
            ip++;
            break;}
        
        case HLT:
            {fprintf(file_code, "%d\n", HLT);
            ip++;  // Из switch можно как-то остановить внешний цикл? (break занят, получается)
            break;}
        
        default:
            break;
        }

    }
}
















int code_put(int argc, const char *argv[], double code[])
{
    FILE* file_asm = NULL;
    //printf("%p - uk1\n", file_code);
    int ip = 0;
    

    if (argc != 1)
    {
        file_asm = fopen(argv[1], "r");
    }
    else
    {
        //printf("AAAAAAAAAAAAA\n");
        file_asm = fopen("program_asm.txt", "r");
    }



    //int counter_comand = 0;
    while (true)   // ЭТО ПЛОХО!!! НИЖЕ HLT СТРОКИ НЕ ПРОЧИТАЕТ!!!! Надо сделать пока не EOF
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
                code[ip++] = PUSH;
                code[ip++] = (double) atoi(arg);
                //fprintf(file_code, "%d ", PUSH);
                //fprintf(file_code, "%lg \n", (double) atoi(arg));
            }
            else
            {
                code[ip++] = PUSHR;
                //fprintf(file_code, "%d ", PUSHR);

                if      (strcmp(arg, "RAX") == 0) code[ip++] = RAX; // ТУТ ДОЛЖЕН БЫТЬ if С ПРОВЕРКОЙ, что это за регистр
                else if (strcmp(arg, "RBX") == 0) code[ip++] = RBX;
                else if (strcmp(arg, "RCX") == 0) code[ip++] = RCX;
                else if (strcmp(arg, "RDX") == 0) code[ip++] = RDX;
                else if (strcmp(arg, "REX") == 0) code[ip++] = REX;
            }




            // printf("%lg ", arg);

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "POP") == 0)
        {
            code[ip++] = POP;
            //fprintf(file_code, "%d ", POP);

            char arg[10] = {};
            fscanf(file_asm, "%s", arg);

            //fprintf(file_code, "0 \n"); // ТУТ ДОЛЖЕН БЫТЬ if С ПРОВЕРКОЙ arg, что это за регистр
            if      (strcmp(arg, "RAX") == 0) code[ip++] = RAX; // ТУТ ДОЛЖЕН БЫТЬ if С ПРОВЕРКОЙ, что это за регистр
            else if (strcmp(arg, "RBX") == 0) code[ip++] = RBX;
            else if (strcmp(arg, "RCX") == 0) code[ip++] = RCX;
            else if (strcmp(arg, "RDX") == 0) code[ip++] = RDX;
            else if (strcmp(arg, "REX") == 0) code[ip++] = REX;

            //counter_comand++;

            continue;
        }

        

        if (strcmp(command, "ADD") == 0)
        {
            //fprintf(file_code, "%d \n", ADD);
            code[ip++] = ADD;

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "SUB") == 0)
        {
            //fprintf(file_code, "%d \n", SUB);
            code[ip++] = SUB;

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "MUL") == 0)
        {
            //fprintf(file_code, "%d \n", MUL);
            code[ip++] = MUL;

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "OUT") == 0)
        {
            //fprintf(file_code, "%d \n", OUT);
            code[ip++] = OUT;

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "JUMP") == 0)
        {
            //fprintf(file_code, "%d ", JUMP);
            code[ip++] = JUMP;

            int arg = 0;
            fscanf(file_asm, "%d", &arg);
            //fprintf(file_code, "%d \n", arg);
            code[ip++] = (double) arg;

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "JA") == 0)
        {
            //fprintf(file_code, "%d ", JA);
            code[ip++] = JA;

            int arg = 0;
            fscanf(file_asm, "%d", &arg);
            //fprintf(file_code, "%d \n", arg);
            code[ip++] = (double) arg;

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "HLT") == 0)
        {
            //fprintf(file_code, "%d \n", HLT);
            code[ip++] = HLT;

            //counter_comand++;

            break;  // ЭТО ПЛОХО!!! НИЖЕ ЭТОЙ СТРОКИ НЕ ПРОЧИТАЕТ!!!! Надо сделать пока не EOF
        }
    }

    return ip;

    //fseek(file_code, 0L, SEEK_SET );
    //fprintf(file_code, "%d \n", counter_comand);
}


void print_code(double code[], size_t size_code)
{
    for (size_t i = 0; i < size_code; i++)
    {
        printf("%g ", code[i]);
    }
    printf("\n");
}


















// Закрыть файл !!!!!

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

    //int counter_comand = 0;
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

            //counter_comand++;

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

            //counter_comand++;

            continue;
        }

        

        if (strcmp(command, "ADD") == 0)
        {
            fprintf(file_code, "%d \n", ADD);

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "SUB") == 0)
        {
            fprintf(file_code, "%d \n", SUB);

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "MUL") == 0)
        {
            fprintf(file_code, "%d \n", MUL);

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "OUT") == 0)
        {
            fprintf(file_code, "%d \n", OUT);

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "JUMP") == 0)
        {
            fprintf(file_code, "%d ", JUMP);

            int arg = 0;
            fscanf(file_asm, "%d", &arg);
            fprintf(file_code, "%d \n", arg);

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "JA") == 0)
        {
            fprintf(file_code, "%d ", JA);

            int arg = 0;
            fscanf(file_asm, "%d", &arg);
            fprintf(file_code, "%d \n", arg);

            //counter_comand++;

            continue;
        }

        if (strcmp(command, "HLT") == 0)
        {
            fprintf(file_code, "%d \n", HLT);

            //counter_comand++;

            break;
        }
    }

    //fseek(file_code, 0L, SEEK_SET );
    //fprintf(file_code, "%d \n", counter_comand);
}
*/




