#include <iostream>
#include <string>

using namespace std;

namespace lz01{

    void test01(){
        int i;      // 未定义value
        int j{};    // 默认0
        int* p;     // 未定义value
        int* q{};   // 默认nullptr

        int x1(5.3);
        cout << x1 << endl;
        int x2 = 5.3;
        cout << x2 << endl;
        // int x3{5.0};
        // cout << x3 << endl;
        // int x4 = {5.3};
        // cout << x4 << endl;
        char c1{7};
        cout << c1 << endl;
        // char c2{99999};
        // cout << c2 << endl;
        // vector<int> v1{1,2,3,4,5};
        // vector<int> v2{1,2.3,4,5};
    }

}

namespace lz02{

    void print(initializer_list<int> vals) {
        for(auto p=vals.begin(); p!=vals.end(); ++p) {
            cout << *p << endl;
        }
    }

    class P{
    public:
        P(int a, int b){
            cout << "P(int, int), a=" << a << ", b=" << b << endl;
        }

        // 若下面的构造函数不存在
        // 则r{1,2,3};会报错
        // 其中1,2,3为三个参数多余了上面的构造函数参数数量
        // 编译器拆解之后也无法通过
        // 因此需要判断P(int a, int b)参数个数之后
        // 与 r{1,2,3...,}; {}中的个数进行比较
        // 必须一致才可通过编译
        P(initializer_list<int> initlist) {
            cout << "size = " << initlist.size() << endl;
            cout << "P(initializer_list<int>), values=";
            for(auto i: initlist)
                cout << i << ',';
            cout << endl;
        }
    };

    void func1(){
        P p(11, 2);
        P q{12, 2};
        P r{1,2,3};
        P s = {5,6,7,8};
        P m{1};
    }
}

namespace lz03{
    void func1(){
        cout << max(string("ABC"), string("AAC")) << endl;
        cout << max({string("ABC"), string("AAC"), string("DEF"), string("GHI")}) << endl;
        cout << min({52,4,12,3}) << endl;
        cout << max({52,4,12,3}) << endl;
        // 某些算法使用到了initialize_list
        // 因此可以通过使用{}在其中引入多个参数
        // template<class _Tp>
        // inline
        // min(initializer_list<_Tp> __l) {
        //     return *std::min_element(__l.begin(), __l.end());
        // }
    }
}

int main(){

    // lz01::test01();
    // lz02::print({1,2,3,4,5});
    // lz02::func1();
    lz03::func1();

    return 0;
}