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
    std::shared_ptr<BoardSpot> getKingSpotOfColour(Colour colour) const;

    bool isSpotAttackedBy(int row, int col, Colour colour) const;

    void setEnPassantCol(int col);
    int getEnPassantCol() const;

    std::string getSpotTexturePath(int row, int col) const;
private:
    void initializeOccupiedSpots();
    void initializeEmptySpots();
    void initializeOneSideSpots(Colour sideColour);
    void fillWithSameColour(std::vector<std::shared_ptr<BoardSpot>> &vec, Colour colour) const;

    void createFirstRow(Colour sideColour);
    void createPawnRow(Colour sideColour);
    void setPositionFactoryColour(Colour colour) const;
    std::shared_ptr<BoardSpot> board[BOARD_LENGTH][BOARD_LENGTH];
    int enPassantCol;
};


