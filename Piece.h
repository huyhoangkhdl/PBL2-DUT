#ifndef PIECE_H
#define PIECE_H
#include <string>
enum class PlayerColor { RED, BLACK };
class Piece{
protected:
    PlayerColor color;
    bool alive;
    int x, y;
public:
    Piece(PlayerColor c, int x, int y) : color(c), x(x), y(y) {}
    virtual ~Piece() = default;

    virtual bool isValidMove(int toX, int toY, Piece* const grid[10][9]) const = 0;
    virtual std::string getSymbol() const = 0;

    PlayerColor getColor() const { return color; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    int getX() const { return x; }
    int getY() const { return y; }
};
#endif