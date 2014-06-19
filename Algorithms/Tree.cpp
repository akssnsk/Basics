#include "Tree.h"


template<typename T>
void PrintValue(const TreeNode<T> *root)
{
    printf("0x%x", root->data);
}

template<>
void PrintValue(const TreeNode<int> *root)
{
    printf("%2d ", root->data);
}
