/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : bst.c                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/23 16:27:36 by Abdellah A.                              */
/* ************************************************************************** */

#include "bst.h"
#include "helpers.h"
#include "queue.h"

BST_NODE *bst_create_tree(int value)
{
    BST_NODE *fresh_node = (BST_NODE *)malloc(sizeof(BST_NODE));

    fresh_node->value = value;
    fresh_node->left = NULL;
    fresh_node->right = NULL;

    return fresh_node;
}

BST_NODE *bst_find(int target, BST_NODE *head_node)
{
    if (head_node == NULL)
        return NULL;

    if (head_node->value < target)
        return bst_find(target, head_node->right);

    if (head_node->value > target)
        return bst_find(target, head_node->left);

    return head_node;
}

bool bst_insert_node(BST_NODE **node_ptr, int value)
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

int bst_calculate_height(BST_NODE *node)
{
    if (node == NULL)
        return 0;

    int left_height = 0;
    int right_height = 0;

    left_height = bst_calculate_height(node->left);
    right_height = bst_calculate_height(node->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}

static void bst_print_lvl(BST_NODE *node, int level, void (*callback)(BST_NODE *node))
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

void bst_lvl_order_traverse(BST_NODE *node, void (*callback)(BST_NODE *node))
{
    int height;

    height = bst_calculate_height(node);

    for (int i = 1; i <= height; i++)
    {
        bst_print_lvl(node, i, callback);
    }
}

void bst_lvl_order_traverse_queue(
    BST_NODE *node, void (*callback)(BST_NODE *node))
{
    Queue *q;

    q = create_queue();
    enqueue(q, node);

    while (queue_is_empty(q) == false)
    {
        BST_NODE *current = (BST_NODE *)dequeue(q);

        callback(current);

        if (current->left != NULL)
            enqueue(q, current->left);

        if (current->right != NULL)
            enqueue(q, current->right);
    }

    free(q);
}

void bst_in_order_traversal(BST_NODE *node, void (*callback)(BST_NODE *node))
{
    if (node == NULL)
        return;

    bst_in_order_traversal(node->left, callback);
    callback(node);
    bst_in_order_traversal(node->right, callback);
}

void bst_find_predecessor_successor(
    BST_NODE *node, int target, BST_NODE **predecessor, BST_NODE **successor)
{
    if (node == NULL)
        return;

    if (node->value == target)
    {
        if (node->left != NULL)
        {
            BST_NODE *tmp = node->left;
            while (tmp->right != NULL)
                tmp = tmp->right;
            *predecessor = tmp;
        }
        if (node->right != NULL)
        {
            BST_NODE *tmp = node->right;
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

BST_NODE *bst_delete_node(BST_NODE **root, int target)
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
            BST_NODE *tmp = *root;
            *root = (*root)->right;
            free(tmp);
        }
        else if ((*root)->right == NULL)
        {
            BST_NODE *tmp = *root;
            *root = (*root)->left;
            free(tmp);
        }
        // Case 3: both childs exists
        else
        {
            BST_NODE *proc = NULL;
            BST_NODE *suc = NULL;

            bst_find_predecessor_successor(*root, target, &proc, &suc);

            (*root)->value = proc->value;
            bst_delete_node(&(*root)->left, proc->value);
        }
    }
    return *root;
}

void bst_free_tree(BST_NODE **node)
{
    if (*node != NULL)
    {
        bst_free_tree(&(*node)->left);
        bst_free_tree(&(*node)->right);
        free(*node);
        *node = NULL;
    }
}

/*
 ************************************************************
 *****************  BST Print Tree Helpers  *****************
 ************************************************************
 */
void *bst_get_child(void *node, bool is_left)
{
    return is_left ? ((BST_NODE *)node)->left : ((BST_NODE *)node)->right;
}

char *bst_get_value(void *node)
{
    char *result = malloc(3);
    if (result != NULL)
    {
        snprintf(result, 3, "%d", ((BST_NODE *)node)->value);
    }
    return result;
}

node_handler bst_handler = {
    .get_child = bst_get_child,
    .get_value = bst_get_value};

void bst_print_tree(BST_NODE *node)
{
    printf("\n");
    if (node != NULL)
        print_tree_recursive("", node, false, &bst_handler);
    else
        printf("[DEBUG] This BST Node is EMPTY\n");
    printf("\n");
}

void print_node_value(BST_NODE *node)
{
    printf("[%d] ", node->value);
}

void bst_main_test()
{

    BST_NODE *node = NULL;
    node = bst_create_tree(7);

    int values[] = {7, 5, 12, 3, 6, 9, 15, 1, 4, 8, 10, 17};
    int i = 0;
    while (i < (int)(sizeof(values) / sizeof(int)))
        bst_insert_node(&node, values[i++]);

    BST_NODE *last_branch;
    BST_NODE *trgt;

    trgt = bst_find(17, node);
    last_branch = bst_create_tree(13);
    trgt->left = last_branch;
    /*
          7
        /   \
       5     12
      / \    /  \
     3   6   9   15
    / \     / \   \
   1   4   8  10  17
                 /
                13
  └──────7
         ├──────5
         │      ├──────3
         │      │      ├──────1
         │      │      └──────4
         │      └──────6
         └──────12
                ├──────9
                │      ├──────8
                │      └──────10
                └──────15
                       └──────17
                              ├──────13
  */

    printf("+---------------------------------------------------------+\n");
    printf("+-------------------- Balanced Binary Tree----------------+\n");
    printf("+---------------------------------------------------------+\n");
    bst_print_tree(node);

    bst_delete_node(&node, 7); // The nood head will be 6

    bst_print_tree(node);

    bst_in_order_traversal(node, print_node_value);
    // output: [1] [3] [4] [5] [6] [7] [8] [9] [10] [12] [15] [13] [17]

    int targets[] = {1, 3, 5, 7, 8, 15, 17};
    i = 0;
    while (i < (int)(sizeof(targets) / sizeof(int)))
    {
        int target = targets[i];
        BST_NODE *proc = NULL;
        BST_NODE *suc = NULL;

        printf("\n+------- Target: [%d] --------+\n", target);
        bst_find_predecessor_successor(node, target, &proc, &suc);

        if (proc != NULL)
            printf("Predecessor of [%d] is [%d]\n", target, proc->value);

        if (suc != NULL)
            printf("Successor   of [%d] is [%d]\n", target, suc->value);

        i++;
    }
    bst_lvl_order_traverse_queue(node, print_node_value);
    /*
    Free the homies
    */
    bst_free_tree(&node);
}
