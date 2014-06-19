#include <vector>

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

void TreeAlgorithmRun()
{
    std::vector<int> printVector;
    printVector = { 50, 25, 75, 12, 37, 63, 87, 6, 18, 31, 42, 58, 69, 81, 93 };

    TreeNodeInt *root = nullptr;
    for (int num : printVector)
    {
        TreeNodeInt *node = new TreeNodeInt(num);
        if (root == nullptr)
        {
            root = node;
            continue;
        }

        Insert(root, node);
    }

    std::function<void(const TreeNodeInt *node)> func = [](const TreeNodeInt *node){PrintValue(node); };

    printf("TraverseAround: ");
    TraverseAround(root, func);
    printf("\n");

    printf("PreTraverse: ");
    PreTraverse(root, func);
    printf("\n");

    printf("TraverseDFS: ");
    TraverseDFS(root, func);
    printf("\n");

    printf("TraverseBFS: ");
    TraverseBFS(root, func);
    printf("\n");
}
