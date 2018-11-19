#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "binaryTree.h"
#include "constants.h"


int isNumber(char *exp)
{
    char *end;
    double value = strtod(exp, &end);
    return end == exp + strlen(exp);
}

void buildSyntaxTree(char exp[SIZE], struct treeNode *treeRoot)
{
    //printf("exp: %s\n", exp);
    int i, j, N, par;
    char ctostr[2];
    char ldata[SIZE], rdata[SIZE];
    ctostr[1] = '\0';
    if(isNumber(exp))
    {
        strcpy(treeRoot->data, exp);
        return;
    }
    N = strlen(exp);
    par = 0;
    for(i = N - 1; i >= 0; i--)
    {
        if(exp[i] == ')')
            par++;
        else if(exp[i] == '(')
            par--;
        else if((exp[i] == '+' || exp[i] == '-') && par == 0)
        {
            ctostr[0] = exp[i];
            strcpy(treeRoot->data, ctostr);
            
            strncpy(ldata, exp, i);
            ldata[i] = '\0';
            strcpy(rdata, exp + i + 1);
            initTreeChildren(treeRoot);
            buildSyntaxTree(ldata, treeRoot->left);
            buildSyntaxTree(rdata, treeRoot->right);
            return;
        }
    }
    
    
    par = 0;
    for(i = N - 1; i >= 0; i--)
    {
        if(exp[i] == ')')
            par++;
        else if(exp[i] == '(')
            par--;
        else if((exp[i] == '*' || exp[i] == '/') && par == 0)
        {
            ctostr[0] = exp[i];
            strcpy(treeRoot->data, ctostr);
            
            strncpy(ldata, exp, i);
            ldata[i] = '\0';
            strcpy(rdata, exp + i + 1);
            initTreeChildren(treeRoot);
            buildSyntaxTree(ldata, treeRoot->left);
            buildSyntaxTree(rdata, treeRoot->right);
            return;
        }
    }
    
    par = 0;
    for(i = N - 1; i >= 0; i--)
    {
        if(exp[i] == ')')
            par++;
        else if(exp[i] == '(')
            par--;
        else if(exp[i] == '^' && par == 0)
        {
            ctostr[0] = exp[i];
            strcpy(treeRoot->data, ctostr);
            
            strncpy(ldata, exp, i);
            ldata[i] = '\0';
            strcpy(rdata, exp + i + 1);
            initTreeChildren(treeRoot);
            buildSyntaxTree(ldata, treeRoot->left);
            buildSyntaxTree(rdata, treeRoot->right);
            return;
        }
    }
    
    if(exp[0] == '(' && exp[N - 1] == ')')
    {
        strcpy(ldata, exp + 1);
        ldata[N - 2] = '\0';
        buildSyntaxTree(ldata, treeRoot);
        return;
    }
    
}


double evaluateTree(struct treeNode *treeRoot)
{
    if(treeRoot->left == NULL || treeRoot->right == NULL)
        return strtod(treeRoot->data, NULL);
    
    switch(treeRoot->data[0]){
        case '+':
            return evaluateTree(treeRoot->left) + evaluateTree(treeRoot->right);
            break;
        case '-':
            return evaluateTree(treeRoot->left) - evaluateTree(treeRoot->right);
            break;
        case '*':
            return evaluateTree(treeRoot->left) * evaluateTree(treeRoot->right);
            break;
        case '/':
            return evaluateTree(treeRoot->left) / evaluateTree(treeRoot->right);
            break;
        case '^':
            return pow(evaluateTree(treeRoot->left), evaluateTree(treeRoot->right));
            break;
    }
}

int evaluateOne(struct treeNode *treeRoot, int evaluated)
{
    double lValue, rValue, value;
    if(evaluated || treeRoot->left == NULL || treeRoot->right == NULL)
        return evaluated;
    
    if(isNumber(treeRoot->left->data) &&  isNumber(treeRoot->right->data))
    {
        evaluated = 1;
        lValue = strtod(treeRoot->left->data, NULL);
        rValue = strtod(treeRoot->right->data, NULL);
        switch(treeRoot->data[0]){
        case '+':
            value = lValue + rValue;
            break;
        case '-':
            value = lValue - rValue;
            break;
        case '*':
            value = lValue * rValue;
            break;
        case '/':
            value = lValue / rValue;;
            break;
        case '^':
            value = pow(lValue, rValue);
            break;
        }
        free(treeRoot->left);
        free(treeRoot->right);
        treeRoot->left = NULL;
        treeRoot->right = NULL;
        sprintf(treeRoot->data, "%.2lf", value);
    }
    else
    {
        evaluated = evaluateOne(treeRoot->left, evaluated);
        evaluated = evaluateOne(treeRoot->right, evaluated);
    }
    
    return evaluated;
}

void deleteWhitespaces(char *str)
{
    int i, j, N;
    N = strlen(str);
    for(i = 0; i < N; i++)
        if(str[i] == ' ')
            for(int j = i; j < strlen(str); j++)
                str[j] = str[j + 1];
}

void toPostfixString(struct treeNode* root, char *outStr)
{
    if(root->left)
        toPostfixString(root->left, outStr);
    if(root->right)
        toPostfixString(root->right, outStr);
    
    strcat(outStr, root->data);
    strcat(outStr, " ");
}

void toPostfixStack(struct treeNode* root, struct stack *s)
{
    push(s, root->data);
    if(root->right)
        toPostfixStack(root->right, s);
    if(root->left)
        toPostfixStack(root->left, s);
}

double evaluatePostfix(struct stack* s)
{
    struct stack evaluationStack;
    char token[SIZE];
    char op1[SIZE], op2[SIZE], result[100];
    double lValue, rValue, value;
    while(!isStackEmpty(s))
    {
        pop(s, token);
        if(!isNumber(token))
        {
            pop(&evaluationStack, op2);
            pop(&evaluationStack, op1);
            lValue = strtod(op1, NULL);
            rValue = strtod(op2, NULL);
            switch (token[0]) {
                case '+':
                    value = lValue + rValue;
                    break;
                case '-':
                    value = lValue - rValue;
                    break;
                case '*':
                    value = lValue * rValue;
                    break;
                case '/':
                    value = lValue / rValue;
                    ;
                    break;
                case '^':
                    value = pow(lValue, rValue);
                    break;
            }
            sprintf(result, "%lf", value);
            push(&evaluationStack, result);
        }
        else
        {
            push(&evaluationStack, token);
        }
    }
    
    pop(&evaluationStack, result);
    return strtod(result, NULL);
}

int findChar(char *str, char token)
{
    int i;
    for(i = 0; i < strlen(str); i++)
        if(str[i] == token)
            return i;
    return strlen(str);
}

double evaluatePostfixString(char *postfix)
{
    struct stack evaluationStack;
    int pos;
    char token[SIZE];
    char op1[SIZE], op2[SIZE], result[100];
    double lValue, rValue, value;
    while(*postfix != '\0')
    {
        pos = findChar(postfix, ' ');
        strncpy(token, postfix, pos);
        token[pos] = '\0';
        postfix += pos + 1;
        
        if(!isNumber(token))
        {
            pop(&evaluationStack, op2);
            pop(&evaluationStack, op1);
            lValue = strtod(op1, NULL);
            rValue = strtod(op2, NULL);
            switch (token[0]) {
                case '+':
                    value = lValue + rValue;
                    break;
                case '-':
                    value = lValue - rValue;
                    break;
                case '*':
                    value = lValue * rValue;
                    break;
                case '/':
                    value = lValue / rValue;
                    ;
                    break;
                case '^':
                    value = pow(lValue, rValue);
                    break;
            }
            sprintf(result, "%lf", value);
            push(&evaluationStack, result);
        }
        else
        {
            push(&evaluationStack, token);
        }
    }
    
    pop(&evaluationStack, result);
    return strtod(result, NULL);
}

int main(int argc, char** argv) {
    
    char exp[SIZE] ="2+2*2";// "2/(3+4*5)-5*(2^(2+3)-1)+4";
    gets(exp);
    char postfix[SIZE] = "";
    struct treeNode *syntaxTree, *copy;
    struct stack s;
    
    syntaxTree = (struct treeNode *)malloc(sizeof(struct treeNode));
    copy = (struct treeNode *)malloc(sizeof(struct treeNode));
    initTree(syntaxTree);
    initTree(copy);
    initStack(&s);
    
    deleteWhitespaces(exp);
    
    syntaxTree = (struct treeNode *)malloc(sizeof(struct treeNode));
    buildSyntaxTree(exp, syntaxTree);
    
    
    
    toPostfixStack(syntaxTree, &s);
    printf("Postfix result: %lf\n", evaluatePostfix(&s));
    while(!isStackEmpty(&s))
    {
        pop(&s, postfix);
        printf("%s ", postfix);
    }
    
    
    toPostfixString(syntaxTree, postfix);
    printf("%s\n", postfix);
    printf("Postfix string result: %lf\n", evaluatePostfixString(postfix));
    printf("Tree result: %lf\n", evaluateTree(syntaxTree));
    
    copy = treeCopy(syntaxTree);
    visitTree(syntaxTree, 0);
    stepByStepGraph(syntaxTree);
    
    deleteTree(syntaxTree);
    deleteTree(copy);
    deleteStack(&s);
    return 0;
}