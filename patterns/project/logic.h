#ifndef LOGIC_H
#define LOGIC_H
#include "fraction.h"
class Game;

class Logic {
    Game* game;

public:
    explicit Logic(Game* game_);
    void SwitchToNext();
	void MovePtr(int key);
	void Move();
	void MoveUnit();
	void MoveSquad();
	void Attack();
	void AttackUnit();
	void AttackSquad();
	void Upgrade();
	void UpgradeVillage();
	void UpgradeSquad();
	void Create();
	void GetInfo();
	void Accept(Visitor* visitor, int x, int y);
	int GetMaxScore() const;
	Village* GetUnitsVillage(Unit* unit) const;
	void TakeOverVillage();
	void FormSquad();
	void DisbandSquad();
    bool IsUnitFieldEmpty(int x, int y) const;
	bool IsVillFieldEmpty(int x, int y) const;
    std::vector<std::vector<bool>> GetIsEmptyField();
};

#endif