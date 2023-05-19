#include <iostream>
#include <vector>
#include <list>
#include <deque>

const int SIZE = 3000000;

template<typename T, template<class> class Container>
class XCls{
    Container<T> c;
public:
    XCls() {
        for(long i=0; i<SIZE; i++)
            c.insert(c.end(), T());

        output_static_data(T());
        Container<T> c1(c);
        Container<T> c2(std::move(c));
        c1.swap(c2);
    }
};

class MyString{};
class MyStrNoMove{};

template<class T>
using Vec = std::vector<T, std::allocator<T>>;

template<class T>
using Lst = std::list<T, std::allocator<T>>;

template<class T>
using Deq = std::deque<T, std::allocator<T>>;

void output_static_data(const MyString&) {
    // 根据需要实现该函数的定义
}

int main() {
    XCls<MyString, Vec> c1;
    // XCls<MyStrNoMove, Vec> c2;

    return 0;
}