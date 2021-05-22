#ifndef GAME_H
#define GAME_H
#include "unit.h"
#include "fraction.h"
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdio.h>
#include <cstdlib>
#include <random>
#include "logic.h"
#include "PlayCommand.h"
#include "PrintWCommand.h"

class WrongNumber : std::exception{};

class Game {
	static const int max_numbers_of_moves = 20;
	static const int length = 15;
	static const int width = 15;
	static const int max_number_of_players = 4;
	std::string icons[max_number_of_players] = {"_/::\\_", "//||\\\\", "\\_/\\_/", ":|-|-|:"};
	std::string field[length][width];
	std::vector<std::vector<Unit*>> unit_field;
	//Unit* unit_field[length][width];
	Village* village_field[length][width];
	std::vector<Fraction*> fractions_;
	int turn_ = 1;
	int current_move_ = 1;
	int ptr_x_ = 0;
	int ptr_y_ = 0;
	int number_of_players_ = 3;
	
	void SetColor(int text, int background);
	void ExecuteCommand(int key);
	void FillField();
	void Draw(int colour);
	void GetInfo();
	int GetMaxScore() const;
	friend class Logic;

public:
	Game(int counter);
	~Game();
	void Play();
	void PrintWinner() const;
};

int SetNumberOfPlayers();

#endif

