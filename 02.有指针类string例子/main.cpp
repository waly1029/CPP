#include <iostream>
#include "mystring.h"

using namespace std;

int main() {
    // MyString s1;    // 无参数构造函数，可以省略括号
    // MyString s2{};  // 无参数构造函数，可以使用空括号

    // MyString s3("Hello");  // 有参数构造函数，需要使用括号并提供参数
    // MyString s4{"World"};  // 有参数构造函数，可以使用括号或花括号提供参数

    MyString s1;
    MyString s2("Hello");

    // 
    MyString* p = new MyString("world");

    cout << s2 << endl;
    cout << *p << endl;
    delete p;



    return 0;
}