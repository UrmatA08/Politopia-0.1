#include "game.h"

enum units { rider = 49, archer, dragon, giant };
enum buttons {left = 'a', right = 'd', down = 's', up = 'w', attack = 'g',
move_unit = 'm', form = 'p', create = 'c', next_turn = 'n', take_over = 't', 
disband = 'o', upgrade = 'u'};

int SetNumberOfPlayers() {
	int number_of_players;
	std::cout << "Enter the number of players: ";
	std::cin >> number_of_players;
	if (number_of_players > 4 || number_of_players < 2) {
		throw WrongNumber();
	}
	return number_of_players;
}

Game::Game(int players) {
	number_of_players_ = players;
	unit_field = std::vector<std::vector<Unit*>>(length, std::vector<Unit*>(width, nullptr));
	std::random_device device;
	std::mt19937 generator(device());
	for (int i = 0; i < number_of_players_; ++i) {
		fractions_.push_back(new Fraction);
	}
	for (int i = 0; i < number_of_players_; ++i) {
		fractions_[i]->icon_ = icons[i];
		fractions_[i]->belongs_ = i + 1;
		fractions_[i]->villages_[0]->belogns_ = i + 1;
		std::uniform_int_distribution<int> distr_len(0, length - 1);
		fractions_[i]->villages_[0]->village_x_ = distr_len(generator);
		std::uniform_int_distribution<int> distr_width(i * (width / number_of_players_), ((i + 1) * width) / number_of_players_ - 1);
		fractions_[i]->villages_[0]->village_y_ = distr_width(generator);
	}
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < width; ++j) {
			unit_field[i][j] = nullptr;
			village_field[i][j] = nullptr;
		}
	}
}

void Game::FillField() {
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < width; ++j) {
			unit_field[i][j] = nullptr;
			village_field[i][j] = nullptr;
			field[i][j] = "";
		}
	}
	for (int k = 0; k < number_of_players_; ++k) {
		const int number_of_villages = fractions_[k]->GetNumberOfVillages();
		for (int i = 0; i < number_of_villages; ++i) {
			int x = fractions_[k]->villages_[i]->village_x_;
			int y = fractions_[k]->villages_[i]->village_y_;
			field[x][y] += fractions_[k]->icon_;
			village_field[x][y] = fractions_[k]->villages_[i];
			const int number_of_units = fractions_[k]->villages_[i]->current_number_of_units_;
			for (int j = 0; j < number_of_units; ++j) {
				int x_u = fractions_[k]->villages_[i]->army_[j]->x_;
				int y_u = fractions_[k]->villages_[i]->army_[j]->y_;
				field[x_u][y_u] += k + 1 + '0';
				field[x_u][y_u] += fractions_[k]->villages_[i]->army_[j]->model_;
				unit_field[x_u][y_u] = fractions_[k]->villages_[i]->army_[j];
			}
		}
	}
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < width; ++j) {
			field[i][j].resize(10, ' ');
		}
	}
}

void Game::Draw(int colour) {
	clear();
	for (int j = 0; j < width; ++j) {
		printw("%s", "-----------");
	}
	printw("\n");
	for (int i = 0; i < length; ++i)
	{
		printw("%s", "|");
		for (int j = 0; j < width; ++j) {
			if (ptr_x_ == i && ptr_y_ == j){
				init_pair(1, COLOR_WHITE, colour);
				attron(COLOR_PAIR(1));
				for (auto k : field[i][j]){
					printw("%c", k);
				}
				attroff(COLOR_PAIR(1));
			} else{
				for (auto k : field[i][j]){
					printw("%c", k);
				}
			}
			printw("%s", "|");
		}
		printw("\n");
		for (int j = 0; j < width; ++j) {
			printw("%s", "-----------");
		}
		printw("\n");
	}
	GetInfo();
}


void Game::Play() {
	FillField();
	Draw(turn_ + 3);
	while (current_move_ < max_numbers_of_moves) {
		int key = getch();
		ExecuteCommand(key);
		FillField();
		Draw(turn_+ 3);
	}

}

void Game::ExecuteCommand(int key) {
	Logic logic(this);
	if (key == left || key == right || key == up || key == down) {
		logic.MovePtr(key);
	}
	switch (key) {
	case create:
		logic.Create();
		break;
	case move_unit:
		logic.Move();
		break;
	case attack:
		logic.Attack();
		break;
	case next_turn:
		logic.SwitchToNext();
		break;
	case upgrade:
		logic.Upgrade();
		break;
	case take_over:
		logic.TakeOverVillage();
		break;
	case form:
		logic.FormSquad();
		break;
	case disband:
		logic.DisbandSquad();
		break;
	default:
		break;
	}

}


void Game::GetInfo() {
	Logic logic(this);
	const char* a;
	switch (turn_) {
	case 1:
		a = "first ";
		break;
	case 2:
		a = "second ";
		break;
	case 3:
		a = "third ";
		break;
	case 4:
		a = "fourth ";
		break;
	default:
		break;;
	}
	printw("%s%d%s", "Now the ", current_move_, " round\n");
	printw("%s%s%s%s", "Now the ", a, "players's move.", "Icon - ");
	for (auto ch: icons[turn_ - 1]){
		printw("%c", ch);
	}
	printw("%s%d", "\nYour score is ", fractions_[turn_ - 1]->score_);
	printw("%s%d%s", "\nYou have ", fractions_[turn_ - 1]->number_of_stars_, " stars\n\n");
	if (!logic.IsUnitFieldEmpty(ptr_x_, ptr_y_)) {
		printw("%s","unit: ");
		for (auto ch: unit_field[ptr_x_][ptr_y_]->model_){
			printw("%c", ch);
		}
		printw("%s%d", "\nhealth: ", unit_field[ptr_x_][ptr_y_]->health_);
		printw("%s%d", "\ndamage: ", unit_field[ptr_x_][ptr_y_]->damage_);
		printw("%s%d", "\nattack radius: ", unit_field[ptr_x_][ptr_y_]->attack_radius_);
		printw("%s%d", "\nmax number of steps: ", unit_field[ptr_x_][ptr_y_]->max_number_of_steps_);
		printw("%s%d", "\nnumber of kills: ", unit_field[ptr_x_][ptr_y_]->number_of_kills_);
		printw("%s%d", "\ntotal kills for upgrading: ", unit_field[ptr_x_][ptr_y_]->kills_for_upgrade_);
		
		const char* can_move = unit_field[ptr_x_][ptr_y_]->can_move_ ? "Yes" : "No";
		printw("%s%s\n", "\ncan move: ", can_move);
	}
	if (!logic.IsVillFieldEmpty(ptr_x_, ptr_y_)) {
		printw("%s%s%s", "\nThe village belongs to the ", a, "player");
		printw("%s%d", "\nlevel: ", village_field[ptr_x_][ptr_y_]->level_);
		printw("%s%d", "\ncurrent number of units: ", village_field[ptr_x_][ptr_y_]->current_number_of_units_);
		if (village_field[ptr_x_][ptr_y_]->is_squad_) {
			printw("%s", "\nall units of this village are in the squad");
		}
		if (village_field[ptr_x_][ptr_y_]->belogns_ == turn_) {
			printw("%s%d", "\nmax number of units you can create: ", village_field[ptr_x_][ptr_y_]->max_number_of_units_);
			if (fractions_[turn_ - 1]->number_of_stars_ >= Fraction::kPriceForUpgrading) {
				printw("%s", "\nyou can upgrade this village");
			} else {
				printw("%s%d%s", "\nyou need ", -(fractions_[turn_ - 1]->number_of_stars_ - Fraction::kPriceForUpgrading), " more stars to upgrade this village");
			}
			if (logic.IsUnitFieldEmpty(ptr_x_, ptr_y_)) {
				if (village_field[ptr_x_][ptr_y_]->current_number_of_units_ >= village_field[ptr_x_][ptr_y_]->max_number_of_units_) {
					printw("%s", "\nvillage is full. you can't create new units");
				} else {
					if (village_field[ptr_x_][ptr_y_]->CanCreate(fractions_[turn_ - 1]->number_of_stars_, Rider::kPrice_)) {
						printw("%s", "\nyou can create a rider");
					} else {
						printw("%s%d%s", "\nyou need ", -(fractions_[turn_ - 1]->number_of_stars_ - Rider::kPrice_), " more stars to create a rider");
					}
					if (village_field[ptr_x_][ptr_y_]->CanCreate(fractions_[turn_ - 1]->number_of_stars_, Archer::kPrice_)) {
						printw("%s", "\nor you can create an archer.");
					} else {
						printw("%s%d%s", "\nyou need ", -(fractions_[turn_ - 1]->number_of_stars_ - Archer::kPrice_), " more stars to create an archer");
					}
					if (village_field[ptr_x_][ptr_y_]->CanCreate(fractions_[turn_ - 1]->number_of_stars_, Giant::kPrice_)) {
						printw("%s", "\nor you can create a giant.");
					} else {
						printw("%s%d%s", "\nyou need ", -(fractions_[turn_ - 1]->number_of_stars_ - Giant::kPrice_), " more stars to create a giant");
					}
					if (village_field[ptr_x_][ptr_y_]->CanCreate(fractions_[turn_ - 1]->number_of_stars_, Dragon::kPrice_)) {
						printw("%s", "\nor you can create a dragon.");
					} else {
						printw("%s%d%s", "\nyou need ", -(fractions_[turn_ - 1]->number_of_stars_ - Dragon::kPrice_), " more stars to create a dragon");
					}
				}
			}
		}
	}
	if (logic.IsUnitFieldEmpty(ptr_x_, ptr_y_) && logic.IsVillFieldEmpty(ptr_x_, ptr_y_)) {
		if (fractions_[turn_ - 1]->number_of_stars_ >= Village::kPrice) {
			printw("%s", "\nyou can create a village here");
		} else {
			printw("%s%d%s", "\nyou need ", -(fractions_[turn_ - 1]->number_of_stars_ - Village::kPrice), " more stars to create a village");
		}
	}

}


int Game::GetMaxScore() const {
	int max_score = 0;
	for (int i = 0; i < number_of_players_; ++i) {
		if (max_score < fractions_[i]->score_) {
			max_score = fractions_[i]->score_;
		}
	}
	return max_score;
}

void Game::PrintWinner() const {
	clear();
	const int max_score = GetMaxScore();
	for (int i = 0; i < number_of_players_; ++i) {
		if (fractions_[i]->score_ == max_score) {
			printw("%s%d%s", "Player number ", i + 1, " won!\n");
		}
	}
	printw("\n");
	printw("%s", "  00    10    10  01      00     1010    111       100100  10     01  10      111       100100  011010    10    10  01       101    1\n");
	printw("%s", "10    01  00  0111  01  10       01  01  01  1       11    01    101  01      01  1       11      10    01  00  0110  01   10       1\n");
	printw("%s", "10    01  00  0111  01  10       01  01  01  1       11    01    101  01      01  1       11      10    01  00  0110  01   10       1\n");
	printw("%s", "01    10  11  00    01  01   11  0011    0010101     00    11  11 11  00      0010101     00      00    01  11  00    11       01   1\n");
	printw("%s", "  10    00    10    10    100    11  01  10     01   01    0001   10  110101  10     01   01    111001    00    10    10    101     0\n");
	printw("\n%s", "press any key to shutdown ...");
	getch();
}


Game::~Game() {
	for (int i = 0; i < number_of_players_; ++i) {
		delete fractions_[i];
	}
}
