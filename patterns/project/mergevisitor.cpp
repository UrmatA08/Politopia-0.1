#include "mergevisitor.h"
#include "decorator.h"

MergeVisitor::MergeVisitor(const std::vector<std::vector<bool>>& field, int x, int y) : is_empty_(field), x_(x), y_(y) {
}

void MergeVisitor::Visit(Decorator* dec) {
    const std::vector<int> null{ -1,-1 };
    for (auto unit : dec->squad_) {
        unit->can_move_ = false;
        unit->can_upgrade_ = false;
        is_empty_[unit->x_][unit->y_] = true;
        int x = x_;
        int y = y_;
        int length = 1;
        std::vector<int> empty = FindEmptyPlace(x, y, length);
        while (empty == null) {
            --x;
            --y;
            length += 2;
            empty = FindEmptyPlace(x, y, length);
        }
        unit->x_ = empty[0];
        unit->y_ = empty[1];
    }
}

std::vector<int> MergeVisitor::FindEmptyPlace(int x, int y, int length) {
    for (int i = x; i < x + length; ++i) {
        for (int j = y; j < y + length; ++j) {
            if (IsCorrect(i, j) && is_empty_[i][j]) {
                is_empty_[i][j] = false;
                return std::vector<int>{i, j};
            }
        }
    }
    return std::vector<int>{-1, -1};
}

bool MergeVisitor::IsCorrect(int x, int y) {
    int n = is_empty_.size();
    int m = is_empty_[0].size();
    return x >= 0 && y >= 0 && x < n&& y < m;
}