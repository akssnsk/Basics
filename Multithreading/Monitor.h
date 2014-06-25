#pragma once

#include <mutex>

template <class T>
class monitor
{
private:
    mutable T object;
    mutable std::mutex m_m;

    T object_copy() const
    {
        std::lock_guard<std::mutex> lock{ m_m };
        return object;
    }

public:
    monitor() = default;

    monitor(const T& _obj)
        : object(_obj)
    {}

    monitor(const monitor<T>& other_monitor)
        : object{ other_monitor.object_copy() }
    {}

    //monitor(T&& _obj)
    //    : object (std::move(_obj) )
    //{}

    monitor& operator=(const monitor& other_monitor)
    {
        {
            std::lock_guard<std::mutex> lock{ m_m };
            object = other_monitor.synced_obj_copy();
        }
        return *this;
    }

    template <typename F>
    auto operator()(F f) const -> decltype(f(object))
    {
        std::lock_guard<std::mutex> _{ m_m };
        return f(object);
    }
};

void MonitorRun();
