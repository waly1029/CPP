#ifndef FRACTION3_H
#define FRACTION3_H

#include <iostream>

class Fraction3 {
    int m_numerator;
    int m_denominator;

public:
    // 禁止自动转换
    explicit Fraction3(int num, int den = 1) : m_numerator(num), m_denominator(den) {
        std::cout << "Fraction structure called " << std::endl;
    }

    operator double() const {
        return (double)m_numerator / m_denominator;
    }

    Fraction3 operator+(const Fraction3& f) const {
        std::cout << "Fraction::operator+(const Fraction&) called" << std::endl;
        int numerator = m_numerator * f.m_denominator + f.m_numerator * m_denominator;
        int denominator = m_denominator * f.m_denominator;
        return Fraction3(numerator, denominator);
    }

};

#endif
