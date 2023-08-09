//
// Created by szczepan on 26.04.23.
//

#include <iostream>
#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"
#include "model/pieces/Rook.h"

King::King(Colour initColour) : Piece(initColour) {
    castlingAvailable = true;
}

King::~King() {

}

bool King::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    Colour colour = board.getSpot(end.getRow(), end.getColumn())->getPieceColour();
    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    if (colour == getColour()) {
        if (isCastlingPossible(x, y)) {
            return canCastleTo(board, start, end);
        }
        return false;
    }

    if (x == 0 && y == 0) return false;

    if (x > 1 || y > 1) return false;
    return true;
}


bool King::isCastlingPossible(const int offsetX, const int offsetY) const {
    return offsetX == 0 && offsetY > 1 && castlingAvailable;
}


bool King::canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    int diffY = end.getColumn() - start.getColumn();

    if (!isRookValidForCastling(end)) {
        return false;
    }

    if (board.isSpotAttackedBy(start.getRow(), start.getColumn(), getOppositeColour())) {
        return false;
    }

    int startingCol = start.getColumn();
    int spotsToCheck = abs(diffY) - 1;
    for (int i = 0; i < spotsToCheck; i++) {
        if (diffY > 0) {
            startingCol += 1;
        } else {
            startingCol -= 1;
        }
        std::shared_ptr<BoardSpot> midSpot = board.getSpot(start.getRow(), startingCol);
        if (midSpot->isOccupied() || board.isSpotAttackedBy(start.getRow(), startingCol,
                                                            getOppositeColour())) {
            return false;
        }
    }
    return true;
}

bool King::isRookValidForCastling(const BoardSpot &rookSpot) const {
    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(rookSpot.getPiece());
    if (rook == nullptr) {
        return false;
    }
    if (rook->isMoved()) {
        return false;
    }
    return true;
}






