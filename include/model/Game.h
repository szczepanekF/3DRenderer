#pragma once

#include "Board.h"
#include "Move.h"
#include <deque>

class Game {
public:
    virtual ~Game();
    explicit Game(const Board &gameBoard);

    void turn();
    void resetGame();
    void rewindLastMove();
    void rewindAllMoves();
    void forwardOneMove();
    void forwardAllMoves();
private:

    Board gameBoard;
    std::deque<std::unique_ptr<Move>> moves;
    Colour turnColor;

    unsigned long long visibleMove;


    bool playerMove(int srcX, int srcY, int dstX, int dstY);
    bool isMoveValid();



};

