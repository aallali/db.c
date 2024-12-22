/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : avl.h                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 12:55:28 by Abdellah A.                              */
/*   Updated: 2024/12/22 03:16:05 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define HEIGHT_OR_ZERO(a) ((a) != NULL ? (a->height) : (0))

typedef struct AVL_NODE
{
    int value;
    int height;
    struct AVL_NODE *left;
    struct AVL_NODE *right;
} AVL_NODE;

AVL_NODE *avl_create_node(int value);

AVL_NODE *avl_insert_node(AVL_NODE *root, int value);

AVL_NODE *avl_rotation_left(AVL_NODE *x);

AVL_NODE *avl_rotation_right(AVL_NODE *y);

int avl_height(AVL_NODE *node);

int avl_get_balance(AVL_NODE *node);

void avl_free_tree(AVL_NODE *node);

void avl_main_test();

#endif // AVL_H