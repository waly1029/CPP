#include <iostream>
using namespace std;

class Component{
public:
    Component(){
        cout << "Component()" << endl;
    }
    ~Component(){
        cout << "~Component()" << endl;
    }
};

class Base{
    Component comp;
public:
    Base(){
        cout << "Base()" << endl;
    }
    ~Base(){
        cout << "~Base()" << endl;
    }
};

class Derived: public Base{
    // Component comp;
public:
    Derived(){
        cout << "Derived()" << endl;
    }
    ~Derived(){
        cout << "~Derived()" << endl;
    }
};

int main() {
    Derived derived;

    return 0;
}
