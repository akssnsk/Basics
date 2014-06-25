#pragma once

#include <stdio.h>
#include <functional>
#include <stack>
#include <queue>

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

template <typename T>
struct XmlNode
{
    T data;
    XmlNode *pChild;
    XmlNode *pSibling;

    XmlNode(const T &param)
    {
        data = param;
        pChild = nullptr;
        pSibling = nullptr;
    }

    void AddSibling(T data)
    {
        return AddSibling(new XmlNode(data));
    }

    void AddSibling(XmlNode<T> *node)
    {
        if (pSibling == nullptr)
        {
            pSibling = node;
            return;
        }

        if (0)
        {
            // Iter
            XmlNode<T> *pTmp = pSibling;
            while (pTmp->pSibling != nullptr)
            {
                pTmp = pTmp->pSibling;
            }
            pTmp->pSibling = node;
        }
        else
        {
            // Recurse
            if (pSibling != nullptr)
                pSibling->AddSibling(node);
        }

        return;
    }

    void AddChild(T data)
    {
        return AddChild(new XmlNode(data));
    }

    void AddChild(XmlNode<T> *child)
    {
        if (pChild == nullptr)
        {
            pChild = child;
            return;
        }

        // add another sibling to child
        return pChild->AddSibling(child);
    }

    void DetachSibling(const XmlNode<T> *node)
    {
        if (pSibling == nullptr)
            return; // empty list

        if (pSibling == node)
        {
            pSibling = node->pSibling;
            return;
        }

        if (0)
        {
            XmlNode<T> *pTmp = pSibling;
            while (pTmp->pSibling != node && pTmp->pSibling != nullptr)
            {
                pTmp = pTmp->pSibling;
            }

            if (pTmp->pSibling == nullptr)
                return; // node not found

            // node found, it's pTmp->pSibling
            pTmp->pSibling = pTmp->pSibling->pSibling;

            return;
        }
        else
        {
            pSibling->DetachSibling(node);
        }
    }

    void DetachChild(const XmlNode<T> *node)
    {
        if (pChild == nullptr)
            return; // empty list

        pChild->DetachSibling(node);
    }

    void DeleteSubtree()
    {
        if (1)
        {
            std::stack<XmlNode<T> *> stack;

            if (pChild != nullptr)
            {
                stack.push(pChild);
                pChild = nullptr;
            }

            if (pSibling != nullptr)
            {
                stack.push(pSibling);
                pSibling = nullptr;
            }

            while (!stack.empty())
            {
                XmlNode<T> *pTmpNode = stack.top();
                stack.pop();

                if (pTmpNode->pChild != nullptr)
                { 
                    stack.push(pTmpNode->pChild);
                    pTmpNode->pChild = nullptr;
                }

                while (pTmpNode->pSibling != nullptr)
                {
                    XmlNode<T> *pTmpSibling = pTmpNode->pSibling;
                    pTmpNode->pSibling = pTmpNode->pSibling->pSibling;

                    pTmpSibling->pSibling = nullptr;
                    stack.push(pTmpSibling);
                }

                delete pTmpNode;
                pTmpNode = nullptr;
            }


        }
        else
        {
            while (pChild)
            {
                pChild->DeleteSubtree();
                delete pChild;
                pChild = nullptr;
            }

            while (pSibling)
            {
                XmlNode<T> *pTmpSibling = pSibling;
                pSibling = pSibling->pSibling;

                pTmpSibling->DeleteSubtree();
                delete pTmpSibling;
                pSibling = nullptr;
            }
        }
    }
};

typedef XmlNode<int> XmlNodeInt;

typedef TreeNode<int> TreeNodeInt;

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

void XmlAlgorithmRun();
void TreeAlgorithmRun();
