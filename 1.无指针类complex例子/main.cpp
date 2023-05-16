#include "complex.h"
#include <iostream>
using namespace std;

int main() {
    complex<double> c1(2, 1);
    // cout << c1.real() << endl;
    // cout << c1.imag() << endl;

    const complex<double> c2(1, 2);
    // cout << c2.real() << endl;
    // cout << c2.imag() << endl;

    complex<double> c3(7, 8);
    complex<double> c4(2, 5);
    // c1 += c3 += c4;
    // cout << c1.real() << endl;
    // cout << c1.imag() << endl;

    complex<double> c5;
    print(c5);
    c5 = c1 + c3 + c4;
    print(c5);
    c5 = c5 + 3.0;
    print(c5);
    // 构造函数中的隐士转换被禁止
    c5 = double(3) + c5;
    print(c5);
    c5 = c5 - c4;
    print(c5);
    c5 = -c5;

    complex<double> c6;
    cout << (c6==c5) << endl;
    cout << (c6==double(2)) << endl;
    cout << (double(0)==c6) << endl;

    cout << c5 << c5.conj() << endl;
    c5 += double(0.55);
    cout << c5 << c5.conj() << endl;

    return 0;
}
