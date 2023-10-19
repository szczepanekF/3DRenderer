#include "model/pieces/Knight.h"
#include "model/Board.h"

Knight::Knight(Colour initColour) : Piece(initColour) {

}

Knight::~Knight() = default;

bool Knight::canMoveTo(const Board&, const BoardSpot &start, const BoardSpot &end) const {
    return !isSpotOccupiedByAlly(end) && isPieceAllowedToMove(start, end);
}

bool Knight::isSpotOccupiedByAlly(const BoardSpot &spot) const {
    return spot.getPieceColour() == getColour();
}

bool Knight::isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) {
    int x = std::abs(start.getRow() - end.getRow());
    int y = std::abs(start.getColumn() - end.getColumn());
    return x * y == 2;
}



std::string Knight::getTexturePath() const {
    return Piece::getTexturePath()+"knight.png";
}



