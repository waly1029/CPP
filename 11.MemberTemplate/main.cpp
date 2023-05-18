#include <iostream>

class Base1{};
class Derived1: public Base1{};

class Base2{};
class Derived2: public Base2{};

// template <class T1, class T2>
// struct pair{
//     // ...

//     template<class U1, class U2>
//     pair(const pair<U1, U2>& p): first(p.first), second(p.second){}
// };

int main() {

    std::pair<Derived1, Derived2> p;

    // 整个代码的含义是在派生类和基类之间进行对象的类型转换。
    // 派生类可以隐式地转换为基类，但基类不能隐式地转换为派生类。
    // 所以在这里，将派生类的对象存储在基类的pair中是允许的。
    std::pair<Base1, Base2> p2(p);

    std::pair<Base1, Base2> p3(std::pair<Derived1, Derived2>());

    std::cout << __cplusplus << std::endl;

    return 0;
}