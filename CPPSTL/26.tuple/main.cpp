#include <iostream>
#include <complex>
#include <tuple>
#include <string>

using namespace std;

ostream& operator<<(ostream& o, const tuple<int, int, double>& t) {
    o << "(";
    o << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << ")";
    return o;
}

int main() {

    tuple<string, int, int, complex<double> > t1;
    cout << sizeof(t1) << endl;

    tuple<float, int, string > t2(41.1, 66, "niko");
    cout << sizeof(t2) << endl;
    cout << get<0>(t2) << endl;

    auto t3 = make_tuple(1, 2, 3.14);
    cout << get<2>(t3) << endl;

    get<1>(t2) = get<1>(t3);

    cout << t3 << endl;


    typedef tuple<int, float, string> TupleType;
    cout << tuple_size<TupleType>::value << endl;
    tuple_element<1, TupleType>::type t1 = 3.14f;

    return 0;
}