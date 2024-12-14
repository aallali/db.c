#include "btree.h"

void print_n_tabs(int n)
{
    for (int i = 0; i < n; i++)
        printf("       ");
}

void print_tree(treeNode *node, int level)
{
    if (node == NULL)
    {
        print_n_tabs(level);
        printf("---<empty>---\n");
        return;
    }
    print_n_tabs(level);
    printf("value-->[%d]\n", node->value);

    print_n_tabs(level);
    printf("left:\n");
    print_tree(node->left, level + 1);

    print_n_tabs(level);
    printf("right:\n");
    print_tree(node->right, level + 1);
    return;
}

treeNode *createTree(int value)
{
    treeNode *freshOne = (treeNode *)malloc(sizeof(treeNode));
    freshOne->value = value;
    freshOne->left = NULL;
    freshOne->right = NULL;
    return freshOne;
}

treeNode *find(int target, treeNode *startNode)
{
    if (startNode == NULL)
        return NULL;

    if (startNode->value < target)
        return find(target, startNode->right);

    if (startNode->value > target)
        return find(target, startNode->left);

    return startNode;
}

bool insert_node(treeNode **nodePtr, int v)
{
    treeNode *root = *nodePtr;

    if (root == NULL)
    {
        *nodePtr = createTree(v);
        return true;
    }

    if (v > root->value)
        return insert_node(&(root->right), v);
    if (v < root->value)
        return insert_node(&(root->left), v);

    return true;
}

int calculate_height(treeNode *node)
{
    if (node == NULL)
        return 0;

    int left_height = 0;
    int right_height = 0;

    left_height = calculate_height(node->left);
    right_height = calculate_height(node->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}