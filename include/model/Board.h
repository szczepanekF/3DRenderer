#pragma once

#include "BoardSpot.h"
#include "model/pieces/King.h"
#include <vector>


#define BOARD_LENGTH 8


class Board {

public:
    Board();
    void initBoard();
    void clearBoard();

    std::shared_ptr<BoardSpot> getSpot(int row, int col) const;
    std::vector<std::shared_ptr<BoardSpot>> getPiecesOfColour(Colour colour) const;
    std::shared_ptr<King> getKingOfColour(Colour colour) const;
    bool isSpotAttackedBy(int x, int y, Colour colour) const;

private:
    void initializeOccupiedSpots();
    void initializeEmptySpots();
    void initializeOneSideSpots(Colour side);
    void fillWithSameColour(std::vector<std::shared_ptr<BoardSpot>> &vec, Colour colour) const;


    std::shared_ptr<BoardSpot> board[BOARD_LENGTH][BOARD_LENGTH];
};


