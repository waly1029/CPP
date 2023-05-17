#ifndef MYSTRING_H
#define MYSTRING_H
#include <string>
#include <iostream>

class MyString{
private:
    char* m_data;
    // class有指针member时 必须有copy ctor和 copy op=
public:
    // 构造函数
    MyString(const char* cstr = nullptr);

    // 复制构造函数
    MyString(const MyString& str);

    // =重载
    MyString& operator=(const MyString& str);

    // 析构函数
    ~MyString();

    // const不做改变并且保护私有成员m_data不暴露给<<全局重载
    char* get_c_str() const { return m_data; }
};

//class methods=====================================================================
inline
// 默认参数只能在定义或者声明中一个地方定义
// MyString(const char* cstr = nullptr);
MyString::MyString(const char* cstr) {
    if(cstr) {
        m_data = new char[strlen(cstr) + 1];
        // strcpy会默认拷贝上最后的\0
        strcpy(m_data, cstr);
    }
    else {
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
MyString::MyString(const MyString& str) {
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

inline
MyString& MyString::operator=(const MyString& str) {
    // 自我检测,自我赋值
    // 若没有自我检测，那么会执行delete行
    // 之后的语句就无法分配空间会出错
    if(this == & str) return *this;

    delete[] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);

    return *this;
}

inline
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    return os << str.get_c_str();
}

inline
MyString::~MyString () {
    delete[] m_data;
}
//class methods end=================================================================



//Global-functions=====================================================================

//Global-functions end=================================================================


#endif