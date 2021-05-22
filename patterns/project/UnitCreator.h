#ifndef UNIT_CREATOR_H
#define UNIT_CREATOR_H
#include "unit.h"

class UnitCreator {
public:
	virtual Unit* CreateUnit(int x, int y, int belongs) = 0;
};


#endif
