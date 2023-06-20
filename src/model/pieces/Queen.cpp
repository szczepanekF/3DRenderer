//
// Created by szczepan on 26.04.23.
//

#include <iostream>
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
    int steps = x;
    if (steps == 0) {
        steps = y;
    }
    std::shared_ptr<BoardSpot> checkedSpot;
    for (int i = 1; i < steps; i++) {
        if (diffX > 0) startingRow += 1;
        else if (diffX != 0) startingRow -= 1;


        if (diffY > 0) startingCol += 1;
        else if (diffY != 0) startingCol -= 1;

        checkedSpot = board.getSpot(startingRow,startingCol);
        if (checkedSpot->isOccupied()) return false;
    }
    return true;
}

