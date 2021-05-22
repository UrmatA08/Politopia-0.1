#include "fraction.h"

Fraction::Fraction() {
	number_of_stars_ = 0;
	number_of_villages_ = 0;
	score_ = -20;
	CreateVillage(0, 0);
	belongs_ = 0;
	AddStars();
	number_of_stars_ += Village::kPrice;
	is_legion_ = false;
}

bool Fraction::CanCreate() const {
	return number_of_stars_ >= Village::kPrice;
}


void Fraction::CreateVillage(int x, int y) {
	Village* a = new Village;
	a->village_x_ = x;
	a->village_y_ = y;
	a->belogns_ = belongs_;
	a->icon_ = icon_;
	villages_.push_back(a);
	++number_of_villages_;
	number_of_stars_ -= Village::kPrice;
	score_ += Village::kPrice;
}

void Fraction::AddStars() {
	for (auto village : villages_) {
		number_of_stars_ += village->level_ + village->kDefaultNumberOfStars;
		score_ += village->level_ + village->kDefaultNumberOfStars;
	}
}

void Fraction::DestroyVillage(Village* village) {
	std::swap(village, villages_[number_of_villages_ - 1]);
	delete villages_[number_of_villages_ - 1];
	villages_.pop_back();
	--number_of_villages_;
}

int Fraction::GetNumberOfVillages() const {
	return number_of_villages_;
}

void Fraction::RemoveUnit(Unit* unit) {
	for (auto village : villages_) {
		for (int i = 0; i < village->current_number_of_units_; ++i) {
			if (village->army_[i] == unit) {
				std::swap(village->army_[i], village->army_[village->current_number_of_units_ - 1]);
				score_ += kDefaultNumberOfPoints;
				delete village->army_[village->current_number_of_units_ - 1];
				village->army_.pop_back();
				--(village->current_number_of_units_);
				return;
			}
		}
	}
}

void Fraction::AddVillage(int x, int y) {
	CreateVillage(x, y);
	number_of_stars_ += (Village::kPrice + Village::kDefaultNumberOfStars);
}

void Fraction::UpgradeVillage(Village* village) {
	++(village->level_);
	++(village->max_number_of_units_);
	number_of_stars_ -= kPriceForUpgrading;
}

bool Fraction::CanUpgrade() const {
	return number_of_stars_ >= kPriceForUpgrading;
}

Fraction::~Fraction() {
	for (auto village : villages_) {
		delete village;
	}
}
