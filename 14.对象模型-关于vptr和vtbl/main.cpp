#include <iostream>

using namespace std;

// c++编译器看见一个函数后
// 1.静态绑定：call xxxx
// 2.动态绑定：指针调用向上转型up-cast
//   调用虚函数
//   (*(p->vptr)[n])(p);
//       ||
//   (*p->vptr[n])(p);

namespace lz01{
    class A{
        int m_data1, m_data2;
    public:
        virtual void vfunc1(){
            cout << "A::virtual vfunc1()" << endl;
        }
        virtual void vfunc2(){
            cout << "A::virtual vfunc2()" << endl;
        }
        void func1();
        void func2();
    };
// +-------------------------+
// |          Object A       |
// +-------------------------+
// |  vptr --------------->  |
// |  m_data1                |
// |  m_data2                |
// +-------------------------+

    class B: public A{
        int m_data3;
    public:
        virtual void vfunc1(){
            cout << "B::virtual vfunc1()" << endl;
        }
        void func2();
    };
// +-------------------------+
// |          Object B       |
// +-------------------------+
// |  vptr --------------->  |
// |  m_data1                |
// |  m_data2                |
// |  m_data3                |
// +-------------------------+

    class C: public B{
        int m_data1, m_data4;
    public:
        virtual void vfunc1(){
            cout << "C::virtual vfunc1()" << endl;
        }
        void func2();
    };
// +-------------------------+
// |          Object C       |
// +-------------------------+
// |  vptr --------------->  |
// |  Class A::m_data1       |
// |  m_data2                |
// |  m_data3                |
// |  m_data1                |
// |  m_data4                |
// +-------------------------+

    void process() {
        A a;
        B b;
        C c;
        // cout << sizeof(A) << endl;
        // cout << sizeof(B) << endl;
        // cout << sizeof(C) << endl;
        a.vfunc1();
        a.vfunc2();
        b.vfunc1();
        b.vfunc2();
        c.vfunc1();
        c.vfunc2();

        C* pc = &c;
        // (*(p->vptr)[n])(p);
        // ||
        // (*p->vptr[n])(p);
    }
}

int main() {
    lz01::process();

    return 0;
}