#include <iostream>
using namespace std;

class A{
public:
    A(int x=0): m_x(x){}
    void func1() {
        cout << "non-static func1" << endl;
    }

    // 没有this pointer 独立于对象
    // 作为类方法使用
    // 只能处理静态数据
    static void func2(const int& x) {
        // this->m_y = x;
        m_y = x;
        cout << "static func2" << endl;
    }
private:
    int m_x;
    static int m_y;
};
// 必须类外初始化
int A::m_y = 5;

class Singleton{
private:
    Singleton() {
        cout << "Singleton init..." << endl;
    }
    Singleton(const Singleton&);
    // static Singleton s_singleton; 放入getInstance()
public:
    static Singleton& getInstance(){
        static Singleton s_singleton;
        return s_singleton;
    }
    void setup(){
        // ...
        cout << "Singleton setup()..." << endl;
    }
};
// Singleton Singleton::s_singleton;

int main(){

    A a1, a2, a3;
    
    a1.func1();

    // static函数的2种调用方法
    // 对象调用
    // 类：：方法名调用
    a1.func2(10);
    A::func2(9);
    // ================================

    Singleton::getInstance().setup();

    return 0;
}