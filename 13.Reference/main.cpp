#include <iostream>

using namespace std;

// 内存角度看变量有三种
// Java中所有变量都是引用Reference
// 指针
// 引用
// 本身

namespace lz01{
    void f1() {
        int x = 0;
        int* p = &x;
        int& r = x;

        int x2 = 5;
        r = x2;     // r不能重新代表其他物体。现在r x都是5，都是r现在所代表的物体

        int& r2 = r;      // r2是5，r2代表r以及x

        cout << ((*p)==r) << endl;
        cout << (&r==p) << endl;
        cout << ((*(&r)) == x) << endl;

        cout << sizeof(r) << endl;
    }
}

namespace lz02{
    typedef struct Stag{
        int a,b,c,d;
    } S;

    void f1(){
        double x = 0;
        double* p = &x;
        double& r = x;

        cout << sizeof(x) << endl;  // 8
        cout << sizeof(p) << endl;  // win32位:4 macOS:8
        cout << sizeof(r) << endl;  // 8

        cout << p << endl;      // a1
        cout << *p << endl;     // 0
        cout << x << endl;      // 0
        cout << r << endl;      // 0
        cout << &x << endl;     // a1
        cout << &r << endl;     // a1

        S s;
        S& rs = s;
        cout << sizeof(s) << endl;  // 16
        cout << sizeof(rs) << endl; // 16
        cout << &s << endl;         // a2
        cout << &rs << endl;        // a2
    }
}

namespace lz03{
    class Cls{
    public:
        void xxx(){
            cout << "Cls::xxx() called" << endl;
        }
    };

    void f1(Cls* pobj){
        pobj->xxx();
    }

    void f2(Cls obj){
        obj.xxx();
    }

    void f3(Cls& obj){
        obj.xxx();
    }
    // 和上面的f3二义性
    // void f3(Cls obj){ }

    void run() {
        Cls obj;
        f1(&obj);
        f2(obj);
        f3(obj);
        // reference通常不用于声明变量
        // 而是参数类型和返回值的描述
    }
}

int main() {

    // lz01::f1();

    // lz02::f1();

    lz03::run();

    return 0;
}