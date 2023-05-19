#include <iostream>
#include <vector>
using namespace std;

// 无参情况下的print()函数
void print() {
    cout << "print() called" << endl;
}

// 可变参数模板函数print，用于打印任意数量的参数
// 参数说明：
//   const T& firstArg: 参数包中的第一个参数，使用引用类型以避免拷贝
//   const Types&... args: 参数包中的剩余参数，使用引用类型以避免拷贝
template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
    // 输出当前参数包中的第一个参数
    cout << "firstArg: " << firstArg << endl;
    cout << "sizeof...(args) = " << sizeof...(args) << endl;

    // 递归调用print函数，传入剩余的参数包args
    print(args...);
}

int main() {
    // 调用print函数，并传入多个不同类型的参数
    print(5, "hello", 9.9, 'c');

    return 0;
}
