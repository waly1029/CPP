#include <iostream>

using namespace std;

namespace lz01{
    class Zoo{
        int d1, d2;
    public:
        // 注意：
        // 如果自定义一个ctor，编译器就不会再生成默认的ctor
        // 当然单独的class中可能没有什么用
        // 当有继承关系的时候，默认构造函数就会帮你实现父类的继承

        // 如果你强制加上=default，就可以重新获得并使用default ctor
        Zoo(int i1, int i2): d1(i1), d2(i2) {}
        Zoo(const Zoo&) = delete;
        Zoo(Zoo&&) = default;
        Zoo& operator=(const Zoo&) = default;
        Zoo& operator=(const Zoo&&) = delete;
        virtual ~Zoo() {}
    };
}

namespace lz02{
    class Foo{
        int _i;
    public:
        Foo(int i): _i(i) {}
        Foo() = default;    // 可以和上一个并存（ctor可以多个并存）

        Foo(const Foo& x): _i(x._i) {}
        //! Foo(const Foo&) = default; //[Error] 'Foo::Foo(const Foo&)' cannot be overloaded
        //! Foo(const Foo&) = delete; //[Error] 'Foo::Foo(const Foo&)' cannot be overloaded

        Foo& operator=(const Foo& x) { _i = x._i; return *this; }
        //! Foo& operator=(const Foo&) = default; //[Error] 'Foo& Foo::operator=(const Foo&)' cannot be overloaded
        //! Foo& operator=(const Foo&) = delete; //[Error] 'Foo& Foo::operator=(const Foo&)' cannot be overloaded

        //! void func1() = default; //“= default”只能出现在默认构造函数、复制/移动构造函数、复制/移动赋值运算符和析构函数中C/C++(1774)
        void func2() = delete; //ok

        //! ~Foo() = delete; //这会造成使用Foo foo时出错=>无法引用 函数 "lz02::Foo::~Foo() noexcept" (已声明 所在行数:42) -- 它是已删除的函数
        ~Foo() = default; //ok
    };

    // 总结
    // =default用于big-five(构造，复制构造，operator=，析构，移动move)之外：-》无意义，编译报错
    // =delete；可以用于任何函数身上（=0只能用于virtual函数）

    // big-three
    // 如果一个类有指针成员，几乎可以断定需要自己写big-three
    // 因为指针的默认拷贝等只是浅拷贝
    // 如果一个类没有指针成员，绝大部分用默认的big-three就可以


    void func1(){
        Foo foo(5);
        Foo foo2(foo);
        Foo foo3 = foo;
        foo3 = foo2;
    }
}

int main(){
    lz02::func1();

    return 0;
}