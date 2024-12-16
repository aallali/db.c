/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   main.c                                      _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/16 04:01:11 by aallali      -------- 1337.ma -------    */
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
  int values[] = {7, 5, 12, 3, 6, 9, 15, 1, 4, 8, 10, 17};
  int i = 0;
  while (i < (int)(sizeof(values) / sizeof(int)))
    bt_insert_node(&root_node, values[i++]);

  btree *last_branch;
  btree *trgt;

  bt_insert_node(&last_branch, 13);
  trgt = bt_find(17, root_node);
  trgt->left = last_branch;

  printf("-------------------- Multi Branch Tree----------------\n");
  printf("Height is [%d]\n", bt_calculate_height(root_node));

  bt_delete_node(&root_node, 10);
  bt_delete_node(&root_node, 17);
  bt_delete_node(&root_node, 9);

  print_tree(root_node);
  printf("Height after deleteing some bottom nodes is [%d]\n", bt_calculate_height(root_node));

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

  printf("Height is [%d]\n", bt_calculate_height(one_sided));

  return 0;
}
