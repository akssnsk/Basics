#include "Examples.h"


// Task simulation 1
bool IsPrime(int n)
{
    if (n < 2)
        return false;

    bool retVal = true;
    for (int i = 2; i < n / 2; ++i)
    {
        if (n%i == 0)
        {
            retVal = false;
            break;
        }
    }

    return retVal;
}

// Task simulation 2
int Fibonacchi(int n)
{
    return (n < 3) ?
        1 :
        Fibonacchi(n - 1) + Fibonacchi(n - 2);
}

bool Blocking(int num)
{
    int iFibNum = Fibonacchi(num);
    bool bRes = IsPrime(iFibNum);
    return bRes;
}

bool HalfBlocking(int num)
{
    auto iFibNumAsync = std::async([=] { return Fibonacchi(num); });
    bool bRes = IsPrime(iFibNumAsync.get());
    return bRes;
}

bool NonBlocking(int num)
{
    auto iFibNumAsync = std::async([=] { return Fibonacchi(num); });
    auto bIsPrime = std::async([&] { return IsPrime(iFibNumAsync.get()); });

    return bIsPrime.get();
}


void ExamplesRun()
{
    bool bRes1 = Blocking(23);
    bool bRes2 = HalfBlocking(23);
    bool bRes3 = NonBlocking(23);
}


