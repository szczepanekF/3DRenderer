//
// Created by szczepan on 26.04.23.
//

#include "model/pieces/Queen.h"
#include "model/Board.h"

Queen::Queen(Colour initColour) : Piece(initColour) {

}


Queen::~Queen() {

}

bool Queen::canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const {
    if (board.getSpot(end.getRow(),end.getColumn())->getPieceColour() == getColour()) return false;
    int startingRow = start.getRow();
    int startingCol = start.getColumn();
    int diffX = end.getRow() - startingRow;
    int diffY = end.getColumn() - startingCol;
    int x = std::abs(diffX);
    int y = std::abs(diffY);

    if ((y != 0 && x != 0) && x != y) return false;

    bool forwardX = true;
    bool forwardY = true;
    if (diffX < 0) forwardX = false;
    if (diffY < 0) forwardY = false;
    std::shared_ptr<BoardSpot> checkedSpot;
    for (int i = 1; i < x; i++) {
        if (forwardX) startingRow += 1;
        else if (diffX == 0) startingRow = 0;
        else startingRow -= 1;

        if (forwardY) startingCol += 1;
        else if (diffY == 0) startingCol = 0;
        else startingCol -= 0;

        checkedSpot = board.getSpot(startingRow,startingCol);
        if (checkedSpot->isOccupied()) return false;
    }
    return true;
}

