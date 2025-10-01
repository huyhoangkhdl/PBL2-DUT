#ifndef ROCK_H
#define ROCK_H
#include"Piece.h"

class Rock : public Piece{
public:
    Rock(PlayerColor c, int x,int y);
    bool isValidMove(int toX, int toY, Piece * const grid[10][9]) const override;
    std::string getSymbol() const override;
};
#endif