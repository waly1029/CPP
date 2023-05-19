#include <iostream>
#include <vector>

using namespace std;

namespace lz01{
    template<typename T>
    using Vec = vector<T, ::allocator<T>>;

    // #define Vec<T> template<typename T> vector<T, MyAlloc<T>>;
    // Vec<int> coll;
    //     ||
    // template<typename T> vector<int, MyAlloc<int>>;  // 错误

    // typedef vector<int, MyAlloc<int>> Vec; // 错误
    

    // ****************************************************************
    // 天方夜谭
    // void test_moveable(Container cntr, T elem) {
        // Container<T> c;                  // 创建一个容器

    //     for(long i=0; i<SIZE; ++i)       // 放入大量数据
    //         c.insert(c.end(), T());

    //     output_static_data(T());
    //     Container<T> c1(c);              // 使用复制构造
    //     Container<T> c2(std::move(c));   // CPP11新特性move测试时间
    //     c1.swap(c2);                     // 测试交换
    // }

    // test_moveable(list, MyString); //不可能传入一个list 需要的是一个list对象
    // test_moveable(list, MyStrNoMove);
    // 于是改动如下：
                // ||
                // ||
                // ↓↓
    // ****************************************************************
    // 天方夜谭
    // 尝试使用Template来做Container，但是不可以 [Error] 'Container'is not a template
    // template<typename Container, typename T>
    // void test_moveable(Container cntr, T elem) {
    //     Container<T> c;                  // [Error] 'Container'is not a template
    //     typename Container<T> c;         // [Error] expected nested-name-specifier before 'Container'
    //     for(long i=0; i<SIZE; ++i)
    //         c.insert(c.end(), T());

    //     output_static_data(T());
    //     Container<T> c1(c);
    //     Container<T> c2(std::move(c));
    //     c1.swap(c2);
    // }
    // test_moveable(list(), MyString());
    // test_moveable(list(), MyStrNoMove());
    // 于是改动如下：
                // ||
                // ||
                // ↓↓
    // ****************************************************************
    const int SIZE = 10000000;

    template <typename T>
    void output_static_data(const T& obj) {
        // cout <<
    }

    // 有没有template语法能够在模版接受一个template参数Container时
    // 当Container本身又是一个class template，能取出Container的template参数？
    // 例如收到一个vector<string>,能够取出其元素类型string？
    template<class Container>
    void test_moveable(Container c) {
        typedef typename iterator_traits<typename Container::iterator>::value_type Valtype;

        for(long i=0; i<SIZE; ++i) {
            c.insert(c.end(), Valtype());
        }

        output_static_data(*(c.begin()));
        Container c1(c);
        Container c2(std::move(c));
        c1.swap(c2);
    }
    class MyString{
        // ...
    };
    class MyStrNoMove{
        // ...
    };
    void func(){
        // 于是可以传入类型了
        test_moveable(vector<MyString>());
        test_moveable(vector<MyStrNoMove>());
    }
}

int main(){


    return 0;
}