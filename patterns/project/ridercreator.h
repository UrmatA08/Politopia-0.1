#ifndef RIDER_CREATOR_H
#define RIDER_CREATOR_H
#include "UnitCreator.h"
#include "rider.h"

struct RiderCreator : public UnitCreator {
	Unit* CreateUnit(int x, int y, int belongs) override {
		return new Rider(x, y, belongs);
	}
};

#endif
