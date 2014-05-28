#include <stdio.h>

#include <Windows.h>

#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <condition_variable>


class CSpinLock
{
public:
    CSpinLock(INT iMaxSpin) : m_iMaxSpinValue(iMaxSpin), m_bSem(FALSE) {};

    ~CSpinLock()
    { 
        Unlock();
    };

    void Lock()
    {
        //while (InterlockedCompareExchange((LONG*)&m_Status, Busy, Available) != Available);
        while (InterlockedCompareExchange((LONG *)&m_bSem, TRUE, FALSE) != FALSE);

        return;
    }

    BOOL TryLock()
    {
        INT counter = 0 ;
        //while (InterlockedCompareExchange((LONG*)&m_Status, Busy, Available) != Available);
        while (counter++ < m_iMaxSpinValue && InterlockedCompareExchange((LONG *)&m_bSem, TRUE, FALSE) != FALSE);
        
        if (counter >= m_iMaxSpinValue)
        {
            printf(" Timed-out ");
        }

        return counter < m_iMaxSpinValue;
    }

    void Unlock()
    {
        m_bSem = FALSE;
    }

private:
    INT m_iMaxSpinValue;
    BOOL m_bSem;
}; 

CSpinLock g_sl(1000);

void SpinLockTest(int thNum)
{
    std::this_thread::yield();

    g_sl.Lock();

    printf("Thread %d locked\n", thNum);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    printf("Thread %d unlocked\n", thNum);

    g_sl.Unlock();
}

void SpinTryLockTest(int thNum)
{
    std::this_thread::yield();

    while (!g_sl.TryLock())
    {
        printf("Thread %d didn't get the lock and go sleep\n", thNum);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    printf("Thread %d locked\n", thNum);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    printf("Thread %d unlocked\n", thNum);

    g_sl.Unlock();
}

void SpinLockRun()
{
    int numThread = 10;
    
    std::vector<std::thread> thVector;
    thVector.reserve(numThread);
    
    int i = 0;
    for (; i < numThread; i++)
    {
        //thVector.emplace_back(SpinLockTest, i);
        thVector.emplace_back(SpinTryLockTest, i);
    }

    for (auto &t : thVector)
    {
        t.join();
    }

    return;
}