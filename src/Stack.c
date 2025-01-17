/***************************************
Group No 35
 2018A7PS0238P Name: Hritwik Goklaney		         
 2018A7PS0262P Name: Yash Gupta 
 2018A7PS0161P Name: Chaitanya Kulkarni		         
 2018A7PS0004P Name: Aashay Garg	
***************************************/
#include <stdio.h>
#include<stdlib.h>
#include "Stack.h"

stack *stack_init(){
    stack *stack_ptr = (stack *)malloc(sizeof(stack));
    if (stack_ptr == NULL)
        perror("stack init error.. memory not available\n");
    stack_ptr->size = INIT_STACK_SIZE;
    stack_ptr->arr = (void **)malloc(sizeof(void *) * (stack_ptr->size));
    if (stack_ptr->arr == NULL)
        perror("stack array member init error.. memory not available\n");
    stack_ptr->top = 0;
    return stack_ptr;
}

void push(stack *stack_ptr, void *node){
    if (stack_ptr->top == (stack_ptr->size)){
        stack_ptr->size *= 2;
        void **tmp = realloc(stack_ptr->arr, sizeof(void *) * stack_ptr->size);
        if (tmp == NULL)
            perror("Error in doubling stack's size: realloc failed\n");
        else
            stack_ptr->arr = tmp;
    }
    stack_ptr->arr[stack_ptr->top] = node;
    stack_ptr->top++;
}

void *pop(stack *stack_ptr){
    if (stack_ptr->top == 0)
        return NULL;
    stack_ptr->top--;
    return stack_ptr->arr[stack_ptr->top];
}

void *top(stack *stack_ptr){
    if (stack_ptr->top == 0)
        return NULL;
    else
        return stack_ptr->arr[stack_ptr->top - 1];
}

