·Inheritance（继承）
·Composition（组合）
·Delegation （委托）

###Composition（组合），表示has-a

queue◆-->deque

```
template <class T>
class queue{
// ...
protected:
    deque<T> c; // 底层容器
public:
    // 以下完全利用c的操作函数完成
    bool empty() { return c.empty(); }
    size_type size() const { return c.size(); }
    reference front() { return c.front(); }
    reference back() { return c.back(); }
    //
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_front(); }
};
```
