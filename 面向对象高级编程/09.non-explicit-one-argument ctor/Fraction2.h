#ifndef FRACTION2_H
#define FRACTION2_H

#include <iostream>

class Fraction2 {
    int m_numerator;
    int m_denominator;

public:
    Fraction2(int num, int den = 1) : m_numerator(num), m_denominator(den) {
        std::cout << "Fraction structure called " << std::endl;
    }

    operator double() const {
        return (double)m_numerator / m_denominator;
    }

    Fraction2 operator+(const Fraction2& f) const {
        std::cout << "Fraction::operator+(const Fraction&) called" << std::endl;
        int numerator = m_numerator * f.m_denominator + f.m_numerator * m_denominator;
        int denominator = m_denominator * f.m_denominator;
        return Fraction2(numerator, denominator);
    }

};

#endif
