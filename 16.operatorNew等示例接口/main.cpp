#include <iostream>
using namespace std;

class Foo{
public:
    int _id;
    long _data;
    string _str;

    Foo(): _id(0) {
        cout << "default ctor.this=" << this << " id=" << _id << endl;
    }
    Foo(int i): _id(i) {
        cout << "ctor.this=" << this << " id=" << _id << endl;
    }

    // virtual
    ~Foo() {
        cout << "dtor.this=" << this << " id=" << _id << endl;
    }

    static void* operator new(size_t size) {
        Foo* p = (Foo*)malloc(size);
        cout << "Foo::operator new(), size=" << size << "\treturn:" << p << endl;
        return p;
    }

    static void* operator new[](size_t size) {
        Foo* p = (Foo*)malloc(size);
        cout << "Foo::operator new()[], size=" << size << "\treturn:" << p << endl;
        return p;
    }

    static void operator delete(void* pdead, size_t size) {
        cout << "Foo::operator delete(), pdead=" << pdead << "\tsize= " << size << endl;
        free(pdead);
    }

    static void operator delete[](void* pdead, size_t size) {
        cout << "Foo::operator delete()[], pdead=" << pdead << "\tsize= " << size << endl;
        free(pdead);
    }
};

int main() {

    cout << "sizeof(Foo)=" << sizeof(Foo) << endl;

    // 会去找上面重载的new和delete
    Foo* pf = new Foo(7);
    delete pf;

    Foo* pArray = new Foo[5];
    delete[] pArray;

    // 若无成员方法就调用全局global
    // new 和 delete
    // 因为没有重载，所以没有输出new 和 delete信息
    // Foo* pf2 = ::new Foo;       // void* ::operator new(size_t);
    // ::delete pf2;               // void ::operator delete(void*);


    return 0;
}