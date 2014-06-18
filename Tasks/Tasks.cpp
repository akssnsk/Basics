// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

#include "Tasks.h"

#include "CutTheTree.h"
#include "Bytes.h"

#include "Node.h"

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

        if (i <= j) // less or equal required to update indexes
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
    if (ar.size() < 2)
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

SlnType FindDecentNum(const int length)
{
    if (length < 3)
        return SlnType();

    SlnType retValue(length);
    int mod3 = length % 3;
    if (mod3 == 0)
    {
        std::fill_n(retValue.begin(), length, 5);
        return retValue;
    }

    int numThree = length % 5;              // 1
    int numFive = length - numThree;        // 10

    while (numFive > 0 && !(numFive % 3 == 0 && numThree % 5 == 0))
    {
        numFive -= 1;                    // 9 8 7 6
        numThree = (length - numFive);   // 2 3 4 5
    }

    if (numFive == 0 && numThree % 5 != 0)
        return SlnType();

    std::fill_n(retValue.begin(), numFive, 5);
    std::fill_n(retValue.begin() + numFive, numThree, 3);
    
    return retValue;
}

int Sherlock()
{
    int numTestCases = 0;

    std::cin >> numTestCases;
    std::cin.ignore();

    if (numTestCases < 1)
        return 0;

    std::vector<int> cases(numTestCases);
    for (int i = 0; i < numTestCases; i++)
    {
        std::cin >> cases[i];
        std::cin.ignore();
    }

    for (int i = 0; i < numTestCases; i++)
    {
        SlnType numRes = FindDecentNum(cases[i]);

        if (numRes.size() == 0)
        {
            std::cout << -1;
        }
        else
        {
            for (auto n : numRes) std::cout << n;
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

void Rotate(std::vector<int> &arr, size_t shift)
{
    if (arr.empty() || shift == 0 || shift == arr.size())
        return;

    if (shift > arr.size())
        shift %= arr.size();

    // description
    //reverse(first, last);
    //reverse(first, middle);
    //reverse(middle, last);

    // stl helpers
    //std::reverse(arr.begin(), arr.end());
    //std::reverse(arr.begin(), arr.begin() + shift);
    //std::reverse(arr.begin() + shift, arr.end());

    size_t nElems = arr.size();
    for (size_t i = 0; i < nElems/2; i++)
    {
        std::swap(arr[i], arr[nElems-i-1]);
    }

    for (size_t i1 = 0; i1 < shift/2; i1++)
    {
        std::swap(arr[i1], arr[shift-i1-1]);
    }

    for (size_t i2 = 0; i2 < (nElems - shift)/2; i2++)
    {
        std::swap(arr[shift + i2], arr[nElems-i2-1]);
    }

    return;
}

std::vector<int> PrepareVector(int length)
{
    srand((unsigned int)time(NULL));

    std::vector<int> sortVect(length);

    for (int ii = 0; ii < length; ii++)
    {
        int val = rand() % 100;
        sortVect.push_back(val);
    }

    //std::sort(sortVect.begin(), sortVect.end()); // or
    quickSort(sortVect, sortVect.size());

    size_t shift_idx = rand() % length;
    while (shift_idx == 0)
    {
        shift_idx = rand() % length;
    }

    //std::rotate(sortVect.begin(), sortVect.begin() + shift_idx, sortVect.end()); // or
    Rotate(sortVect, shift_idx);

    // Here there is rotated 
    return sortVect;
}

// 2 
// 01234
// 40123
// 34012

// 12340
// 23401

typedef std::unordered_map<char, size_t> HashType;
typedef std::pair<char, short> CharCounterT;
typedef std::vector<CharCounterT> CharAmtType;

int AnagramDifference(const std::string &str)
{
    if (str.size() % 2 != 0)
        return -1;

    if (str.empty())
        return -1;

    size_t ll = str.size();
    size_t mid = ll / 2;
    std::string strA = str.substr(0, mid);
    std::string strB = str.substr(mid, ll);

    CharAmtType hash1(26); // d - 1, e -1, .. r-1
    CharAmtType hash2(26); // d-1...

    // Count chars
    for (auto c1 : strA) 
    { 
        hash1[c1 - 'a'].first = c1;
        hash1[c1-'a'].second++; 
    }
    for (auto c2 : strB) { hash2[c2 - 'a'].first = c2; hash2[c2 - 'a'].second++; }

    //auto cmpFunc = [=](CharCounterT &ci1, CharCounterT &ci2)
    //{
    //    return !(ci1.second < ci2.second);
    //};

    //std::sort(hash1.begin(), hash1.end(), cmpFunc);
    //std::sort(hash2.begin(), hash2.end(), cmpFunc);

    int iRes = 0;
    for (size_t i = 0; i < hash1.size(); i++)
    {
        iRes += abs(hash1[i].second - hash2[i].second);
    }

    return iRes / 2;
}

void AnagramDifferenceStarter()
{
    int numTestCases = 1;
    std::cin >> numTestCases;

    if (numTestCases < 1)
        return;

    std::cin.ignore();

    std::vector<std::string> strVect(numTestCases);
    for (int i = 0; i < numTestCases; i++)
    {
        std::cin >> strVect[i];
    }

    for (auto &s : strVect)
    {
        int iRes = AnagramDifference(s);
        std::cout << iRes << std::endl;
    }

}

bool IsAnagram(const std::string &str1, const std::string &str2)
{
    // Test input
    if (str1.empty() && str2.empty())
        return true;

    HashType hash1; // d - 1, e -1, .. r-1
    HashType hash2; // d-1...

    // Count chars
    for (auto c1 : str1) 
    {
        if (c1 != ' ') // -> add more chars to ignore
            hash1[c1]++;
    }

    for (auto c2 : str2) 
    {
        if (c2 != ' ')
            hash2[c2]++;
    }

    // Compare the results
    if (hash1.size() != hash2.size())
        return false;

    
    HashType::iterator i1 = hash1.begin();
    for (; i1 != std::end(hash1); ++i1)
    {
        auto i2 = hash2.find(i1->first);
        if (i2 == hash2.end())
            return false;
        
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

int FindMedian2(const std::vector<int> &vInput, int minParam, int maxParam)
{
    std::vector<int> vInputCopy = vInput;

    // nth_element works in linear time
    std::nth_element(std::begin(vInputCopy), vInputCopy.begin() + vInputCopy.size() / 2, vInputCopy.end());
    return vInputCopy[vInput.size() / 2];
}

int FindMedian1(const std::vector<int> &vInput, int minParam, int maxParam)
{
    int kindAmount = maxParam - minParam + 1;

    std::vector<int> HashCounter(kindAmount);

    for (auto &i : vInput)
    {
        HashCounter[i-minParam]++;
    }

    // hash table iterators
    size_t i = 0; size_t j = 0;

    while (i < HashCounter.size() && HashCounter[i] == 0) i++;
    while (j < HashCounter.size() && HashCounter[HashCounter.size() - j - 1] == 0) j++;

    // source vector iterators
    size_t i2 = HashCounter[i]-1; i++;
    size_t j2 = HashCounter[HashCounter.size() - j - 1]; j++;

    size_t distance = std::max(i2, j2);
    while (distance < vInput.size()/2)
    {
        if (i2 < distance)
        {
            while (i < HashCounter.size() && HashCounter[i] == 0) i++;
            i2 += HashCounter[i]; i++;
        }  
        else
        {
            while (j < HashCounter.size() && HashCounter[HashCounter.size() - j - 1] == 0) j++;
            size_t idxR = HashCounter.size() - j - 1;
            j2 += HashCounter[idxR]; j++;
        }

        distance = std::max(i2, j2);
    }

        // src: 1111133^^77777779

        // table: 0123456789
        //        0502000701
    size_t idxL = i;
    size_t idxR = HashCounter.size() - j - 1;

    return vInput[i2];
}

void ClosestNumbers()
{
    size_t numTestCases = 0;

    std::cin >> numTestCases;
    std::cin.ignore();

    if (numTestCases < 1)
        return;

    std::vector<int> array(numTestCases);
    for (size_t i = 0; i < numTestCases; i++)
    {
        std::cin >> array[i];
    }

    std::sort(array.begin(), array.end());

    unsigned int minDiff = abs(array[1] - array[0]);
    std::vector<int> diffStorage;
    diffStorage.push_back(1);

    for (size_t i = 2; i < numTestCases; i++)
    {
        unsigned int diffTmp = abs(array[i] - array[i - 1]);

        if (diffTmp < minDiff)
        {
            diffStorage.clear();
            minDiff = diffTmp;
        }

        if (diffTmp == minDiff)
        {
            diffStorage.push_back(i);
        }
    }

    size_t numDiffs = diffStorage.size();
    for (size_t i2 = 0; i2 < numDiffs; i2++)
    {
        size_t minIdx1 = diffStorage[i2] - 1;
        size_t minIdx2 = diffStorage[i2];
        
        std::cout << array[minIdx1] << " " << array[minIdx2] << " ";
    }

    std::cout << std::endl;

    return;
}


int fibonacchi(int n)
{
    return (n < 3) ?
        1 :
        fibonacchi(n - 1) + fibonacchi(n - 2);
}


int AllTasks()
{
    MaxXor();
    return 0;
    //Sherlock();

    //ChangeEndian();

    // Remove the duplicate characters in a string without using any additional bu$er
    //std::string sss = "this is my string with duplicates"; std::string sss = " ";
    //std::string str2 = RemoveDuplicates(sss);

    //auto vect = PrepareVector(25);
    //auto res = BinSearch(vect, 0, vect.size());

    //KnapsackProblem();

    //int d = AnagramDifference("dnqaurlplofnrtmh");
    //AnagramDifferenceStarter();
    //bool bRet = IsAnagram("qwert  asdfg1", "asdfgqwert");
    //bool bRet = IsAnagram("str1", "str2");

    //std::vector<int> vect = { 1, 1, 1, 1, 1, 14, 15, 44, 97 };
    //std::vector<int> vect = { 1, 1, 1, 1, 1, 14, 15, 44, 97, 97 };

    //int maxVal = *std::max_element(vect.begin(), vect.end());
    //int minVal = *std::min_element(vect.begin(), vect.end());

    //int iRes1 = FindMedian1(vect, minVal, maxVal);

    //int iRes2 = FindMedian2(vect, minVal, maxVal);

    //ClosestNumbers();

    //CutTheTree();
    
    //ByteTasks();




#if 0

    bool calcReady = false;
    std::mutex textMutex;
    std::condition_variable cv;

    std::shared_ptr<Work> w =
        std::make_shared<Work>(0, 3, fibonacchi,
        [&](size_t uid, int res)
    {
        int  ii = 5+res;
        calcReady = true;
        cv.notify_one();
    });

    std::unique_lock<std::mutex> lock(textMutex);
    while (!calcReady) cv.wait(lock);
    lock.release();

    calcReady = false;

    int calls = 0;
    Node::NodeCallbackT func = Node::NodeCallbackT([&](int res) 
    {
        calls++;
        calcReady = (calls == 3);
        cv.notify_one();
    });

    Node nn(1, 3, func);

    nn.DoWorkOnUnit(fibonacchi, 10);
    nn.DoWorkOnUnit(fibonacchi, 5);
    nn.DoWorkOnUnit(fibonacchi, 7);

    std::mutex mut2;
    std::unique_lock<std::mutex> lock2(mut2);
    while (!calcReady) cv.wait(lock2);


    for (int i = 0; i < 10 * 1000; i++)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
#endif

#if 1
    bool calcReady = false;
    std::condition_variable cv;

    int calls = 0;
    Node::NodeCallbackT func = Node::NodeCallbackT([&](int res)
    {
        calls++;
        printf("Call: %d\n", calls);

        calcReady = (calls == 3);
        cv.notify_one();
    });

    int nodeId = 1;
    size_t unitNum = 5;
    Node nn(nodeId, unitNum, func);

    nn.DoWorkOnUnit(fibonacchi, 10);
    nn.DoWorkOnUnit(fibonacchi, 5);
    nn.DoWorkOnUnit(fibonacchi, 7);

    std::mutex mut2;
    std::unique_lock<std::mutex> lock2(mut2);
    while (!calcReady) cv.wait(lock2);

#endif 

    return 0;
}

