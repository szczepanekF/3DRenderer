
#include "model/pieces/Pawn.h"
#include "model/Board.h"

Pawn::Pawn(Colour initColour) : MoveSensitivePiece(initColour) {

}

Pawn::~Pawn() {

}

bool Pawn::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    if (end.getPieceColour() == getColour()) return false;
    int startingRow = start.getRow();
    int startingCol = start.getColumn();
    int diffX = end.getRow() - startingRow;
    int diffY = end.getColumn() - startingCol;

    if (abs(diffY) > 1) {
        return false;
    }

    int moveDir = 1;
    if (getColour() == BLACK) {
        moveDir = -1;
    }

    if (abs(diffY) == 1 && diffX == moveDir) {
        if (end.isOccupied()) return true;
        else return false;
    }


    if (!wasMoved()) {
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

bool Pawn::canTake(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    Colour colour = board.getSpot(end.getRow(), end.getColumn())->getPieceColour();
    if (colour == getColour()) return false;
    int startingRow = start.getRow();
    int startingCol = start.getColumn();
    int diffX = end.getRow() - startingRow;
    int diffY = end.getColumn() - startingCol;

    int moveDir = 1;
    if (getColour() == BLACK) {
        moveDir = -1;
    }

    if (abs(diffY) != 1 || diffX != moveDir) {
        return false;
    }
    return true;
}

std::string Pawn::getTexturePath() const {
    return Piece::getTexturePath()+"pawn.png";
}
