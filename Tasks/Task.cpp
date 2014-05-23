// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <time.h>

#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <random>
#include <deque>
#include <unordered_map>

typedef std::vector<std::vector<int>> SlnType;

//int Knapsack(int W, int wt[], int val[], int n)
//{
//    if (n == 0)
//        return 0;
//
//    if (wt[n - 1] > W)
//        return Knapsack(W, wt, val, n - 1);
//
//    // Return the maximum of two cases: (1) nth item included (2) not included
//    else return std::max(
//        val[n - 1] + Knapsack(W - wt[n - 1], wt, val, n - 1),
//        Knapsack(W, wt, val, n - 1)
//        );
//}

int Partition(std::vector<int> &ar, size_t l, size_t r)
{
    int pivotValue = ar[l];

    size_t i = l;
    size_t j = r;

    while (i <= j)
    {
        while (ar[i] < pivotValue && i < r) i++;
        while (ar[j] > pivotValue && j > 0) j--;

        if (i <= j)
        {
            std::swap(ar[i], ar[j]);
            if (i<r) i++; 
            if (j>0) j--;
        }
    }

    return i;
}

void QuickSortHelper(std::vector<int> &ar, size_t l, size_t r)
{
    if (ar.size() < 1)
        return;

    if (l == r)
        return;

    size_t pIdx = Partition(ar, l, r);

    if (l < pIdx)
        QuickSortHelper(ar, l, pIdx-1);

    if (pIdx < r)
        QuickSortHelper(ar, pIdx, r);
}

void quickSort(std::vector<int> &ar, int ar_size)
{
    return QuickSortHelper(ar, 0, ar.size() - 1);
}



SlnType::value_type FindDecentNum(int length)
{
    SlnType::value_type retValue;
    if (length < 3)
        return retValue;

    int mod3 = length % 3;
    if (mod3 == 0)
    {
        retValue.resize(length);
        std::fill(retValue.begin(), retValue.end(), 5);
        return retValue;
    }

    int numThree = length % 5;              // 1
    int numFive = length - numThree;        // 10

    while (!(numFive % 3 == 0 && numThree % 5 == 0))
    {
        numFive -= 1;                    // 9 8 7 6
        numThree = (length - numFive);   // 2 3 4 5
    }

    if (numFive == 0 && numThree % 5 != 0)
        return retValue;

    retValue.resize(length);
    std::fill(retValue.begin(), retValue.begin()+numFive, 5);
    std::fill(retValue.begin()+numFive, retValue.end(), 3);
    
    return retValue;
}

int Sherlock()
{
    int numTestCases = 1;

    std::cin >> numTestCases;

    if (numTestCases < 1)
        return 0;

    std::vector<int> cases(numTestCases);

    for (int i = 0; i < numTestCases; i++)
    {
        std::cin >> cases[i];
    }

    SlnType solutions(numTestCases);

    for (int i = 0; i < numTestCases; i++)
    {
        solutions[i] = FindDecentNum(cases[i]);
    }

    for (int i = 0; i < numTestCases; i++)
    {
        if (solutions[i].size() == 0)
        {
            std::cout << -1;
        }
        else
        {
            for (auto n : solutions[i]) std::cout << n;
        }

        std::cout << std::endl;
    }

    return 0;
}

int ChangeEndian()
{
    typedef union EndianConverter
    {
        long ll;
        char cc[4];
    } EndianConverter;

    long num;
    num = 0x12345678;

    EndianConverter ec;
    ec.ll = num;

    std::swap(ec.cc[0], ec.cc[3]);
    std::swap(ec.cc[1], ec.cc[2]);

    long num2 = ec.ll;

    return 0;
}

std::string RemoveDuplicates(std::string str)
{
    if (str.empty())
        return str;

    for (size_t i = 0; i < str.size(); i++)
    {
        char cc = str[i];

        if (cc == ' ')
            continue;

        for (size_t j = i+1; j < str.size(); j++)
        {
            if (str[j] == cc)
            {
                str[j] = ' ';
            }
        }

    }

    int nonSpaceIdx = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            std::swap(str[nonSpaceIdx], str[i]);
            nonSpaceIdx++;
        }
    }

    size_t iSpace = str.find(' ');
    if (iSpace >= str.size())
        return str;

    return str.substr(0, iSpace+1);
}

std::vector<int> PrepareVector(int length)
{
    std::vector<int> sortVect;

    srand((unsigned int)time(NULL));

    for (int ii = 0; ii < length; ii++)
    {
        int val = rand() % 100;
        sortVect.push_back(val);
    }

    //std::sort(sortVect.begin(), sortVect.end());
    quickSort(sortVect, sortVect.size());

    size_t shift_idx = rand() % length;
    while (shift_idx == 0)
    {
        shift_idx = rand() % length;
    }

    std::vector<int> retVect(sortVect.size());

    size_t i = 0;
    for (; i < shift_idx; i++)
    {
        retVect[i] = sortVect[sortVect.size() - shift_idx + i];
    }
    for (; i < sortVect.size(); i++)
    {
        retVect[i] = sortVect[i - shift_idx];
    }

    // Here there is rotated 
    return retVect;
}

// 2 
// 01234
// 40123
// 34012

// 12340
// 23401

void PrintDifferent(const std::vector<int> dataArr)
{
    std::map<int, int> dataMap;

    for (auto i : dataArr)
    {
        dataMap[i]++;
    }



}

bool IsAnagram(const std::string &str1, const std::string &str2)
{
    typedef std::unordered_map<char, size_t> HashType;

    // Test input
    if (str1.empty() && str2.empty())
        return true;

    HashType hash1; // d - 1, e -1, .. r-1
    HashType hash2; // d-1...

    // Count chars
    for (auto c1 : str1) // -> iterating along the stream
    {
        if (c1 != ' ') // -> add more chars to ignore
            hash1[c1]++;
    }

    for (auto c2 : str2) // -> stream too
    {
        if (c2 != ' ')
            hash2[c2]++;
    }

    // Compare the results
    if (hash1.size() != hash2.size())
        return false;

    HashType::iterator i1 = hash1.begin();
    HashType::iterator i2 = hash2.begin();
    for (; i1 != std::end(hash1); ++i1, ++i2)
    {
        if (i1->second != i2->second)
            return false;
    }

    return true;
}


size_t BinSearch(const std::vector<int> &searchVector, size_t i, size_t j)
{
    if (searchVector.empty())
        return -1;

    if (i == j || i+1 == j)
        return i;

    size_t mid = i + (j-i)/2 ;
    size_t leftMinIdx = BinSearch(searchVector, i, mid);
    size_t rightMinIdx = BinSearch(searchVector, mid, j);

    int leftVal = searchVector[leftMinIdx];
    int rightVal = searchVector[rightMinIdx];

    return (leftVal <= rightVal) ? leftMinIdx : rightMinIdx;
}

int main()
{
    //Sherlock();

    //ChangeEndian();

    // Remove the duplicate characters in a string without using any additional bu$er
    //std::string sss = "this is my string with duplicates"; std::string sss = " ";
    //std::string str2 = RemoveDuplicates(sss);

    //auto vect = PrepareVector(25);
    //auto res = BinSearch(vect, 0, vect.size());

    //KnapsackProblem();

    bool bRet = IsAnagram("qwert  asdfg1", "asdfgqwert");

    //PrintDifferent(vect);

    return 0;
}

