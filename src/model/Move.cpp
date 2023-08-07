//
// Created by szczepan on 26.04.23.
//
#include "model/Board.h"
#include "model/Move.h"


// TODO finish this function
bool Move::canBeMade(const Board &board) {
    if (!areSameColour()) return false;
    std::shared_ptr<Piece> piece = fromSpot->getPiece();

    if (!piece->canMoveTo(board, *fromSpot, *toSpot)) {
        return false;
    }

    Colour fromSpotColour = fromSpot->getPieceColour();
    std::shared_ptr<BoardSpot> kingSpot = board.getKingSpotOfColour(fromSpotColour);
    Colour enemyColour = BLACK;
    if (fromSpotColour == BLACK) {
        enemyColour = WHITE;
    }

    if (kingSpot->getPiece().get() != piece.get()) {
//        makeMove();
        if (board.isSpotAttackedBy(kingSpot->getRow(),kingSpot->getColumn(),enemyColour)) {
            return false;
        }

//        undoMove();
    }


    return false;
}

Move::Move(const std::shared_ptr<BoardSpot> &fromSpot, const std::shared_ptr<BoardSpot> &toSpot) : fromSpot(fromSpot),
                                                                                                   toSpot(toSpot) {}

bool Move::areSameColour() {
    Colour firstSpotPieceColour = fromSpot->getPieceColour();
    Colour secondSpotPieceColour = toSpot->getPieceColour();
    if (firstSpotPieceColour == secondSpotPieceColour) {
        return true;
    }
    return false;
}
