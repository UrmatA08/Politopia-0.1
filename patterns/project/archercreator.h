#ifndef ARCHER_CREATOR_H
#define ARCHER_CREATOR_H
#include "UnitCreator.h"
#include "archer.h"

struct ArcherCreator: public UnitCreator {
	Unit* CreateUnit(int x, int y, int belongs) override {
		return new Archer(x, y, belongs);
	}
};


#endif
