/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : test_crud_bst.c                                                */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/22 03:20:41 by Abdellah A.                              */
/* ************************************************************************** */

#include "test.h"
#include "bst.h"

static int temp_counter = 0;

static void count_nodes(BST_NODE *node)
{
    (void)node;
    temp_counter++;
}

TEST_CASE(test_bst_create_tree)
{
    BST_NODE *root_node = bst_create_tree(10);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left, NULL);
    TEST_EQUAL(root_node->right, NULL);
    bst_free_tree(&root_node);
}

TEST_CASE(test_bst_insert_node)
{
    BST_NODE *root_node = bst_create_tree(10);
    bst_insert_node(&root_node, 1);
    bst_insert_node(&root_node, 11);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left->value, 1);
    TEST_EQUAL(root_node->right->value, 11);
    bst_free_tree(&root_node);
}

TEST_CASE(test_bst_calculate_height)
{
    BST_NODE *node = NULL;
    int height = 1337;

    for (int i = 0; i < height; i++)
        bst_insert_node(&node, i);

    TEST_EQUAL(bst_calculate_height(node), height);
    bst_free_tree(&node);
}

TEST_CASE(test_bst_find)
{
    BST_NODE *node = NULL;
    int height = 10;

    for (int i = 0; i < height; i++)
        bst_insert_node(&node, i);

    TEST_EQUAL(bst_find(height - 1, node)->value, height - 1);
    TEST_EQUAL(bst_find(0, node)->value, 0);
    TEST_EQUAL(bst_find(height, node), NULL);
    bst_free_tree(&node);
}

TEST_CASE(test_bst_lvl_order_traverse)
{
    BST_NODE *node = NULL;
    int height = 10;
    temp_counter = 0;

    for (int i = 1; i <= height; i++)
        bst_insert_node(&node, i * 11);

    bst_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, height);
    bst_free_tree(&node);
}
}

TEST_CASE(test_bst_delete_node)
{
    BST_NODE *node = NULL;
    int height = 10;
    temp_counter = 0;

    for (int i = 1; i <= height; i++)
        bst_insert_node(&node, i);

    bst_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, height);

    bst_delete_node(&node, height - 1);
    bst_delete_node(&node, height - 2);

    temp_counter = 0;
    bst_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, height - 2);
    bst_free_tree(&node);
}

TEST_CASE(test_bst_delete_node_2children)
{
    BST_NODE *node = bst_create_tree(7);
    node->right = bst_create_tree(12);
    node->left = bst_create_tree(5);
    node->left->left = bst_create_tree(3);
    node->left->right = bst_create_tree(6);
    /*
            7
          /   \
         5     12
        / \
       3   6
    */
    temp_counter = 0;
    bst_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, 5);
    TEST_EQUAL(node->value, 7);
    bst_delete_node(&node, 7);
    /*
            6
          /   \
         5     12
        /
       3
    */
    temp_counter = 0;
    bst_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, 4);
    TEST_EQUAL(node->value, 6);
    bst_delete_node(&node, 6);

    TEST_EQUAL(node->value, 5);
    TEST_EQUAL(node->right->value, 12);
    TEST_EQUAL(node->left->value, 3);

    temp_counter = 0;
    bst_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, 3);
    bst_delete_node(&node, 3);
    bst_delete_node(&node, 12);
    bst_delete_node(&node, 5);
    TEST_EQUAL(node, NULL);
    bst_free_tree(&node);
}
