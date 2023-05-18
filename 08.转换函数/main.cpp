#include <iostream>
#include "Fraction.h"

using namespace std;

int main() {

    Fraction f(3, 5);
    double d = f + 4;   // 调用 Fraction::operator double();
    double dd = 4 + f;

    cout << d << endl;
    cout << dd << endl;

    return 0;
}