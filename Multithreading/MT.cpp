#include <stdio.h>

#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <condition_variable>

// Semaphore
class Semaphore
{
private:
    std::mutex m;
    long currValue;
    long maxValue;

public:
    Semaphore(int maxParam)
        : currValue(maxParam), maxValue(maxParam)
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

    long CAS(long *var, long oldval, long newval)
    {
        if (*var == oldval) {
            *var = newval;
            return 0;
        }
        return oldval;
    }

    void Acquire()
    {
        //while (true)
        //{
        //    long new = curr;
        //    if (_InterlockedCompareExchange(&curr, oldVal + 1, oldVal) == 0) {
        //        if (curr < maxVal)
        //            return;
        //    }
        //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //}

        // option with CAS (???)
        //while (true)
        //{
        //    int oldlock = curr;
        //    if (oldlock < maxVal) {
        //        if (CAS(&curr, oldlock, oldlock + 1) == 0)
        //            return;
        //        
        //        //printf("waiting ");
        //        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //    }
        //}


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

    void Release()
    {
        std::unique_lock<std::mutex> lock(m);

        if (currValue < maxValue)
            currValue++;

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

void Three()
{
    evenReady = true;
    int max = 20;
    std::thread t1(PrintOdd, max);
    std::thread t2(PrintEven, max);

    t1.join();
    t2.join();
}

void One()
{
    Semaphore sharedSemaphore(2);

    int nThreads = 10;
    std::vector<std::thread> thVect;
    for (int i = 0; i < nThreads; i++)
    {
        thVect.emplace_back([&](Semaphore &s1, int num)
        {
            std::this_thread::yield();
            s1.Acquire();
            printf("Thread %2d aquired semaphore\n", num);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            s1.Release();
        },
        std::ref(sharedSemaphore), i);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    for (auto &t : thVect)
    {
        t.join();
    }
}

void Two()
{
    std::vector<Semaphore> vS;
    // If no resize or reserve:
    // 10 ctors +  10 copy ctors + 
    // numerous (depends on implementation) copy ctors mostly because of array reallocation on extension
    // If resize: 
    // 100 ctors + 100 copy ctors (extension) + 10 ctors + 10 copy ctors 
    // vS.resize(100);
    // If reserve: 
    // 10 ctors +  10 copy ctors
    vS.reserve(100);
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < 10; i++)
    {
        Semaphore s = Semaphore(2); // Missed this point as I always use "Semaphore s(0, 2);" style
        vS.push_back(s);
    }
}

int main(int argc, char* argv[])
{
    One();
    //Two();
    //Three();
	
    return 0;
}

