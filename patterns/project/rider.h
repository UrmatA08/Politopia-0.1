#ifndef RIDER_H
#define RIDER_H
#include "unit.h"

struct Rider : public Unit {
	static const int kPrice_ = 2;
	static const int kCreateRider = 3;
	static const int kKillsForUpgrade = 3;
	static const int kUpgradeRiderHealth = 5;
	static const int kUpgradeRiderDamage = 5;
	Rider(int x, int y, int belongs);
};

#endif
