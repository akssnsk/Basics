#include "Complex.h"

std::ostream &operator<<(std::ostream &ostr, const Complex &rhs)
{
    printf("Global Complex op <<\n");
    
    // class member approach
    return rhs.operator<<(ostr);

    // friend approach
    //ostr << "(" << rhs.m_i << "," << rhs.m_j << ")" << std::endl;
    //return ostr;
}


//Complex operator+(const Complex &lhs, const Complex &rhs)
//{
//    printf("Global Complex op add\n");
//
//        Complex tmp(lhs);
//
//        tmp.m_i += rhs.m_i;
//        tmp.m_j += rhs.m_j;
//
//        return tmp;
//}
