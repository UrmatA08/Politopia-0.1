#ifndef DRAGON_CREATOR_H
#define DRAGON_CREATOR_H
#include "UnitCreator.h"
#include "dragon.h"

struct DragonCreator : public UnitCreator {
	Unit* CreateUnit(int x, int y, int belongs) override {
		return new Dragon(x, y, belongs);
	}
};

#endif
