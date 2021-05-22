#include "game.h"

enum units { rider = 49, archer, dragon, giant };
enum buttons {left = 'a', right = 'd', down = 's', up = 'w', attack = 'g',
move_unit = 'm', form = 'p', create = 'c', next_turn = 'n', take_over = 't'};

Logic::Logic(Game* game_) : game(game_){
}

Village* Logic::GetUnitsVillage(Unit* unit) const {
	for (auto village : game->fractions_[game->turn_ - 1]->villages_) {
		for (auto unit_ : village->army_) {
			if (unit == unit_) {
				return village;
			}
		}
	}
	return nullptr;
}

void Logic::SwitchToNext() {
	const int number = game->number_of_players_ + 1;
	game->turn_ = (game->turn_ + 1) == number ? 1 : (game->turn_ + 1) % number;
	if (game->turn_ == 1) {
		++game->current_move_;
	}
	if (game->current_move_ != 1) {
		game->fractions_[game->turn_ - 1]->AddStars();
	}
	for (auto village : game->fractions_[game->turn_ - 1]->villages_) {
		for (auto unit : village->army_) {
			unit->can_move_ = true;
			unit->can_attack_ = true;
			unit->can_upgrade_ = true;
		}
	}
}

void Logic::MovePtr(int key) {
	switch (key) {
	case left:
		if (game->ptr_y_ > 0) {
			--game->ptr_y_;
		}
		break;
	case right:
		if (game->ptr_y_ < game->width - 1) {
			++game->ptr_y_;
		}
		break;
	case up:
		if (game->ptr_x_ > 0) {
			--game->ptr_x_;
		}
		break;
	case down:
		if (game->ptr_x_ < game->length - 1) {
			++game->ptr_x_;
		}
		break;
	default:
		break;
	}
}

void Logic::Move() {
	if (!IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ == game->turn_) {
		GetUnitsVillage(game->unit_field[game->ptr_x_][game->ptr_y_])->is_squad_ ? MoveSquad() : MoveUnit();
	}
}


void Logic::MoveUnit() {
	if (game->unit_field[game->ptr_x_][game->ptr_y_]->can_move_) {
		const int before_x = game->ptr_x_;
		const int before_y = game->ptr_y_;
		int k = left;
		game->FillField();
		game->Draw(COLOR_YELLOW);
		while (k != move_unit && (k == left || k == right || k == up || k == down)) {
			k = getch();
			MovePtr(k);
			game->Draw(COLOR_YELLOW);
		}
		const int step = abs(game->ptr_x_ - before_x) + abs(game->ptr_y_ - before_y);
		if (step <= game->unit_field[before_x][before_y]->max_number_of_steps_ &&
			game->unit_field[game->ptr_x_][game->ptr_y_] == nullptr) {
			game->unit_field[before_x][before_y]->Move(game->ptr_x_, game->ptr_y_);
		}
	}
}

void Logic::MoveSquad() {
	const int before_x = game->ptr_x_;
	const int before_y = game->ptr_y_;
	if (!game->unit_field[game->ptr_x_][game->ptr_y_]->can_move_) {
		return;
	}
	int k = left;
	game->FillField();
	game->Draw(COLOR_YELLOW);
	while (k != move_unit && (k == left || k == right || k == up || k == down)) {
		k = getch();
		MovePtr(k);
		game->Draw(COLOR_YELLOW);
	}
	const int step = abs(game->ptr_x_ - before_x) + abs(game->ptr_y_ - before_y);
	if (step <= game->unit_field[before_x][before_y]->max_number_of_steps_) {
		auto mv = new MergeVisitor(GetIsEmptyField(), game->ptr_x_, game->ptr_y_);
		Accept(mv, before_x, before_y);
		delete mv;
	}
}

void Logic::Attack() {
	if (!IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ == game->turn_) {
		GetUnitsVillage(game->unit_field[game->ptr_x_][game->ptr_y_])->is_squad_ ? AttackSquad() : AttackUnit();
	}
}

void Logic::AttackUnit() {
	if (!IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ == game->turn_
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->can_attack_) {
		const int before_x = game->ptr_x_;
		const int before_y = game->ptr_y_;
		int k = 'a';
		game->FillField();
		game->Draw(COLOR_RED);
		while (k != attack && (k == left || k == right || k == up || k == down)) {
			k = getch();
			MovePtr(k);
			game->Draw(COLOR_RED);
		}
		int radius = abs(game->ptr_x_ - before_x) + abs(game->ptr_y_ - before_y);
		if (!IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
			&& game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ != game->turn_
			&& radius <= game->unit_field[before_x][before_y]->attack_radius_) {
			game->unit_field[before_x][before_y]->MakeAttack(game->unit_field[game->ptr_x_][game->ptr_y_]);
			if (game->unit_field[game->ptr_x_][game->ptr_y_]->health_ <= 0) {
				game->fractions_[game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ - 1]->RemoveUnit(game->unit_field[game->ptr_x_][game->ptr_y_]);
				++game->unit_field[before_x][before_y]->number_of_kills_;
				if (game->unit_field[before_x][before_y]->CheckOnUpgrade()) {
					game->unit_field[before_x][before_y]->Upgrade();
				}
			}
		}
	}
}

void Logic::AttackSquad() {
	if (!game->unit_field[game->ptr_x_][game->ptr_y_]->can_attack_) {
		return;
	}
	const int before_x = game->ptr_x_;
	const int before_y = game->ptr_y_;
	int k = 'a';
	game->FillField();
	game->Draw(COLOR_RED);
	while (k != attack && (k == left || k == right || k == up || k == down)) {
		k = getch();
		MovePtr(k);
		game->Draw(COLOR_RED);
	}
	if (!IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ != game->turn_) {
		auto av = new AttackVisitor(game->unit_field[game->ptr_x_][game->ptr_y_]);
		Accept(av, before_x, before_y);
		delete av;
		if (game->unit_field[game->ptr_x_][game->ptr_y_]->health_ <= 0) {
			game->fractions_[game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ - 1]->RemoveUnit(game->unit_field[game->ptr_x_][game->ptr_y_]);
		}
    }
}

void Logic::Upgrade() {
	if (!IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->belongs_ == game->turn_ 
		&& GetUnitsVillage(game->unit_field[game->ptr_x_][game->ptr_y_])->is_squad_
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->can_upgrade_) {
		UpgradeSquad();
	}
	if (!IsVillFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->village_field[game->ptr_x_][game->ptr_y_]->belogns_ == game->turn_) {
		UpgradeVillage();
	}
}

void Logic::UpgradeSquad() {
	if (!game->unit_field[game->ptr_x_][game->ptr_y_]->can_upgrade_) {
		return;
	}
	auto uv = new UpgradeVisitor(&game->fractions_[game->turn_ - 1]->number_of_stars_);
	Accept(uv, game->ptr_x_, game->ptr_y_);
	delete uv;
}

void Logic::UpgradeVillage() {
	if (game->fractions_[game->turn_ - 1]->CanUpgrade()) {
		game->fractions_[game->turn_ - 1]->UpgradeVillage(game->village_field[game->ptr_x_][game->ptr_y_]);
	}
}

std::vector<std::vector<bool>> Logic::GetIsEmptyField() {
	std::vector<std::vector<bool>>  is_empty(game->length, std::vector<bool>(game->width, true));
	for (int i = 0; i < game->length; ++i) {
		for (int j = 0; j < game->width; ++j) {
			is_empty[i][j] = (game->unit_field[i][j] == nullptr);
		}
	}
	return is_empty;
}


void Logic::Create() {
	if (!IsVillFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->village_field[game->ptr_x_][game->ptr_y_]->belogns_ == game->turn_) {
		int k = getch();
		int before_number = game->village_field[game->ptr_x_][game->ptr_y_]->current_number_of_units_;
		switch (k) {
		case rider:
			if (game->village_field[game->ptr_x_][game->ptr_y_]->CanCreate((game->fractions_[game->turn_ - 1]->number_of_stars_), Rider::kPrice_)) {
				RiderCreator rider;
				game->village_field[game->ptr_x_][game->ptr_y_]->AddUnit(&rider, game->ptr_x_, game->ptr_y_);
				game->fractions_[game->turn_ - 1]->number_of_stars_ -= Rider::kPrice_;
				++game->fractions_[game->turn_ - 1]->score_;
			}
			break;
		case archer:
			if (game->village_field[game->ptr_x_][game->ptr_y_]->CanCreate((game->fractions_[game->turn_ - 1]->number_of_stars_), Archer::kPrice_)) {
				ArcherCreator archer;
				game->village_field[game->ptr_x_][game->ptr_y_]->AddUnit(&archer, game->ptr_x_, game->ptr_y_);
				game->fractions_[game->turn_ - 1]->number_of_stars_ -= Archer::kPrice_;
				++game->fractions_[game->turn_ - 1]->score_;
			}
			break;
		case dragon:
			if (game->village_field[game->ptr_x_][game->ptr_y_]->CanCreate((game->fractions_[game->turn_ - 1]->number_of_stars_), Dragon::kPrice_)) {
				DragonCreator dragon;
				game->village_field[game->ptr_x_][game->ptr_y_]->AddUnit(&dragon, game->ptr_x_, game->ptr_y_);
				game->fractions_[game->turn_ - 1]->number_of_stars_ -= Dragon::kPrice_;
				++game->fractions_[game->turn_ - 1]->score_;
			}
			break;
		case giant:
			if (game->village_field[game->ptr_x_][game->ptr_y_]->CanCreate((game->fractions_[game->turn_ - 1]->number_of_stars_), Giant::kPrice_)) {
				GiantCreator giant;
				game->village_field[game->ptr_x_][game->ptr_y_]->AddUnit(&giant, game->ptr_x_, game->ptr_y_);
				game->fractions_[game->turn_ - 1]->number_of_stars_ -= Giant::kPrice_;
				game->fractions_[game->turn_ - 1]->score_ += 2;
			}
			break;
		default:
			break;
		}
		if (game->village_field[game->ptr_x_][game->ptr_y_]->current_number_of_units_ > before_number
		&& game->village_field[game->ptr_x_][game->ptr_y_]->is_squad_){
			game->village_field[game->ptr_x_][game->ptr_y_]->army_.back()->can_move_ = false;
			game->village_field[game->ptr_x_][game->ptr_y_]->army_.back()->can_attack_ = false;
			game->village_field[game->ptr_x_][game->ptr_y_]->army_.back()->can_upgrade_ = false;
		}
	}
	else if (IsVillFieldEmpty(game->ptr_x_, game->ptr_y_) && IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)) {
		int k = getch();
		if (k == 53 && game->fractions_[game->turn_ - 1]->CanCreate()) {
			game->fractions_[game->turn_ - 1]->CreateVillage(game->ptr_x_, game->ptr_y_);
		}
	}
}

void Logic::TakeOverVillage() {
	if (!IsVillFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& !IsUnitFieldEmpty(game->ptr_x_, game->ptr_y_)
		&& game->village_field[game->ptr_x_][game->ptr_y_]->belogns_ != game->turn_
		&& game->unit_field[game->ptr_x_][game->ptr_y_]->can_move_) {
		const int belongs = game->village_field[game->ptr_x_][game->ptr_y_]->belogns_;
		game->fractions_[belongs - 1]->DestroyVillage(game->village_field[game->ptr_x_][game->ptr_y_]);
		game->fractions_[game->turn_ - 1]->AddVillage(game->ptr_x_, game->ptr_y_);
	}
}

bool Logic::IsUnitFieldEmpty(int x, int y) const {
	return game->unit_field[x][y] == nullptr;
}

bool Logic::IsVillFieldEmpty(int x, int y) const {
	return game->village_field[x][y] == nullptr;
}

void Logic::Accept(Visitor* visitor, int x, int y) {
	auto ptr = GetUnitsVillage(game->unit_field[x][y]);
	if (game->unit_field[x][y]->model_ == Archer(0, 0, 0).model_) {
		ArcherDec dec(ptr);
		dec.Accept(visitor);
	}
	else if (game->unit_field[x][y]->model_ == Rider(0, 0, 0).model_) {
		RiderDec dec(ptr);
		dec.Accept(visitor);
	}
	else if (game->unit_field[x][y]->model_ == Dragon(0, 0, 0).model_) {
		DragonDec dec(ptr);
		dec.Accept(visitor);
	}
	else if (game->unit_field[x][y]->model_ == Giant(0, 0, 0).model_) {
		GiantDec dec(ptr);
		dec.Accept(visitor);
	}
}

void Logic::FormSquad() {
	if (!IsVillFieldEmpty(game->ptr_x_, game->ptr_y_)) {
		std::vector<std::vector<bool>>  is_empty(GetIsEmptyField());
		game->village_field[game->ptr_x_][game->ptr_y_]->FormSquad();
		auto mv = new MergeVisitor(is_empty, game->ptr_x_, game->ptr_y_);
		int k = getch();
		switch (k) {
		case rider: {
			RiderDec rd(game->village_field[game->ptr_x_][game->ptr_y_]);
			rd.Accept(mv);
		}
			break;
		case archer: {
			ArcherDec ad(game->village_field[game->ptr_x_][game->ptr_y_]);
			ad.Accept(mv);
		}
			break;
		case dragon: {
			DragonDec dd(game->village_field[game->ptr_x_][game->ptr_y_]);
			dd.Accept(mv);
		}
			break;
		case giant: {
			GiantDec gd(game->village_field[game->ptr_x_][game->ptr_y_]);
			gd.Accept(mv);
		}
			break;
		default:
			break;
		}
		delete mv;
	}
}

void Logic::DisbandSquad() {
	if (!IsVillFieldEmpty(game->ptr_x_, game->ptr_y_)) {
		if (game->village_field[game->ptr_x_][game->ptr_y_]->is_squad_) {
			game->village_field[game->ptr_x_][game->ptr_y_]->DisbandSquad();
		}
	}
}