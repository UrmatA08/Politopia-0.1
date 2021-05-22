#ifndef VILLAGE_H
#define	VILLAGE_H

#include "dragon.h"
#include <string>
#include <vector>
#include "rider.h"
#include "archer.h"
#include "giant.h"
#include "archercreator.h"
#include "ridercreator.h"
#include "dragoncreator.h"
#include "giantcreator.h"

enum Fractions { nobody = 0, imperius, vengir, quezatli };

struct Village {
	const static int kDefaultNumberOfUnits = 4;
	const static int kDefaultNumberOfStars = 4;
	const static int kPrice = 15;
	std::string icon_ = "";
	int belogns_ = nobody;
	int village_x_ = 0;
	int village_y_ = 0;
	int level_ = 1;
	int current_number_of_units_ = 0;
	int max_number_of_units_ = kDefaultNumberOfUnits;
	bool is_squad_ = false;
	std::vector<Unit*> army_;

	bool CanCreate(int number_of_stars, int price);
	void AddUnit(UnitCreator* factory, int x, int y);
	void UpgradeArmy();
	void FormSquad();
	void DisbandSquad();
	~Village();
};

#endif