#ifndef FRACTION_H
#define FRACTION_H
#include "village.h"
#include "archerdec.h"
#include "riderdec.h"
#include "giantdec.h"
#include "dragondec.h"
#include "attackvisitor.h"
#include "upgradevisitor.h"
#include "mergevisitor.h"


class Fraction {
public:
	static const int kPriceForUpgrading = 8;
	static const int kDefaultNumberOfPoints = 10;
	std::string icon_;
	int belongs_;
	int number_of_villages_;
	int number_of_stars_;
	int score_;
	bool is_legion_;
	std::vector<Village*> villages_;

	Fraction();
	~Fraction();
	void AddStars();
	void CreateVillage(int x, int y);
	bool CanCreate() const;
	bool CanUpgrade() const;
	void AddVillage(int x, int y);
	void DestroyVillage(Village* village);
	void RemoveUnit(Unit* unit);
	void UpgradeVillage(Village* village);
	int GetNumberOfVillages() const;
};

#endif