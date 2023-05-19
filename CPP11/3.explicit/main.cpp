#include <iostream>
using namespace std;

namespace lz01{
    struct Complex{
        int real, imag;

        explicit
        Complex(int x, int y=0): real(x), imag(y){}

        Complex operator+(const Complex& other) {
            return Complex(real+other.real, imag+other.imag);
        }
    };

    void func01(){
        Complex c1(1, 2);

        // explicit 禁止自动类型转换
        // Complex c2 = c1 + 5;

        Complex c2 = c1 + Complex(5);
    }
}

int main(){
    lz01::func01();
    
    return 0;
}