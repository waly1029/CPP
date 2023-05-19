template<class T>
class shared_ptr{
public:
    T& operator*() const {
        return *px;
    }
    T* operator->() const {
        return px;
    }

    shared_ptr(T* p): px(p) {}
private:
    T* px;
    long * pn;
    // ...
};