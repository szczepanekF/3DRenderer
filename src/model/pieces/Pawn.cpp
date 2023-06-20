//
// Created by szczepan on 26.04.23.
//

#include <iostream>
#include "model/pieces/Pawn.h"
#include "model/Board.h"

Pawn::Pawn(Colour initColour) : Piece(initColour) {

}

Pawn::~Pawn() {

}

bool Pawn::canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const{
    if (end.getPieceColour() != NO_COLOUR && end.getPieceColour() != getColour()) return false;
    int startingRow = start.getRow();
    int diffX = end.getRow() - startingRow;
    int moveDir = 1;
    if(getColour() == BLACK) {
        moveDir = -1;
    }


    if (!hasMoved) {
        if (diffX != moveDir * 2 && diffX != moveDir * 1) {
            return false;
        }
        if (diffX == moveDir * 1 && !end.isOccupied()) {
            return true;
        } else if (diffX == moveDir * 1) return false;
        int pos1X = start.getRow() + moveDir * 1;
        int pos1Y = start.getColumn();

        if (!board.getSpot(pos1X, pos1Y)->isOccupied() && !end.isOccupied()) {
            return true;
        } else return false;
    }
    if (diffX != moveDir * 1) return false;
    if (end.isOccupied()) return false;
    return true;
}


void Pawn::move() {
    this->hasMoved = true;
}

bool Pawn::isMoved() const {
    return hasMoved;
}