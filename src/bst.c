/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : bst.c                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/19 15:42:56 by Abdellah A.                              */
/* ************************************************************************** */

#include "bst.h"
#include "string.h"

void print_n_tabs(int n)
{
    for (int i = 0; i < n; i++)
        printf("    ");
}

static void print_tree_recursive(char *prefix, bst *node, bool is_left)
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

void print_tree(bst *node)
{
    printf("\n");
    if (node != NULL)
        print_tree_recursive("", node, false);
    else
        printf("[DEBUG] This Node is EMPTY\n");

    printf("\n");
}

bst *bst_create_tree(int value)
{
    bst *fresh_node = (bst *)malloc(sizeof(bst));

    fresh_node->value = value;
    fresh_node->left = NULL;
    fresh_node->right = NULL;

    return fresh_node;
}

bst *bst_find(int target, bst *head_node)
{
    if (head_node == NULL)
        return NULL;

    if (head_node->value < target)
        return bst_find(target, head_node->right);

    if (head_node->value > target)
        return bst_find(target, head_node->left);

    return head_node;
}

bool bst_insert_node(bst **node_ptr, int value)
{
    if (*(node_ptr) == NULL)
    {
        *node_ptr = bst_create_tree(value);
        return true;
    }

    if (value > (*node_ptr)->value)
        return bst_insert_node(&(*node_ptr)->right, value);

    if (value < (*node_ptr)->value)
        return bst_insert_node(&(*(node_ptr))->left, value);

    return true;
}

int bst_calculate_height(bst *node)
{
    if (node == NULL)
        return 0;

    int left_height = 0;
    int right_height = 0;

    left_height = bst_calculate_height(node->left);
    right_height = bst_calculate_height(node->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}

static void bst_print_lvl(bst *node, int level, void (*callback)(bst *node))
{
    if (node == NULL)
        return;

    if (level == 1)
    {
        callback(node);
        return;
    }

    bst_print_lvl(node->left, level - 1, callback);
    bst_print_lvl(node->right, level - 1, callback);
}

void bst_lvl_order_traverse(bst *node, void (*callback)(bst *node))
{
    int height;

    height = bst_calculate_height(node);

    for (int i = 1; i <= height; i++)
    {
        bst_print_lvl(node, i, callback);
    }
}

void bst_in_order_traversal(bst *node, void (*callback)(bst *node))
{
    if (node == NULL)
        return;

    bst_in_order_traversal(node->left, callback);
    callback(node);
    bst_in_order_traversal(node->right, callback);
}

void bst_find_predecessor_successor(
    bst *node, int target, bst **predecessor, bst **successor)
{
    if (node == NULL)
        return;

    if (node->value == target)
    {
        if (node->left != NULL)
        {
            bst *tmp = node->left;
            while (tmp->right != NULL)
                tmp = tmp->right;
            *predecessor = tmp;
        }
        if (node->right != NULL)
        {
            bst *tmp = node->right;
            while (tmp->left != NULL)
                tmp = tmp->left;
            *successor = tmp;
        }
        return;
    }

    if (node->value > target)
    {
        *successor = node;
        bst_find_predecessor_successor(
            node->left, target, predecessor, successor);
    }
    else
    {
        *predecessor = node;
        bst_find_predecessor_successor(
            node->right, target, predecessor, successor);
    }
}

bst *bst_delete_node(bst **root, int target)
{

    if (*root == NULL)
        return *root;

    if ((*root)->value < target)
        return bst_delete_node(&(*root)->right, target);
    else if ((*root)->value > target)
        return bst_delete_node(&(*root)->left, target);
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
            bst *tmp = *root;
            *root = (*root)->right;
            free(tmp);
        }
        else if ((*root)->right == NULL)
        {
            bst *tmp = *root;
            *root = (*root)->left;
            free(tmp);
        }
        // Case 3: both childs exists
        else
        {
            bst *proc = NULL;
            bst *suc = NULL;

            bst_find_predecessor_successor(*root, target, &proc, &suc);

            (*root)->value = proc->value;
            bst_delete_node(&(*root)->left, proc->value);
        }
    }
    return *root;
}

void bst_free_tree(bst **node)
{
    if (node == NULL || *node == NULL)
    {
        return;
    }
    bst_free_tree(&(*node)->right);
    bst_free_tree(&(*node)->left);
    free(*node);
    *node = NULL;
}