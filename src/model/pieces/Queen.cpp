#include "model/pieces/Queen.h"
#include "model/Board.h"

Queen::Queen(Colour initColour) : Piece(initColour) {

}


Queen::~Queen() = default;

bool Queen::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return isPieceAllowedToMove(start, end) && !isMoveBlocked(board, start, end);
}

bool Queen::isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) {
    int absoluteRowDiff = std::abs(end.getRow() - start.getRow());
    int absoluteColDiff = std::abs(end.getColumn() - start.getColumn());

    bool eitherOneEqualZero = (absoluteRowDiff == 0 || absoluteColDiff == 0);
    bool equalToEachother = absoluteRowDiff == absoluteColDiff;
    bool bothNotZero = !(absoluteRowDiff == 0 && absoluteColDiff == 0);
    return (eitherOneEqualZero && bothNotZero) || equalToEachother;
}

bool Queen::isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return isSpotOccupiedByAlly(end) || exsistsPieceBetweenStartAndEnd(board, start, end);
}

bool Queen::isSpotOccupiedByAlly(const BoardSpot &spot) const {
    return spot.getPieceColour() == getColour();
}

bool Queen::exsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end) {
    int rowDiff = end.getRow() - start.getRow();
    int colDiff = end.getColumn() - start.getColumn();
    int steps = rowDiff ? abs(rowDiff) : abs(colDiff);
    int currentRow = start.getRow();
    int currentCol = start.getColumn();
    for (int i = 0; i < steps - 1; i++) {
        if (rowDiff != 0) {
            currentRow += (rowDiff > 0) ? 1 : -1;
        }
        if (colDiff != 0) {
            currentCol += (colDiff > 0) ? 1 : -1;
        }
        std::shared_ptr<BoardSpot> checkedSpot = board.getSpot(currentRow, currentCol);
        if (checkedSpot->isOccupied()) {
            return true;
        }
    }
    return false;
}

std::string Queen::getTexturePath() const {
    return Piece::getTexturePath() + "queen.png";
}

