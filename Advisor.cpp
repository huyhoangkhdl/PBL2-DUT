#include "Mylib.h"

Advisor::Advisor(PlayerColor c, int x, int y) : Piece(c, x, y) {}

bool Advisor::isValidMove(int toX, int toY, Piece* const grid[10][9]) const {
    if (toX < 0 || toX > 9 || toY < 0 || toY > 8) return false;
    if (toY < 3 || toY > 5) return false;

    if (color == PlayerColor::RED) {
        if (toX < 7 || toX > 9) return false;
    } else {
        if (toX < 0 || toX > 2) return false;
   	}

    int dx = abs(toX - x);
    int dy = abs(toY - y);
    return (dx == 1 && dy == 1);
}

std::string Advisor::getSymbol() const {
    return (color == PlayerColor::RED) ? "RA" : "BA";
}
