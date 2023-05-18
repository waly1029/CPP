#include <iostream>
using namespace std;

class Test{
public:
    Test(int a=0): num(a) { cout << "Test 构造..." << this << endl; }
    ~Test(){ cout << "Test 析构..." << this << endl; }
private:
    int num;
};

int g = 0;

int main() {

    {
        static int m = 5;
        Test a;
        
        // new 可以被认为是如下步骤调用
        Test* b = new Test(5);
        // ****************************
        // Test* b;
        // void* mem = operator new(sizeof(Test)); // 分配内存
            // ↑
            // 内部调用malloc(n)
        // b = static_cast<Test*>(mem);            // 强制类型转换
        // b->Test::Test(5);                       // 构造函数
            // ↓
            // Test::Test(b, 5);  b也就是this
        // ****************************

        // delete可以被认为如下步骤调用
        // 若类中有指针member则实际上是删除了2次
        // 第一次是调用了此指针类中的指针成员的删除(class内部的例如MyString中的 char* m_data)
        // 第二次是这个b，也就是指向new出来的指针类的成员（此时这个成员是一个指针 Test* b）
        delete b;
        // ============================
        // Test::~Test(b);                             // 析构函数
        // operator delete(b);                         // 释放内存
            // ↓
            // 其内部调用free(b)
        // ============================
    }

    // delete b;

    Test* t = new Test[3];
    // 只会删除第一个指针，后面的指针会内存泄露
    // delete t;
    
    delete []t;

    return 0;
}