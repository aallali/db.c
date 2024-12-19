/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : bst.h                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/19 15:42:56 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bst
{
    int value;
    struct bst *left;
    struct bst *right;
} bst;

void print_n_tabs(int n);

void print_tree(bst *node);

bst *bst_create_tree(int value);

bst *bst_find(int target, bst *startNode);

bool bst_insert_node(bst **nodePtr, int v);

int bst_calculate_height(bst *node);

void bst_lvl_order_traverse(bst *node, void (*callback)(bst *node));

void bst_in_order_traversal(bst *node, void (*callback)(bst *node));

void bst_find_predecessor_successor(
    bst *node, int target, bst **predecessor, bst **successor);

bst *bst_delete_node(bst **node, int target);

void bst_free_tree(bst **node);

#endif // bst_H