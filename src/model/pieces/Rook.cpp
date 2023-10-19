#include "model/pieces/Rook.h"
#include "model/Board.h"

Rook::Rook(Colour initColour) : MoveSensitivePiece(initColour) {

}

Rook::~Rook() = default;

bool Rook::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {


    return isPieceAllowedToMove(start, end) && !isMoveBlocked(board, start, end);
}

std::string Rook::getTexturePath() const {
    return Piece::getTexturePath() + "rook.png";
}

bool Rook::isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) {
    int absoluteRowDiff = std::abs(end.getRow() - start.getRow());
    int absoluteColDiff = std::abs(end.getColumn() - start.getColumn());

    return (absoluteColDiff != 0 && absoluteRowDiff == 0) || (absoluteColDiff == 0 && absoluteRowDiff != 0);
}

bool Rook::isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return isSpotOccupiedByAlly(end) || exsistsPieceBetweenStartAndEnd(board, start, end);
}

bool Rook::isSpotOccupiedByAlly(const BoardSpot &spot) const {
    return spot.getPieceColour() == getColour();
}

bool Rook::exsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end) {
    int rowDiff = end.getRow() - start.getRow();
    int colDiff = end.getColumn() - start.getColumn();
    int x = std::abs(rowDiff);
    int y = std::abs(colDiff);

    int finalPosNumber = (x != 0) ? x : y;
    int nextPos = (x != 0) ? start.getRow() : start.getColumn();
    bool iterateThroughRow = (x) != 0;
    bool forward = !(colDiff < 0 || rowDiff < 0);

    int currentRow = start.getRow();
    int currentColumn = start.getColumn();
    for (int i = 1; i < finalPosNumber; i++) {
        nextPos += forward ? 1 : -1;
        if (iterateThroughRow) {
            currentRow = nextPos;
        } else {
            currentColumn = nextPos;
        }
        std::shared_ptr<BoardSpot> checkedSpot = board.getSpot(currentRow, currentColumn);
        if (checkedSpot->isOccupied()) {
            return true;
        }
    }
    return false;
}



