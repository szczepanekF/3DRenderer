#pragma once

#include "Board.h"
#include "Move.h"
#include <deque>

class Game {
    Board gameBoard;
    std::deque<Move> moves;

};

