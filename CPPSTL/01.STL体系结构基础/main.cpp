// 容器
// 迭代器
// 算法
// 仿函数
// 适配器
// 分配器
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main(){
    int ia[6] = {27, 210, 12, 47, 109, 83};

    vector<int, allocator<int>> vi(ia, ia+6);
    // allocator
    // container

    // TODO: 实现bind2nd,not1
    // cout << count_if(vi.begin(), vi.end(), not_fn(bind(less<int>(), 40))); // >= 40
    cout << count_if(vi.begin(), vi.end(), std::not_fn(std::function<bool(int)>(std::bind(std::less<int>(), std::placeholders::_1, 40))));

    // vi.begin(): iterator
    // count_if: algorithm
    // not1: function adapter(negator)
    // bind2nd: function adapter(binder)
    // less: function object

    return 0;
}