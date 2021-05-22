#include "archer.h"

Archer::Archer(int x, int y, int belongs) {
	model_ = "A->";
	x_ = x;
	y_ = y;
	health_ = 10;
	damage_ = 5;
	attack_radius_ = 8;
	max_number_of_steps_ = 1;
	belongs_ = belongs;
	kills_for_upgrade_ = kKillsForUpgrade;
	upgrade_health_ = kUpgradeArcherHealth;
	upgrade_damage_ = kUpgradeArcherDamage;
	Unit::kPrice_ = kPrice_;
}