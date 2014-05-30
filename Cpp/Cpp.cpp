// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <cmath>

#include <stdio.h>

static int aDefCtr = 0;
static int aCopyCtr = 0;
static int aAssignCtr = 0;

class A
{
private:
    int aa;

public:
    A()
        :aa(aDefCtr)
    {
        printf("A::A ctor(%2d)\n", aa);
        aDefCtr++;
    }

    A(const A &a)
    {
        printf("A::A copy ctor(%2d) for %d\n", aCopyCtr, a.aa);
        aa = a.aa;
        aCopyCtr++;
    }

    A& operator=(const A &a)
    {
        printf("A::= assignment(%2d) for %d\n", aAssignCtr, a.aa);
        aa = a.aa;
        aAssignCtr++;
        return *this;
    }
};


class StackOnly {
private:
    void* operator new(size_t size);
};

class HeapOnly {
public:
    HeapOnly() {};
    void destroy() const { delete this; };

    ~HeapOnly() {} ;
};

StackOnly s1;
//HeapOnly h1;     // Destructor is protected so h1 can't be created globally

HeapOnly func()  // Compiler error because destructor of temporary is protected
{
// This is ok. No destructor is invoked automatically for heap-based objects
    HeapOnly *hoptr = new HeapOnly;
    return *hoptr;
}

struct Point { 
    char y; 
    int ii;
};

template <typename Duration, typename Function>
void timer(const Duration & d, const Function & f)
{
    std::thread([d, &f](){
        std::this_thread::sleep_for(d);
        f();
    }).detach();
}

void hello() { 
    std::cout << "Hello!\n"; 
}

bool IsPrime(int n)
{
    if (n < 2)
        return false;

    bool retVal = true;
    for (int i = 2; i < n/2; ++i)
    {
        if (n%i == 0)
        {
            bool retVal = false;
            break;
        }
    }

    return retVal;
}

std::vector<bool> Eratosphenes(int limit)
{
    std::vector<bool> primeFlagArray(limit);
    primeFlagArray[0] = primeFlagArray[1] = false;
    int n = 2;
    std::generate(primeFlagArray.begin()+n, primeFlagArray.end(), [&]() { return n++%2 != 0; });
    for (int i = 3; i*i < limit; i++)
    {
        if (primeFlagArray[i])
        {
            for (int j = i+i; j < limit; j = j + i)
            {
                primeFlagArray[j] = false;
            }
        }
    }

    return primeFlagArray;
}

int NumBit(int num)
{
    int bitNum = 0;
    for (int i = 0; i < 8 * sizeof(num); i++)
    {
        int resI = (num >> i);
        long long resL = (num >> i);
        if ((resL & 0x1) == 1)
            bitNum++;
    }

    return bitNum;
}

void stringConst(char* str)
{
    str[1] = 'Q';
}

class SmallCmp
{
public:
    size_t operator()(const std::string &str1, const std::string &str2) const
    {
        return str1[0] == str2[0];
    }
};

class SmallHash
{
public:
    size_t operator()(const std::string &str) const
    {
        char c = str[0];
        c >>= 1;
        return c;
    }
};

typedef char* CharPtrT;
typedef CharPtrT (*RetCharPtrT)(void);
typedef RetCharPtrT (*RequiredFuncT)(void);
typedef void *(*SameTypeRetT)();


char *RetCharFunc()
{
    static char s_string[] = "RetString";
    return s_string;
}

RetCharPtrT RetFuncPtrFunc()
{
    RetCharPtrT fff = RetCharFunc;
    return fff;
}

void* funcfunc22()
{
    return nullptr;
}

void FuncPtr()
{
    // Declare an array of N pointers to functions returning pointers to functions returning pointers to characters ?
    // Raw types
    char *ptr;
    char *(*aa1)(void) = RetCharFunc;
    // One var
    char * (*(*aa2)(void))(void) = RetFuncPtrFunc;
    auto funcRes1 = aa2();
    auto cRes1 = funcRes1();

    // Array
    char * (*(*funcArrRaw[10])(void))(void);
    funcArrRaw[0] = RetFuncPtrFunc;
    auto funcRes2 = funcArrRaw[0]();
    auto cRes2 = funcRes2();

    // Typedefs
    // One
    RequiredFuncT funcOne = RetFuncPtrFunc;
    auto funcRes3 = funcOne();
    auto cRes3 = funcRes3();

    // Array
    RequiredFuncT funcArr[10] = { 0 };
    funcArr[0] = RetFuncPtrFunc;
    auto funcRes4 = funcArr[0]();
    auto cRes4 = funcRes2();

    // Declare a function that returns a pointer to a function of its own type
    // ???
}

int main(int argc, char* argv[])
{
    FuncPtr();

    // Vector creation
    std::vector<A> vS;
    // If no resize or reserve:
    // 10 ctors +  10 copy ctors +  numerous (depends on implementation) copy ctors 
    // mostly because of array reallocation on extension
    // If resize to 100: 
    // 100 ctors + 100 copy ctors (extension on next insertion) + 10 ctors + 10 copy ctors 
    // vS.resize(100);
    // If reserve: 
    // 10 ctors +  10 copy ctors
    // vS.reserve(100);
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < 10; i++)
    {
        A s = A();
        vS.push_back(s);
    }

    aDefCtr = 0;
    aCopyCtr = 0;
    aAssignCtr = 0;

    // Vector insertion
    std::vector<A> vectQWER(10);
    printf("\n");
    vectQWER.erase(vectQWER.begin(), vectQWER.begin() + 2);
    printf("\n");
    vectQWER.erase(vectQWER.end()-2, vectQWER.end());
    printf("\n");
    vectQWER.insert(vectQWER.end() - 4, A());
    printf("\n");

    std::vector<int> vectQWER22;

    for (int i = 0; i < 100; i++)
    {
        printf("Capacity before: %3d", vectQWER22.capacity());
        vectQWER22.push_back(23);
        printf("  and after: %3d", vectQWER22.capacity());
        printf("\n");
    }

    // Hash insertion
    std::unordered_map<std::string, int> ush;
    ush.insert({ "string2", 2 });
    ush.insert({ "string2", 2 });

    // Hash insertion with custom hash func and collisions
    std::unordered_map<std::string, int, SmallHash> ssh;
    auto res = ssh.insert({ "string1", 1 });
    res = ssh.insert({ "string2", 2 });
    res = ssh.insert({ "zzstr11", 3 });
    res = ssh.insert({ "string2", 2 });

    int val1 = ssh["string1"];
    int val2 = ssh["string2"];

    size_t shash01 = ssh.hash_function()("string1");
    size_t shash02 = ssh.hash_function()("string2");
    size_t shash03 = ssh.hash_function()("zzstr11");

    size_t hash01 = ush.hash_function()("generated_id_0");
    size_t hash02 = ush.hash_function()("generated_id_1");
    size_t hash1 = std::hash<std::string>()("generated_id_0");
    size_t hash2 = std::hash<std::string>()("generated_id_1");

    auto lf = ssh.load_factor();
    auto mlf = ssh.max_load_factor();

    // Hash insertion with custom hash func, compare func and collisions
    std::unordered_map<std::string, int, SmallHash, SmallCmp> ssh2;
    res = ssh2.insert({ "string1", 1 });
    res = ssh2.insert({ "string2", 2 });
    res = ssh2.insert({ "zzstr11", 3 });
    res = ssh2.insert({ "string2", 2 });


    A cA1;
    A cA2 = A();

    cA2 = cA1;

    printf("\n");

    std::vector<A> aArr;
    //aArr.resize(20);
    printf("\n");

    aArr.push_back(cA1);
    printf("\n");
    aArr.push_back(cA2);
    aArr.push_back(cA1);
    printf("\n");
    aArr.push_back(cA2);
    printf("\n");
    aArr.push_back(cA1);
    aArr.push_back(cA2);
    printf("\n");

    int cArr = aArr.capacity();

    // Bites
    long long numEven = 8;
    bool evenNumber1 = (numEven % 2) == 0;
    bool evenNumber2 = ((numEven-1) & 0x1) != 0;
    bool evenNumber3 = ((numEven - 1) << (8 * sizeof(numEven)-1)) != 0;
    
    // Count with union 
    struct byte
    {
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;
        unsigned char b8 : 1;
    };

    union bits
    {
        char symb;
        struct byte bit;
    } u11;

    u11.symb = 101;
    unsigned char k = u11.bit.b1 + u11.bit.b2 + u11.bit.b3 + u11.bit.b4 + u11.bit.b5 + u11.bit.b6 + u11.bit.b7 + u11.bit.b8;

    // Count with table
    std::vector<int> bitTable;
    for (int i = 0; i < 256; i++)
    {
        bitTable.push_back(NumBit(i));
    }

    int anotherNum = u11.symb;
    int bitNumTable = 0;
    for (int i = 0; i < sizeof(anotherNum); ++i)
    {
        int mask = 0xff << (i*8);
        int maskNum = (anotherNum & mask) >> (i*8);
        int partNum = bitTable[maskNum];

        bitNumTable += partNum;
    }

    int bitNumLoop = 0;
    int anotherNum2 = u11.symb;
    while (anotherNum2 != 0)
    {
        if (anotherNum2 & 0x1)
        {
            bitNumLoop++;
        }
        anotherNum2 >>= 1;
    }


    // Strings
    // Const
    char ssstr[] = "My string";
    stringConst(ssstr);
//    char *pSsstr = "My string2";
//    stringConst(ssstr); // FAIL: cannot change ???????????

    // Primes
    std::vector<bool> primeRes = Eratosphenes(10000);

    // Threads
    timer(std::chrono::seconds(1), hello);
    std::cout << "Thread launched\n";
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Continue\n";

    //Point pp;
    //int s = sizeof(pp);

    int sI = sizeof(int);
    int sL = sizeof(long);
    int sLL = sizeof(long long);

    StackOnly s1;
    //StackOnly *s2 = new StackOnly();
    //HeapOnly h1;

    std::vector<int> v{ 9, 3, 6, 2, 1, 7, 8, 5, 4, 0 };//{ 5, 6, 4, 3, 2, 6, 7, 9, 3 };

    std::nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
    std::cout << "The median is " << v[v.size() / 2] << '\n';

    std::nth_element(v.begin(), v.begin() + 3, v.end());//, std::greater<int>());
    std::cout << "The required element is " << v[3] << '\n';


    std::map<int, std::string> om;
    om.insert({2, "two"});
    om.insert(std::make_pair(3, "three"));
    om.insert(std::make_pair(5, "five"));
    om.insert(std::make_pair(1, "one"));
    om.insert(std::make_pair(4, "four"));
    om.insert(std::make_pair(6, "six"));
    om.insert(std::make_pair(7, "seven"));

    for (auto i = om.begin(); i != om.end(); i++)
    {
        printf("(%d, %s) ", i->first, i->second.c_str());
    }

    printf("\n");

    auto iter = om.begin();
    while (iter != om.end())
    {
        if (iter->first % 3 == 0)
        {
            iter = om.erase(iter);
        }

        ++iter;
    }

    for (auto i = om.begin(); i != om.end(); i++)
    {
        printf("(%d, %S) ", i->first, i->second.c_str());
    }

    printf("\n");

    typedef std::unordered_map<int, std::string> MyHash;
    MyHash um;

    int c11 = um.bucket_count();

    um.insert({ 2, "two" });
    um.insert(std::make_pair(3, "three"));
    um.insert(std::make_pair(5, "five"));
    um.insert(std::make_pair(1, "one"));
    um.insert(std::make_pair(4, "four"));

    MyHash::hasher hfn = um.hash_function();

    auto hfn2 = hfn(2);
    auto hfn3 = hfn(3);

    int c21 = um.bucket_count();

    um.rehash(100);

    int c3 = um.bucket_count();

    for (auto i = um.begin(); i != um.end(); i++)
    {
        printf("(%d, %S) ", i->first, i->second.c_str());
    }

    printf("\n");

	return 0;
}

