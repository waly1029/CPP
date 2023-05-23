#include <iostream>
#include <list>

using namespace std;

int main () {

    list<int> foo, bar;
    for(int i = 1; i <= 5; ++i) {
        foo.push_back(i);
        bar.push_back(i*10);
    }

    auto it = foo.begin();
    advance(it, 3);

    copy(bar.begin(), bar.end(), inserter(foo, it));

    for(auto i = foo.begin(); i != foo.end(); ++i)
        cout << *i << endl;

    return 0;
}