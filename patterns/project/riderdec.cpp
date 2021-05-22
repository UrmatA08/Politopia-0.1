#include "riderdec.h"
#include "iterator.h"
#include "visitor.h"

RiderDec::RiderDec(Village* vill) {
	village_ = vill;
	UnitIterator it;
	auto rider = new Rider(0, 0, 0);
	Unit* unit = rider;
	while ((unit = it.Next(this, rider)) != nullptr) {
		squad_.push_back(unit);
	}
	delete rider;
}

void RiderDec::Accept(Visitor* visitor) {
	visitor->Visit(this);
}