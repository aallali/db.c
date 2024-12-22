/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : avl.c                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 02:09:52 by Abdellah A.                              */
/*   Updated: 2024/12/21 00:18:49 by Abdellah A.                              */
/* ************************************************************************** */

/*

The AVL tree is named after its inventors, Georgy Adelson-Velsky and Evgenii
Landis, who published it in their 1962 paper “An algorithm for the organization
of information”.

An AVL tree defined as a self-balancing Binary Search Tree (BST) where the
difference between heights of left and right subtrees for any node cannot be
more than one.

*/

#include "avl.h"
#include "helpers.h"

AVL_NODE *avl_create_node(int value)
{
    AVL_NODE *node = (AVL_NODE *)malloc(sizeof(AVL_NODE));
    node->value = value;
    node->height = 0;
    node->left = node->right = NULL;
    return node;
}

AVL_NODE *avl_insert_node(AVL_NODE **root, int value)
{
    if (*root == NULL)
    {
        *root = avl_create_node(value);
        return *root;
    }
    if ((*root)->value < value)
    {
        return avl_insert_node(&(*root)->right, value);
    }
    else if ((*root)->value > value)
    {
        return avl_insert_node(&(*root)->left, value);
    }
    else
    {
        // Duplicate values not allowed in AVL tree.
        return *root;
    }
int avl_get_balance(AVL_NODE *node)
{
    if (node == NULL)
        return 0;
    return HEIGHT_OR_ZERO(node->left) - HEIGHT_OR_ZERO(node->right);
}

int avl_height(AVL_NODE *node)
{
    if (node == NULL)
        return 0;

    int left_h = avl_height(node->left);
    int right_h = avl_height(node->right);

    if (left_h > right_h)
        return left_h + 1;
    else
        return right_h + 1;
}

void avl_free_tree(AVL_NODE *node)
{
    if (node == NULL)
        return;

    avl_free_tree(node->right);
    avl_free_tree(node->left);
    free(node);
    node = NULL;
}

AVL_NODE *avl_rotation_right(AVL_NODE *y)
{
    /*
       y
      / \
     x   yr  (yr == y right)
      \
       z
    rotated to
       x
      /
     z
      \
       y
    */
    AVL_NODE *x = y->left;
    AVL_NODE *z = x->right;

    x->right = y;
    y->left = z;

    y->height = MAX(HEIGHT_OR_ZERO(y->left),
                    HEIGHT_OR_ZERO(y->right)) +
                1;
    x->height = MAX(HEIGHT_OR_ZERO(x->left),
                    HEIGHT_OR_ZERO(x->right)) +
                1;

    return x;
}

AVL_NODE *avl_rotation_left(AVL_NODE *x)
{
    /*
       x
        \
         y
        /
       z
    rotated to
       y
        \
         z
        /
       x
    */
    AVL_NODE *y = x->right;
    AVL_NODE *z = y->left;

    // Perform rotation
    y->left = x;
    x->right = z;

    y->height = MAX(HEIGHT_OR_ZERO(y->left),
                    HEIGHT_OR_ZERO(y->right)) +
                1;
    x->height = MAX(HEIGHT_OR_ZERO(x->left),
                    HEIGHT_OR_ZERO(x->right)) +
                1;

    return y;
}

/*
 ************************************************************
 *****************  AVL Print Tree Helpers  *****************
 ************************************************************
 */
void *avl_get_child(void *node, bool is_left)
{
    return is_left ? ((AVL_NODE *)node)->left : ((AVL_NODE *)node)->right;
}

char *avl_get_value(void *node)
{
    char *result = malloc(20); // Allocate enough space for the formatted string
    if (result != NULL)
    {
        snprintf(result, 20, "%d.............h:%d",
                 ((AVL_NODE *)node)->value,
                 ((AVL_NODE *)node)->height);
    }
    return result;
}

node_handler avl_handler = {
    .get_child = avl_get_child,
    .get_value = avl_get_value};

void avl_print_tree(AVL_NODE *node)
{
    printf("\n");
    if (node != NULL)
        print_tree_recursive("", node, false, &avl_handler);
    else
        printf("[DEBUG] This AVL Node is EMPTY\n");
    printf("\n");
}

/*
 * Example of an AVL Tree Node:
 *
 *         20 (Height = 2)
 *        /  \
 *       10  30 (Height = 1)
 *      /  \
 *     5   15
 *
 * Key Details:
 * - Node "20" is the root with height 2.
 * - Node "10" has a height of 1 and is balanced.
 * - Node "30" is a leaf node with height 1.
 * - Left subtree: 10 → 5, 15 (balanced).
 * - Right subtree: 30 (no children).
 */

void avl_main_test()
{
    AVL_NODE *node = avl_create_node(20);
    node->right = avl_create_node(30);
    node->left = avl_create_node(10);
    node->left->left = avl_create_node(5);
    node->left->right = avl_create_node(15);

    avl_insert_node(&node, 1);
    avl_insert_node(&node, 2);
    avl_insert_node(&node, 3);
    avl_insert_node(&node, 3);
    avl_insert_node(&node, 4);

    printf("Height of AVL tree is : %d", avl_height(node));
    avl_print_tree(node);
    /*
    Free My Homie (AVL lives matter)
    */
    avl_free_tree(node);
}
