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
private:
    static Game gameInstance;
    Board gameBoard;
    std::deque<std::unique_ptr<Move>> moves;
    Colour colourTurn;

    bool playerMove(int srcX, int srcY, int dstX, int dstY);
    bool isMoveValid();


};

