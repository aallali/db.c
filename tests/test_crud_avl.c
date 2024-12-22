/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : test_crud_avl.c                                                */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/22 03:33:28 by Abdellah A.                              */
/*   Updated: 2024/12/22 03:33:29 by Abdellah A.                              */
/* ************************************************************************** */

#include "test.h"
#include "avl.h"

TEST_CASE(test_avl_create_tree)
{
    AVL_NODE *root_node = avl_create_node(10);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left, NULL);
    TEST_EQUAL(root_node->right, NULL);
}

