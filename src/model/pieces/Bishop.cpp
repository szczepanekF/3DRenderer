
#include "model/pieces/Bishop.h"
#include "model/Board.h"


Bishop::Bishop(Colour initColour) : Piece(initColour) {

}

Bishop::~Bishop() {

}

bool Bishop::canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) {
    board.getSpot(0,0);
    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    if (x == 0 && y == 0) return false;

    return x == y;
}



