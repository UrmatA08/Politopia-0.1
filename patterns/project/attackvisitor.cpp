#include "attackvisitor.h"
#include "dragondec.h"
#include "archerdec.h"
#include "riderdec.h"
#include "giantdec.h"

AttackVisitor::AttackVisitor(Unit* enemy) : enemy_(enemy) {
}


void AttackVisitor::Visit(Decorator* dec) {
    for (auto unit : dec->squad_) {
        unit->can_upgrade_ = false;
        unit->can_attack_ = false;
        int distance = abs(enemy_->x_ - unit->x_) + abs(enemy_->y_ - unit->y_);
        if (distance <= unit->attack_radius_) {
            unit->MakeAttack(enemy_);
        }
    }
}
