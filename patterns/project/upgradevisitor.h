#ifndef UPGRADE_VISITOR_H
#define UPGRADE_VISITOR_H
#include "visitor.h"

class UpgradeVisitor : public Visitor {
    int* stars_;

public:
    UpgradeVisitor(int *stars);
    void Visit(Decorator* dec) override;
};

#endif