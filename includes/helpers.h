/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : helpers.h                                                      */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 15:17:07 by Abdellah A.                              */
/*   Updated: 2024/12/21 00:12:41 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef HELPERS_H
#define HELPERS_H

#include <bst.h>
#include <avl.h>
#include <string.h>
#include <stdbool.h>

void bst_print_tree(BST_NODE *node);
void avl_print_tree(AVL_NODE *node);

#endif //  HELPERS_H
