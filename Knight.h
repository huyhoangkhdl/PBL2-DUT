#ifndef KNIGHT_H
#define KNIGHT_H
#include"Piece.h"

class Knight : public Piece {
public:
    Knight(PlayerColor c, int x, int y);

    bool isValidMove(int toX, int toY, Piece* const grid[10][9]) const override;

    std::string getSymbol() const override;
};
#endif