#pragma once


#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "BoardSpot.h"

#define BOARD_LENGTH 8

class Board {

public:
    Board();
    void initBoard();


    std::shared_ptr<BoardSpot> getSpot(long unsigned  row, long unsigned  col) const;

private:
    void initializeOccupiedSpots();
    void initializeOneSideSpots(bool whiteSide);
    //std::shared_ptr<std::shared_ptr<std::shared_ptr<BoardSpot>[]>[]> board;
    std::array<std::array<std::shared_ptr<BoardSpot>, BOARD_LENGTH>,BOARD_LENGTH> board;
};


#endif //CHESS_BOARD_H
