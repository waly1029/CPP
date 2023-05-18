template<class T>
struct identity
{
    const T& operator()(const T& x) const {
        return x;
    }
};

template<class Pair>
struct select1st{
    const typename Pair::first_type& operator()
    (const Pair& x) const {
        return x.first;
    }
};


template<class Pair>
struct select2nd{
    const typename Pair::second_type& operator()
    (const Pair& x) const {
        return x.second;
    }
};

template<class T1, class T2>
struct pair{
    T1 first;
    T2 second;
    pair(): first(first), second(second) {}
    pair(const T1& x1, const T2& x2): first(x1), second(x2) {}
    // ...
};