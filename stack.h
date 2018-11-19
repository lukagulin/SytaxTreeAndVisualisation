#ifndef STACK_H
#define STACK_H
#include "constants.h"

struct stackNode
{
    struct stackNode* previous; 
    char data[SIZE];
};

struct stack
{
    struct stackNode* head;
};

void initStack(struct stack* s);
void push(struct stack* s, char* data);
void pop(struct stack* s, char* dest);
void deleteStackNode(struct stackNode* node);
void deleteStack(struct stack* s);
int isStackEmpty(struct stack* s);


#endif /* STACK_H */

