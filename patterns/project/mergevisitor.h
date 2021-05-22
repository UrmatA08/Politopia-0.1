#ifndef MERGE_VISITOR_H
#define MERGE_VISITOR_H
#include "visitor.h"
#include "unit.h"
#include <vector>

class MergeVisitor : public Visitor {
    std::vector<std::vector<bool>> is_empty_;
    int x_;
    int y_;

    std::vector<int> FindEmptyPlace(int x, int y, int length);
    bool IsCorrect(int x, int y);
public:
    MergeVisitor(const std::vector<std::vector<bool>>& field, int x, int y);
    void Visit(Decorator* dec) override;
};

#endif