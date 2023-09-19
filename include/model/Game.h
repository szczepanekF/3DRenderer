#pragma once

#include "Board.h"
#include "RegularMove.h"
#include <deque>

class Game {
public:
    virtual ~Game();
    explicit Game(const Board &gameBoard);


    bool playerMove(int srcX, int srcY, int dstX, int dstY);
    void resetGame();
    void makePromotionMove(int srcX, int srcY, int pieceID);
    void rewindLastMove();
    void rewindAllMoves();
    void forwardOneMove();
    void forwardAllMoves();

    Colour getTurnColour() const;
private:

    Board gameBoard;
    std::deque<std::unique_ptr<Move>> moves;
    Colour turnColour;

    unsigned long long visibleMove;




};

