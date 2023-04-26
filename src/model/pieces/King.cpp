//
// Created by szczepan on 26.04.23.
//

#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"

King::King() {
    castlingAvailable = true;
}

King::~King() {

}

bool King::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) {
    board.getSpot(0,0);
    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    if (x == 0 && y == 0) return false;

    return x<=1 && y<=1;
}





