·Inheritance（继承）

·Composition（组合）

·Delegation （委托）

<p style="font-size: 200px;">#Composition（组合），表示has-a</p>


queue◆-->deque

```C++
template <class T>
class queue{
// ...
protected:
    deque<T> c; // 底层容器
public:
    // 以下完全利用c的操作函数完成
    bool empty() { return c.empty(); }
    size_type size() const { return c.size(); }
    reference front() { return c.front(); }
    reference back() { return c.back(); }
    // 
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_front(); }
};
```

Container◆-->Component

·构造由内而外

Container::Container(...):Component() {...};

·析构有外而内

Container::~Container(...) {... ~Component()};

Delegation（委托）/ Composition by reference

·String◇-->StringRep

```C++ Standard
// file String.hpp
class StringRep;
class String{
public:
    String();
    String(const char* s);
    String(const String& s);
    String& operator=(const String& s);
    ~String();
private:
    StringRep* rep; // pimpl 委托
};
```

```C++
// file StringRep.hpp
#include "String.hpp"
namespace {
class StringRep {
friend class String;
StringRep(const char* s);
~StringRep();
int count;
char* rep;
};
}

String::String() { ... }
```