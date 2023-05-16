#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>
#include <iostream>

using namespace std;

template <typename T>
class complex;

template <typename T>
complex<T>& __doapl(complex<T>* ths, const complex<T>& r);

// 测试类中<>
template <typename T>
void print(const complex<T>& c);

template<class T>
class complex{
private:
    T re, im;
    friend complex& __doapl<>(complex* ths, const complex&);
    friend void print<>(const complex& c);
    // 注意下面友元的错误用法
    // friend void print(const complex& c);
public:
    // =====================================================================
    // 有参函数的初始化列表
    // *************explicit 禁止隐士转换！！！！！*****************************
    explicit complex(T r=0, T i=0): re(r), im(i) {
        // 这里是赋值比初始化列表效率低多一个步骤
        // this.re = r;
        // this.im = i;
    }
    // 无参构造函数,此情况下，有参构造函数有默认值，所以下面这个无参构造函数会报错
    // complex(): re(0), im(0) {}
    // =====================================================================

    complex& operator+=(const complex&);
    complex& operator+=(T value) {
        this->re += value;
        return *this;
    }

    // 当有全局和类中都重载了运算符优先类中的重载
    complex& operator+(const complex&);

    // 由于类中重载运算符只有一个参数的情况
    // 只能作为     operator+(T, const complex<T>&)
    // 而无法作为   operator+(const complex<T>&, T)
    // complex& operator+(T other) {
    //     cout << "class T+" << endl;
    //     re += other;
    //     return *this;
    // }
    complex operator-() const {
        cout << "class 取反" << endl;
        return complex(-re, -im);
    }

    // 本体中编译器会尽量做到inline,简单函数
    // 同名函数重载
    T real() const { return re; }      // ?real@Complex@QBENXZ 函数编译后的实际名称
    complex& real(T r) { 
        this->re = r;
        return *this;   // 可以进行链式调用形如 c.real(1.0).imag(2.0)
    }                                       // ?real@Complex@AENABN@Z

    // class中方法有会改变和不改变2种分类
    // const
    T imag() const { return im; }

    // 共轭复数
    complex conj() const {
        return complex(re, -im);
    }
};

template<class T>
complex<T>& complex<T>::operator+=(const complex<T>& other) {
    // this->re += other.re;
    // this->im += other.im;
    // return *this;
    cout << "real= " << this->re << "+" << other.re << endl;
    cout << "imag= " << this->im << "+" << other.im << endl;
    return __doapl(this, other);
}

template<class T>
complex<T>& complex<T>::operator+(const complex<T>& other) {
    this->im += other.im;
    this->re += other.re;
    cout << "class+" << endl;
    return *this;
}

template<class T>
inline complex<T>& __doapl(complex<T>* ths, const complex<T>& r) {
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

template<class T>
inline void print(const complex<T>& c) {
    cout << "(" << c.re << ", " << c.im << ")" << endl;
    
}

template<class T>
// 返回为局部生成的complex临时对象所以无法返回引用
inline complex<T> operator+(const complex<T>& ths, const complex<T>& other) {
    cout << "global+" << endl;
    // 返回的是临时complex对象 -> typename();
    return complex<T>(ths.real()+other.real(), ths.imag()+other.imag());
}

template<class T>
inline complex<T> operator+(const complex<T>& ths, T other) {
    cout << "global complex+T" << endl;
    // 返回为局部生成的complex临时对象所以无法返回引用
    return complex<T>(ths.real()+other, ths.imag());
}

template<class T>
inline complex<T> operator+(T other, const complex<T>& ths) {
    cout << "global T+complex" << endl;
    // 返回为局部生成的complex临时对象所以无法返回引用
    return complex<T>(ths.real()+other, ths.imag());
}

template<class T>
inline complex<T> operator-(const complex<T>& ths, const complex<T>& other) {
    cout << "global-" << endl;
    // 返回为局部生成的complex临时对象所以无法返回引用
    return complex<T>(ths.real()-other.real(), ths.imag()-other.imag());
}

// 正号根据参数个数判断
// 为什么返回不是引用
template<class T>
inline complex<T> operator+(const complex<T>& ths) {
    return ths;
}

// 取反
template<class T>
inline complex<T> operator-(const complex<T>& ths) {
    cout << "global 取反" << endl;
    return complex<T>(-ths.real(), -ths.imag());
}

// == 重载
template<class T>
inline bool operator==(const complex<T>& ths, const complex<T>& other) {
    return ths.real() == other.real() 
        && ths.imag() == other.imag();
}

template<class T>
inline bool operator==(const complex<T>& ths, T other) {
    return ths.real() == other 
        && ths.imag() == 0;
}

template<class T>
inline bool operator==(T other, const complex<T>& ths) {
    return ths.real() == other 
        && ths.imag() == 0;
}
//!= 重载
// ...

// 重载<<
template<class T>
ostream& operator<<(ostream& os, const complex<T>& ths) {
    return os << "(" << ths.real() << "," << ths.imag() << "i)";
}

#endif