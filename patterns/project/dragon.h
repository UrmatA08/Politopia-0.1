#ifndef DRAGON_H
#define DRAGON_H
#include "unit.h"

struct Dragon : public Unit {
	static const int kPrice_ = 10;
	static const int kCreateDragon = 3;
	static const int kKillsForUpgrade = 6;
	static const int kUpgradeDragonHealth = 5;
	static const int kUpgradeDragonDamage = 5;
	Dragon(int x, int y, int belongs);
};

#endif
