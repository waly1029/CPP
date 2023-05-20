#ifndef MYSTRNOMOVE_H
#define MYSTRNOMOVE_H

#include <string>
// #include <iostream>

class MyStrNoMove{
public:
// 计数用counter
    static size_t DCtor;    // 累计default-ctor调用次数
    static size_t Ctor;     // 累计ctor调用次数
    static size_t CCtor;    // 累计copy-ctor调用次数
    static size_t CAsgn;    // 累计copy-asgn调用次数—— operator=
    static size_t MCtor;    // 累计move-ctor调用次数
    static size_t MAsgn;    // 累计move-asgn调用次数—— operator=
    static size_t Dtor;     // 累计dctor调用次数—— 析构函数
private:
    char* _data;
    size_t _len;
    void _init_data(const char* s) {
        _data = new char[_len+1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    // default-ctor
    MyStrNoMove(): _data(nullptr), _len(0) { ++DCtor; }

    // ctor
    MyStrNoMove(const char* p): _len(strlen(p)) { 
        ++Ctor; 
        _init_data(p);
    }

    // copy constructor
    MyStrNoMove(const MyStrNoMove& other): _len(other._len) {
        ++CCtor; 
        _init_data(other._data);    //copy
    }

    // move constructor, with "noexcept"
    // MyStrNoMove(MyStrNoMove&& other) noexcept : _len(other._len), _data(other._data) {
    //     ++MCtor; 
    //     other._len = 0;
    //     other._data = nullptr;  // 重要
    //                             // 需要结合析构函数来看
    //                             // 如果为nullptr 
    // }

    // copy assignment
    MyStrNoMove& operator=(const MyStrNoMove& other) {
        if(_data != other._data) {
            if(_data != nullptr) delete _data;
            _len = other._len;
            _init_data(other._data);    // copy
        }
        else{}

        return *this;
    }

    // move assignment with noexcept 
    // MyStrNoMove& operator=(MyStrNoMove&& other) {
    //     ++MAsgn;
    //     if(_data != other._data) {
    //         if(_data != nullptr) delete _data;
    //         _len = other._len;
    //         _data = other._data;    // move
    //         other._data = nullptr;  // 重要
    //         other._len = 0;
    //     }
    //     else{}
    //     return *this;
    // }

    // dctor
    virtual ~MyStrNoMove() {
        ++DCtor;
        // if(_data != nullptr)    // 因为使用了move所以需要此处结合使用
            delete _data;
    }

    // 为了set
    bool operator<(const MyStrNoMove& other) {
        // 借用std::string比较大小
        return std::string(_data) < std::string(other._data);
    }

    // 为了set
    bool operator==(const MyStrNoMove& other) {
        // 借用std::string比较大小
        return std::string(_data) == std::string(other._data);
    }

    char* get() const { return _data; }

};
size_t MyStrNoMove::DCtor = 0;    // 累计default-ctor调用次数
size_t MyStrNoMove::Ctor = 0;     // 累计ctor调用次数
size_t MyStrNoMove::CCtor = 0;    // 累计copy-ctor调用次数
size_t MyStrNoMove::CAsgn = 0;    // 累计copy-asgn调用次数—— operator=
size_t MyStrNoMove::MCtor = 0;    // 累计move-ctor调用次数
size_t MyStrNoMove::MAsgn = 0;    // 累计move-asgn调用次数—— operator=
size_t MyStrNoMove::Dtor = 0;     // 累计dctor调用次数—— 析构函数

namespace std{
    template<>
    struct hash<MyStrNoMove> {
        size_t operator()(const MyStrNoMove& s) const noexcept{
            return hash<string>()(string(s.get()));
        }
    };
}

#endif