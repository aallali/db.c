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
    treeNode *rootNode = NULL;

    insert_node(&rootNode, 7);

    insert_node(&rootNode, 5);
    insert_node(&rootNode, 12);

    insert_node(&rootNode, 3);
    insert_node(&rootNode, 6);
    insert_node(&rootNode, 9);
    insert_node(&rootNode, 15);

    insert_node(&rootNode, 1);
    insert_node(&rootNode, 4);
    insert_node(&rootNode, 8);
    insert_node(&rootNode, 10);
    insert_node(&rootNode, 17);

    treeNode *lastOne;
    insert_node(&lastOne, 13);
    treeNode *trgt = find(17, rootNode);
    trgt->left = lastOne;
    print_tree(rootNode, 0);
 

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
    printf("Height of first tree is [%d]\n", calculate_height(rootNode));
    printf("------------------------ One Side Tree------------------\n");
    treeNode *oneSide = NULL;

    insert_node(&oneSide, 1);
    insert_node(&oneSide, 2);
    insert_node(&oneSide, 3);
    insert_node(&oneSide, 4);
    // print_tree(oneSide, 0);
    /*
             1
              \
               2
                \
                 3
                  \
                   4
    */

    printf("Height of second tree is [%d]\n", calculate_height(oneSide));

   
    return 0;
}
 