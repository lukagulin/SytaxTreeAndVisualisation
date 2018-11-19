/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "binaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void initTree(struct treeNode *root)
{
    root->left = NULL;
    root->right = NULL;
}

void addChildTreeNode(struct treeNode *root, char *data, treeDirection td)
{
    struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    if(td == LEFT)
        root->left = newNode;
    else if(td == RIGHT)
        root->right = newNode;
    else
        free(newNode);
}

void initTreeChild(struct treeNode *root, treeDirection td)
{
    struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    newNode->left = NULL;
    newNode->right = NULL;
    if(td == LEFT)
        root->left = newNode;
    else if(td == RIGHT)
        root->right = newNode;
    else
        free(newNode);    
}

void initTreeChildren(struct treeNode *root)
{
    initTreeChild(root, LEFT);
    initTreeChild(root, RIGHT);
}

struct treeNode *treeCopy(struct treeNode *orignal)
{
    struct treeNode *copy = (struct treeNode *)malloc(sizeof(struct treeNode));
    strcpy(copy->data, orignal->data);
    
    if(orignal->left)
        copy->left = treeCopy(orignal->left);
    else
        copy->left = NULL;
    
    if(orignal->right)
        copy->right = treeCopy(orignal->right);
    else
        copy->right = NULL;
    
    return copy;
}


void visitTree(struct treeNode *treeRoot, int depth)
{
    printf("%2d:\t%s\n", depth, treeRoot->data);
    if(treeRoot->left != NULL)
    {
        printf("Going left\n");
        visitTree(treeRoot->left, depth + 1);
    }
    
    if(treeRoot->right != NULL)
    {
        printf("Going right\n");
        visitTree(treeRoot->right, depth + 1);
    }
    
    printf("Going up to %d\n", depth - 1);
}

void deleteTree(struct treeNode *treeRoot)
{
    if(treeRoot->left != NULL)
    {
        deleteTree(treeRoot->left);
    }
    
    if(treeRoot->right != NULL)
    {
        deleteTree(treeRoot->right);
    }
    
    free(treeRoot);
}


void recursivePrint(struct treeNode* node, FILE* f, int i)
{
    int lChild = 2*i;
    int rChild = 2*i + 1;
    fprintf(f, "node%d [label=\"%s\"];\n", i, node->data);
    if (node->left)
    {
        fprintf(f, "node%d -> node%d;\n", i, lChild);
        recursivePrint(node->left, f, lChild);
    }

    if (node->right)
    {
        fprintf(f, "node%d -> node%d;\n", i, rChild);
        recursivePrint(node->right, f, rChild);
    }
}

void generateDOT(struct treeNode* tree, FILE* stream)
{
    fprintf(stream, "digraph BST {\n");
    recursivePrint(tree, stream, 1);
    fprintf(stream, "}\n");
}

void stepByStepGraph(struct treeNode* tree)
{
    int x = 0;
    char command[SIZE];
    FILE *f;
    system("rm tree*.svg");
    while(tree->left)
    {
        f = fopen("tree.dot", "w");
        generateDOT(tree, f);
        fclose(f);
        sprintf(command, "dot -Tsvg  tree.dot -o tree%d.svg", x++);
        system(command);
        evaluateOne(tree, 0);
    }
    
    f = fopen("tree.dot", "w");
    generateDOT(tree, f);
    fclose(f);
    sprintf(command, "dot -Tsvg  tree.dot -o tree%d.svg", x++);
    system(command);
}