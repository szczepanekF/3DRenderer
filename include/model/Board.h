#pragma once


#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "BoardSpot.h"

#define BOARD_LENGTH 8

class Board {

public:
    Board();
    void initBoard();


    std::shared_ptr<BoardSpot> getSpot(unsigned int row, unsigned int col) const;

private:
    void initializeOccupiedSpots();
    void initializeOneSideSpots(Colour side);
    std::shared_ptr<BoardSpot> board[BOARD_LENGTH][BOARD_LENGTH];
};


#endif //CHESS_BOARD_H
