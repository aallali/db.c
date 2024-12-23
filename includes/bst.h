/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : bst.h                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/23 03:07:09 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BST_NODE
{
    int value;
    struct BST_NODE *left;
    struct BST_NODE *right;
} BST_NODE;

void bst_print_tree(BST_NODE *node);

BST_NODE *bst_create_tree(int value);

BST_NODE *bst_find(int target, BST_NODE *startNode);

bool bst_insert_node(BST_NODE **nodePtr, int v);

int bst_calculate_height(BST_NODE *node);

void bst_lvl_order_traverse(
    BST_NODE *node, void (*callback)(BST_NODE *node));

void bst_lvl_order_traverse_queue(
    BST_NODE *node, void (*callback)(BST_NODE *node));

void bst_in_order_traversal(
    BST_NODE *node, void (*callback)(BST_NODE *node));

void bst_find_predecessor_successor(
    BST_NODE *node, int target, BST_NODE **predecessor, BST_NODE **successor);

BST_NODE *bst_delete_node(BST_NODE **node, int target);

void bst_free_tree(BST_NODE **node);

void bst_main_test();

#endif // bst_H