#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstdlib>  // qsort, bsearch, NULL
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <array>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "test_stl.h"

const long ASIZE = 500000L;

namespace lz01{
    using std::cout;
    using std::endl;
    using std::array;

    void test_array(){
        cout << "\ntest_array()........\n";

        array<long, ASIZE> c;

        clock_t timeStart = clock();
        for(long i=0; i<ASIZE; ++i) {
            c[i] = rand();
        }
        cout << "milli-seconds: " << (clock()-timeStart) << endl;
        cout << "array.size()= " << c.size() << endl;
        cout << "array.front() = " << c.front() << endl;
        cout << "array.back() = " << c.back() << endl;
        cout << "array.data() = " << c.data() << endl;

        long target = get_a_target_long();

        timeStart = clock();
        // 先排序
        qsort(c.data(), ASIZE, sizeof(long), compareLongs);
        // 后bs查找
        long* pItem = (long*)bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
        
        cout << "qsort()+bsearch(), milli-seconds: " << (clock()-timeStart) << endl;
        if(pItem != nullptr) 
            cout << "found, " << *pItem << endl;
        else
            cout << "not found!" << endl;
    }


}

namespace lz02{
    using std::cout;
    using std::endl;
    using std::vector;
    using std::string;

    void test_vector(long& value){

        cout << "\ntest_vector().......\n";

        vector<string> c;
        char buf[10];

        clock_t timeStart = clock();

        for(long i=0; i<value; i++){
            try{
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch(std::exception& p) {
                cout << "i= " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock()-timeStart) << endl;
        cout << "array.size()= " << c.size() << endl;
        cout << "array.front() = " << c.front() << endl;
        cout << "array.back() = " << c.back() << endl;
        cout << "array.data() = " << c.data() << endl;
        cout << "array.capacity() = " << c.capacity() << endl;  // 容量,2倍增长

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = std::find(c.begin(), c.end(), target);

            cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

            if(pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found!" << endl;
        }

        {
            timeStart = clock();
            std::sort(c.begin(), c.end());
            cout << "sort(), milli-seconds: " << (clock() - timeStart) << endl;

            string* pItem = (string*)bsearch(&target, (c.data()),
                                             c.size(), sizeof(string), compareStrings);
            cout << "sort()+bsearch(), milli-seconds: " << (clock() - timeStart) << endl;

            if(pItem != nullptr)
                cout << "found, " << *pItem << endl;
            else
                cout << "not found!" << endl;
        }

    }
}


namespace lz03{
    
    using std::list;
    using std::endl;

    void test_list(long& value) {
        cout << "\ntest_list()...........\n";

        list<string> c;
        char buf[10];

        clock_t timeStart = clock();

        for(long i=0; i<value; i++){
            try{
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch(std::exception& p) {
                cout << "i= " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock()-timeStart) << endl;
        cout << "list.size()= " << c.size() << endl;
        cout << "list.max_size() = " << c.max_size() << endl;
        cout << "list.front() = " << c.front() << endl;
        cout << "list.back() = " << c.back() << endl;

        string target = get_a_target_string();
        
        timeStart = clock();
        auto pItem = std::find(c.begin(), c.end(), target);

        cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

        if(pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found!" << endl;

        timeStart = clock();
        // list自己的sort
        // 标准库也有一个全局sort
        c.sort();
        cout << "c.sort(), milli-seconds: " << (clock() - timeStart) << endl;
        
        
    }
}

// deque
// 分段连续
// 段落之间link

// stack & queue 作为deque的adapter
// stack & queue 内部并没有自己的算法实现
// stack & queue 都是借用deque的接口功能实现
// stack & queue 不提供iterator

// 关联容器
// multiset
namespace lz04{
    using std::cout;
    using std::endl;
    using std::string;
    using std::multiset;

    void test_multiset(long& value) {
        cout << "\ntest multiset......" << endl;

        multiset<string> c;
        char buf[10];
        clock_t timeStart = clock();
        for(long i = 0; i < value; i++) {
            try{
                snprintf(buf, 10, "%d", rand());
// insert()
                c.insert(string(buf));
            }
            catch(std::exception& p){
                cout << "i= " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
// size()        
        cout << "multiset.size()= " << c.size() << endl;
// max_size()
        cout << "multiset.max_size()= " << c.max_size() << endl;

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = std::find(c.begin(), c.end(), target); // 比c.find()慢很多
            cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;
            if(pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;
        }
        {
            timeStart = clock();
// multiset.find()            
            auto pItem = c.find(target);
            cout << "c.find(), milli-seconds: " << (clock() - timeStart) << endl;
            if(pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;
        }

    }
}

// multimap
namespace lz05{
    using std::cout;
    using std::endl;
    using std::string;
    using std::multimap;

    void test_multimap(long& value) {
        cout << "\ntest multimap......" << endl;

        multimap<long, string> c;
        char buf[10];
        clock_t timeStart = clock();
        for(long i = 0; i < value; i++) {
            try{
                snprintf(buf, 10, "%d", rand());
// insert()
// 需要组合pair<T1,T2>();
// multimap不可使用[]
                c.insert(std::pair<long, string>(i, buf));
            }
            catch(std::exception& p){
                cout << "i= " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
// size()        
        cout << "multiset.size()= " << c.size() << endl;
// max_size()
        cout << "multiset.max_size()= " << c.max_size() << endl;

        long target = get_a_target_long();
    
        timeStart = clock();
// multimap.find()            
        auto pItem = c.find(target);
        cout << "c.find(), milli-seconds: " << (clock() - timeStart) << endl;
        if(pItem != c.end())
// 取出pair second
            cout << "found, value=" << (*pItem).second << endl;
        else
            cout << "not found! " << endl;

    }
}

// unordered_multiset
namespace lz06{
    using std::cout;
    using std::endl;
    using std::string;
    using std::unordered_multiset;

    void test_unordered_multiset(long& value) {
        cout << "\ntest unordered_multiset......" << endl;

        unordered_multiset<string> c;
        char buf[10];
        clock_t timeStart = clock();
        for(long i = 0; i < value; i++) {
            try{
                snprintf(buf, 10, "%d", rand());
// insert()
                c.insert(string(buf));
            }
            catch(std::exception& p){
                cout << "i= " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
// size()        
        cout << "unordered_multiset.size()= " << c.size() << endl;
// max_size()
        cout << "unordered_multiset.max_size()= " << c.max_size() << endl;
        cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;
// load_factor() 
        cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;
        cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor() << endl;
        cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count() << endl;

        for(unsigned i=0; i<20; i++)
            cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements" << endl;

        string target = get_a_target_string();
    
        {
            timeStart = clock();
// std::find()            
            auto pItem = std::find(c.begin(), c.end(), target);
            cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;
            if(pItem != c.end())
                cout << "found, value=" << (*pItem) << endl;
            else
                cout << "not found! " << endl;
        }

        {
            timeStart = clock();
// unordered_multiset.find() 比 std::find快很多
            auto pItem = c.find(target);
            cout << "c.find(), milli-seconds: " << (clock() - timeStart) << endl;
            if(pItem != c.end())
                cout << "found, value=" << (*pItem) << endl;
            else
                cout << "not found! " << endl;
        }

    }
}

int main() {

    time_t seed = time(NULL);
    srand(seed);

    // lz01::test_array();

    long value = 1000000L;
    std::cout << "elements.size() = " << value << std::endl;

    // lz02::test_vector(value);

    // lz03::test_list(value);

    // lz04::test_multiset(value);

    // lz05::test_multimap(value);

    lz06::test_unordered_multiset(value);

    return 0;
}