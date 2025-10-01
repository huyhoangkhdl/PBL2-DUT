#ifndef CANNON_H
#define CANNON_H
#include "Piece.h"
#include <string>
class Cannon : public Piece {
public:
    Cannon(PlayerColor c, int x, int y);

    bool isValidMove(int toX, int toY, Piece*const grid[10][9]) const override;

    std::string getSymbol() const override;
};
#endif
