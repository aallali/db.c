/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : btree.h                                                        */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/19 15:09:16 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct btree
{
    int value;
    struct btree *left;
    struct btree *right;
} btree;

void print_n_tabs(int n);

void print_tree(btree *node);

btree *bt_create_tree(int value);

btree *bt_find(int target, btree *startNode);

bool bt_insert_node(btree **nodePtr, int v);

int bt_calculate_height(btree *node);

void bt_lvl_order_traverse(btree *node, void (*callback)(btree *node));

void bt_in_order_traversal(btree *node, void (*callback)(btree *node));

void bt_find_predecessor_successor(
    btree *node, int target, btree **predecessor, btree **successor);

btree *bt_delete_node(btree **node, int target);

void bt_free_tree(btree **node);

#endif // BTREE_H