/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   btree.c                                     _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/15 01:16:41 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void print_n_tabs(int n)
{
    for (int i = 0; i < n; i++)
        printf("       ");
}

static void print_tree_recursive(btree *node, int level)
{
    if (node == NULL)
    {
        print_n_tabs(level);
        printf("---<empty>---\n");
        return;
    }

    print_n_tabs(level);
    printf("value: [%d]\n", node->value);

    print_n_tabs(level);
    printf("left:\n");
    print_tree_recursive(node->left, level + 1);

    print_n_tabs(level);
    printf("right:\n");
    print_tree_recursive(node->right, level + 1);
    return;
}

void print_tree(btree *node)
{
    print_tree_recursive(node, 0);
}

btree *bt_create_tree(int value)
{
    btree *fresh_node = (btree *)malloc(sizeof(btree));

    fresh_node->value = value;
    fresh_node->left = NULL;
    fresh_node->right = NULL;

    return fresh_node;
}

btree *bt_find(int target, btree *head_node)
{
    if (head_node == NULL)
        return NULL;

    if (head_node->value < target)
        return bt_find(target, head_node->right);

    if (head_node->value > target)
        return bt_find(target, head_node->left);

    return head_node;
}

bool bt_insert_node(btree **node_ptr, int value)
{
    btree *root = *node_ptr;

    if (root == NULL)
    {
        *node_ptr = bt_create_tree(value);
        return true;
    }

    if (value > root->value)
        return bt_insert_node(&(root->right), value);

    if (value < root->value)
        return bt_insert_node(&(root->left), value);

    return true;
}

int bt_calculate_height(btree *node)
{
    if (node == NULL)
        return 0;

    int left_height = 0;
    int right_height = 0;

    left_height = bt_calculate_height(node->left);
    right_height = bt_calculate_height(node->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}