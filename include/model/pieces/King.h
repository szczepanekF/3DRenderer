#pragma once

#include "Piece.h"


class BoardSpot;
class Board;
class King : public Piece{
private:
    bool castlingAvailable;

public:
    King(Colour initColour = WHITE);
    ~King() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;
//    bool canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end);

};


