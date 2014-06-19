#pragma once

template <typename T>
struct ListNode
{
    T data;
    ListNode *pNext;

    ListNode(const T &param)
    {
        data = param;
        pNext = nullptr;
    }
};

template <typename T>
ListNode<T> *Reverse(ListNode<T> *front);

template <typename T>
ListNode<T> *ReverseRecursively(ListNode<T>  *front);

template <typename T>
ListNode<T> *Reverse(ListNode<T> *top)
{
    if (top == nullptr)
        return top; // Empty list

    if (top->pNext == nullptr)
        return top; // One element list

    // Init
    ListNode<T> *p1 = top;
    ListNode<T> *p2 = top->pNext;
    p1->pNext = nullptr;

    // Run reversing
    while (p2 != nullptr)
    {
        ListNode<T> *t = p2->pNext;

        p2->pNext = p1;

        p1 = p2;
        p2 = t;
    }

    top = p1;
    return top;
}

template <typename T>
ListNode<T> *ReverseRecursively(ListNode<T>  *currNode)
{
    if (currNode == nullptr)
        return currNode; // Empty list

    if (currNode->pNext == nullptr)
        return currNode; // One element list

    ListNode<T> *rest = currNode->pNext;
    currNode->pNext = nullptr;

    ListNode<T> *newTop = ReverseRecursively(rest);

    rest->pNext = currNode;

    return newTop;
}
