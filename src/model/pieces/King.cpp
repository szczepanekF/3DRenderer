#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"
#include "model/pieces/Rook.h"

King::King(Colour initColour) : MoveSensitivePiece(initColour) {

}

King::~King() = default;

bool King::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return (!isSpotOccupiedByAlly(end) && isPieceAllowedToMove(start, end)) || canCastleTo(board, start, end);
}

bool King::isSpotOccupiedByAlly(const BoardSpot &spot) const {
    return spot.getPieceColour() == getColour();
}

bool King::isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) {
    int x = std::abs(end.getRow() - start.getRow());
    int y = std::abs(end.getColumn() - start.getColumn());
    return (x != 0 || y != 0) && x <= 1 && y <= 1;
}

bool King::canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    int colDiff = end.getColumn() - start.getColumn();
    int rowDiff = end.getRow() - start.getRow();
    int rookCol = (colDiff > 0) ? 7 : 0;
    std::shared_ptr<BoardSpot> rookSpot = board.getSpot(start.getRow(), rookCol);

    return isCastlingPossible(rowDiff, colDiff) && isRookValidForCastling(*rookSpot) &&
           !isCastlingBlocked(board, start, end);
}

bool King::isCastlingPossible(const int offsetX, const int offsetY) const {
    return offsetX == 0 && (abs(offsetY) == 2 || offsetY == 3 || offsetY == -4) && !wasMoved();
}

bool King::isRookValidForCastling(const BoardSpot &rookSpot) {
    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(rookSpot.getPiece());
    if (rook == nullptr) {
        return false;
    }
    if (rook->wasMoved()) {
        return false;
    }
    return true;
}

bool King::isCastlingBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    if (board.isSpotAttackedBy(start.getRow(), start.getColumn(), getOppositeColour())) {
        return true;
    }
    bool rightSideCastle = end.getColumn() > start.getColumn();
    int rookCol = rightSideCastle ? 7 : 0;
    int currentCol = start.getColumn();
    int spotsToCheck = abs(rookCol - currentCol) - 1;
    for (int i = 0; i < spotsToCheck; i++) {
        currentCol += rightSideCastle ? 1 : -1;

        std::shared_ptr<BoardSpot> midSpot = board.getSpot(start.getRow(), currentCol);
        if (midSpot->isOccupied() || board.isSpotAttackedBy(start.getRow(), currentCol,
                                                            getOppositeColour())) {
            return true;
        }
    }
    return false;
}

std::string King::getTexturePath() const {
    return Piece::getTexturePath() + "king.png";
}









