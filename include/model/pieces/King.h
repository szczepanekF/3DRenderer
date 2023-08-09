#pragma once

#include "Piece.h"


class BoardSpot;
class Board;
class King : public Piece{

public:
    King(Colour initColour = WHITE);
    ~King() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;

private:
    bool castlingAvailable;

    bool canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const;
    bool isCastlingPossible(const int offsetX, const int offsetY) const;
    bool isRookValidForCastling(const BoardSpot &rookSpot) const;

};


