#pragma once

#include "Piece.h"

class Knight : public Piece{


public:
    Knight(Colour initColour = WHITE);
    ~Knight() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;

};
