#include <iostream>

using namespace std;

// Template Method
// 模板模式
class CDocument {
public:
    void OnFileOpen() {
        cout << ":OnFileOpen() called" << endl;
        Serialise();
    }

    virtual void Serialise() = 0;
};

class MyDoc : public CDocument {
public:
    virtual void Serialise() override {
        cout << ":Serialise() called" << endl;
    }

    static void SerialiseWrapper(MyDoc* obj) {
        obj->Serialise();
    }
};

int main() {
    MyDoc myDoc;

    // // 通过静态成员函数间接调用成员函数
    // void (*serialisePtr)(MyDoc*) = &MyDoc::SerialiseWrapper;
    // serialisePtr(&myDoc);

    // // 打印成员函数的地址
    // void* address = reinterpret_cast<void*>(serialisePtr);
    // cout << "Address of Serialise(): " << address << endl;

    myDoc.OnFileOpen();

    return 0;
}
