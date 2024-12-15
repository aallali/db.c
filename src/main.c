/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   main.c                                      _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/15 01:08:28 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

/*
Binary Search Tree:

        7
      /   \
     5     12
    / \    /  \
   3   6  9   15
  / \     / \   \
 1   4   8  10  17
               /
              13

Rules of a Binary Search Tree:
1. Each node can have 0, 1, or 2 children.
2. For each node, left <= node <= right.
*/
 
int main()
{
    btree *root_node = NULL;

    bt_insert_node(&root_node, 7);

    bt_insert_node(&root_node, 5);
    bt_insert_node(&root_node, 12);

    bt_insert_node(&root_node, 3);
    bt_insert_node(&root_node, 6);
    bt_insert_node(&root_node, 9);
    bt_insert_node(&root_node, 15);

    bt_insert_node(&root_node, 1);
    bt_insert_node(&root_node, 4);
    bt_insert_node(&root_node, 8);
    bt_insert_node(&root_node, 10);
    bt_insert_node(&root_node, 17);

    btree *last_branch;
    bt_insert_node(&last_branch, 13);
    btree *trgt = bt_find(17, root_node);
    trgt->left = last_branch;
    print_tree(root_node);
 

    /*
            7
          /   \
         5     12
        / \    /  \
       3   6  9   15
      / \     / \   \
     1   4   8  10  17
                   /
                  13
    */
    printf("Height of first tree is [%d]\n", bt_calculate_height(root_node));
    printf("------------------------ One Side Tree------------------\n");
    btree *one_sided = NULL;

    bt_insert_node(&one_sided, 1);
    bt_insert_node(&one_sided, 2);
    bt_insert_node(&one_sided, 3);
    bt_insert_node(&one_sided, 4);
/*
             1
              \
               2
                \
                 3
                  \
                   4
*/
    print_tree(one_sided);
/*
------------------------ One Side Tree------------------
value: [1]
left:
       ---<empty>---
right:
       value: [2]
       left:
              ---<empty>---
       right:
              value: [3]
              left:
                     ---<empty>---
              right:
                     value: [4]
                     left:
                            ---<empty>---
                     right:
                            ---<empty>---
*/


    printf("Height of second tree is [%d]\n", bt_calculate_height(one_sided));

    return 0;
}
 