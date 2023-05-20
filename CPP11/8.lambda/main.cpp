// lambda 当做参数或者一个local obj, 或inline function
// lambda 改变了c++STL使用方式

#include <iostream>
#include <vector>

using namespace std;

namespace lz01{
    // warning: expression result unused [-Wunused-value]
    // 是一个类型,只是定义了一个函数并未使用
    // 如下：
    void lambda_test01(){
        []{
            cout << "test01 hello lambda" << endl;
        };
    }


    // 最后加上()就是直接调用
    void lambda_test02(){
        []{
            cout << "test02 hello lambda" << endl;
        }();    // 打印输出，直接调用
    }

    // pass it to objects to get called
    void lambda_test03(){
        auto l = [] {
            cout << "test03 hello lambda" << endl;
        };
        // ...
        l();    // 打印输出
    }
}

// lambda 一般表达式
// mu throw ret都是可选
// 如果写了任意一个就需要加入()
// [...](...)mutable throwSpec ->retType {...}
//   ↑    ↑ 放入参数
//   ↑      外部变量

namespace lz02{
    class Functor{
        int id;
    public:
        void operator()(){
            cout << "id:" << id << endl;
            ++id;
        }
    };

    void lambda_test01(){
        int id = 0;
        // 注意[id]和[&id]
        // mutable可变的，不写mutable不能++id
        // 只有在创建f表达式的时候捕获一次外部id
        // 之后使用的++id递增的只是这个第一次捕获的id
        // 与外界的id没有影响
        auto f = [id]()mutable{
            cout << "test01 id:" << id << endl;
            ++id;
        };
        f();
        id = 42;
        f(); f(); f();
        cout << id << endl;
        // 0 1 2 42
    }
    void lambda_test02(){
        int id = 0;
        auto f = [&id](int param){
            cout << "test02 id:" << id << endl;
            cout << "test02 para:" << param << endl;
            ++id;
            ++param;
            static int si = 0;
            si++;
            cout << "test02 si:" << si << endl;
        };
        id = 42;
        f(7); f(7); f(7);
        cout << id << endl;
        // id: 42 43 44 45 para:7 7 7
    }
    void lambda_test03(){
        int id = 0;
        // Error 需要加入mutable
        // increment of read-only variable 'id'
        auto f = [id]() mutable {
            cout << "test03 id:" << id << endl;
            ++id;
        };
        id = 42;
        f(); f(); f();
        cout << id << endl;
        // 0 1 2 42
    }
}

namespace lz03{
    void lambda_test01(){
        vector<int> vi {99,5, 28, 50,83,70,590,245,59,24};
        int x = 30;
        int y = 100;
        vi.erase(remove_if(vi.begin(),vi.end(),
                    [x,y](int n){
                        return x<n && n<y;
                    }),
                    vi.end());
        for(auto& v: vi) cout << v << ',';
    }
}

int main() {

    // lz01::lambda_test01();
    // lz01::lambda_test02();
    // lz01::lambda_test03();

    // lz02::lambda_test01();
    // lz02::lambda_test02();

    lz03::lambda_test01();


    return 0;
}