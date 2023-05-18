#include <iostream>
#include <vector>
using namespace std;

class Observer;

class Subject{
    int m_value;
    vector<Observer*> m_views;
public:
    Subject(int value=0) : m_value(value) {}

    void attach(Observer* o) {
        m_views.push_back(o);
    }
    void set_val(int value) {
        m_value = value;
        notify();
    }
    int get_val() const {
        return m_value;
    }
    void notify();
};

class Observer{
public:
    virtual void update(const Subject* sub) = 0;
    virtual ~Observer() {}
};

class V1: public Observer{
public:
    virtual void update(const Subject* sub) override {
        cout << "V1 update called. Value: " << sub->get_val() << endl;
    }
};
class V2: public Observer{
public:
    virtual void update(const Subject* sub) override {
        cout << "V2 update called. Value: " << sub->get_val() << endl;
    }
};
class V3: public Observer{
public:
    virtual void update(const Subject* sub) override {
        cout << "V3 update called. Value: " << sub->get_val() << endl;   
    }
};

void Subject::notify() {
    for(auto& view : m_views)
        view->update(this);
}

int main() {
    Subject s;

    Observer* o1 = new V1;
    Observer* o2 = new V2;
    Observer* o3 = new V3;

    s.attach(o1);
    s.attach(o2);
    s.attach(o3);

    s.set_val(1);
    s.set_val(999);

    delete o1;
    delete o2;
    delete o3;

    return 0;
}
