/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : helpers.c                                                      */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 15:16:37 by Abdellah A.                              */
/*   Updated: 2024/12/21 00:12:52 by Abdellah A.                              */
/* ************************************************************************** */

#include <helpers.h>
#include <bst.h>
#include <avl.h>

typedef struct
{
    void *(*get_child)(void *node, bool is_left);
    int (*get_value)(void *node);
} node_handler;

void print_n_tabs(int n)
{
    for (int i = 0; i < n; i++)
        printf("    ");
}

static void print_tree_recursive(
    char *prefix,
    void *node,
    bool is_left,
    node_handler *handler)
{
    if (node == NULL)
        return;

    printf("%s", prefix);
    printf("%s", is_left ? "├──────" : "└──────");
    printf("%d\n", handler->get_value(node));

    char *new_prefix = malloc(strlen(prefix) + 9 + 1);

    strcpy(new_prefix, prefix);
    strcat(new_prefix, is_left ? "│      " : "       ");

    print_tree_recursive(
        new_prefix, handler->get_child(node, true), true, handler);
    print_tree_recursive(
        new_prefix, handler->get_child(node, false), false, handler);

    free(new_prefix);
    return;
}

/*
 ************************************************************
 *****************  BST Print Tree Helpers  *****************
 ************************************************************
 */
void *bst_get_child(void *node, bool is_left)
{
    return is_left ? ((BST_NODE  *)node)->left : ((BST_NODE  *)node)->right;
}

int bst_get_value(void *node)
{
    return ((BST_NODE  *)node)->value;
}

node_handler bst_handler = {
    .get_child = bst_get_child,
    .get_value = bst_get_value};

void bst_print_tree(BST_NODE  *node)
{
    printf("\n");
    if (node != NULL)
        print_tree_recursive("", node, false, &bst_handler);
    else
        printf("[DEBUG] This BST Node is EMPTY\n");
    printf("\n");
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

int avl_get_value(void *node)
{
    return ((BST_NODE  *)node)->value;
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
