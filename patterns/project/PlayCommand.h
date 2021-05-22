#ifndef PLAY_COMMAND_H
#define PLAY_COMMAND_H
#include "command.h"

class PlayCommand: public Command {
public:
    explicit PlayCommand(Game* game);
    void Execute() override;
};


#endif