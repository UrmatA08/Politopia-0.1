#include "game.h"

int main() {
	int counter = 0;
	while (true) {
		try {
			counter = SetNumberOfPlayers();
			break;
		}
		catch (WrongNumber) {
			std::cout << "\nWrong number of players.\n";
		}
	}
	initscr();
    curs_set(0);
	start_color();
    keypad(stdscr, true); 
	Game game(counter);
	std::vector<Command*> commands;
	commands.push_back(new PlayCommand(&game));
	commands.push_back(new PrintWCommand(&game));
	for (auto it : commands){
		it->Execute();
	}
	endwin();
	return 0;
}