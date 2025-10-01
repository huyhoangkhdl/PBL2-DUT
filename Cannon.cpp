#include "Mylib.h"

Cannon::Cannon(PlayerColor c, int x, int y)
    : Piece(c, x, y) {}

bool Cannon::isValidMove(int toX, int toY, Piece* const grid[10][9]) const {
    // kiểm tra biên
    if (toX < 0 || toX > 9 || toY < 0 || toY > 8) return false;

    int dx = toX - getX();
    int dy = toY - getY();

    // pháo chỉ đi thẳng
    if (dx != 0 && dy != 0) return false;

    int numblock = 0;

    if (dx != 0) { // đi theo trục dọc
        int step = (dx > 0) ? 1 : -1;
        for (int i = getX() + step; i != toX; i += step) {
            if (grid[i][getY()] != nullptr) numblock++;
        }
    } else { // đi theo trục ngang
        int step = (dy > 0) ? 1 : -1;
        for (int j = getY() + step; j != toY; j += step) {
            if (grid[getX()][j] != nullptr) numblock++;
        }
    }

    // Nếu không có quân cản → ô đến phải trống
    if (numblock == 0) {
        return (grid[toX][toY] == nullptr);
    }

    // Nếu có đúng 1 quân cản → ô đến phải có quân (ăn quân)
    if (numblock == 1) {
        return (grid[toX][toY] != nullptr);
    }

    // Có nhiều hơn 1 quân cản → không đi được
    return false;
}

std::string Cannon::getSymbol() const {
    return (color == PlayerColor::RED) ? "RC" : "BC";
}
