/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : avl.c                                                          */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 02:09:52 by Abdellah A.                              */
/*   Updated: 2024/12/31 01:09:11 by Abdellah A.                              */
/* ************************************************************************** */

/*

The AVL tree is named after its inventors, Georgy Adelson-Velsky and Evgenii
Landis, who published it in their 1962 paper “An algorithm for the organization
of information”.

An AVL tree defined as a self-balancing Binary Search Tree (BST) where the
difference between heights of left and right subtrees for any node cannot be
more than one.

Example:
Original Tree: 10->20->30->40->50->25
AVL Tree:
    30 (Height = 2)
   /  \
  20  40 (Height = 1)
 /  \   \
10  25  50
*/

#include "avl.h"
#include "helpers.h"
#include "queue.h"

AVL_NODE *avl_create_node(int value)
{
    AVL_NODE *node = (AVL_NODE *)malloc(sizeof(AVL_NODE));
    node->value = value;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

static void avl_update_height(AVL_NODE **node)
{
    (*node)->height = 1 + MAX(
                              HEIGHT_OR_ZERO((*node)->right),
                              HEIGHT_OR_ZERO((*node)->left));
}
/**
 * @brief Inserts a node with the given value into the AVL tree.
 *
 * This function inserts a new node with the specified value into the AVL tree
 * while maintaining the AVL tree property (balance factor of each node is -1,0, or 1).
 * It performs necessary rotations to ensure the tree remains balanced after insertion.
 *
 * The rotations are as follows:
 *
 * - Left Left Case:
 *      - A single right rotation is performed.
 *      - e.g:
 *   Insert 1 into the tree:
 *           3
 *          /
 *         2
 *        /
 *       1
 *   rotation:
 *           2
 *          / \
 *         1   3
 *
 * - Right Right Case:
 *      - A single left rotation is performed.
 *      - e.g:
 *   Insert 3 into the tree:
 *       1
 *        \
 *         2
 *          \
 *           3
 *   rotation:
 *           2
 *          / \
 *         1   3
 *
 * - Left Right Case:
 *      - A left rotation is performed on the left child,
 *      - followed by a right rotation on the root.
 *      - e.g:
 *   Insert 2 into the tree:
 *           3
 *          /
 *         1
 *          \
 *           2
 *   rotation:
 *           2
 *          / \
 *         1   3
 *
 * - Right Left Case:
 *      - A right rotation is performed on the right child,
 *      - followed by a left rotation on the root.
 *      - e.g:
 *       Insert 2 into the tree:
 *       1
 *        \
 *         3
 *        /
 *       2
 * After right rotation on right child:
 *     1
 *      \
 *       2
 *        \
 *         3
 * After left rotation on root:
 *         2
 *        / \
 *       1   3
 *
 * @param root The root node of the AVL tree.
 * @param value The value to be inserted into the AVL tree.
 * @return AVL_NODE* The new root of the AVL tree after insertion.
 */
AVL_NODE *avl_insert_node(AVL_NODE *root, int value)
{
    if (root == NULL)
    {
        root = avl_create_node(value);
        return root;
    }
    if (value < (root)->value)
    {
        root->left = avl_insert_node((root)->left, value);
    }
    else if (value > (root)->value)
    {
        root->right = avl_insert_node((root)->right, value);
    }
    else
    {
        // Duplicate values not allowed in AVL tree.
        return root;
    }

    avl_update_height(&root);
    int balance = avl_get_balance(root);

    // Left Left Case
    if (balance > 1 && value < (root)->left->value)
        return avl_rotation_right(root);

    // Right Right Case
    if (balance < -1 && value > (root)->right->value)
        return avl_rotation_left(root);

    // Left Right Case
    if (balance > 1 && value > (root)->left->value)
    {
        (root)->left = avl_rotation_left((root)->left);
        return avl_rotation_right(root);
    }

    // Right Left Case
    if (balance < -1 && value < (root)->right->value)
    {
        (root)->right = avl_rotation_right((root)->right);
        return avl_rotation_left(root);
    }
    return root;
}

void avl_find_predecessor_successor(
    AVL_NODE *node, int target, AVL_NODE **predecessor, AVL_NODE **successor)
{
    if (node == NULL)
        return;

    if (node->value == target)
    {
        if (node->left != NULL)
        {
            AVL_NODE *tmp = node->left;
            while (tmp->right != NULL)
                tmp = tmp->right;
            *predecessor = tmp;
        }
        if (node->right != NULL)
        {
            AVL_NODE *tmp = node->right;
            while (tmp->left != NULL)
                tmp = tmp->left;
            *successor = tmp;
        }
        return;
    }

    if (node->value > target)
    {
        *successor = node;
        avl_find_predecessor_successor(
            node->left, target, predecessor, successor);
    }
    else
    {
        *predecessor = node;
        avl_find_predecessor_successor(
            node->right, target, predecessor, successor);
    }
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

AVL_NODE *avl_find(AVL_NODE *node, int target)
{
    if (node == NULL)
        return NULL;

    if (target < node->value)
        return avl_find(node->left, target);

    if (target > node->value)
        return avl_find(node->right, target);

    return node;
}

void avl_lvlorder_traverse(AVL_NODE *node, void(callback)(AVL_NODE *node))
{
    Queue *q;

    q = create_queue();
    enqueue(q, node);

    while (queue_is_empty(q) == false)
    {
        AVL_NODE *current = (AVL_NODE *)dequeue(q);

        callback(current);
        if (current->left != NULL)
            enqueue(q, current->left);
        if (current->right != NULL)
            enqueue(q, current->right);
    }

    free(q);
}

void avl_inorder_traverse(AVL_NODE *node, void(callback)(AVL_NODE *node))
{
    if (node == NULL)
        return;

    avl_inorder_traverse(node->left, callback);
    callback(node);
    avl_inorder_traverse(node->right, callback);
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
 *         30 (Height = 2)
 *        /  \
 *       20  40 (Height = 1)
 *      /  \   \
 *     10  25  50
 */

static void print_node_value(AVL_NODE *node)
{
    printf(" %d |", node->value);
}

void avl_main_test()
{
    AVL_NODE *node;
    int target;
    AVL_NODE *found_node;

    node = avl_create_node(10);
    node = avl_insert_node(node, 20);
    node = avl_insert_node(node, 30);
    node = avl_insert_node(node, 40);
    node = avl_insert_node(node, 50);
    node = avl_insert_node(node, 25);

    avl_print_tree(node);

    printf("Height of AVL tree is : %d\n", avl_height(node));

    target = 55;
    found_node = avl_find(node, target);

    if (found_node != NULL)
        printf("Node with value %d found: %d\n", target, found_node->value);
    else
        printf("Node with value %d not found.\n", target);

    target = 30;
    AVL_NODE *proc = NULL;
    AVL_NODE *suc = NULL;

    printf("\n:-----Target: [%d] :-----:\n", target);
    avl_find_predecessor_successor(node, target, &proc, &suc);
    // print successor and predecessor
    if (proc != NULL)
        printf("Predecessor: %d\n", proc->value);
    if (suc != NULL)
        printf("Successor: %d\n", suc->value);

    printf("in order:    ");
    avl_inorder_traverse(node, print_node_value);
    // output: 10 | 20 | 25 | 40 | 50 |
    printf("\nlevel order: ");
    avl_lvlorder_traverse(node, print_node_value);
    // output: 25 | 20 | 40 | 10 | 50 |

    /*
    Free My Homie (AVL lives matter)
    */
    avl_free_tree(node);
}
