/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : helpers.c                                                      */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/20 15:16:37 by Abdellah A.                              */
/*   Updated: 2024/12/21 14:44:18 by Abdellah A.                              */
/* ************************************************************************** */

#include <helpers.h>
#include <bst.h>
#include <avl.h>

void print_n_tabs(int n)
{
    for (int i = 0; i < n; i++)
        printf("    ");
}

void print_tree_recursive(char *prefix, void *node,
                          bool is_left, node_handler *handler)
{
    if (node == NULL)
        return;

    char *node_value_formatted = handler->get_value(node);
    printf("%s", prefix);
    printf("%s", is_left ? "├──────" : "└──────");
    printf("%s\n", node_value_formatted);
    free(node_value_formatted);

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
