#include "archerdec.h"
#include "iterator.h"
#include "visitor.h"

ArcherDec::ArcherDec(Village* vill) {
	village_ = vill;
	UnitIterator it;
	auto archer = new Archer(0, 0, 0);
	Unit* unit = archer;
	while ((unit = it.Next(this, archer)) != nullptr) {
		squad_.push_back(unit);
	}
	delete archer;
}

void ArcherDec::Accept(Visitor* visitor) {
	visitor->Visit(this);
}