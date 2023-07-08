//
// Created by szczepan on 25.04.23.
//

#include "model/pieces/Piece.h"

Piece::Piece(Colour initColour): colour(initColour) {

}

Colour Piece::getColour() const {
    return colour;
}

bool Piece::canTake(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return canMoveTo(board,start,end);
}


