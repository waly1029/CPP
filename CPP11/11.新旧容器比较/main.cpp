#include <iostream>

// array
namespace ex01 {
    /*
    template<typename _Tp, std::size_t _Nm>
    // 没有ctor，没有dtor
    struct array{
        typedef _Tp value_type;
        typedef _Tp* pointer;
        typedef value_type* iterator;

        value_type _M_instance[ _Nm ? _Nm : 1];

        iterator begin()
        { return iterator(&_M_instance[0]); }

        iterator end()
        { return iterator(&_M_instance[_Nm]);}

        // ...
    };
    */
}

// hashtable
// Separate Chaining
// 篮子下面接链表
// hash-code -> put in vector baskets -> if baskets almost full -> vector.size()*2
namespace ex02{
#include<string>

    void test_hash_code() {
        void* pi = (void*)(new int(100));
        std::cout << std::hash<int>()(123) << std::endl;
        std::cout << std::hash<long>()(123L) << std::endl;
        std::cout << std::hash<std::string>()(std::string("Ace")) << std::endl;
        std::cout << std::hash<const char*>()("Ace") << std::endl;
        std::cout << std::hash<char>()('A') << std::endl;
        std::cout << std::hash<float>()(3.141592653) << std::endl;
        std::cout << std::hash<double>()(3.141592653) << std::endl;
        std::cout << std::hash<void*>()(pi) << std::endl;
        // 123
        // 123
        // 8925841732762002877
        // 1822296350306153722
        // 65
        // 1078530011
        // 4614256656550717752
        // 9667259626824844715
    }
}

// 一个万用的hash function
// no source code
namespace ex03{

}

// tuple
namespace ex04{
#include <tuple>
#include <string>
    class MyComplex{
        double x;
        double y;
    public:
        MyComplex():x(0),y(0) {}
    };

    template <typename... Types>
    std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& t) {
        std::apply([&os](const auto&... args) {
            ((os << args << ' '), ...);
        }, t);
        return os;
    }

    void test01(){
        std::cout << "string, sizeof=" << sizeof(std::string) << std::endl;
        std::cout << "double, sizeof=" << sizeof(double) << std::endl;
        std::cout << "float, sizeof=" << sizeof(float) << std::endl;
        std::cout << "int, sizeof=" << sizeof(int) << std::endl;
        std::cout << "MyComplex<double>, sizeof=" << sizeof(MyComplex) << std::endl;

        std::tuple<std::string, int, int, MyComplex> t;
        std::cout << "tuple, sizeof=" << sizeof(t) << std::endl;

        std::tuple<std::string, int, int> t1("nico", 4, 6);
        std::cout << "tuple, sizeof=" << sizeof(t1) << std::endl;

        std::cout << "t1:" << std::get<0>(t1) << ' ' << std::get<1>(t1) << ' ' << std::get<2>(t1) << std::endl;

        auto t2 = std::make_tuple("stacked", 99, 3.141);

        std::get<1>(t1) = std::get<1>(t2);
        std::cout << std::get<1>(t1) << std::endl;

        if(t1<t2)
            std::cout << "t1<t2" << std::endl;
        else if(t1>t2)
            std::cout << "t1>t2" << std::endl;
        else
            std::cout << "t2==t1" << std::endl;

        std::cout << t1 << std::endl;
        t1 = t2;
        std::cout << t1 << std::endl;

        std::tuple<int, float, std::string> t3(77, 1.123, "more light");
        int i1;
        float f2;
        std::string s1;
        std::tie(i1, f2, s1) = t3;
        std::cout << i1 << std::endl;
        std::cout << f2 << std::endl;
        std::cout << s1 << std::endl;

        // 元编程
        typedef std::tuple<int, float, std::string> TupleType;
        std::cout << std::tuple_size<TupleType>::value << std::endl;
        std::tuple_element<1, TupleType>::type f1 = 1.03;
        typedef std::tuple_element<1, TupleType>::type ElementType;
    }
}

int main () {

    // ex02::test_hash_code();
    ex04::test01();

    return 0;
}