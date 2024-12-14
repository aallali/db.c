#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef struct treeNode
{
    int value;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

void print_n_tabs(int n);

void print_tree(treeNode *node, int level);

treeNode *createTree(int value);

treeNode *find(int target, treeNode *startNode);

bool insert_node(treeNode **nodePtr, int v);

int calculate_height(treeNode *node);

#endif // BTREE_H