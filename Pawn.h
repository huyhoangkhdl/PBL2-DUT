#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"
#include<string>
class Pawn : public Piece {
public:
    Pawn(PlayerColor c, int x, int y);
    bool isValidMove(int toX, int toY, Piece* const grid[10][9]) const override;
    std::string getSymbol() const override;
};
#endif
