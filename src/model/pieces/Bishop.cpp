#include "model/pieces/Bishop.h"
#include "model/Board.h"


Bishop::Bishop(Colour initColour) : Piece(initColour) {

}

Bishop::~Bishop() = default;
bool Bishop::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return isPieceAllowedToMove(start, end) && !isMoveBlocked(board, start, end);
}

bool Bishop::isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) {
    int x = std::abs(end.getRow() - start.getRow());
    int y = std::abs(end.getColumn() - start.getColumn());

    return (x != 0 && y != 0) && x == y;
}

bool Bishop::isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    return isSpotOccupiedByAlly(end) || exsistsPieceBetweenStartAndEnd(board, start, end);
}

bool Bishop::isSpotOccupiedByAlly(const BoardSpot &spot) const {
    return spot.getPieceColour() == getColour();
}

bool Bishop::exsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end) {
    int rowDiff = end.getRow() - start.getRow();
    int colDiff = end.getColumn() - start.getColumn();

    int moveLength = std::abs(rowDiff);
    int currentRow = start.getRow();
    int currentCol = start.getColumn();
    int incrementX = (rowDiff >= 0) ? 1 : -1;
    int incrementY = (colDiff >= 0) ? 1 : -1;

    for (int i = 0; i < moveLength - 1; i++) {
        currentRow += incrementX;
        currentCol += incrementY;
        std::shared_ptr<BoardSpot> checkedSpot = board.getSpot(currentRow, currentCol);

        if (checkedSpot->isOccupied()) {
            return true;
        }
    }
    return false;
}

std::string Bishop::getTexturePath() const {
    return Piece::getTexturePath() + "bishop.png";
}

