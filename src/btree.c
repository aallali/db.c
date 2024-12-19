/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : btree.c                                                        */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/19 15:08:38 by Abdellah A.                              */
/* ************************************************************************** */

#include "btree.h"
#include "string.h"

void print_n_tabs(int n)
{
    for (int i = 0; i < n; i++)
        printf("    ");
}

static void print_tree_recursive(char *prefix, btree *node, bool is_left)
{
    if (node == NULL)
        return;

    printf("%s", prefix);
    printf("%s", is_left == true ? "├──────" : "└──────");
    printf("%d\n", node->value);

    char *new_prefix = malloc(strlen(prefix) + 9 + 1);

    strcpy(new_prefix, prefix);
    strcat(new_prefix, is_left ? "│      " : "       ");

    print_tree_recursive(new_prefix, node->left, true);
    print_tree_recursive(new_prefix, node->right, false);

    free(new_prefix);
    return;
}

void print_tree(btree *node)
{
    printf("\n");
    if (node != NULL)
        print_tree_recursive("", node, false);
    else
        printf("[DEBUG] This Node is EMPTY\n");

    printf("\n");
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
    if (*(node_ptr) == NULL)
    {
        *node_ptr = bt_create_tree(value);
        return true;
    }

    if (value > (*node_ptr)->value)
        return bt_insert_node(&(*node_ptr)->right, value);

    if (value < (*node_ptr)->value)
        return bt_insert_node(&(*(node_ptr))->left, value);

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

void bt_lvl_order_traverse(btree *node, void (*callback)(btree *node))
{
    int height;

    height = bt_calculate_height(node);

    for (int i = 1; i <= height; i++)
    {
        bt_print_lvl(node, i, callback);
    }
}

void bt_in_order_traversal(btree *node, void (*callback)(btree *node))
{
    if (node == NULL)
        return;

    bt_in_order_traversal(node->left, callback);
    callback(node);
    bt_in_order_traversal(node->right, callback);
}

void bt_find_predecessor_successor(
    btree *node, int target, btree **predecessor, btree **successor)
{
    if (node == NULL)
        return;

    if (node->value == target)
    {
        if (node->left != NULL)
        {
            btree *tmp = node->left;
            while (tmp->right != NULL)
                tmp = tmp->right;
            *predecessor = tmp;
        }
        if (node->right != NULL)
        {
            btree *tmp = node->right;
            while (tmp->left != NULL)
                tmp = tmp->left;
            *successor = tmp;
        }
        return;
    }

    if (node->value > target)
    {
        *successor = node;
        bt_find_predecessor_successor(
            node->left, target, predecessor, successor);
    }
    else
    {
        *predecessor = node;
        bt_find_predecessor_successor(
            node->right, target, predecessor, successor);
    }
}

btree *bt_delete_node(btree **root, int target)
{

    if (*root == NULL)
        return *root;

    if ((*root)->value < target)
        return bt_delete_node(&(*root)->right, target);
    else if ((*root)->value > target)
        return bt_delete_node(&(*root)->left, target);
    else
    {

        // Case 1: no child
        if ((*root)->right == NULL && (*root)->left == NULL)
        {
            free(*root);
            *root = NULL;
        }
        // Case 2: one
        else if ((*root)->left == NULL)
        {
            btree *tmp = *root;
            *root = (*root)->right;
            free(tmp);
        }
        else if ((*root)->right == NULL)
        {
            btree *tmp = *root;
            *root = (*root)->left;
            free(tmp);
        }
        // Case 3: both childs exists
        else
        {
            btree *proc = NULL;
            btree *suc = NULL;

            bt_find_predecessor_successor(*root, target, &proc, &suc);

            (*root)->value = proc->value;
            bt_delete_node(&(*root)->left, proc->value);
        }
    }
    return *root;
}

void bt_free_tree(btree **node)
{
    if (node == NULL || *node == NULL)
    {
        return;
    }
    bt_free_tree(&(*node)->right);
    bt_free_tree(&(*node)->left);
    free(*node);
    *node = NULL;
}