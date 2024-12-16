/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   btree.c                                     _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/16 03:28:21 by aallali      -------- 1337.ma -------    */
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

static void bt_print_lvl(btree *node, int level, void (*callback)(btree *node))
{
    if (node == NULL)
        return;

    if (level == 1)
    {
        callback(node);
        return;
    }

    bt_print_lvl(node->left, level - 1, callback);
    bt_print_lvl(node->right, level - 1, callback);
}

// static void print_node_value(btree *node) {
//     printf("%d ", node->value);
// }

void bt_lvl_order_traverse(btree *node, void (*callback)(btree *node))
{
    int height;

    height = bt_calculate_height(node);

    for (int i = 1; i <= height; i++)
    {
        bt_print_lvl(node, i, callback);
    }
}

static btree *bt_temp_delete_node_check(btree *node)
{
    if (node->left != NULL && node->right != NULL)
    {
        printf("[WARNING] Two-child deletion not yet implemented\n");
        return node;
    }
    if (node->left != NULL)
    {
        btree *temp_node = node->left;
        free(node);
        return temp_node;
    }
    if (node->right != NULL)
    {
        btree *temp_node = node->right;
        free(node);
        return temp_node;
    }
    return NULL;
}
void bt_delete_node(btree **head_node, int target)
{
    if (head_node == NULL)
        return;

    if ((*head_node)->right != NULL && (*head_node)->right->value == target)
    {
 
        (*head_node)->right = bt_temp_delete_node_check((*head_node)->right);
        return;
    }
    if ((*head_node)->left != NULL && (*head_node)->left->value == target)
    {

        (*head_node)->left = bt_temp_delete_node_check((*head_node)->left);
        return;
    }
    if ((*head_node)->value < target)
        return bt_delete_node(&(*head_node)->right, target);

    if ((*head_node)->value > target)
        return bt_delete_node(&(*head_node)->left, target);

    return;
    *node = NULL;
}