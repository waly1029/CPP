// Variadic Template

// template分为：
// ->function template
// ->class template

// 变化的是template parameters
// ->参数个数:利用参数个数逐一递减的特性，实现函数递归。使用function template完成。
// ->参数类型:利用参数个数逐一递减导致参数类型也注意递减的特性，实现递归继承或递归复合，以class template完成。

// {
//     void func(){}

//     template<class T, class... Types>
//     void func(const T& firstArg, const Types&... args) {
//         do sth. with firstArg
//         func(args...);
//     }
// }

#include <iostream>
using namespace std;

// 例1
namespace ex01{
    void printX(){
        cout << "无参printX()调用" << endl;
    }

    template<class T, class... Types>
    void printX(const T& firstArg, const Types&... args){
        cout << firstArg << endl;
        cout << "sizeof...(args):" << sizeof...(args) << endl;
        printX(args...);
    }
    // 上面的比较特化,下面的永远不会被调用
    //          ||
    // 上下2个可以并存
    template<class... Types>
    void printX(const Types&... args){
    }

    void test(){
        printX(1, 2.3, 'A', "breathe", bitset<16>(15));
    }
}

// 例2
// 重写printf()
namespace ex02{
    void printf(const char* s) {
        while(*s) {
            if(*s=='%' && *(++s)!='%')
                throw std::runtime_error("invalid format string: missing arguments");
            cout << *s++;
        }
    }

    template<class T, class... Types>
    void printf(const char* s, const T& value, const Types&... args) {
        while(*s) {
            if(*s=='%' && *(++s)!='%') {
                cout << value << endl;
                printf(++s, args...);
                return;
            }
            cout << *s++;
        }
        throw logic_error("extra arguments provided to printf");
    }

    void test() {
        int* pi = new int;
        printf("%d%s%p%f\n", 15, "This is an example", pi, 3.1415);

        delete pi;
    }
}


// 例3
namespace ex03{
    struct _Iter_less_iter
    {
        template<typename _Iterator1, typename _Iterator2>
        bool operator()(_Iterator1 __it1, _Iterator2 __it2) const{
            return *__it1 < *__it2;
        }
    };

    inline _Iter_less_iter __iter_less_iter() {
        return _Iter_less_iter();
    }

    template<typename _ForwardIterator, typename _Compare>
    _ForwardIterator __max_element(_ForwardIterator __first, 
                                   _ForwardIterator __last,
                                   _Compare __comp)
    {
        if(__first == __last) return __first;
        _ForwardIterator __result = __first;
        while(++__first != __last)
            if(__comp(__result, __first))
                __result = __first;
        return __result;
    }

    template<typename _ForwardIterator>
    inline _ForwardIterator max_element(_ForwardIterator __first,
                                        _ForwardIterator __last)
    {
        return __max_element(__first, __last, __iter_less_iter());
    }    

    // 可以使用initializer_list来传入多个参数
    // initializer_list背后是一个array在工作
    // 若参数types相同，不用使用variadic template
    // 使用initializer_list<T>即可
    template<typename _Tp>
    inline _Tp max(initializer_list<_Tp> __l) {
        return *max_element(__l.begin(), __l.end());
    }

    // =================================================================
    // 使用variadic template 进行比较大小
    // 单参数版本的maximum函数，这是递归的基准情况
    // 当仅剩一个参数时，这个函数会被调用，并返回该参数
    int maximum(int n){
        return n;
    }
    // 多参数版本的maximum函数，使用了变长参数模板
    // 当有多个参数时，这个函数会被调用
    template<class... Args>
    int maximum(int n, Args... args) {
        // 调用std::max函数，比较当前参数n和剩余参数中的最大值
        // maximum(args...)会递归地调用自身，找出剩余参数中的最大值
        // 如果剩余参数为空，那么会调用单参数版本的maximum函数，返回最后一个参数
        // std::max函数会比较n和剩余参数中的最大值，返回其中的较大者
        // 然后函数会回溯，每一步都返回当前已知的最大值，直到回溯到最初的调用
        return std::max(n, maximum(args...));
        // 例如参数为 maximum(4,65,1,63,57,347,755)
        // std::max(4, maximum(args...)); // args... == 65,1,63,57,347,755
        // std::max(4, std::max(65, maximum(args...))); // args... == 1,63,57,347,755
        // ...
        // 直到最后755，此时最后一次递归调用分解为如下调用
        // std::max(347, 755) -> 755
        // 递归回溯
        // std::max(57, 755) -> 755
        // std::max(63, 755) -> 755
        // ...
        // std::max(4, 755) -> 755
        // 返回755
    }
    // =================================================================

    void test_max_initializer_list() {
        cout << max({34,6,89,45,77,6,105}) << endl;
    }

    void test_max_variadic_template() {
        cout << maximum(4,65,1,63,57,347,755) << endl;
    }
}

// 例4
// 类模板
namespace ex04{
#include <string>

    // 2-1
    template<int IDX, const int MAX, typename... Args>
    struct PRINT_TUPLE{
        static void print(ostream& os, const tuple<Args...>& t) {
            os << get<IDX>(t) << (IDX+1 == MAX ? "":",");
            PRINT_TUPLE<IDX+1, MAX, Args...>::print(os, t);
        }
    };
    template<const int MAX, typename... Args>
    struct PRINT_TUPLE<MAX, MAX, Args...>{
        static void print(ostream& os, const tuple<Args...>& t) {}
    };

    // 1-1
    // 重载 << 作用于 make_tuple
    template<typename... Args>
    ostream& operator<<(ostream& os, const tuple<Args...>& t) {
        os << '[';
        // 2.打印tuple内的参数
        PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);
        return os << ']';
    }

    void test() {
        // 1. 为了可以让make_tuple作用于 << ， 所以先重载 <<
        cout << make_tuple(1.2, string("foo"), bitset<16>(377), 42);
        // 形如: [1.2, hello, xxxxx, 42]
    }
}

// 例5
// 用于递归继承
namespace ex05{
    // #include <tuple>

    template<typename... Values> class tuple;
    template<> class tuple<>{};
    
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...>: private tuple<Tail...>{
        typedef tuple<Tail...> inherited;
    protected:
        Head m_head;
    public:
        tuple(){}
        tuple(Head v, Tail... vtail): m_head(v), inherited(vtail...) {}

        // 以下2个版本都可以
        // auto head()->decltype(m_head) { return m_head; }
        Head head() { return m_head; }


        inherited& tail() { return *this; }
    };

    void test() {
        tuple<int, float, string> t (41, 3.14, "foo");

        cout << sizeof(t) << endl;

        cout << t.head() << endl;
        cout << t.tail().head() << endl;
        cout << t.tail().tail().head() << endl;
    }
}

// 例6
// 递归组合
namespace ex06{
    template<typename... Values> class tuple;
    template<> class tuple<>{};
    
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...>: private tuple<Tail...>{
        typedef tuple<Tail...> composited;
    protected:
        composited m_tail;
        Head m_head;
    public:
        tuple(){}
        tuple(Head v, Tail... vtail): m_head(v), m_tail(vtail...) {}

        Head head() { return m_head; }

        composited& tail() { return m_tail; }
    };

    void test() {
        tuple<int, float, string> t (41, 3.14, "foo");

        cout << sizeof(t) << endl;

        cout << t.head() << endl;
        cout << t.tail().head() << endl;
        cout << t.tail().tail().head() << endl;
    }
}


int main () {

    // ex01::func1();
    // ex02::test();
    // ex03::test_max_initializer_list();
    // ex03::test_max_variadic_template();

    // ex04::test();
    // ex05::test();

    ex06::test();

    return 0;
}