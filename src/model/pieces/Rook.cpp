//
// Created by szczepan on 26.04.23.
//

#include "model/pieces/Rook.h"
#include "model/Board.h"

Rook::Rook() {}

Rook::~Rook() {

}

bool Rook::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) {
    board.getSpot(0,0);
    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    if (x == 0 && y == 0) return false;

    return y == 0 || x == 0;
}
