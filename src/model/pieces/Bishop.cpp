
#include "model/pieces/Bishop.h"
#include "model/Board.h"


Bishop::Bishop(Colour initColour) : Piece(initColour) {

}

Bishop::~Bishop() {

}

bool Bishop::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const {
    if (end.getPieceColour() == getColour()) return false;


    int startingRow = start.getRow();
    int startingCol = start.getColumn();
    int diffX = end.getRow() - startingRow;
    int diffY = end.getColumn() - startingCol;
    int x = std::abs(diffX);
    int y = std::abs(diffY);

    if (x == 0 && y == 0) return false;

    if (x != y) return false;


    bool forwardX = true;
    bool forwardY = true;
    if (diffX < 0) forwardX = false;
    if (diffY < 0) forwardY = false;

    std::shared_ptr<BoardSpot> checkedSpot;
    for (int i = 1; i < x; i++) {
        if (forwardX) startingRow += 1;
        else startingRow -= 1;
        if (forwardY) startingCol += 1;
        else startingCol -= 1;
        checkedSpot = board.getSpot(startingRow, startingCol);
        if (checkedSpot->isOccupied()) return false;
    }


    return true;
}



