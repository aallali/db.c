/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : helpers.h                                                      */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 15:17:07 by Abdellah A.                              */
/*   Updated: 2024/12/22 01:09:54 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef HELPERS_H
#define HELPERS_H

#include <bst.h>
#include <avl.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    void *(*get_child)(void *node, bool is_left);
    char *(*get_value)(void *node);
} node_handler;

void bst_print_tree(BST_NODE *node);
void avl_print_tree(AVL_NODE *node);
void print_tree_recursive(
    char *prefix,
    void *node,
    bool is_left,
    node_handler *handler);

#endif //  HELPERS_H
