// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <functional>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>

#include <time.h>
#include <stdlib.h>

using namespace std;


class MyClass {
    virtual void a() = 0;
};

class MyClass2 : public MyClass {
    void a(){}
};

// template definition
template< class T >
void f(const T& value)
{
    cout << "DEFAULT" << endl;
};

// specialization for MyClass
template<>
void f(const MyClass & value)
{
    cout << "MyClass" << endl;
};

// specialization for vector of MyClass
template<>
void f(const std::vector<MyClass> & v)
{
    cout << "vector" << endl;
}



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
void PrintValue(const TreeNode<T> *root)
{
    printf("0x%x", root->data);
}

template<>
void PrintValue(const TreeNode<int> *root)
{
    printf("%2d ", root->data);
}


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

// Test if sorted array and BST have all the same values
template<typename T>
bool areSameHelper(const std::vector<int> &array, const TreeNode<T> *node, int &ctr)
{
    // TODO: Check for empty node
    bool  bRet = true;

    // Go left   
    if (node->pLeft != nullptr)
        bRet = areSameHelper(array, node->pLeft, ctr);

    if (bRet == false)
        return bRet;

    // Process current node
    if (ctr >= (int)array.size())
        return false;

    bRet = (array[ctr] == node->data); ++ctr;

    // Go right    
    if (node->pRight != nullptr)
        bRet = areSameHelper(array, node->pRight, ctr);

    return bRet;
}

template<typename T>
bool areSame(const std::vector<int> &array, const TreeNode<T> *root)
{
    // Empty cases
    if (root == nullptr && array.size() == 0)
        return true;

    if ((root == nullptr && !array.empty()) || (root != nullptr && array.empty()))
        return false;

    int cc = 0;
    return areSameHelper(array, root, cc);
}


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

typedef TreeNode<int> TreeNodeInt;
typedef ListNode<int> ListNodeInt;

ListNodeInt *Reverse(ListNodeInt *top)
{
    if (top == nullptr)
        return top; // Empty list

    if (top->pNext == nullptr)
        return top; // One element list
        
    // Init
    ListNodeInt *p1 = top;
    ListNodeInt *p2 = top->pNext;
    p1->pNext = nullptr;
    
    // Run reversing
    while (p2 != nullptr)
    {
        ListNodeInt *t = p2->pNext;

        p2->pNext = p1;

        p1 = p2;
        p2 = t;
    }

    top = p1;
    return top;
}

ListNodeInt *ReverseRecursively(ListNodeInt *currNode)
{
    if (currNode == nullptr)
        return currNode; // Empty list

    if (currNode->pNext == nullptr)
        return currNode; // One element list

    ListNodeInt *rest = currNode->pNext;
    currNode->pNext = nullptr;

    ListNodeInt *newTop = ReverseRecursively(rest);

    rest->pNext = currNode;

    return newTop;
}


std::string RotateWords(const std::string &strInput)
{
    std::string strRet(strInput);

    size_t i1 = 0;

    // Find the end of the ith word
    while (i1 < strRet.size())
    {
        // Find the beginning of the ith word
        while (strRet[i1] == ' ' && i1 < strRet.size())
        {
            i1++;
        }

        // Find the beginning of the (i+1)th word (or EOL)
        size_t i2 = i1 + 1;
        while (strRet[i2] != ' ' && i2 < strRet.size())
        {
            i2++;
        }

        int length = (i2 - i1);
        for (int i = 0; i < length / 2; ++i)
        {
            std::swap(strRet[i1 + i], strRet[i2 - i - 1]);
        }
        i1 += (length + 1);
        i2 = i1 + 1;
    }

    for (size_t i = 0; i < strRet.size() / 2; i++)
    {
        std::swap(strRet[i], strRet[strRet.size() - i - 1]);
    }

    return strRet;
}

std::pair<int, int> TheLongestIncSeq(const std::vector<int> inputArr)
{
    if (inputArr.empty() || inputArr.size() == 1)
        return std::make_pair(0, inputArr.size());

    int maxSum = inputArr[0];
    auto retIdxs = std::make_pair(0, 0);

    for (size_t i = 0; i < inputArr.size(); i++)
    {
        for (size_t j = i; j < inputArr.size(); j++)
        {
            int maxSumTmp = 0;
            for (size_t k = i; k < j; k++)
            {
                maxSumTmp += inputArr[k];
                if (maxSumTmp > maxSum)
                {
                    maxSum = maxSumTmp;
                    retIdxs = std::make_pair(i, j);
                }
            }
        }
    }

    return retIdxs;
}

// 0(0):
// 1(1):  ()
// 2(2):  ()(), 
//        (())
// 3(5):  ()()(), 
//        (())(), ()(()), 
//        (()())
//        ((()))
// 4(14): ()()()(),
//        (())()(), ()(())(), ()()(()), 
//        ((()))(), (())(()), ()((())), 
//        ((())()), (()(())), (()())(), ()(()()), (()()()), ((()()))
//        (((())))

void PrintParenthesisHelper(int l, int r, std::string &str)
{
    if (l < 0 || r < 0)
        return;

    if (l == 0 && r == 0)
    {
        printf("%s\n", str.c_str());
        return;
    }

    if (l > 0)
        PrintParenthesisHelper(l-1, r+1, str + "(");
    
    if (r > 0)
        PrintParenthesisHelper(l, r-1, str + ")");

    return;
}

void PrintParenthesis(int n)
{
    std::string s = "";
    return PrintParenthesisHelper(n, 0, s);
}


int _tmain(int argc, _TCHAR* argv[])
{
    f(2);

    MyClass2 e;
    f<MyClass>(e);

    vector<MyClass> vM;
    f(vM);


    std::string s1("12345 67890 my string");
    int iS1 = s1.size();

    std::string strRes1 = RotateWords(s1);

    std::vector<int> tmpVector(10);
    size_t sss = tmpVector.size();

    int nElem = 10;

    srand((unsigned int)time(NULL));

    std::vector<int> printVector;

    for (int i = 0; i < nElem; i++)
    {
        int num = rand() % 100;

        if (rand() % 2)
            num *= -1;

        printVector.push_back(num);
    }

    auto idxs = TheLongestIncSeq(printVector);


    ListNodeInt *top = nullptr;

    for (int num : printVector)
    {
        ListNodeInt *n = new ListNodeInt(num);

        if (top == nullptr)
        {
            top = n;
            continue;
        }
        else
        {
            n->pNext = top;
            top = n;
        }
    }

    ListNodeInt *t = top;

    while (t != nullptr)
    {
        printf("%d ", t->data);
        t = t->pNext;
    }

    printf("\n");

    top = Reverse(top);
    t = top;
 
    while (t != nullptr)
    {
        printf("%d ", t->data);
        t = t->pNext;
    }

    printf("\n");

    top = ReverseRecursively(top);
    t = top;

    while (t != nullptr)
    {
        printf("%d ", t->data);
        t = t->pNext;
    }

    printf("\n");
    printf("\n");

    TreeNodeInt *root = nullptr;

    printVector = {50, 25, 75, 12, 37, 63, 87, 6, 18, 31, 42, 58, 69, 81, 93};

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

    std::sort(printVector.begin(), printVector.end());
    bool bRes = areSame(printVector, root);

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

    PrintParenthesis(3);

    return 0;
}
