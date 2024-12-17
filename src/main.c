/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   main.c                                      _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/17 16:53:27 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void print_node(btree *node)
{
  printf("[%d] ", node->value);
}

int main()
{
  btree *node = NULL;
  node = bt_create_tree(7);

  int values[] = {7, 5, 12, 3, 6, 9, 15, 1, 4, 8, 10, 17};
  int i = 0;
  while (i < (int)(sizeof(values) / sizeof(int)))
    bt_insert_node(&node, values[i++]);

  btree *last_branch;
  btree *trgt;

  trgt = bt_find(17, node);
  last_branch = bt_create_tree(13);
  trgt->left = last_branch;
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

  bt_delete_node(&node, 7); // [WARNING] Two-child deletion not yet implemented

  print_tree(node);

  bt_in_order_traversal(node, print_node);
  // output: [1] [3] [4] [5] [6] [7] [8] [9] [10] [12] [15] [13] [17]

  int targets[] = {1, 3, 5, 7, 8, 15, 17};
  i = 0;
  while (i < (int)(sizeof(targets) / sizeof(int)))
  {
    int target = targets[i];
    btree *proc = NULL;
    btree *suc = NULL;

    printf("\n+------- Target: [%d] --------+\n", target);
    bt_find_predecessor_successor(node, target, &proc, &suc);

    if (proc != NULL)
      printf("Predecessor of [%d] is [%d]\n", target, proc->value);

    if (suc != NULL)
      printf("Successor   of [%d] is [%d]\n", target, suc->value);

    i++;
  }
  /*
  Free the homies
  */
  bt_free_tree(&node);
  return 0;
}
