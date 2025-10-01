#include "Mylib.h"

Knight::Knight(PlayerColor c, int x, int y) : Piece(c, x, y) {}
bool Knight::isValidMove(int toX, int toY, Piece*const grid[10][9]) const {
    if (toX < 0 || toX > 9 || toY < 0 || toY > 8) return false;

    int dx = toX - x;
    int dy = toY - y;

    // Kiểm tra nước đi chữ L
    if (!((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)))
        return false;

    // Kiểm tra chân mã
    if (abs(dx) == 2) {
        int legX = x + dx / 2;
        if (grid[legX][y] != nullptr) return false;
    } else {
        int legY = y + dy / 2;
        if (grid[x][legY] != nullptr) return false;
    }

    return true;
}

std::string Knight::getSymbol() const {
    return (color == PlayerColor::RED) ? "RH" : "BH";
}
