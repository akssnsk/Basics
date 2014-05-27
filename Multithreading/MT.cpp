#include <stdio.h>


#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <condition_variable>

#include <windows.h>

void SpinLockRun();


// Semaphore
class Semaphore
{
private:
    std::mutex m;
    BOOL m_bMutex;

    long currValue;
    long maxValue;

public:
    Semaphore(int maxParam)
        : currValue(maxParam), maxValue(maxParam), m_bMutex(FALSE)
    {
        printf("Semaphore ctor\n");
    }

    Semaphore()
    {
        // Just for test def ctor
        printf("Semaphore default ctor\n");
    }

    Semaphore(const Semaphore &rhs)
        : currValue(rhs.currValue), maxValue(rhs.currValue)
    {
        // Just for test copy ctor
        printf("Semaphore copy ctor\n");
    }

    Semaphore &operator=(const Semaphore &rhs)
    {
        // Just for test assignment ctor
        currValue = rhs.currValue;
        maxValue = rhs.maxValue;
        printf("Assignment op\n");
    }

    long CompareAndSwap(long *var, long newval, long oldval)
    {
        if (*var == oldval) {
            *var = newval;
//            return newval;
        }
        return oldval;
    }

    void AcquireWithMutex()
    {
        // Option with mutex
        std::unique_lock<std::mutex> lock(m);
        while (currValue == 0)
        {
            //printf("waiting ");
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            lock.lock();
        }

        currValue--;
    }

    void ReleaseWithMutex()
    {
        std::unique_lock<std::mutex> lock(m);

        if (currValue < maxValue)
            currValue++;

        return;
    }

    void AcquireSpin()
    {
        while (true)
        {
            while (InterlockedCompareExchange((LONG *)&m_bMutex, TRUE, FALSE) != FALSE);

            if (currValue > 0)
                break;

            m_bMutex = FALSE;
        }

        // option with CAS
        //while (true)
        //{
        //    while (CompareAndSwap((LONG *)&m_bMutex, TRUE, FALSE) != FALSE);

        //    if (currValue > 0)
        //        break;
        //    
        //    m_bMutex = FALSE;
        //}

        currValue--;
        m_bMutex = FALSE;
    }

    void ReleaseSpin()
    {
        while (InterlockedCompareExchange((LONG *)&m_bMutex, TRUE, FALSE) != FALSE);

        if (currValue < maxValue)
            currValue++;

        m_bMutex = FALSE;

        return;
    }
};

bool oddReady = false;
bool evenReady = false;
std::mutex numMutex;
std::condition_variable numCV;

void PrintOdd(int max)
{
    for (int i = 1; i < max; i = i + 2)
    {
        std::unique_lock<std::mutex> lock(numMutex);
        while (!evenReady) numCV.wait(lock);

        printf("PrintOdd: %2d\n", i); std::this_thread::sleep_for(std::chrono::microseconds(30));
        oddReady = true;
        evenReady = false;
        numCV.notify_one();
    }

    return;
}

void PrintEven(int max)
{
    for (int i = 2; i < max; i = i + 2)
    {
        std::unique_lock<std::mutex> lock(numMutex);
        while (!oddReady) numCV.wait(lock);

        printf("PrintEven: %2d\n", i);
        evenReady = true;
        oddReady = false;
        numCV.notify_one();
    }

    return;
}

// Two threads printing odd and even numbers
void Three()
{
    evenReady = true;
    int max = 20;
    std::thread t1(PrintOdd, max);
    std::thread t2(PrintEven, max);

    t1.join();
    t2.join();
}

// Implement and test semaphore 
void One()
{
    Semaphore sharedSemaphore(2);

    int nThreads = 10;
    std::vector<std::thread> thVect;
    for (int i = 0; i < nThreads; i++)
    {
        thVect.emplace_back([](Semaphore &s1, int num)
        {
            std::this_thread::yield();
            s1.AcquireWithMutex();
            printf("Thread %2d aquired semaphore\n", num);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            s1.ReleaseWithMutex();
        },
        std::ref(sharedSemaphore), i);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    for (auto &t : thVect)
    {
        t.join();
    }

    return;
}

// Five threads to run run one after another
#define THREAD_COUNT 5
std::condition_variable seqCV;
bool bSeqFlag[THREAD_COUNT];
std::mutex seqMutex;
std::thread seqThreads[THREAD_COUNT];

void SequenceThread(int repTime, int thNum)
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        {
            std::unique_lock<std::mutex> lock(seqMutex);
            while (!seqCV.wait_for(lock, std::chrono::milliseconds(10), [thNum]() { return bSeqFlag[thNum]; }))
            {
                lock.unlock();
                std::this_thread::yield();
                lock.lock();
            }

            printf("SeqThread %d ", thNum);
            if (thNum == 4) printf("\n");

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            bSeqFlag[thNum] = false;
            bSeqFlag[(thNum + 1) % THREAD_COUNT] = true;

            seqCV.notify_one();
        }
    }

    return;
}

void Two()
{
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<int> iUrandStartFrom(0, THREAD_COUNT-1);

    int iRepetitionNumber = 3;
    int iStartFrom = iUrandStartFrom(rng);
    bSeqFlag[iStartFrom] = true;
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        seqThreads[i] = std::thread(SequenceThread, iRepetitionNumber, i);
    }

    // Wait till they done
    for (auto &t : seqThreads)
    {
        t.join();
    }
}

int main(int argc, char* argv[])
{
    One();
    //Two();
    //Three();

    //SpinLockRun();

    return 0;
}

