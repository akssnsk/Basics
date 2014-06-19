#include <iostream>
#include <vector>

#include "Template.h"


class MyClass {
    virtual void a() = 0;
};

class MyClass2 : public MyClass {
    void a(){}
};

// template definition
template< class T >
void foo(const T& value)
{
    std::cout << "DEFAULT" << std::endl;
};

// specialization for MyClass
template<>
void foo(const MyClass & value)
{
    std::cout << "MyClass" << std::endl;
};

// specialization for vector of MyClass
template<>
void foo(const std::vector<MyClass> & v)
{
    std::cout << "vector" << std::endl;
}


void TemplateRun()
{
    foo(2);

    MyClass2 e;
    foo<MyClass>(e);

    std::vector<MyClass> vM;
    foo(vM);



}