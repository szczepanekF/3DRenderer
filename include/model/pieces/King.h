#pragma once

#include "MoveSensitivePiece.h"


class BoardSpot;
class Board;
class King : public MoveSensitivePiece {

public:
    King(Colour initColour = WHITE);
    ~King() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;
    bool canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const;

private:


    bool isCastlingPossible(const int offsetX, const int offsetY) const;
    bool isRookValidForCastling(const BoardSpot &rookSpot) const;

};


