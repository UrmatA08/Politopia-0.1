#include "giant.h"

Giant::Giant(int x, int y, int belongs) {
	model_ = "|G|";
	x_ = x;
	y_ = y;
	health_ = 40;
	damage_ = 10;
	attack_radius_ = 2;
	max_number_of_steps_ = 2;
	belongs_ = belongs;
	kills_for_upgrade_ = kKillsForUpgrade;
	upgrade_health_ = kUpgradeGiantHealth;
	upgrade_damage_ = kUpgradeGiantDamage;
	Unit::kPrice_ = kPrice_;
}