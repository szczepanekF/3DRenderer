#include "model/BoardSpot.h"
#include "model/pieces/Piece.h"
#include <exception>

BoardSpot::BoardSpot(int row, int column, std::shared_ptr<Piece> piece) : row(row), column(column),
                                                                          piece(std::move(piece)) {


}

int BoardSpot::getRow() const {
    return row;
}

int BoardSpot::getColumn() const {
    return column;
}

std::shared_ptr<Piece> BoardSpot::replacePiece(std::shared_ptr<Piece> replacingPiece) {
    auto pieceHolder = std::move(this->piece);
    this->piece = std::move(replacingPiece);
    return pieceHolder;
}

Colour BoardSpot::getPieceColour() const {
    if (piece == nullptr) return NO_COLOUR;
    return piece->getColour();
}

Colour BoardSpot::getPieceOppositeColour() const {
    if (piece == nullptr) return NO_COLOUR;
    return piece->getOppositeColour();
}


bool BoardSpot::isOccupied() const {
    if (piece == nullptr) return false;
    return true;
}

std::shared_ptr<Piece> BoardSpot::getPiece() const {
    return piece;
}


