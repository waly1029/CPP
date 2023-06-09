#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction{
    int m_numerator;
    int m_denominator;
public:
    Fraction(int num, int den=1): m_numerator(num), m_denominator(den) {}

    // 转换函数
    operator double() const {
        // return (double)(m_numerator/m_denominator);
        // return (double)m_numerator/m_denominator;

        return (m_numerator/(double)m_denominator);
    }
    
    // double operator+(double val) const {
    //     return (m_numerator/m_denominator) + val;
    // }
};


#endif