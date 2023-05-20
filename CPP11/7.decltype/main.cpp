#include <iostream>
#include <map>
#include <set>
#include <string>

// 1.声明一个返回类型
template<typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x + y) {
    return x + y;
}

// 2.元编程
template<typename T>
void test_decltype(T obj) {
    std::map<std::string, float>::value_type elem1;

    std::map<std::string, float> coll;
    decltype(coll)::value_type elem2;

    typedef typename decltype(obj)::iterator iType;
    // typedef typename T::iterator iType;

    decltype(obj)another(obj);
}


class Person {
public:
    bool lastname() { return false; }
    bool firstname() { return false; }
};

void func1(){
    int a = 5;
    double b = 2.5;
    auto result = add(a, b);
    std::cout << result << std::endl;

    // ??
    test_decltype(std::map<int, int>());

    // 3.传递lambda类型
    auto cmp = [](const Person& p1, const Person& p2) {
        return p1.lastname()<p2.lastname() || (p1.lastname()==p2.lastname() && p1.firstname()<p2.firstname());
    };
    std::set<Person, decltype(cmp)> coll(cmp);
}

int main() {

    func1();


    return 0;
}