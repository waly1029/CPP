#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<string> cities{"A", "B", "C", "D", "E", "F"};
    // 形成一个initializer_list<string>
    // 背后有一个array<string, 6>
    // 调用vector<string> 构造函数时，找到vector<string> ctor接受initializer_list<string>
    // 所有容器都有这种ctor构造函数

    return 0;
}