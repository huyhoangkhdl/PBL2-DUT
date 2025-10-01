#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstring>
#include "Piece.h"
#include "General.h"
#include "Advisor.h"
#include "Elephant.h"
#include "Knight.h"
#include "Rock.h"
#include "Cannon.h"
#include "Pawn.h"
#include "Move.h"
#include "MoveStack.h"
#include "MyVector.h"
class Board {
private:
    MyVector<Piece*> allPieces;
    Piece* grid[10][9];
    bool attackedByRed[10][9];
    bool attackedByBlack[10][9];
    PlayerColor currentPlayer;
    General* redGeneral;
    General* blackGeneral;
    bool is_Red_over;
    bool is_Black_over;
    bool is_valid_move_piece[10][9];

    MoveStack history;
    MoveStack redoStack;

    void clearAttackMap();
    void markAttacks(Piece* p);
    bool generalsFacing() const;
    bool isInCheck(PlayerColor side);

public:
    Board();
    ~Board();

    void initializePieces();
    void printBoard() const;

    bool movePiece(int fromX, int fromY, int toX, int toY);
    bool canMove(int fromX, int fromY, int toX, int toY);
    bool canMoveForAI(int fromX, int fromY, int toX, int toY, PlayerColor side);
    bool simulateMove(const Move& m);

    bool is_game_over();
    bool get_is_over_game();
    void check_piece(int fromX, int fromY);

    void undoMove();
    void redoMove();

    void rebuildAttackMap();
    MyVector<Move> generateMoves(PlayerColor side);
    int evaluate(PlayerColor side);
    int minimax(int depth, int alpha, int beta, PlayerColor side);
    Move findBestMove(PlayerColor side, int depth);

    PlayerColor getCurrentPlayer() const;
    Piece* getPiece(int x, int y) const;
    void setCurrentPlayer(PlayerColor side);
};

#endif // BOARD_H
