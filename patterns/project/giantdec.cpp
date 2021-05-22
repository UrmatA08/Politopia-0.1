#include "giantdec.h"
#include "iterator.h"
#include "visitor.h"

GiantDec::GiantDec(Village* vill) {
	village_ = vill;
	UnitIterator it;
	auto giant = new Giant(0, 0, 0);
	Unit* unit = giant;
	while ((unit = it.Next(this, giant)) != nullptr) {
		squad_.push_back(unit);
	}
	delete giant;
}

void GiantDec::Accept(Visitor* visitor) {
	visitor->Visit(this);
}