#include <iostream>
using namespace std;

namespace lz01 {
    // 辅助函数模板，用于计算可变参数模板中参数的个数
    // template<typename... Args>
    // constexpr size_t countArgs(Args...) {
    //     return sizeof...(Args);
    // }

    // printX 函数模板
    // 处理边界条件当args为0时,处理最后情况
    void printX() {
        cout << "non-arg printX()" << endl;
    }

    // "..."可变参数模版
    template<typename T, typename... Types>
    void printX(const T& firstArg, const Types&... args) {
        cout << "current Arg: " << firstArg << endl;
        cout << sizeof...(args) << endl;
        printX(args...);
    }

    // 无限递归
    // template<typename... Types>
    // void printX(const Types&... args) {
    //     cout << sizeof...(args) << endl;
    //     printX(args...);
    // }
}

int main() {

    lz01::printX(1, 2.2, 'c', "World");

    return 0;
}
