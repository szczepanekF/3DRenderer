
#include "model/Board.h"
#include "model/Move.h"
#include "model/pieces/Rook.h"

Move::Move(const std::shared_ptr<BoardSpot> &fromSpot, const std::shared_ptr<BoardSpot> &toSpot) : fromSpot(fromSpot),
                                                                                                   toSpot(toSpot),
                                                                                                   castlingMove(false)
                                                                                                   {}

bool Move::isLegal(const Board &board) {
    if (isCastling(board)) {
        return true;
    }

    if (arePiecesSameColour()) {
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
    Colour enemyColour = fromSpot->getPieceOppositeColour();

    make();

    std::shared_ptr<BoardSpot> kingSpot = board.getKingSpotOfColour(fromSpotColour);
    if (board.isSpotAttackedBy(kingSpot->getRow(), kingSpot->getColumn(), enemyColour)) {
        revert();
        return false;
    }
    revert();

    return true;
}


bool Move::arePiecesSameColour() const {
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
    if (fromSpot->isOccupied()) return;

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
        castlingMove = king->canCastleTo(board, *fromSpot, *toSpot);
        return castlingMove;
    }

    return castlingMove;
}

void Move::performCastling(const Board &board) {
    std::shared_ptr<Piece> movingPiece = fromSpot->replacePiece(nullptr);
    std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(movingPiece);
    king->move();

    int diffY = toSpot->getColumn() - fromSpot->getColumn();
    int posDir = (diffY > 0) ? 1 : -1;
    std::shared_ptr<BoardSpot> newPosition = board.getSpot(fromSpot->getRow(),
                                                           fromSpot->getColumn() + posDir * 2);
    newPosition->replacePiece(king);

    int rookCol = (diffY > 0) ? 7 : 0;
    std::shared_ptr<BoardSpot> rookSpot = board.getSpot(fromSpot->getRow(),rookCol);
    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(rookSpot->replacePiece(nullptr));

    rookSpot = board.getSpot(fromSpot->getRow(), fromSpot->getColumn() + posDir * 1);
    rookSpot->replacePiece(rook);
}

void Move::unperformCastling(const Board &board) {
    if (fromSpot->isOccupied()) return;
    int diffY = toSpot->getColumn() - fromSpot->getColumn();
    int posDir = (diffY > 0) ? 1 : -1;

    std::shared_ptr<BoardSpot> kingCurrentSpot = board.getSpot(fromSpot->getRow(),
                                                               fromSpot->getColumn() + posDir * 2);
    std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(kingCurrentSpot->replacePiece(nullptr));
    fromSpot->replacePiece(king);

    std::shared_ptr<BoardSpot> rookSpot = board.getSpot(fromSpot->getRow(),
                                                               fromSpot->getColumn() + posDir * 1);

    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(rookSpot->replacePiece(nullptr));
    int rookCol = (diffY > 0) ? 7 : 0;
    rookSpot = board.getSpot(fromSpot->getRow(),rookCol);
    rookSpot->replacePiece(rook);
}

bool Move::makeIfIsLegal(const Board &board) {
    if (isLegal(board)) {
        if (castlingMove) {
            performCastling(board);
        } else {
            make();
        }
        return true;
    }
    return false;
}
