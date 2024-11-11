#include "to_do_commands.h"


static StackElem_t  get_arg_push(SPU* proc, int bit_arg); 
static StackElem_t* get_arg_pop(SPU* proc, int bit_arg); 


StackElem_t get_arg_push(SPU* proc, int bit_arg) // Возвращает значение того, что нужно положить в стек
{
    StackElem_t which_push = 0;
    
    if (bit_arg & REGISTER) // регистр
    {
        which_push += proc->registers[(int) proc->code[proc->ip++]];
    }
    if (bit_arg & NUMBER)  // число 
    {
        which_push += proc->code[proc->ip++];
    }
    if (bit_arg & RAM)    // оперативная память 
    {
        which_push = proc->ram[(int) which_push];
    }

    return which_push;
}


StackElem_t* get_arg_pop(SPU* proc, int bit_arg) // Возвращает указатель на регистр или на ячейку в оперативной памяти
{
    if (bit_arg & RAM)                                                       // Опреативная память
    {
        StackElem_t which_push = 0;
        if (bit_arg & REGISTER)                                                  // регистр
        {
            which_push += proc->registers[(int) proc->code[proc->ip++]];
        }
        if (bit_arg & NUMBER)                                                   // число
        {
            which_push += proc->code[proc->ip++];
        }

        return &proc->ram[(int) which_push]; // указатель на яч в оп памяти
    }
    else                                                                     // Только регистр
    {
        int arg = (int) proc->code[proc->ip++];
        return &proc->registers[arg];        // указатель на регистр
    }
}


void to_do_push(SPU* proc)
{
    int bit_arg = (int) proc->code[proc->ip++] & ONLY_ELEM_TYPES_MASK; 

    stack_push(&proc->stack, get_arg_push(proc, bit_arg));
}


void to_do_pop(SPU* proc)
{
    int bit_arg = (int) proc->code[proc->ip++] & ONLY_ELEM_TYPES_MASK; 

    StackElem_t last_elem = 0;
    stack_pop(&proc->stack, &last_elem); // Вытаскиваем элемент

    StackElem_t* place_to_put = get_arg_pop(proc, bit_arg); // Место, куда pop должен положить
    *place_to_put = last_elem;
}


void to_do_calculate(SPU* proc, MashineCode operation)
{
    StackElem_t elem1 = 0;
    StackElem_t elem2 = 0;
    
    stack_pop(&proc->stack, &elem1); 
    stack_pop(&proc->stack, &elem2); 

    switch (operation)
    {
    case ADD:
        {
        stack_push(&proc->stack, elem1 + elem2);
        break;
        }

    case SUB:
        {
        stack_push(&proc->stack, elem1 - elem2);
        break;
        }

    case MUL:
        {
        stack_push(&proc->stack, elem1 * elem2);
        break;
        }

    case DIV:
        {
        stack_push(&proc->stack, elem1 / elem2);
        break;
        }

    default:
        {
        printf("Синтаксическая ошибка\n");
        break;
        }
    }
}


void to_do_sqrt(SPU* proc)
{
    StackElem_t elem = 0;
    stack_pop(&proc->stack, &elem);
    stack_push(&proc->stack, sqrt(elem));
}


void to_do_out(SPU* proc)
{
    StackElem_t elem = 0;
    stack_pop(&proc->stack, &elem);

    printf("%f - это результат\n", elem);
}


void to_do_outc(SPU* proc)
{
    StackElem_t elem = 0;
    stack_pop(&proc->stack, &elem);

    printf("%c", (int) elem);
}


void to_do_draw(SPU* proc)
{
    int num = (int) proc->code[proc->ip++];

    for (int i = 0; i < num * 8; i += 8) printf("%c", (int) proc->ram[i]); 
}


void to_do_in(SPU* proc)
{
    StackElem_t arg = 0;
    printf("Введите число: \n");
    scanf("%lg", &arg);
    
    stack_push(&proc->stack, arg);
}


void to_do_call(SPU* proc)
{
    stack_push(&proc->stack, (StackElem_t)(proc->ip + 1));
    proc->ip = (size_t) proc->code[proc->ip];
}


void to_do_ret (SPU* proc)
{
    StackElem_t elem1 = 0;
    stack_pop(&proc->stack, &elem1);
    proc->ip = (size_t) elem1; // прыжок на элемент из стека
}


void to_do_conditional_jump(SPU* proc, MashineCode operation)
{
    StackElem_t elem1 = 0;
    StackElem_t elem2 = 0;
    
    stack_pop(&proc->stack, &elem1); 
    stack_pop(&proc->stack, &elem2); 

    bool correctness_condition = false;

    switch (operation)
    {
    case JA:
        {
        correctness_condition = (elem2 > elem1);
        break;
        }
    case JB:
        {
        correctness_condition = (elem2 < elem1);
        break;
        }
    case JE:
        {
        correctness_condition = (fabs(elem2 - elem1) < DELTA);
        break;
        }
    case JNE:
        {
        correctness_condition = (fabs(elem2 - elem1) > DELTA);
        break;
        }
    default:
        printf("Синтаксическая ошибка\n"); 
    }

    if (correctness_condition) proc->ip = (size_t) proc->code[++(proc->ip)];
    else                       proc->ip += 2;
}
