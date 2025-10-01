#ifndef ELEPHANT_H
#define ELEPHANT_H
#include "Piece.h"
#include<string>

class Elephant : public Piece {
public:
    Elephant(PlayerColor c, int x, int y);

    bool isValidMove(int toX, int toY, Piece* const grid[10][9]) const override;

    std::string getSymbol() const override;
};

#endif