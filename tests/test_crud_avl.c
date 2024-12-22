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

TEST_CASE(test_avl_insert_node)
{
    AVL_NODE *root_node = avl_create_node(10);
    root_node = avl_insert_node(root_node, 1);
    root_node = avl_insert_node(root_node, 11);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left->value, 1);
    TEST_EQUAL(root_node->right->value, 11);
}

TEST_CASE(test_avl_insert_node_2)
{
    AVL_NODE *root_node = avl_create_node(10);
    root_node = avl_insert_node(root_node, 20);
    root_node = avl_insert_node(root_node, 30);
    root_node = avl_insert_node(root_node, 40);
    root_node = avl_insert_node(root_node, 50);
    root_node = avl_insert_node(root_node, 25);
    TEST_EQUAL(root_node->value, 30);
    TEST_EQUAL(root_node->left->value, 20);
    TEST_EQUAL(root_node->right->value, 40);
    TEST_EQUAL(root_node->left->left->value, 10);
    TEST_EQUAL(root_node->left->right->value, 25);
    TEST_EQUAL(root_node->right->right->value, 50);
}

TEST_CASE(test_avl_insert_node_3)
{
    AVL_NODE *root_node = avl_create_node(10);
    root_node = avl_insert_node(root_node, 20);
    root_node = avl_insert_node(root_node, 30);
    root_node = avl_insert_node(root_node, 40);
    root_node = avl_insert_node(root_node, 50);
    root_node = avl_insert_node(root_node, 25);
    root_node = avl_insert_node(root_node, 35);
    root_node = avl_insert_node(root_node, 45);
    root_node = avl_insert_node(root_node, 55);
    TEST_EQUAL(root_node->value, 30);
    TEST_EQUAL(root_node->left->value, 20);
    TEST_EQUAL(root_node->right->value, 40);
    TEST_EQUAL(root_node->left->left->value, 10);
    TEST_EQUAL(root_node->left->right->value, 25);
    TEST_EQUAL(root_node->right->right->value, 50);
    TEST_EQUAL(root_node->right->left->value, 35);
    TEST_EQUAL(root_node->right->right->right->value, 55);
    TEST_EQUAL(root_node->right->right->left->value, 45);
}

