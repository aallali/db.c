/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : main.c                                                         */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/19 15:42:56 by Abdellah A.                              */
/* ************************************************************************** */

#include "bst.h"

void print_node(bst *node)
{
  printf("[%d] ", node->value);
}

int main()
{
  bst *node = NULL;
  node = bst_create_tree(7);

  int values[] = {7, 5, 12, 3, 6, 9, 15, 1, 4, 8, 10, 17};
  int i = 0;
  while (i < (int)(sizeof(values) / sizeof(int)))
    bst_insert_node(&node, values[i++]);

  bst *last_branch;
  bst *trgt;

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
  print_tree(node);

  bst_delete_node(&node, 7); // The nood head will be 6

  print_tree(node);

  bst_in_order_traversal(node, print_node);
  // output: [1] [3] [4] [5] [6] [7] [8] [9] [10] [12] [15] [13] [17]

  int targets[] = {1, 3, 5, 7, 8, 15, 17};
  i = 0;
  while (i < (int)(sizeof(targets) / sizeof(int)))
  {
    int target = targets[i];
    bst *proc = NULL;
    bst *suc = NULL;

    printf("\n+------- Target: [%d] --------+\n", target);
    bst_find_predecessor_successor(node, target, &proc, &suc);

    if (proc != NULL)
      printf("Predecessor of [%d] is [%d]\n", target, proc->value);

    if (suc != NULL)
      printf("Successor   of [%d] is [%d]\n", target, suc->value);

    i++;
  }
  /*
  Free the homies
  */
  bst_free_tree(&node);
  return 0;
}
