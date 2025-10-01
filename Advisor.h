#ifndef ADVISOR_H
#define ADVISOR_H
#include "Piece.h"
class Advisor : public Piece {
public:
    Advisor(PlayerColor c, int x, int y);

    bool isValidMove(int toX, int toY, Piece* const grid[10][9]) const;

    std::string getSymbol() const;
};
#endif