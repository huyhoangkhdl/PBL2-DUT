#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"
/*#include "General.h"
#include "Advisor.h"
#include "Elephant.h"
#include "Knight.h"
#include "Rock.h"
#include "Cannon.h"
#include "Pawn.h"*/

struct Move {
    int fromX, fromY;
    int toX, toY;
    Piece* movedPiece;   // con trỏ quân đã di chuyển
    Piece* capturedPiece; // quân bị ăn (nếu có, NULL nếu không)
};
#endif