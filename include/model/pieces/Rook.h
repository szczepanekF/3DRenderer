#pragma once





#include "Piece.h"

class Rook : public Piece{

public:
    Rook(Colour initColour = WHITE);
    ~Rook() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;

    void move();

    bool isMoved() const;
private:
    bool hasMoved = false;
};



