#ifndef GIANT_H
#define GIANT_H
#include "unit.h"

struct Giant : public Unit {
	static const int kPrice_ = 8;
	const int kCreateGiant = 3;
	static const int kKillsForUpgrade = 5;
	const int kUpgradeGiantHealth = 10;
	const int kUpgradeGiantDamage = 10;
	Giant(int x, int y, int belongs);
};

#endif