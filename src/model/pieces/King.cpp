//
// Created by szczepan on 26.04.23.
//

#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"
#include "model/pieces/Rook.h"

King::King(Colour initColour) : Piece(initColour) {
    castlingAvailable = true;
}

King::~King() {

}

bool King::canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const {
    Colour colour = board.getSpot(end.getRow(),end.getColumn())->getPieceColour();
    if (colour == getColour()) return false;

    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    if (x == 0 && y == 0) return false;

    if (x == 0 && y > 1 && castlingAvailable) {
        return canCastleTo(board,start,end);
    }
    if (x > 1 || y > 1) return false;
    return true;
}

bool King::canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    int diffY = start.getColumn() - end.getColumn();
    Colour enemy = WHITE;

    if (getColour() == WHITE) {
        enemy = BLACK;
    }

    if (board.isSpotAttackedBy(start.getRow(),start.getColumn(), enemy)) {
        return false;
    }
    int row = 0;
    if (getColour() == BLACK) {
        row = 7;
    }
    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(board.getSpot(row,7)->getPiece());

    int spotsToCheck = 2;
    if (diffY < 0) {
        spotsToCheck = 3;
        rook = std::dynamic_pointer_cast<Rook>(board.getSpot(row,0)->getPiece());
    }
    if (rook == nullptr) {
        return false;
    }
    if (rook->isMoved()) {
        return false;
    }


    int startingCol = start.getColumn();

    std::shared_ptr<BoardSpot> betweenSpot;

    for (int i = 0; i < spotsToCheck; i++) {
        if (diffY > 0) {
            startingCol += 1;
        } else {
            startingCol -= 1;
        }
        betweenSpot = board.getSpot(row,startingCol);
        if (betweenSpot->isOccupied() || board.isSpotAttackedBy(row,startingCol,enemy)) return false;
    }

    return true;
}






