#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <typeinfo> // typeid

using namespace std;

// 五种iterator category
// struct input_iterator_tag {};
// struct ouput_iterator_tag {};
// struct forward_iterator_tag: public input_iterator_tag {};
// struct bidirectional_iterator_tag: public forward_iterator_tag {};
// struct random_access_iterator_tag: public bidirectional_iterator_tag {};

namespace lz01{
    void _display_category(random_access_iterator_tag) {
        cout << "random_access_iterator" << endl;
    }
    void _display_category(bidirectional_iterator_tag) {
        cout << "bidirectional_iterator" << endl;
    }
    void _display_category(forward_iterator_tag) {
        cout << "forward_iterator" << endl;
    }
    void _display_category(output_iterator_tag) {
        cout << "output_iterator" << endl;
    }
    void _display_category(input_iterator_tag) {
        cout << "input_iterator" << endl;
    }

    template<class I>
    void display_category(I itr){
        // 提问iterator_traits<I>::iterator_category
        typename iterator_traits<I>::iterator_category cagy;
        _display_category(cagy);

        cout << "typeid(itr).name()= " << typeid(itr).name() << endl << endl;
        // The output depends on library implementation.
        // THe particular representation pointed by the returned value's implementation-defined.
        // and may or may not be different from different types.
    }

    void test_iterator_category() {
        cout << "\ntest_iterator_category().............." << endl;

        display_category(array<int, 10>::iterator());
        display_category(vector<int>::iterator());
        display_category(list<int>::iterator());
        display_category(forward_list<int>::iterator());
        display_category(deque<int>::iterator());

        display_category(set<int>::iterator());
        display_category(map<int, int>::iterator());
        display_category(multiset<int>::iterator());
        display_category(multimap<int, int>::iterator());
        display_category(unordered_set<int>::iterator());
        display_category(unordered_map<int, int>::iterator());
        display_category(unordered_multiset<int>::iterator());
        display_category(unordered_multimap<int, int>::iterator());

        display_category(istream_iterator<int>::iterator());
        display_category(ostream_iterator<int>(cout, ""));
    }
}

int main() {

    lz01::test_iterator_category();

    return 0;
}