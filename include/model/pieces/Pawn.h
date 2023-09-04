#pragma once

#include <utility>
#include "MoveSensitivePiece.h"


class Pawn : public MoveSensitivePiece {

public:
    Pawn(Colour initColour = WHITE);
    ~Pawn() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const override;
    bool canTake(const Board &board, const BoardSpot &start, const BoardSpot &end) const override;
};

