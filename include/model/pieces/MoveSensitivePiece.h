#pragma once

#include "Piece.h"


class MoveSensitivePiece : public Piece {
public:
    explicit MoveSensitivePiece(Colour initColour);
    ~MoveSensitivePiece() override;

    void move();
    void undoMove();
    bool wasMoved() const;

private:
    bool hasMoved = false;
};

