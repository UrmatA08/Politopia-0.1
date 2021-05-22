#include "unit.h"

Unit::Unit() : model_(""), x_(0), y_(0), health_(0),
damage_(0), attack_radius_(0), number_of_kills_(0),
max_number_of_steps_(0), belongs_(0),kills_for_upgrade_(0),
upgrade_health_(0), upgrade_damage_(0), can_move_(true), can_attack_(true), can_upgrade_(true), kPrice_(0){}


void Unit::Move(int x, int y) {
	x_ = x;
	y_ = y;
	can_move_ = false;
}

void Unit::MakeAttack(Unit* enemy) {
	enemy->health_ -= damage_;
	can_attack_ = false;
}

void Unit::Upgrade() {
	health_ += upgrade_health_;
	damage_ += upgrade_damage_;
}

bool Unit::CheckOnUpgrade() const {
	return number_of_kills_ >= kills_for_upgrade_;
}
