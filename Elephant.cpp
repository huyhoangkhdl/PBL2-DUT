#include "Mylib.h"

Elephant::Elephant(PlayerColor c, int x, int y) : Piece(c, x, y) {} 
bool Elephant::isValidMove(int toX, int toY, Piece* const grid[10][9]) const {
    // Kiểm tra biên bàn cờ
    if (toX < 0 || toX > 9 || toY < 0 || toY > 8) return false;

    // Không vượt sông
    if (color == PlayerColor::RED && toX < 5) return false;  // đỏ không qua sông
    if (color == PlayerColor::BLACK && toX > 4) return false; // đen không qua sông

    int dx = abs(toX - x);
    int dy = abs(toY - y);

    // Di chuyển chéo 2 ô
    if (dx == 2 && dy == 2) {
        int eyeX = (x + toX) / 2;
        int eyeY = (y + toY) / 2;
        if (grid[eyeX][eyeY] != nullptr)
            return false; // bị chặn
        return true;
    }

    return false; // các nước đi khác không hợp lệ
}

std::string Elephant::getSymbol() const {
    return (color == PlayerColor::RED) ? "RE" : "BE";
}
