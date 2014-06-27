#pragma once

class RefCounter
{
private:
    unsigned long refCounter;

    RefCounter() : refCounter(0) {}

public:
    RefCounter(unsigned long _val) : refCounter(_val) {}

    unsigned long Inc()
    {
        refCounter++;
        return refCounter;
    }

    unsigned long Dec()
    {
        refCounter--;
        return refCounter;
    }
};

template <typename T>
class SharedPtr
{
private:
    T *object;
    RefCounter *refCtr;

public:
    SharedPtr<T>() : object(nullptr), refCtr(0) {}
    
    SharedPtr<T>(SharedPtr<T> &rhs)
    {
        if (rhs.object != nullptr)
        {
            object = rhs.object;
            refCtr = rhs.refCtr;
            refCtr->Inc();
        }
    }

    explicit SharedPtr<T>(T *ptr) : object(nullptr), refCtr(0) 
    {
        object = ptr;
        refCtr = new RefCounter(0);
        refCtr->Inc();
    }

    SharedPtr &operator=(SharedPtr<T> &rhs)
    {
        if (rhs.object == this->object)
            return *this;

        if (object != nullptr)
        {
            DecRef();
            object = nullptr;
        }

        if (rhs.object != nullptr)
        {
            object = rhs.object;
            refCtr = rhs.refCtr;
            refCtr->Inc();
        }

        return *this;
    }

    ~SharedPtr()
    {
        DecRef();
        object = nullptr;
    }

private:
    void DecRef()
    {
        unsigned long refs = refCtr->Dec();
        if (refs == 0)
        {
            delete refCtr;
            delete object;
        }
    }
};