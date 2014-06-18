#include "Node.h"


Node::~Node()
{
}

int Node::DoWorkOnUnit(const UnitWork::WorkActionT &action, int argument)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    size_t availId = 0;
    for (auto &w : m_units)
    {
        if (w == nullptr)
            break;

        availId++;
    }

    if (availId >= m_units.size())
    {
        return -1; // too much jobs
    }

    UnitWork::WorkCallbackT cb = std::bind(&Node::WorkDoneOn, this, std::placeholders::_1, std::placeholders::_2);
    m_units[availId] = std::make_shared<UnitWork>(availId, argument, action, cb);

    return 0;
}

void Node::WorkDoneOn(size_t unitId, int res)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    m_units[unitId].reset();

    m_callback(res);
}
