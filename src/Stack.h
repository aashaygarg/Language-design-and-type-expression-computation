#include <stdio.h>
#include<stdlib.h>

#define INIT_STACK_SIZE 200

typedef struct{
    void **arr;
    int top;
    int size;
} stack;

stack *stack_init();

void push(stack *stack_ptr, void *node);

void *pop(stack *stack_ptr);

void *top(stack *stack_ptr);
