#pragma once





#include "MoveSensitivePiece.h"

class Rook : public MoveSensitivePiece {

public:
    Rook(Colour initColour = WHITE);
    ~Rook() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;
};



