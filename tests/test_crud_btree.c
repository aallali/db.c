/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   test_crud_btree.c                           _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/16 02:13:38 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "btree.h"

int main()
{
    return 0;
}

TEST_CASE(test_bt_create_tree)
{
    btree *root_node = bt_create_tree(10);
    bt_insert_node(&root_node, 10);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left, NULL);
    TEST_EQUAL(root_node->right, NULL);
}

TEST_CASE(test_bt_insert_node)
{
    btree *root_node = bt_create_tree(10);
    bt_insert_node(&root_node, 10);
    TEST_EQUAL(root_node->value, 10);
    TEST_EQUAL(root_node->left, NULL);
    TEST_EQUAL(root_node->right, NULL);

    bt_insert_node(&root_node, 1);
    TEST_EQUAL(root_node->left->value, 1);
    TEST_NOTEQUAL(root_node->left, NULL);

    bt_insert_node(&root_node, 11);
    TEST_NOTEQUAL(root_node->right, NULL);
    TEST_EQUAL(root_node->right->value, 11);
}

TEST_CASE(test_bt_calculate_height)
{
    btree *node;
    int height;

    node = NULL;
    height = 1337;

    for (int i = 0; i < height; i++)
        bt_insert_node(&node, i);

    TEST_EQUAL(bt_calculate_height(node), height);
}

TEST_CASE(test_bt_find)
{
    btree *node;
    int height;

    node = NULL;
    height = 10;

    for (int i = 0; i < height; i++)
        bt_insert_node(&node, i);

    // last node in tree
    TEST_EQUAL(bt_find(height - 1, node)->value, height - 1);
    // first node (head)
    TEST_EQUAL(bt_find(0, node)->value, 0);
    // doesn't exists
    TEST_EQUAL(bt_find(height, node), NULL);
}
int temp_counter = 0;
static void test_count_nodes_on_traversal(btree *node)
{
    // (void)v;
    printf("%d ", node->value);
    temp_counter++;
    return;
}
TEST_CASE(test_bt_lvl_order_traverse)
{
    btree *node;
    int height;

    node = NULL;
    height = 10;

    for (int i = 1; i <= height; i++)
        bt_insert_node(&node, i * 11);
        
    bt_lvl_order_traverse(node, test_count_nodes_on_traversal);
    TEST_EQUAL(temp_counter, height);
}
