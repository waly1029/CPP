#include <iostream>
#include "Fraction.h"
#include "Fraction2.h"
#include "Fraction3.h"

using namespace std;

namespace nsp_Fraction{
    void test1() {
        Fraction f(3, 5);
        Fraction f2 = f + 4; // 调用 non-explicit ctor将4转换为Fraction(4, 1)
                             // 然后调用operator+
    }
}

namespace nsp_Fraction2{
    void test1() {
        Fraction2 f(2, 3);

        // [Error] ambiguous二义性
        // 有多个运算符 "+" 与这些操作数匹配:C/C++(350)
        // main.cpp(20, 26): 内置运算符 "arithmetic + arithmetic"
        // main.cpp(20, 26): 函数 "Fraction2::operator+(const Fraction2 &f) const"
        // main.cpp(20, 26): 操作数类型为: Fraction2 + int

        // 第一条路 4经由构造non-explicit ctor转换成Fraction2(4,1)
        // 之后operator+
        // 第二条路 f经由 operator double() 转换成double
        // 之后 两个double相加 f+4 内置的double相加
        // **************多于一种办法的情况下出现二义性********************************
        // Fraction2 f2 = f + 4;
    }
}

namespace nsp_Fraction3 {
    void test1() {
        Fraction3 f(3, 5);

        // explict只用于构造函数之前90%，还有模版的很小的一部分
        // 不存在从 "double" 转换到 "Fraction3" 的适当构造函数C/C++(415)
        // explict 禁止4的自动转换成Fraction3(4, 1)
        // Fraction3 f2 = f + 4;
        Fraction3 f2 = f + Fraction3(4, 1);
    }
}

int main() {

    // nsp_Fraction::test1();

    // nsp_Fraction2::test1();

    nsp_Fraction3::test1();



    return 0;
}