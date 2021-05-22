#include "PlayCommand.h"
#include "game.h"

PlayCommand::PlayCommand(Game* game) {
    game_ = game;
}

void PlayCommand::Execute() {
    game_->Play();
}