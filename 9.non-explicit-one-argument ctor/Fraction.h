#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
    int m_numerator;
    int m_denominator;

public:
    // non-explicit constructor
    // 4+f(4,5)情况下，把4转化成分母为1分子为4的Fraction对象
    // 因此可以进行加法Fraction operator+(const Fraction& f);
    Fraction(int num, int den = 1) : m_numerator(num), m_denominator(den) {
        std::cout << "Fraction structure called " << std::endl;
    }

    Fraction operator+(const Fraction& f) const {
        std::cout << "Fraction::operator+(const Fraction&) called" << std::endl;
        int numerator = m_numerator * f.m_denominator + f.m_numerator * m_denominator;
        int denominator = m_denominator * f.m_denominator;
        return Fraction(numerator, denominator);
    }

};

#endif
