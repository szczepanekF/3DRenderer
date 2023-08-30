#include "model/Board.h"
#include "model/Move.h"

Move::Move(const std::shared_ptr<BoardSpot> &fromSpot, const std::shared_ptr<BoardSpot> &toSpot) : fromSpot(fromSpot),
                                                                                                   toSpot(toSpot) {}

bool Move::canBeMade(const Board &board) {
    if (arePiecesSameColour()) {
        if (isCastling(board)) {
            return true;
        }
        return false;
    }
    std::shared_ptr<Piece> fromPiece = fromSpot->getPiece();


    if (fromPiece == nullptr) {
        return false;
    }

    if (!fromPiece->canMoveTo(board, *fromSpot, *toSpot)) {
        return false;
    }



    Colour fromSpotColour = fromSpot->getPieceColour();
    std::shared_ptr<BoardSpot> kingSpot = board.getKingSpotOfColour(fromSpotColour);


    if (kingSpot->getPiece().get() != fromPiece.get()) {
        Colour enemyColour = fromSpot->getPieceOppositeColour();
        make();
        if (board.isSpotAttackedBy(kingSpot->getRow(), kingSpot->getColumn(), enemyColour)) {
            revert();
            return false;
        }
        revert();
    }


    return true;
}



bool Move::arePiecesSameColour() {
    Colour firstSpotPieceColour = fromSpot->getPieceColour();
    Colour secondSpotPieceColour = toSpot->getPieceColour();
    if (firstSpotPieceColour == secondSpotPieceColour) {
        return true;
    }
    return false;
}

void Move::make() {
    std::shared_ptr<Piece> movingPiece = fromSpot->replacePiece(nullptr);
    std::shared_ptr<MoveSensitivePiece> moveSensitive = std::dynamic_pointer_cast<MoveSensitivePiece>(movingPiece);
    if (moveSensitive != nullptr) {
        moveSensitive->move();
    }
    this->takenPiece = toSpot->replacePiece(movingPiece);
}

void Move::revert() {
    std::shared_ptr<Piece> movedPiece = toSpot->replacePiece(this->takenPiece);
    std::shared_ptr<MoveSensitivePiece> moveSensitive = std::dynamic_pointer_cast<MoveSensitivePiece>(movedPiece);
    if (moveSensitive != nullptr) {
        moveSensitive->undoMove();
    }
    fromSpot->replacePiece(movedPiece);
}

bool Move::isCastling(const Board &board) {
    std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(fromSpot->getPiece());
    if (king != nullptr) {
        return king->canCastleTo(board,*fromSpot,*toSpot);
    }
    return false;
}

bool Move::isMovingPieceKing() {
    std::shared_ptr<King> possibleKing = std::dynamic_pointer_cast<King>(fromSpot->getPiece());
    return possibleKing != nullptr;
}
