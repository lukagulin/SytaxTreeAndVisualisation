#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "constants.h"
#include <stdio.h>
    
typedef enum
{
    LEFT, RIGHT
} treeDirection;

struct treeNode
{
    struct treeNode *left;
    struct treeNode *right;
    char data[SIZE];
};

void initTree(struct treeNode *root);
void addChildTreeNode(struct treeNode *root, char *data, treeDirection td);
void initTreeChild(struct treeNode *root, treeDirection td);
void initTreeChildren(struct treeNode *root);
struct treeNode *treeCopy(struct treeNode *orignal);
void visitTree(struct treeNode *treeRoot, int depth);
void deleteTree(struct treeNode *treeRoot);

void recursivePrint(struct treeNode* node, FILE* f, int i);
void generateDOT(struct treeNode* tree, FILE* stream);
void stepByStepGraph(struct treeNode* tree);

#endif /* BINARYTREE_H */

