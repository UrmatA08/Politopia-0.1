#include "dragondec.h"
#include "iterator.h"
#include "visitor.h"

DragonDec::DragonDec(Village* vill) {
	village_ = vill;
	UnitIterator it;
	auto dragon = new Dragon(0, 0, 0);
	Unit* unit = dragon;
	while ((unit = it.Next(this, dragon)) != nullptr) {
		squad_.push_back(unit);
	}
	delete dragon;
}

void DragonDec::Accept(Visitor* visitor) {
	visitor->Visit(this);
}