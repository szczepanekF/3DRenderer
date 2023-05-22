#pragma once

#include <utility>
#include "Piece.h"


class Pawn : public Piece{

public:
    Pawn(Colour initColour = WHITE);
    ~Pawn() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;

    void move();

    bool isMoved() const;
private:
    bool hasMoved = false;
};

