#include "PrintWCommand.h"
#include "game.h"

PrintWCommand::PrintWCommand(Game* game) {
    game_ = game;
}

void PrintWCommand::Execute() {
    game_->PrintWinner();
}