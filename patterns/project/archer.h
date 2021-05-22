#ifndef ARCHER_H
#define ARCHER_H
#include "unit.h"

struct Archer: public Unit {
	static const int kPrice_ = 4;
	static const int kCreateArcher = 3;
	static const int kKillsForUpgrade = 4;
	static const int kUpgradeArcherHealth = 5;
	static const int kUpgradeArcherDamage = 5;
	Archer(int x, int y, int belongs);
};

#endif