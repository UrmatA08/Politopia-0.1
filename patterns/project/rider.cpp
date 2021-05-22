#include "rider.h"

Rider::Rider(int x, int y, int belongs) {
	model_ = "R";
	x_ = x;
	y_ = y;
	health_ = 10;
	damage_ = 5;
	attack_radius_ = 1;
	max_number_of_steps_ = 4;
	belongs_ = belongs;
	kills_for_upgrade_ = kKillsForUpgrade;
	upgrade_health_ = kUpgradeRiderHealth;
	upgrade_damage_ = kUpgradeRiderDamage;
	Unit::kPrice_ = kPrice_;
}