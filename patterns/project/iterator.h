#ifndef ITERATOR_H
#define ITERATOR_H
#include "unit.h"
class Decorator;


class UnitIterator {
    int idx_ = 0;

public:
    Unit* Next(Decorator* dec, Unit* unit);
};

#endif