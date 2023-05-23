#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

void ostream_iterator_test(){

    vector<int> v;
    for(int i=0; i<10; i++)
        v.push_back(i*10);

    ostream_iterator<int> out_it(cout, ",");

    copy(v.begin(), v.end(), out_it);

}

void istream_iterator_test1() {
    double v1, v2;
    cout << "Please, insert two values:";

    istream_iterator<double> eos; // end-of-stream,只要无参就是结束符
    istream_iterator<double> iit(cin);
    if(iit!=eos) v1 = *iit;

    ++iit;

    if(iit!=eos) v2 = *iit;

    cout << v1 << "*" << v2 << "=" << (v1*v2) << endl;
}

void istream_iterator_test2() {
    list<int> c{1, 2, 3, 4};
    istream_iterator<int> iit(cin), eos;

    while (iit != eos) {
        int value = *iit;
        if (value == -1) {  // 终止条件：输入 -1 停止读取
            break;
        }
        c.push_back(value);
        ++iit;
    }

    // 输出结果
    for (const auto& value : c) {
        cout << value << " ";
    }
    cout << endl;
}


int main() {

    // istream_iterator_test1();

    istream_iterator_test2();


    return 0;
}