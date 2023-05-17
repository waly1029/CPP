#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape{
public:
    virtual void draw() const = 0;                  // 纯虚函数
    virtual void error(const std::string& msg);     // 有定义的虚函数
    int objectID() const;                           // 非虚函数
    // ...
};

class Rectangle: public Shape{
};

class Ellipse: public Shape{
};

#endif