#ifndef PRINTW_COMMAND_H
#define PRINTW_COMMAND_H
#include "command.h"

class PrintWCommand: public Command {
public:
    explicit PrintWCommand(Game* game);
    void Execute() override;
};


#endif