/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "constants.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>

void initStack(struct stack* s)
{
    s->head = NULL;
}

void push(struct stack* s, char* data)
{
    struct stackNode* newNode = (struct stackNode*)malloc(sizeof(struct stackNode));
    strcpy(newNode->data, data);
    newNode->previous = s->head;
    s->head = newNode;
}

void pop(struct stack* s, char* dest)
{  
    strcpy(dest, s->head->data);
    struct stackNode* newHead = s->head->previous;
    free(s->head);
    s->head = newHead;
}

void deleteStackNode(struct stackNode* node)
{
    if(node->previous)
        deleteStackNode(node->previous);
    
    free(node);
}

void deleteStack(struct stack* s)
{
    if(s->head)
        deleteStackNode(s->head);
}

int isStackEmpty(struct stack* s)
{
    return !s->head;
}