#include "model/pieces/Pawn.h"
#include "model/Board.h"

Pawn::Pawn(Colour initColour) : MoveSensitivePiece(initColour) {

}

Pawn::~Pawn() = default;

bool Pawn::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    int colDiff = end.getColumn() - start.getColumn();
    if (abs(colDiff) && end.isOccupied()) {
        return canTake(board, start, end);
    }

    return isPieceAllowedToMove(start, end) && !isMoveBlocked(board, start, end);
}

bool Pawn::isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) const {
    int colDiff = end.getColumn() - start.getColumn();
    if (abs(colDiff))
        return false;

    int rowDiff = end.getRow() - start.getRow();
    int moveDir = getMovingdirection();
    if (!wasMoved()) {
        return rowDiff == moveDir * 2 || rowDiff == moveDir;
    }
    return rowDiff == moveDir;
}

bool Pawn::isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return egsistsPieceBetweenStartAndEnd(board, start, end) || end.isOccupied();
}

bool Pawn::isSpotOccupiedByAlly(const BoardSpot &spot) const {
    return spot.getPieceColour() == getColour();
}

bool Pawn::egsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    int rowToCheck = start.getRow() + getMovingdirection();
    int columnToCheck = start.getColumn();
    int absoluteRowDiff = std::abs(end.getRow() - start.getRow());
    return absoluteRowDiff == 2 && board.getSpot(rowToCheck, columnToCheck)->isOccupied();
}

bool Pawn::canTake(const Board &, const BoardSpot &start, const BoardSpot &end) const {
    int moveDir = getMovingdirection();

    int rowDiff = end.getRow() - start.getRow();
    int colDiff = end.getColumn() - start.getColumn();
    return (abs(colDiff) == 1 && rowDiff == moveDir) && !isSpotOccupiedByAlly(end);
}

std::string Pawn::getTexturePath() const {
    return Piece::getTexturePath() + "pawn.png";
}

int Pawn::getMovingdirection() const {
    return (getColour() == WHITE) ? 1 : -1;
}
