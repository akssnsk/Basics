#include "Monitor.h"

#include <iostream>
#include <string>
#include <vector>
#include <future>

void SynchedOutput2()
{
    monitor<std::reference_wrapper<std::ostream>> synced_cout{ { std::cout } };

    const auto name = { 'e', 't', 'a', 'm' };
    auto futures = std::vector<std::future<void>>();
    
    for (char c : name)
    {
        futures.emplace_back(std::async(std::launch::async, [&, c] {
            std::this_thread::yield();
            synced_cout([c](std::ostream& ostream) {
                ostream << c;
            });
        }));
    }

    for (std::future<void>& future : futures) future.wait();

    synced_cout([=](std::ostream &sync_cout)
    {
        sync_cout << std::endl << "Done\n";
    });

}

void SynchedOutput()
{
    monitor<std::ostream&> sync_cout{ std::cout };

    std::vector<std::future<void>> v;

    for (int i = 0; i < 5; i++)
    {
        v.push_back(std::async([&, i]
        {
            sync_cout([=](std::ostream &sync_cout)
            {
                sync_cout << std::to_string(i) << " " << std::to_string(i);
                sync_cout << "\n";
            });

            sync_cout([=](std::ostream &sync_cout)
            {
                sync_cout << "Hi from" << i << std::endl;
            });

        }));
    }

    for (auto &f : v) f.wait();
    
    sync_cout([=](std::ostream &sync_cout)
    {
        sync_cout << "Done\n";
    });

    return;
}

void UnsynchedOutput()
{
    monitor<std::string> s = "start\n";
    std::vector<std::future<void>> v;

    for (int i = 0; i < 5; i++)
    {
        v.push_back(std::async([&, i]
        {
            s([=](std::string &s)
            {
                s += std::to_string(i) + " " + std::to_string(i);
                s += "\n";
            });

            s([](std::string &s)
            {
                std::cout << s;
            });

        }));
    }

    for (auto &f : v) f.wait();
    std::cout << "Done\n";

    return;
}




void MonitorRun()
{
    std::cout << "UnsynchedOutput\n";
    UnsynchedOutput();
    
    std::cout << "SynchedOutput\n";
    SynchedOutput();

    std::cout << "SynchedOutput2\n";
    SynchedOutput2();


}