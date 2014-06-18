#pragma once

#include <stdio.h>

#include <iostream>

class Complex
{
private:
    int m_i;
    int m_j;

public:
    Complex() : m_i(0), m_j(0) 
    {
        printf("Complex def ctor\n");
    };
    
    Complex(int i, int j) : m_i(i), m_j(j) 
    {
        printf("Complex param ctor\n");
    };
    Complex(const Complex &rhs) : m_i(rhs.m_i), m_j(rhs.m_j) 
    { 
        printf("Complex copy ctor\n");
    };

    Complex &operator=(const Complex &rhs)
    {
        printf("Complex op assign\n");

        m_i = rhs.m_i;
        m_j = rhs.m_j;

        return *this;
    }

    Complex operator+(const Complex &rhs) const
    {
        printf("Complex op add\n");

        Complex tmp(*this);

        tmp.m_i += rhs.m_i;
        tmp.m_j += rhs.m_j;

        return tmp;
    }

    Complex operator-(const Complex &rhs) const
    {
        printf("Complex op add\n");

        Complex tmp(*this);

        tmp.m_i -= rhs.m_i;
        tmp.m_j -= rhs.m_j;

        return tmp;
    }

    // ostream class method approach
    std::ostream &operator<<(std::ostream &ostr) const
    {
        printf("Complex op out\n");

        ostr << "(" << m_i << ", " << m_j << ")" << std::endl;

        return ostr;
    }

    //// ostream friend approach
    //friend std::ostream &operator<<(std::ostream &ostr, const Complex &rhs);
};

std::ostream &operator<<(std::ostream &ostr, const Complex &rhs);
//Complex operator+(const Complex &lhs, const Complex &rhs);
