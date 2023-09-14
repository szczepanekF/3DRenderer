//
// Created by szczepan on 25.04.23.
//

#include "model/pieces/Piece.h"

Piece::Piece(Colour initColour) : colour(initColour) {

}


bool Piece::canTake(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return canMoveTo(board, start, end);
}

Colour Piece::getColour() const {
    return colour;
}

Colour Piece::getOppositeColour() const {
    if (colour == WHITE) {
        return BLACK;
    }
    return WHITE;
}

std::string Piece::getTexturePath() const {
    if (colour == WHITE) {
        return "../../images/white/";
    }
    return "../../images/black/";
}


