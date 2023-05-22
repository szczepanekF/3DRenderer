//
// Created by szczepan on 26.04.23.
//

#include "model/pieces/Pawn.h"
#include "model/Board.h"

Pawn::Pawn(Colour initColour) : Piece(initColour) {

}

Pawn::~Pawn() {

}

bool Pawn::canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const{
    if (board.getSpot(end.getRow(),end.getColumn())->getPieceColour() != getColour()) return false;
    int startingRow = start.getRow();
    int diffX = end.getRow() - startingRow;



    if (!hasMoved) {
        if (diffX != 2 && diffX != 1)
            return false;
        if (diffX == 1 && !end.isOccupied()) {
            return true;
        } else if (diffX == 1) return false;
        int pos1X = start.getRow() + 1;
        int pos1Y = start.getColumn();

        if (!board.getSpot(pos1X, pos1Y)->isOccupied() && !end.isOccupied()) {
            return true;
        } else return false;
    }
    if (diffX != 1) return false;
    if (end.isOccupied()) return false;
    return true;
}


void Pawn::move() {
    this->hasMoved = true;
}

bool Pawn::isMoved() const {
    return hasMoved;
}