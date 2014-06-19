#pragma once

#include <stdio.h>
#include <functional>

template <typename T>
struct TreeNode
{
    T data;
    TreeNode *pLeft;
    TreeNode *pRight;

    TreeNode(const T &param)
    {
        data = param;
        pLeft = nullptr;
        pRight = nullptr;
    }

};

template<typename T>
void Insert(TreeNode<T> *root, TreeNode<T> *node)
{
    if (root == nullptr)
    {
        // Empty tree
        return;
    }

    TreeNode<T> *nextNode = (node->data > root->data) ?
        root->pRight :
        root->pLeft;
    if (nextNode != nullptr)
    {
        return Insert(nextNode, node);
    }

    if (node->data > root->data)
    {
        root->pRight = node;
    }
    else
    {
        root->pLeft = node;
    }

    return;
}

template<typename T>
void PrintValue(const TreeNode<T> *root);

template<>
void PrintValue(const TreeNode<int> *root);

template<typename T>
void PreTraverse(const TreeNode<T> *node, std::function<void(const TreeNode<T> *)> Func)
{
    if (node == nullptr)
        return;

    Func(node);

    PreTraverse(node->pLeft, Func);

    PreTraverse(node->pRight, Func);
}

template<typename T>
void TraverseLeftSidePreOrder(const TreeNode<T> *node, const std::function<void(const TreeNode<T> *)> &Func)
{
    if (node == nullptr)
        return;

    if (node->pLeft != nullptr || node->pRight != nullptr)
    {
        Func(node);
    }

    TraverseLeftSidePreOrder(node->pLeft, Func);
}

template<typename T>
void TraverseRightSidePostOrder(const TreeNode<T> *node, std::function<void(const TreeNode<T> *)> Func)
{
    if (node == nullptr)
        return;

    TraverseRightSidePostOrder(node->pRight, Func);

    if (node->pLeft != nullptr || node->pRight != nullptr)
    {
        Func(node);
    }
}

template<typename T>
void TraverseLeavesLeftToRight(const TreeNode<T> *node, std::function<void(const TreeNode<T> *)> Func)
{
    if (node == nullptr)
        return;

    if (node->pLeft == nullptr && node->pRight == nullptr)
    {
        Func(node);
    }

    TraverseLeavesLeftToRight(node->pLeft, Func);

    TraverseLeavesLeftToRight(node->pRight, Func);
}

template<typename T>
void TraverseAround(const TreeNode<T> *node, std::function<void(const TreeNode<T> *)> Func)
{
    TraverseLeftSidePreOrder(node, Func);

    TraverseLeavesLeftToRight(node, Func);

    TraverseRightSidePostOrder(node, Func);
}

template<typename T, typename U>
void TraverseDFS(const TreeNode<T> *node, const std::function<void(const TreeNode<U> *)> &Func)
{
    return;
}

template<typename T, typename U>
void TraverseBFS(const TreeNode<T> *node, const std::function<void(const TreeNode<U> *)> &Func)
{
    return;
}

template<typename U>
void TraverseDFS(const TreeNode<int> *node, const std::function<void(const TreeNode<U> *)> &Func)
{
    if (node == nullptr)
        return;

    std::stack<const TreeNode<int> *> stack;
    stack.push(node);

    while (!stack.empty())
    {
        const TreeNode<int> *nodeCurr = stack.top();
        stack.pop();

        Func(nodeCurr);

        if (nodeCurr->pRight != nullptr)
        {
            stack.push(nodeCurr->pRight);
        }

        if (nodeCurr->pLeft != nullptr)
        {
            stack.push(nodeCurr->pLeft);
        }
    }
}

template<typename U>
void TraverseBFS(const TreeNode<int> *node, const std::function<void(const TreeNode<U> *)> &Func)
{
    if (node == nullptr)
        return;

    std::queue<const TreeNode<int> *> queue;
    queue.push(node);

    while (!queue.empty())
    {
        const TreeNode<int> *nodeCurr = queue.front();
        queue.pop();

        Func(nodeCurr);

        if (nodeCurr->pLeft != nullptr)
        {
            queue.push(nodeCurr->pLeft);
        }

        if (nodeCurr->pRight != nullptr)
        {
            queue.push(nodeCurr->pRight);
        }
    }
}
