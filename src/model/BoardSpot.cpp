#include "model/BoardSpot.h"
#include "model/pieces/Piece.h"
#include "model/pieces/Rook.h"
#include <exception>

BoardSpot::BoardSpot(int row, int column, std::shared_ptr<Piece> piece) : row(row), column(column),
                                                                          piece(piece) {


}

int BoardSpot::getRow() const {
    return row;
}

int BoardSpot::getColumn() const {
    return column;
}

std::shared_ptr<Piece> BoardSpot::replacePiece(std::shared_ptr<Piece> replacingPiece) {
    auto pieceHolder = this->piece;
    this->piece = replacingPiece;
    return pieceHolder;
}

Colour BoardSpot::getPieceColour() const {
    if (piece == nullptr) return NO_COLOUR;
    return piece->getColour();
}

bool BoardSpot::isOccupied() const {
    if (piece == nullptr) return false;
    return true;
}

std::shared_ptr<Piece> BoardSpot::getPiece() const {

    return piece;
}


