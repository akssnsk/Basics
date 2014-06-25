// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

#include <functional>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>

#include <time.h>
#include <stdlib.h>

using namespace std;


#include "List.h"
#include "Tree.h"


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


int main(int argc, char* argv[])
{
    int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
    tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF;
    tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpDbgFlag);


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


    ListsAlgorithmRun(); // has memory leaks

    printf("\n");
    printf("\n");

    XmlAlgorithmRun();
    TreeAlgorithmRun(); // has memory leaks

#if 1
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

    std::sort(printVector.begin(), printVector.end());
    bool bRes = areSame(printVector, root);
#endif 

    PrintParenthesis(3);

    return 0;
}



