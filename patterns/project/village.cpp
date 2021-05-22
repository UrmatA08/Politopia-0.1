#include "village.h"


void Village::AddUnit(UnitCreator* factory, int x, int y) {
	Unit* unit = factory->CreateUnit(x, y, belogns_);
	army_.push_back(unit);
	++current_number_of_units_;
}

bool Village::CanCreate(int number_of_stars, int price) {
	return number_of_stars >= price;
}

void Village::UpgradeArmy() {
	for (auto unit : army_) {
		unit->Upgrade();
	}
}


void Village::FormSquad() {
	is_squad_ = true;
}

void Village::DisbandSquad() {
	is_squad_ = false;
}


Village::~Village() {
	for (int i = 0; i < current_number_of_units_; ++i) {
		delete army_[i];
	}
}
