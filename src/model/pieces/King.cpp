//
// Created by szczepan on 26.04.23.
//

#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"

King::King(Colour initColour) : Piece(initColour) {
    castlingAvailable = true;
}

King::~King() {

}

bool King::canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const {
    if (board.getSpot(end.getRow(),end.getColumn())->getPieceColour() != getColour()) return false;

    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    if (x == 0 && y == 0) return false;

    if (x > 1 || y > 1) return false;

    if (castlingAvailable) {
        //TODO castling
    }

    return true;
}

//bool King::canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end) {
//    if (!castlingAvailable) return castlingAvailable;
//
//
//    return false;
//}






