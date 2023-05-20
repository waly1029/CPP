// 右值引用是一种类型
// 解决： 不必要的拷贝；

// Lvalue：可以出现于 operator= 左侧
// Rvalue：只能出现于 operator= 右侧

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <unordered_set>
#include "mystring.h"
#include "mystrnomove.h"
#include <typeinfo> //typeid()

namespace ex01{
    // #include <iostream>
    #include <string>
    // using namespace std;

    void test_int() {

        int a = 9;
        int b = 4;

        a = b;
        b = a;
        a = a + b;

        // a + b = 42;  // a+b为右值
    }


    void test_string(){
        std::string s1{"Hello"};
        std::string s2{"lz"};
        s1 + s2 = s2;
        std::cout << "s1 " << s1 << std::endl;
        std::cout << "s2 " << s2 << std::endl;

        // warning: braces around scalar initializer [-Wbraced-scalar-init]
        // string() = {"The World!"}; // 右值可以给临时对象
    }

    class MyComplex{
    public:
        int real;
        int imag;
    public:
        MyComplex(): real(0), imag(0) {}
        MyComplex(int r, int i): real(r), imag(i) {}
        MyComplex operator+(const MyComplex& other) {
            return MyComplex(real+other.real, imag+other.imag);
        }
    };
    std::ostream& operator<<(std::ostream& os, const MyComplex& mc){
        os << "(";
        os << mc.real << ", " << mc.imag << ")";
        return os;
    }
    void test_mycomplex(){
        MyComplex c1(3, 8), c2(1, 0);
        c1 + c2 = MyComplex(4, 9);
        std::cout << "c1:" << c1 << std::endl;
        std::cout << "c2:" << c2 << std::endl;
        // 临时对象是一种右值，不可以放在左边
        MyComplex() = MyComplex(4, 9);
    }

    int foo() { return 0; }
    void test_foo(){
        int x = foo();
        // int* p = &foo();    // cannot take the address of an rvalue of type 'int'
        // foo() = 7;          // expression is not assignable
    }
}

namespace ex02{

    template<typename T>
    void output_static_data(const T& myStr) {
        std::cout << "typeid(myStr).name(): " << typeid(myStr).name() << " -- " << std::endl;
        std::cout << "CCtor=" << T::CCtor
             << " MCtor=" << T::MCtor
             << " CAsgn=" << T::CAsgn
             << " MAsgn=" << T::MAsgn
             << " Dtor=" << T::Dtor
             << " Ctor=" << T::Ctor
             << " DCtor=" << T::DCtor
             << std::endl;
    }

    template<typename M, typename NM>
    void test_moveable(M c1, NM c2, long& value) {
        char buf[10];

        // 测试moveable
        typedef typename std::iterator_traits<typename M::iterator>::value_type V1type;
        clock_t timeStart = clock();
        for(long i = 0; i <value; ++i) {
            snprintf(buf, 10, "%d", rand());
            auto ite = c1.end();
            c1.insert(ite, V1type(buf));
        }
        std::cout << "construction milli-seconds: " << (clock() - timeStart) << std::endl;
        std::cout << "size()= " << c1.size() << std::endl;
        output_static_data(*(c1.begin()));

        M c11(c1);
        M c12(std::move(c1));        // 确定以后不使用这个变量利用move
        c11.swap(c12);
    }

}

namespace ex03{

    void process(int& i) {
        std::cout << "process(int&): " << i << std::endl;
    }
    void process(int&& i) {
        std::cout << "process(int&&): " << i << std::endl;
    }

    void forward(int&& i) {
        std::cout << "forward(int&&)" << i << ",";
        process(i);
    }

    void test_unperfect_forwarding() {
        int a = 0;
        process(a);                 // process(int&): 0
                                    // a被视为左值，通常认知

        process(1);                 // process(int&&): 1
                                    // 临时obj被视为右值，通常认知

        process(std::move(a));      // process(int&&): 0
                                    // 标准库的move强制把变量a从左值变为右值

        forward(2);                 // forward(int&&): 2 -> process(int&): 2
                                    // 类似于vector.insert(MyClass())
                                    // insert有2个版本，普通的深拷贝&和移动的&&
                                    // 2为右值，forward(int&&)没问题
                                    // 但是第二次却变成了process(int&)调用？？
                                    // 从一个右值变成了左值
                                    // 原因是传递过程中右值2变成了一个：named object

        forward(std::move(a));      // forward(int&&): 0, process(int&): 0;
                                    // Rvalue经由forward()传出去变成了Lvalue

        // forward(a);              // candidate function not viable: expects an rvalue for 1st argument
                                    // a是左值，forward需要右值编译不了

        const int& b = 1;
        // process(b);
        // process(std::move(b));

        // int& x(5);

        // process(std::move(x));
    }
}

int main() {

    // ex01::test_int();
    // ex01::test_string();
    // ex01::test_mycomplex();
    // ex01::test_foo();

    long value = 3000000L;
    ex02::test_moveable(std::vector<MyString>(), 
                        std::vector<MyStrNoMove>(), 
                        value);
    // vector
    // MCtor 7194303因为vector会成长
    // construction milli-seconds: 510514
    // size()= 3000000
    // typeid(myStr).name(): 8MyString -- 
    // CCtor=0 MCtor=7194303 CAsgn=0 MAsgn=0 Dtor=0 Ctor=3000000 DCtor=7194303

    // list
    // construction milli-seconds: 564071
    // size()= 3000000
    // typeid(myStr).name(): 8MyString -- 
    // CCtor=0 MCtor=3000000 CAsgn=0 MAsgn=0 Dtor=0 Ctor=3000000 DCtor=3000000

    // deque
    // construction milli-seconds: 575499
    // size()= 3000000
    // typeid(myStr).name(): 8MyString -- 
    // CCtor=0 MCtor=3000000 CAsgn=0 MAsgn=0 Dtor=0 Ctor=3000000 DCtor=3000000

    // multiset
    // construction milli-seconds: 10627916
    // size()= 3000000
    // typeid(myStr).name(): 8MyString -- 
    // CCtor=0 MCtor=3000000 CAsgn=0 MAsgn=0 Dtor=0 Ctor=3000000 DCtor=3000000

    // unordered_multiset
    // construction milli-seconds: 3221057
    // size()= 3000000
    // typeid(myStr).name(): 8MyString -- 
    // CCtor=0 MCtor=3000000 CAsgn=0 MAsgn=0 Dtor=0 Ctor=3000000 DCtor=3000000


    // ex03::test_unperfect_forwarding();

    return 0;
}