#include "model/pieces/MoveSensitivePiece.h"

void MoveSensitivePiece::move() {
    hasMoved = true;
}

void MoveSensitivePiece::undoMove() {
    hasMoved = false;
}

bool MoveSensitivePiece::wasMoved() const {
    return hasMoved;
}

MoveSensitivePiece::MoveSensitivePiece(Colour initColour) : Piece(initColour) {
    hasMoved = false;
}

MoveSensitivePiece::~MoveSensitivePiece() = default;
