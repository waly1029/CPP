#include <iostream>
#include <cstddef>
#include <unordered_set>
#include "./my_hash_function.h"

using namespace std;

struct Customer {
    std::string fname;
    std::string lname;
    long no;

    Customer(std::string fname, std::string lname, long no) : fname(fname), lname(lname), no(no) {}


    // 为了使用set 需要重载排序方式也就是运算符的重载至少有<  =
    bool operator<(const Customer& c) const{
        return (fname < c.fname);
    }

    bool operator==(const Customer& c) const{
        return (fname == c.fname);
    }
};

class CustomerHash {
public:
    size_t operator()(const Customer& c) const { 
        return hash_val(c.fname, c.lname, c.no);
    }
};

int main() {

    // Customer customer{"pika", "kairyu", 99};

    // cout << CustomerHash()(customer) << endl;

    unordered_set<Customer, CustomerHash> ct;
    ct.insert(Customer("ab", "cd", 1L));
    ct.insert(Customer("ds", "fg", 2L));
    ct.insert(Customer("ab", "nb", 3L));
    ct.insert(Customer("4h", "e4", 4L));
    ct.insert(Customer("bfa", "ggt4", 5L));
    ct.insert(Customer("32fd", "4ggt", 6L));
    ct.insert(Customer("bfe", "gh5h5", 7L));

    cout << ct.bucket_count() << endl;  // 11

    CustomerHash hh;
    cout << "bucket position of ab = " << hh(Customer("ab", "cd", 1L)) % 11 << endl;
    cout << "bucket position of ds = " << hh(Customer("ds", "fg", 2L)) % 11 << endl;
    cout << "bucket position of ab = " << hh(Customer("ab", "nb", 3L)) % 11 << endl;
    cout << "bucket position of 4h = " << hh(Customer("4h", "e4", 4L)) % 11 << endl;
    cout << "bucket position of bfa = " << hh(Customer("bfa", "ggt4", 5L)) % 11 << endl;
    cout << "bucket position of 32fd = " << hh(Customer("32fd", "4ggt", 6L)) % 11 << endl;
    cout << "bucket position of bfe = " << hh(Customer("bfe", "gh5h5", 7L)) % 11 << endl;

    for(unsigned int i = 0; i < ct.bucket_count(); i++) {
        cout << "Bucket #" << i << " has " << ct.bucket_size(i) << " elements." << endl;
    }

    return 0;
}