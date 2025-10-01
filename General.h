#ifndef GENERAL_H
#define GENERAL_H
#include "Piece.h"
#include <string>
class General : public Piece {
public:
    General(PlayerColor c, int x, int y);

    bool isValidMove(int toX, int toY, Piece* const grid[10][9]) const override;

    std::string getSymbol() const override;
};
#endif