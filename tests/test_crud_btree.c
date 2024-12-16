/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   test_crud_btree.c                           _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/16 14:14:22 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "btree.h"

static int temp_counter = 0;

static void count_nodes(btree *node)
{
    (void)node;
    temp_counter++;
}

int main()
{
    return 0;
}

TEST_CASE(test_bt_create_tree)
{
    btree *root_node = bt_create_tree(10);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left, NULL);
    TEST_EQUAL(root_node->right, NULL);
}

TEST_CASE(test_bt_insert_node)
{
    btree *root_node = bt_create_tree(10);
    bt_insert_node(&root_node, 1);
    bt_insert_node(&root_node, 11);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left->value, 1);
    TEST_EQUAL(root_node->right->value, 11);
}

TEST_CASE(test_bt_calculate_height)
{
    btree *node = NULL;
    int height = 1337;

    for (int i = 0; i < height; i++)
        bt_insert_node(&node, i);

    TEST_EQUAL(bt_calculate_height(node), height);
}

TEST_CASE(test_bt_find)
{
    btree *node = NULL;
    int height = 10;

    for (int i = 0; i < height; i++)
        bt_insert_node(&node, i);

    TEST_EQUAL(bt_find(height - 1, node)->value, height - 1);
    TEST_EQUAL(bt_find(0, node)->value, 0);
    TEST_EQUAL(bt_find(height, node), NULL);
}

TEST_CASE(test_bt_lvl_order_traverse)
{
    btree *node = NULL;
    int height = 10;
    temp_counter = 0;

    for (int i = 1; i <= height; i++)
        bt_insert_node(&node, i * 11);

    bt_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, height);
}

TEST_CASE(test_bt_delete_node)
{
    btree *node = NULL;
    int height = 10;
    temp_counter = 0;

    for (int i = 1; i <= height; i++)
        bt_insert_node(&node, i);

    bt_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, height);

    bt_delete_node(&node, height - 1);
    bt_delete_node(&node, height - 2);

    temp_counter = 0;
    bt_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, height - 2);
}

TEST_CASE(test_bt_delete_node_2children)
{
    btree *node = bt_create_tree(7);
    node->right = bt_create_tree(12);
    node->left = bt_create_tree(5);
    node->left->left = bt_create_tree(3);
    node->left->right = bt_create_tree(6);
    /*
            7
          /   \
         5     12
        / \
       3   6
    */
    temp_counter = 0;
    bt_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, 5); 

    bt_delete_node(&node, 5); // Should not be deleted because it sitll have 2 childrens;

    temp_counter = 0;
    bt_lvl_order_traverse(node, count_nodes);
    TEST_EQUAL(temp_counter, 5);
}
