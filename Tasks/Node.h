#pragma once

#include "stlheaders.h"

class UnitWork
{
public:
    typedef std::function<void(size_t, int)> WorkCallbackT;
    typedef std::function<int(int)> WorkActionT;

    size_t m_id;
    size_t m_arg;
    WorkActionT m_action;
    WorkCallbackT m_callback;

    UnitWork(size_t id_, size_t arg_, const WorkActionT &action_, const WorkCallbackT &callback_) :
        m_id(id_), m_arg(arg_), m_action(action_), m_callback(callback_)
    {
        std::thread(&UnitWork::Do, this).detach();
    }

    void Do()
    {
        int res = m_action(m_arg);
        
        m_callback(m_id, res);
    }
};

class Node
{
public:
    typedef std::function<void(int)> NodeCallbackT;

    Node(int id_, size_t count_, const NodeCallbackT &callback_) :
        m_id(id_), m_maxUnitsAvail(count_), m_callback(callback_)
    {
        m_units.resize(count_);
    };
    
    ~Node();

    int DoWorkOnUnit(const UnitWork::WorkActionT &, int);
    void WorkDoneOn(size_t unitId, int res);

private:
    int m_id;
    std::mutex m_mutex;
    size_t m_maxUnitsAvail;
    std::vector<std::shared_ptr<UnitWork>> m_units;

    NodeCallbackT m_callback;
};
