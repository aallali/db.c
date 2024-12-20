/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : avl.h                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 12:55:28 by Abdellah A.                              */
/*   Updated: 2024/12/21 00:05:29 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct AVL_NODE
{
    int value;
    int height;
    struct AVL_NODE *left;
    struct AVL_NODE *right;
} AVL_NODE;

AVL_NODE *avl_create_node(int value);

void avl_free_tree(AVL_NODE *node);

void avl_main_test();

#endif // AVL_H