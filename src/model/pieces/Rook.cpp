#include "model/pieces/Rook.h"
#include "model/Board.h"

Rook::Rook(Colour initColour) : Piece(initColour) {

}

Rook::~Rook() {

}

bool Rook::canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const {
    if (board.getSpot(end.getRow(),end.getColumn())->getPieceColour() == getColour()) return false;

    int startingRow = start.getRow();
    int startingCol = start.getColumn();
    int diffX = end.getRow() - startingRow;
    int diffY = end.getColumn() - startingCol;
    int x = std::abs(diffX);
    int y = std::abs(diffY);

    if (y != 0 && x != 0) return false;

    int finalPosNumber;
    int nextPos;
    bool iterateThroughRow = true;
    bool forward = true;
    if (x == 0) {
        iterateThroughRow = false;
        if (diffY < 0) forward = false;
        finalPosNumber = y;
        nextPos = start.getColumn();
    } else {
        if (diffX < 0) forward = false;
        finalPosNumber = x;
        nextPos = start.getRow();
    }


    std::shared_ptr<BoardSpot> checkedSpot;
    for (int i = 1; i < finalPosNumber; i++) {
        if (forward) nextPos += 1;
        else nextPos -= 1;

        if (iterateThroughRow) {
            checkedSpot = board.getSpot(nextPos,start.getColumn());
        } else {
            checkedSpot = board.getSpot( start.getRow(),nextPos);
        }

        if (checkedSpot->isOccupied()) return false;
    }

    return true;
}

void Rook::move() {
    this->hasMoved = true;
}

bool Rook::isMoved() const {
    return hasMoved;
}


