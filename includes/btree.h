/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   btree.h                                     _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/16 04:00:13 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct btree
{
    int value;
    struct btree *left;
    struct btree *right;
} btree;

void print_n_tabs(int n);

void print_tree(btree *node);

btree *bt_create_tree(int value);

btree *bt_find(int target, btree *startNode);

bool  bt_insert_node(btree **nodePtr, int v);

int bt_calculate_height(btree *node);

void bt_lvl_order_traverse(btree *node, void (*callback)(btree *node));

void bt_delete_node(btree **node, int target);

#endif // BTREE_H