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

void avl_free_tree(AVL_NODE *node)
{
    if (node == NULL)
        return;

    avl_free_tree(node->right);
    avl_free_tree(node->left);
    free(node);
    node = NULL;
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

    avl_print_tree(node);
    /*
    Free My Homie (AVL lives matter)
    */
    avl_free_tree(node);
}
