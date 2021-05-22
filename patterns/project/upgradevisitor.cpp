#include "upgradevisitor.h"
#include "decorator.h"

UpgradeVisitor::UpgradeVisitor(int* stars) : stars_(stars) {
}

void UpgradeVisitor::Visit(Decorator* dec) {
    if (*stars_ < dec->squad_.size() * dec->squad_[0]->kPrice_) {
        return;
    }
    *stars_ -= (dec->squad_.size() * dec->squad_[0]->kPrice_ / 2);
    for (auto unit : dec->squad_) {
        unit->can_upgrade_ = false;
        unit->can_move_ = false;
        unit->can_attack_ = false;
        unit->Upgrade();
    }
}