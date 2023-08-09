//
// Created by szczepan on 26.04.23.
//

#include "model/pieces/Knight.h"
#include "model/Board.h"

Knight::Knight(Colour initColour) : Piece(initColour) {

}

Knight::~Knight() {

}

bool Knight::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    Colour colour = board.getSpot(end.getRow(), end.getColumn())->getPieceColour();
    if (colour == getColour()) return false;

    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    if (x == 0 && y == 0) return false;

    return x * y == 2;
}

