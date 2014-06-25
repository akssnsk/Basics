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

void XmlAlgorithmRun()
{
    std::vector<std::vector<int>> startData = 
    {
        /* 0 */ { 10, 20, 30, 40 },
        /* 1 */ { 11, 21, 31, 41 },
        /* 2 */ { 12, 22, 32, 42 }
    };

    int i = 0;
    XmlNodeInt *root = nullptr;

    // Creating
    for (auto &v : startData)
    {
        XmlNodeInt *node = new XmlNodeInt(i++);
        if (root == nullptr)
        {
            root = node;
        }
        else
        {
            root->AddSibling(node);
        }

        for (auto &n : v)
        {
            node->AddChild(n);
        }
    }

    // Detaching
    XmlNodeInt *detachBranch = root->pSibling; // 1
    XmlNodeInt *detachNode = detachBranch->pChild->pSibling; // 21

    // Clean outgoing links
    detachBranch->DetachChild(detachNode);
    detachNode->pChild = nullptr;
    detachNode->pSibling = nullptr;
    
    // Attach one more time
    XmlNodeInt *attachBranch = root->pSibling;
    while (attachBranch->pSibling != nullptr)
    {
        attachBranch = attachBranch->pSibling;
    }

    attachBranch->AddChild(detachNode);

    root->DeleteSubtree();
    delete root;
    root = nullptr;



    int zz = 2 + 2;
    return;


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
