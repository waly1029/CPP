#ifndef MY_HASH_FUNCTION_IN
#define MY_HASH_FUNCTION_IN
#include <cstddef>
#include <functional>

#include <iostream>

template<typename T>
inline void hash_combine(size_t& seed, const T& val)
{
    // std::cout << "current seed: " << seed << std::endl;
    seed ^= std::hash<T>()(val) +
            0x9e3779b9 +
            (seed<<6) +
            (seed>>2);
}

// Auxiliary generic function
template<typename... Types>
inline size_t hash_val(const Types&... args)
{
    size_t seed = 0;
    // c++17折叠表达式 左形式
    ((hash_combine(seed, args)), ...);
    // std::cout << "last seed: " << seed << std::endl;
    return seed;
}

#endif
