#ifndef GIANT_CREATOR_H
#define GIANT_CREATOR_H
#include "UnitCreator.h"
#include "giant.h"

struct GiantCreator : public UnitCreator {
	Unit* CreateUnit(int x, int y, int belongs) override {
		return new Giant(x, y, belongs);
	}
};

#endif
