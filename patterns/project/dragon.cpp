#include "dragon.h"

Dragon::Dragon(int x, int y, int belongs) {
	model_ = "D";
	x_ = x;
	y_ = y;
	health_ = 25;
	damage_ = 15;
	attack_radius_ = 5;
	max_number_of_steps_ = 3;
	belongs_ = belongs;
	kills_for_upgrade_ = kKillsForUpgrade;
	upgrade_health_ = kUpgradeDragonHealth;
	upgrade_damage_ = kUpgradeDragonDamage;
	Unit::kPrice_ = kPrice_;
}