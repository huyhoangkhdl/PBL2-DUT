#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
private:
    Board board;
    bool vsAI;   // true = Người vs AI, false = Người vs Người

public:
    Game(bool aiMode = true);  // constructor

    void start(); // bắt đầu ván game
};

#endif // GAME_H
