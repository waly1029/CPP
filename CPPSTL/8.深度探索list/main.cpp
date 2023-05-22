#include <iostream>

int main() {
    int i(6);

    ++++i; // ++(++i);
    // 因为前置++ 定义：
    // self& operator++() {... return *this;}
    // 返回类型是引用

    // i++++; // 这个表达式是非法的，因为表达式必须是可修改的左值
    // 后置++ 的定义：
    // 后置++ 返回的是临时变量temp，这个临时变量只能作为右值使用
    // 后置++ 运算符的定义类似于下面的伪代码：
    // self operator++(int) {
    //     self = temp;
    //     temp = *this;
    //     ++*this;
    //     return temp;
    // }


    std::cout << i << std::endl;

    return 0;
}