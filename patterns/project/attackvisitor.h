#ifndef ATTACK_VISITOR_H
#define ATTACK_VISITOR_H
#include "visitor.h"
#include "unit.h"

class AttackVisitor : public Visitor {
    Unit* enemy_;

public:
    AttackVisitor(Unit* enemy);
    void Visit(Decorator* dec) override;
};

#endif