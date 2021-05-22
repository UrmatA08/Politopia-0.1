#ifndef VISITOR_H
#define VISITOR_H

class Decorator;


class Visitor {
public:
    virtual void Visit(Decorator* dec) = 0;
    ~Visitor() = default;
};

#endif