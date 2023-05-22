# 操作符重载

# 模版
## 类模版
## 函数模版
## 成员模版

## 泛化
template<class T>
struct A
{...};

## 特化
template<>
struct A<int>
{...};

template<>
struct A<double>
{...};

例：个数偏特化
template<class T, class Alloc = alloc>
class vector
{...};

template<class Alloc>
class vector<bool, Alloc>
{...};

例：范围偏特化
template<class Iterator>
struct iterator_traits
{...};

template<class T>
struct iterator_traits<T*>
{...};

template<class T>
struct iterator_traits<const T*>
{...};