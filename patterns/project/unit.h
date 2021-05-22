#ifndef UNIT_H
#define UNIT_H
#include <algorithm>
#include <string>
#include <iostream>

class Unit {
public:
	std::string model_;
	int x_;
	int y_;
	int health_;
	int damage_;
	int attack_radius_;
	int number_of_kills_;
	int max_number_of_steps_;
	int belongs_;
	int kills_for_upgrade_;
	int upgrade_health_;
	int upgrade_damage_;
	bool can_move_;
	bool can_attack_;
	bool can_upgrade_;
	int kPrice_;
	
	Unit();// 
	void Move(int x, int y);
	void MakeAttack(Unit* enemy);
	bool CheckOnUpgrade() const;
	void Upgrade();
};

#endif