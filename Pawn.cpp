#include "Pawn.h"

Pawn::Pawn(PlayerColor c, int x, int y) : Piece(c, x, y) {}

bool Pawn::isValidMove(int toX, int toY, Piece* const grid[10][9]) const  {
        if (toX < 0 || toX > 9 || toY < 0 || toY > 8) return false;

        int dx = toX - x;
        int dy = toY - y;

        if (color == PlayerColor::RED) {
            // RED đi từ dưới (x=9) lên trên (x=0)
            if (x >= 5) {
                // chưa qua sông: chỉ được đi thẳng lên
                return (dx == -1 && dy == 0);
            } else {
                // đã qua sông: đi thẳng hoặc ngang 1 bước
                return (dx == -1 && dy == 0) || (dx == 0 && abs(dy) == 1);
            }
        } else {
            // BLACK đi từ trên (x=0) xuống (x=9)
            if (x <= 4) {
                // chưa qua sông
                return (dx == 1 && dy == 0);
            } else {
                // đã qua sông
                return (dx == 1 && dy == 0) || (dx == 0 && abs(dy) == 1);
            }
        }
    }

    std::string Pawn:: getSymbol() const {
        return (color == PlayerColor::RED) ? "RP" : "BP";
    }