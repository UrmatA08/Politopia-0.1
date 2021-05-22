#ifndef COMMAND_H
#define COMMAND_H

class Game;

class Command {
public:
    Game* game_;

    virtual ~Command() {}
    virtual void Execute() = 0;
};

#endif